#ifndef _GAMEPLAYER_H_
#define _GAMEPLAYER_H_

#include "BaseSingle.h"
#include "CommonDefine.h"
#include "BaseSession.h"
#include "ObjPool.h"

class NetSocket;
struct NetMsgHead;
class ServerSession;

// ���״̬
enum EClientStatus
{
	ECLIENT_STATUS_INITED		 ,	// ��ʼ����� 
	ECLIENT_STATUS_CONNECTED	 ,  // �Ѿ�������������� 
	ECLIENT_STATUS_ENCRYPTED	 ,	// �����Կ�ɹ���� 
	ECLIENT_STATUS_NOTIFY_INITED ,  // ���Խ������ݲ�������
	ECLIENT_STATUS_LOGINED		 ,	// ��¼������ 
	ECLIENT_STATUS_SELECTED		 ,  // ѡ���ɫ��� 
	ECLIENT_STATUS_IN_WORLD		 ,	// ���Խ������ݽ������  
	ECLIENT_STATUS_IN_SCENE		 ,  // ����Ϸ������
};

/*
 *
 *	Detail: �����
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class ClientSession : public BaseSession
{
public:

	ClientSession(int32 nClientSessionID);

	virtual ~ClientSession();

	// fep��ʹ��
	void SetForFep0(NetSocket& rSocket,ServerSession* pWsSession); // �������� 
	void SetForFep1(ServerSession* pLsSession); // ͬ������ 
	void SetForFep2(ServerSession* pSsSession); // �����ͼ���� 

	// ls,ss��ʹ��
	void SetForLsSs(ServerSession* pWsSession,ServerSession* pFepSession,ServerSession* pDpSession); // ͬ������ 

	// dp��ʹ��
	void SetForDp1(ServerSession* pWsSession,ServerSession* pLsSession); // ͬ������ 
	void SetForDp2(ServerSession* pSsSession); // �����ͼ���� 

	// ws����˵
	void SetForWs1(ServerSession* pFepSession,ServerSession* pLsSession,ServerSession* pDpSession); // ͬ������ 
	void SetForWs2(ServerSession* pSsSession); // �����ͼ���� 

	/*
	 *
	 *	Detail: ���ID
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	int32 SessionID();

	/*
	 *
	 *	Detail: ������Ϣ��client
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void SendMsgToClient( NetMsgHead* pMsg,int32 nSize);

	void SendMsgToWs( NetMsgHead* pMsg,int32 nSize);

	void SendMsgToSs( NetMsgHead* pMsg,int32 nSize);

	void SendMsgToLs( NetMsgHead* pMsg,int32 nSize);

	void SendMsgToDp( NetMsgHead* pMsg,int32 nSize);

	void SendMsgToFep( NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: ����˳�
	 *   
	 *  Created by hzd 2015-1-21
	 *
	 */
	virtual void Exist();

	/*
	 *
	 *	Detail: ����״̬
	 *   
	 *  Created by hzd 2015-5-27
	 *
	 */
	virtual void SetStatus(int32 nStatus);

	/*
	 *
	 *	Detail: ���״̬
	 *   
	 *  Created by hzd 2015-5-27
	 *
	 */
	virtual int32 Status();

	/*
	 *
	 *	Detail: ��ʱѭ��������Ϊ��ʱ����
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void Update(int32 nSrvTime);

	/*
	 *
	 *	Detail: ����ͨ����Կ
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void SetEncryptKey(char arrNewKey[MAX_ENCRYPT_LENTH]);

	/*
	 *
	 *	Detail: ���ͨ����Կ
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void GetEncryptKey(char o_arrEncryptKey[MAX_ACCOUNT_LENG]);

	/*
	 *
	 *	Detail: ���÷���������
	 *   
	 *  Created by hzd 2015-5-28
	 *
	 */
	void SetOnServerType(int32 nServerType);

	/*
	 *
	 *	Detail: ��÷���������
	 *   
	 *  Created by hzd 2015-5-28
	 *
	 */
	int32 OnServerType();


protected:

	void SendMsg(NetSocket* pSocket,NetMsgHead* pMsg,int32 nSize);

private:

private:

	int32				m_nSessionID;						// ����fep��client������SocketID
	int32				mSendPackCount;						// ����������У���˳�򡢶��������
	char				m_arrEncryptKey[MAX_ENCRYPT_LENTH];	// ͨ����Կ

	NetSocket*			m_pSocket;	// Fep�и�clientר��
	ServerSession*		m_pWs;		// ���е�ws
	ServerSession*      m_pFep;		// ���ڵ�fep�����Ӻ�ɻ��
	ServerSession*		m_pLs;		// ���ڵ�ls,Ԥ������	
	ServerSession*		m_pDp;		// ���ڵ�dp,Ԥ������
	ServerSession*		m_pSs;		// ���ڵ�ss,��¼����
	
	int32				m_nOnServerType; // ����������������

};


/*
 *
 *	Detail: ��ҹ�����
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class ClientSessionMgr : public BaseSingle<ClientSessionMgr>
{
	typedef map< int32 , ClientSession* >	ClientSessionMapType; // keyΪssessionID(socketid��Ψһ�����session���Զ�Ӧһ��socket) 
public:

	ClientSessionMgr();
	~ClientSessionMgr();

	/*
	 *
	 *	Detail: ����һ��ClientSession
	 *   
	 *  Created by hzd 2015-5-27
	 *
	 */
	ClientSession* AddSession(int32 nClientSessionID);

	/*
	 *
	 *	Detail: �ͷ�Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void RemoveSession(int32 nFepSessionID);

	/*
	 *
	 *	Detail: ���Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	ClientSession*	GetSession(int32 nFepSessionID);
		  
	/*
	 *
	 *	Detail: �㲥��Ϣ
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void SendToAll( NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: ����
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void Update(uint32 nDelay);

	/*
	 *
	 *	Detail: no
	 *   
	 * Copyright (c) Created by hzd 2015-4-28.All rights reserved
	 *
	 */
	void SendMsgToLs(NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: no
	 *   
	 * Copyright (c) Created by hzd 2015-4-28.All rights reserved
	 *
	 */
	void SendMsgToWs(NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: no
	 *   
	 * Copyright (c) Created by hzd 2015-4-28.All rights reserved
	 *
	 */
	void SendMsgToSs(NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: ͳ��������ws�������
	 *   
	 *  Created by hzd 2015-5-29
	 *
	 */
	int32 ConnectedSessions();

private:

	ClientSessionMapType			m_mapClientSession;			// ������һ���(������δ����)					
	static ObjPool<ClientSession>	s_cClientSessionFactory;	// ClientSession����

};

#endif

