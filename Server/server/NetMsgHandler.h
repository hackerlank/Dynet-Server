#ifndef _NETMSGHANDLER_H_
#define _NETMSGHANDLER_H_

#include "../DyNetServer/NetSocket.h"

class Player;
struct NetMsgHead;

typedef void( *NetMsgHandlerf )( Player& player , NetMsgHead* pHead );


// Э�����Ӧ�ĵ��ú��� 
typedef struct 
{
    uint32			nType;	// Э��
    NetMsgHandlerf	pFun;	// ������
}   NetMsgHandler;

typedef	map< uint32 , NetMsgHandler > NetMsgHandlerMap;
typedef map< uint32 , NetMsgHandler >::iterator NetMsgHandlerMapIter;

/*
 *
 *	Detail: ��ʼ����Ϣ���Ӧ�ĺ���
 *   
 *  Created by hzd 2015/01/26  
 *
 */
void InitNetMsg();

/*
 *
 *	Detail: �����Ϣ��С�Ƿ���ȷ
 *   
 *  Created by hzd 2015/01/26  
 *
 */
bool CheckMsg(const NetMsgHead* pMsg , uint32 nSize );

// ������Ϣת����
#define	CHECKMSG( classType ) const classType* pMsg = (classType*)pHead; if ( !CheckMsg( pMsg , sizeof( classType ) ) ){ FLOG4("CheckMsg Error! %d",pMsg->nType); return ;}

/*
 *
 *	Detail: �пͻ������ӻص�
 *   
 *  Created by hzd 2015/01/26  
 *
 */
void OnNetMsgEnter( NetSocket& rSocket );

/*
 *
 *	Detail: �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����)
 *   
 *  Created by hzd 2015/01/26  
 *
 */
void OnNetMsgExit( NetSocket& rSocket );

/*
 *
 *	Detail: �пͻ�����Ϣ�յ�
 *   
 *  Created by hzd 2015/01/26  
 *
 */
void OnNetMsg( NetSocket& rSocket , NetMsgHead* pHead );
	 
void OnError( int32 nError , int32 nServiceID , NetSocket& rSocket , const byte* pBuffer );
	


#endif

