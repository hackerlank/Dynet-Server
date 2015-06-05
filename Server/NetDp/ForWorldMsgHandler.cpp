#include "ForWorldMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"
#include "../DyNetSocket/NetClient.h"
#include "CommonW2D.h"
#include "CommonD2W.h"
#include "CommonInternal.h"

#include "LogManager.h"

#include "ProcWorldHandler.h"
#include "CommonServerOpt.h"
#include "ServerSession.h"
#include "ClientSession.h"


ForWorldMsgHandler::ForWorldMsgHandler()
{

#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForWorldMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REP_LOGINED,SSRepLogined,RepLogined);	// ��¼��� 
	REGISTER_INTERNAL_MESSAGE(PRO_SS_NOFTTY_SERVERID,SSSessionNofitySInfo,NofityClientSessionInfo); // ͬ�����������ID 
	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_CLIENT_EXIT,SSNofityClientExit,NofityClientExit);

#undef REGISTER_INTERNAL_MESSAGE

}


ForWorldMsgHandler::~ForWorldMsgHandler()
{
}

// �пͻ������ӻص�
void ForWorldMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	FOR_WS_ON_MSG_ENTER(rSocket,ESERVER_TYPE_DP);
}

// �пͻ�����Ϣ�յ�
void ForWorldMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgHead* pHead,int32 nSize)
{
	FOR_WS_ON_MSG(rSocket,pHead);
}

// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
void ForWorldMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	 FOR_WS_ON_MSG_EXIT(rSocket);
}


void ForWorldMsgHandler::RepLogined(BaseSession* pBaseSession, const NetMsgHead* pMsg,int32 nSize)
{
	FOR_WS_REP_LOGINED(pBaseSession,pMsg);
}

void ForWorldMsgHandler::NofityClientSessionInfo(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	const SSSessionNofitySInfo* pPacket = static_cast<const SSSessionNofitySInfo*>(pMsg);
	int32 nLsServerID = pPacket->nLsServerID;
	ServerSession* pLsServerSession = ServerSessionMgr::Instance()->GetSession(pPacket->nLsServerID);
	ASSERT(pLsServerSession);
	ClientSession* pClientSession = ClientSessionMgr::Instance()->AddSession(pPacket->nClientSessionID);
	ASSERT(pClientSession);
	pClientSession->SetForDp1((ServerSession*)pSession,pLsServerSession);
	pClientSession->SetStatus(ECLIENT_STATUS_NOTIFY_INITED);
}

void ForWorldMsgHandler::NofityClientExit(BaseSession* pSession, const NetMsgHead* pMsg, int32 nSize)
{
	const SSNofityClientExit* pPacket = static_cast<const SSNofityClientExit*>(pMsg);
	int32 nClientSessionID = pPacket->nClientSessionID;

	ClientSession* pClientSession = ClientSessionMgr::Instance()->GetSession(nClientSessionID);
	ASSERT(pClientSession);

	// �������ݵ����ݿ�

	// ɾ��
	ClientSessionMgr::Instance()->RemoveSession(nClientSessionID);

}


