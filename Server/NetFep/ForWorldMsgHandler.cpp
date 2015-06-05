#include "ForWorldMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"
#include "../DyNetSocket/NetClient.h"
#include "CommonW2F.h"
#include "CommonF2W.h"
#include "CommonF2C.h"

#include "LogManager.h"
#include "BaseDefine.h"
#include "ProcWorldHandler.h"
#include "CommonServerOpt.h"
#include "CommonInternal.h"
#include "ServerSession.h"
#include "ClientSession.h"


ForWorldMsgHandler::ForWorldMsgHandler()
{

#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForWorldMsgHandler::handler, this , _1, _2, _3)); \
	}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REP_LOGINED,SSRepLogined,RepLogined);	// ��¼��� 
	REGISTER_INTERNAL_MESSAGE(PRO_SS_NOFTTY_SERVERID,SSSessionNofitySInfo,NofityClientSessionInfo); // ͬ�����������ID 

#undef REGISTER_INTERNAL_MESSAGE


#define REGISTER_WS2FEP_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcWorldHandler::handler, ProcWorldHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_WS2FEP_MESSAGE

}


ForWorldMsgHandler::~ForWorldMsgHandler()
{
}

// �пͻ������ӻص�
void ForWorldMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	FOR_WS_ON_MSG_ENTER(rSocket,ESERVER_TYPE_FEP);
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
	ServerSession* pLsServerSession = ServerSessionMgr::Instance()->GetSession(pPacket->nLsServerID);
	ASSERT(pLsServerSession);
	ClientSession* pClientSession = ClientSessionMgr::Instance()->GetSession(pPacket->nClientSessionID);
	ASSERT(pClientSession);
	pClientSession->SetForFep1(pLsServerSession);
	pClientSession->SetStatus(ECLIENT_STATUS_NOTIFY_INITED);

	// ֪ͨClient��Session׼����Ͽ��Խ��е�¼������
	F2CLoginReadyFinish sMsg;
	pClientSession->SendMsgToClient(&sMsg,sMsg.GetPackLength());

}