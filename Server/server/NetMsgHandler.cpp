#include "Server_PCH.h"
#include "NetMsgHandler.h"
#include "NetChatHandler.h"
#include "NetLoginHandler.h"

#include "DBLoginHandler.h"
#include "Player.h"
#include "GlobalVar.h"

using namespace SWA;

static NetMsgHandlerMap	 gMsgHeandlerMap;

bool CheckMsg(const NetMsgHead* pMsg , uint32 nSize )
{
	if ( pMsg->nSize == nSize )
		return true;
	else
		return false;
}


void InitNetMsg()
{

	FLOG_INFO("PROTOCOL INIT...");

	static NetMsgHandler s_arrHandler[] =
	{
		
		// Э��=>������

		{PRO_C2FEP_CLOSE,NetRequestClose},

		// ��¼��Э��
		{ PRO_C2FEP_ENCRYPT		,	NetLoginEncryptInfoHandler		},// �����Կ
		{ PRO_C2LS_LOGIN_ACCOUNT	,	NetLoginAccountHandler		},	//��¼ 
		{ PRO_C2WS_LOGIN_ROLE_LIST ,	NetLoginCharacterListHandler			},	// �����б�
		{ PRO_C2WS_CREATE_ROLE		,	NetLoginCreateCharacterHandler		},	// ������ɫ
		{ PRO_C2WS_SELECT_CHARACTER		,	NetLoginSelectCharacterHandler		},	// ѡ���ɫ
		{ PRO_C2FEP_ENCRYPT			,	NetLoginEncryptInfoHandler		},

		{PRO_C2SS_CLIENT_HAD_READY,		NetLoginResourcesLoaded 		},  // ��Դ�������

		// ��ɫ��Э��

		{ PRO_C2SS_CHAT_TO_WORLD,      NetChatWorldMsgHandler		},
			// end
		{ PRO_C2S_NULL			  ,		NULL			}, // no

	};

	int32 nIndex = 0;
	while ( s_arrHandler[nIndex].nType )
	{
		gMsgHeandlerMap[ s_arrHandler[ nIndex ].nType ] = s_arrHandler[ nIndex ];
		nIndex++;
	}
}


void OnNetMsgEnter( NetSocket& rSocket )
{
	Player& rPlayer = g_rPlayerMgr.GetPlayer( rSocket );
	rPlayer.SetStatus(ECLIENT_STATUS_CONNECTED);

	// ��־״̬ todo

	FLOG_INFO( "player load %s" , rSocket.GetIp().c_str() );

}


void OnNetMsg( NetSocket& rSocket , NetMsgHead* pHead )
{
	Player& rPlayer = g_rPlayerMgr.GetPlayer(rSocket );

	// ���ܴ���
	static char msgBuffer[MAX_SOCKET_BUFFER];
	memcpy(&msgBuffer[0], pHead, pHead->nSize);
	static char msgEncrypt[MAX_ENCRYPT_LENTH];
	rPlayer.GetEncryptKey(msgEncrypt);
	Encrypt::XorCode(pHead->nSize,msgEncrypt,&msgBuffer[sizeof(pHead->nSize)],pHead->nSize);
	pHead = ( NetMsgHead*)&msgBuffer[0];
	NetMsgHandlerMapIter iter = gMsgHeandlerMap.find( pHead->nType );
	if ( iter == gMsgHeandlerMap.end() )
	{
		FLOG_INFO("Not find protocol:%d",pHead->nType);
		rSocket.Disconnect();
		return;
	}
	else
	{
		(iter->second.pFun)( rPlayer , pHead );
		FLOG_INFO("OnNetMsg %d", pHead->nType);
	}
}

void OnNetMsgExit( NetSocket& rSocket )
{
	Player& rPlayer = g_rPlayerMgr.GetPlayer( rSocket );
	rPlayer.SetStatus(ECLIENT_STATUS_INITED);
}


