#include "Client_PCH.h"
#include "ClientCommand.h"
#include <sstream>
#include "ClientNetHandler.h"

#ifdef WIN32 

#include "conio.h"
#else

int _kbhit()
{
    struct timeval tv;
    fd_set rdfs;  
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO( &rdfs );
    FD_SET ( STDIN_FILENO , &rdfs );
    select( STDIN_FILENO + 1 , &rdfs , NULL , NULL , &tv );
    return FD_ISSET( STDIN_FILENO , &rdfs );
}

int _getch()
{
    return getchar();
}

#endif


VectorCommand GameCommand::s_sCommands;
NetSocket*    GameCommand::mCommandSocket;

GameCommand::GameCommand()
:	m_nCommandCount( 0 )
{
}

GameCommand::~GameCommand()
{
}

void GameCommand::Init(NetSocket& rSocket)
{
	mCommandSocket = &rSocket;

	//s_sCommands.push_back( KeyCommand("0","�Ͽ�����"		,	ClientNetHandler::SendRequestClose));
	//s_sCommands.push_back( KeyCommand("1","��ʾ��������"	,	CommandHelp ) );
	//s_sCommands.push_back( KeyCommand("2","�����Կ"		,   ClientNetHandler::SendEncrypt));
	//s_sCommands.push_back( KeyCommand("3","��¼Ĭ���ʺ�"	,	ClientNetHandler::SendLogin) );
	//s_sCommands.push_back( KeyCommand("4","����������Ϣ"	,	ClientNetHandler::SendChar2World) );

}

void GameCommand::Command( float32 nDelay )
{
	static float32 s_nTime = 0.0f;
	s_nTime += nDelay;

	if ( s_nTime < 0.2f )
		return;

	s_nTime = 0.0f;

	if( _kbhit() )
	{
		int32 nKey = _getch();
		switch( nKey )
		{
#ifdef WIN32
		case 13:			// Enter
#else
        case 10:			// Linux
#endif
			{
				if( m_nCommandCount == 0 )
					break;

				ParseCommand( m_arrBuffer );

				// reset command
				m_nCommandCount = 0;
				memset( m_arrBuffer , 0 , MAX_PATH1 );
				printf("\n");
			}
			break;
		case 8:				// BackSpace
			{
				if( m_nCommandCount > 0 )
				{
					printf( "\b \b" );
					m_arrBuffer[m_nCommandCount] = 0;
					m_nCommandCount--;
				}
			}
			break;
		case 27:			// ESC
			{
				// clear command
				m_nCommandCount = 0;
				memset( m_arrBuffer , 0 , MAX_PATH1 );
				printf( "...[Cancel]\nCommand: " );
			}
			break;
		default:
			{
				if( m_nCommandCount >= 255 )
				{
					break;
				}
				m_arrBuffer[ m_nCommandCount ] = (char)nKey;
				m_arrBuffer[ m_nCommandCount + 1 ] = '\0';
				m_nCommandCount++;
				printf( "%c", nKey );
			}
			break;
		}
	}
}

bool GameCommand::ParseCommand( char* command )
{
	VectorCommandIter iterEnd = s_sCommands.end();
	for ( VectorCommandIter iter = s_sCommands.begin() ; iter != iterEnd ; ++iter )
	{
		if ( strstr( command , iter->id.c_str() ) )
		{
			iter->callBack();
			return true;
		}
	}
	printf( "\nUnknown command.\n" );
	return false;
}

void		GameCommand::CommandHelp()
{
	printf("\n");
	VectorCommandIter iterEnd = s_sCommands.end();
	for ( VectorCommandIter iter = s_sCommands.begin() ; iter != iterEnd ; ++iter )
	{
		 FLOG_INFO( "%-8s  %-3s: %-20s" ,  "==========" , iter->id.c_str() ,iter->doc.c_str() );
	}
}

