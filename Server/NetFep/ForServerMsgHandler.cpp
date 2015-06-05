#include "ForServerMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"
#include "../DyNetSocket/NetClient.h"

#include "LogManager.h"
#include "BaseDefine.h"
#include "CommonServerOpt.h"
#include "ServerSession.h"
#include "CommonInternal.h"


ForServerMsgHandler::ForServerMsgHandler()
{

	// �ڲ�Э��
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForServerMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_LOGIN_S, SSReqLoginS, ReqLogined);	// �����¼

#undef REGISTER_INTERNAL_MESSAGE



}


ForServerMsgHandler::~ForServerMsgHandler()
{
}

// �пͻ������ӻص�
void ForServerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	//---------------------------------���������begin-------------------------------
	FOR_S_S_ON_MSG_ENTER(rSocket,ESERVER_TYPE_FEP);
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
	FOR_S_S_ON_MSG_EXIT(rSocket);
	//---------------------------------���������end-------------------------------
}

void ForServerMsgHandler::ReqLogined(BaseSession* pSession,const NetMsgHead* pHead,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	FOR_S_S_REQLOGIN(pSession,pHead);
	//---------------------------------���������end-------------------------------
}
