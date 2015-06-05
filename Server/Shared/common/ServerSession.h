#ifndef _SEVER_SESSION_H_
#define _SEVER_SESSION_H_

#include "BaseSingle.h"
#include "CommonDefine.h"
#include "BaseSession.h"
#include "ObjPool.h"

class NetSocket;
class NetServer;
struct NetMsgHead;

enum EServerStatus
{
	ESERVER_STATUS_INIT = 0,
	ESERVER_STATUS_CONNETED,
	ESERVER_STATUS_LOGINED,
	ESERVER_STATUS_OK,
};


/*
 *
 *	Detail: �������������֮���session
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class ServerSession : public BaseSession
{
public:

	ServerSession(NetSocket* pNetSocket);
	virtual ~ServerSession();

	/*
	 *
	 *	Detail: ΨһID
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	int32 ServerID();

	/*
	 *
	 *	Detail: ������Ϣ
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	virtual void SendMsg( NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: �˳�
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
	 *	Detail: ��÷���������
	 *   
	 * Copyright (c) Created by hzd 2015-4-29.All rights reserved
	 *
	 */
	EServerType ServerTypeRemote();

	/*
	 *
	 *	Detail: ���÷���������
	 *   
	 * Copyright (c) Created by hzd 2015-4-29.All rights reserved
	 *
	 */
	void SetRemoteServerType(EServerType eServerType);

	/*
	 *
	 *	Detail: ����session����
	 *   
	 *  Created by hzd 2015-5-25
	 *
	 */
	EServerType ServerTypeLocal();
	
	/*
	 *
	 *	Detail: ���ñ���session����
	 *   
	 *  Created by hzd 2015-5-25
	 *
	 */
	void SetLocalServerType(EServerType eServerType);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015-5-20
	 *
	 */
	void SetServerID(int32 nServerID);

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
	 *	Detail: ������Ϣ��Dp
	 *   
	 *  Created by hzd 2015-5-21
	 *
	 */
	void SendMsgToDp(NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: ������Ϣ��Fep
	 *   
	 *  Created by hzd 2015-5-21
	 *
	 */
	void SendMsgToFep(NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: ������Ϣ��Client
	 *   
	 *  Created by hzd 2015-5-21
	 *
	 */
	void SendMsgToClient(NetMsgHead* pMsg,int32 nSize);

	/*
	 *
	 *	Detail: ��¼��WS
	 *   
	 *  Created by hzd 2015-5-22
	 *
	 */
	void LoginToWs();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015-5-22
	 *
	 */
	void LoginResult(bool bIsSuccess);

	/*
	 *
	 *	Detail: ��¼��ĳ������
	 *   
	 *  Created by hzd 2015-5-22
	 *
	 */
	void LoginToS();

	/*
	 *
	 *	Detail: ���NetSocket
	 *   
	 * Copyright (c) Created by hzd 2015-5-27.All rights reserved
	 *
	 */
	NetSocket* GetNetSocket();

protected:

private:

private:

	int32				m_nServerID;				// �����ķ�����ID
	int32				m_nSendPackCount;			// ����������У���˳�򡢶��������
	NetSocket*			m_pSocket;					// ��socket��
	EServerType			m_eRemoteServerType;		// Զ�̷���������
	EServerType			m_eLocalServerType;			// ���ط���������

};


/*
 *
 *	Detail: ss������
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class ServerSessionMgr : public BaseSingle<ServerSessionMgr>
{
	typedef map<int32,ServerSession*>	SocketIDSessionMapType;	// ����������Socket��ʱ��¼() 
	typedef map<int32,ServerSession*>	ServerIdSessionMapType;	// �Ѿ���¼������ServerSession 
public:

	ServerSessionMgr();
	~ServerSessionMgr();

	/*
	 *
	 *	Detail: ����һ��ServerSession
	 *   
	 * Copyright (c) Created by hzd 2015-5-27.All rights reserved
	 *
	 */
	ServerSession* CreateSession(int32 nSessionID,NetSocket& rSocket);

	/*
	 *
	 *	Detail: ��ʼ��ServerSession
	 *   
	 *  Created by hzd 2015-5-27
	 *
	 */
	bool InitSession(int32 nServerID,ServerSession* pSession);

	/*
	 *
	 *	Detail: �ͷ�Session(��ѡһ)
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void RemoveSession(uint32 nServerID);

	/*
	 *
	 *	Detail: �ͷ�Session(��ѡһ)
	 *   
	 *  Created by hzd 2015-5-27
	 *
	 */
	void RemoveSession(NetSocket& rSokcet);

	/*
	 *
	 *	Detail: ���Session
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	ServerSession*	GetSession(uint32 nServerID);

	/*
	 *
	 *	Detail: �ú���Ҫ�������ǲ���ͬһ��socket��ȡ���� 
	 *   
	 *  Created by hzd 2015-5-25
	 *
	 */
	ServerSession* GetSession(NetSocket& rSokcet);
		  
	/*
	 *
	 *	Detail: �㲥��Ϣ
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void SendToAll(NetMsgHead* pMsg,int32 nSize);

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
	 *	Detail: ͳ�Ʊ�������������
	 *   
	 *  Created by hzd 2015-5-22
	 *
	 */
	int32 CountConnected();

private:

	SocketIDSessionMapType				m_mapSocketIDSession;		// ��¼������������Socket
	ServerIdSessionMapType				m_mapServerIdSession;		// ��¼�Ѿ���¼ServerSession��serverID��Session
	static ObjPool<ServerSession>		s_cServerSessionFactory;	// ServerSession���� 

};

#endif

