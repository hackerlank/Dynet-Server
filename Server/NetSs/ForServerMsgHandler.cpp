#include "ForServerMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"
#include "../DyNetSocket/NetClient.h"
#include "CommonW2F.h"
#include "CommonF2W.h"
#include "ServerConnectMgr.h"
#include "ServerSession.h"
#include "ServerInfoMgr.h"

#include "LogManager.h"
#include "CommonInternal.h"


ForServerMsgHandler::ForServerMsgHandler()
{

#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForServerMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REP_LOGINED,SSRepLogined,RepLogined);	// ��¼��� 

#undef REGISTER_INTERNAL_MESSAGE

}


ForServerMsgHandler::~ForServerMsgHandler()
{
}

// �пͻ������ӻص�
void ForServerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	//---------------------------------���������begin-------------------------------
	FOR_S_C_ON_MSG_ENTER(rSocket,ESERVER_TYPE_SS);
	//---------------------------------���������end-------------------------------
}

// �пͻ�����Ϣ�յ�
void ForServerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	FOR_S_ON_MSG(rSocket,pMsg);
	//---------------------------------���������end-------------------------------
}

// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
void ForServerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	//---------------------------------���������begin-------------------------------
	FOR_S_C_ON_MSG_EXIT(rSocket);
	//---------------------------------���������end-------------------------------
}



void ForServerMsgHandler::RepLogined(BaseSession* pBaseSession, const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	if(pBaseSession->Status() != ESERVER_STATUS_CONNETED)
	{
		FLOG_INFO("pBaseSession->Status() != EWORLD_STATUS_CONNECTED");
		return;
	}
	const SSRepLogined* pPacket = static_cast<const SSRepLogined*>(pMsg);
	if(pPacket->nResult == SSRepLogined::SUCCESS)
	{
		pBaseSession->SetStatus(ESERVER_STATUS_LOGINED);
	}
	else
	{
		//��¼ʧ�ܣ������ٽ��еڶ��μ������ε�¼���Կ�
		return;
	}
	//---------------------------------���������end-------------------------------

}
