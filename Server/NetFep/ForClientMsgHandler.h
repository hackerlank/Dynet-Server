#ifndef CLIENT_MSG_HANDLER_H_
#define CLIENT_MSG_HANDLER_H_

#include "BaseDefine.h"
#include "BaseSingle.h"

#include "BaseMsgHandler.h"


/*
 *
 *	Detail: ���մ���ͻ��ˣ��û�������
 *   
 * Copyright (c) Created by hzd 2015-4-27.All rights reserved
 *
 */

class ClientSession;
class NetSocket;
struct NetMsgHead;
class ForClientMsgHandler : public BaseMsgHandler, public BaseSingle<ForClientMsgHandler>
{
public:
	ForClientMsgHandler();
	~ForClientMsgHandler();

	// �пͻ������ӻص�
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ�
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgHead* pHead,int32 nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// ���͵�ls
	void ReqSendToLoginServer(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize);

	// ���͵�ss
	void ReqSendToSceneServer(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize);

	// ���͵�ws
	void ReqSendToWorldServer(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize);

	
	//-----------------------------���ش���Э��---------------------------------
	// fep
	void ReqFepEncyptHandler(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize);
	void ReqFepCloseHandler(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize);
	// Ԥ����Ϣ(���ڴ���fep��clientsession��÷���ls,ls��clientsession���dp)

private:
	

};

#define MSG_CLIENT_COMMON_CLIENTSESSIONID(_nClientSessinID,pMsg,nSize) static vector<char> vecMsgBuffer;\
{\
	vecMsgBuffer.resize(nSize); \
	memcpy(&vecMsgBuffer[0], pMsg, nSize); \
	reinterpret_cast<NetMsgHead*>(&vecMsgBuffer[0])->nClientSessionID = _nClientSessinID; \
}\

#define MSG_CLIENT_TO_WS(pSession,pMsg,nSize) ClientSession* pClientSession = static_cast<ClientSession*>(pSession); \
	MSG_CLIENT_COMMON_CLIENTSESSIONID(pClientSession->SessionID(),pMsg,nSize) ;\
	pClientSession->SendMsgToWs((NetMsgHead*)(&vecMsgBuffer[0]), vecMsgBuffer.size());

#define MSG_CLIENT_TO_SS(pSession,pMsg,nSize) ClientSession* pClientSession = static_cast<ClientSession*>(pSession); \
	MSG_CLIENT_COMMON_CLIENTSESSIONID(pClientSession->SessionID(),pMsg,nSize);\
	pClientSession->SendMsgToSs((NetMsgHead*)(&vecMsgBuffer[0]), vecMsgBuffer.size());

#define MSG_CLIENT_TO_LS(pSession,pMsg,nSize) ClientSession* pClientSession = static_cast<ClientSession*>(pSession); \
	MSG_CLIENT_COMMON_CLIENTSESSIONID(pClientSession->SessionID(),pMsg,nSize); \
	pClientSession->SendMsgToLs((NetMsgHead*)(&vecMsgBuffer[0]), vecMsgBuffer.size());


#endif



