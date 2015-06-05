#include "ForServerMsgHandler.h"

#include "LogManager.h"
#include "ServerInfoMgr.h"
#include "ClientSession.h"
#include "ServerSession.h"

#include "BaseProcHandler.h"
#include "ClientProcHandler.h"
#include "DpServerProcHandler.h"
#include "FepServerProcHandler.h"
#include "SceneServerProcHandler.h"
#include "LoginServerProcHandler.h"

#include "CommonF2W.h"
#include "CommonL2W.h"
#include "CommonD2W.h"
#include "CommonC2W.h"
#include "CommonInternal.h"

ForServerMsgHandler::ForServerMsgHandler()
{
	// common ��Ҫ�õ��ڲ�Э��
	// �ڲ�Э�飬�����ֲ�ͬservertype����ȥ��ͳһ�����飬���¼�������б�ping�ȵȲ��� 
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForServerMsgHandler::handler, this, _1, _2, _3)); \
	}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_LOGIN_WS,SSReqLoginWs,ReqLogin);
	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_LOAD_LEST,SSReqLoadLest,ReqRoadLest);
	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_CLIENT_EXIT,SSNofityClientExit,NofityClientExit);

#undef REGISTER_INTERNAL_MESSAGE

	// dp
#define REGISTER_DP_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&DpServerProcHandler::handler, DpServerProcHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_DP_MESSAGE

	// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&LoginServerProcHandler::handler, LoginServerProcHandler::Instance(), _1, _2, _3)); \
	}
	
#undef REGISTER_LS_MESSAGE

// fep
#define REGISTER_FEP_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&FepServerProcHandler::handler, FepServerProcHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_FEP_MESSAGE

	// ss
#define REGISTER_SS_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&SceneServerProcHandler::handler, SceneServerProcHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_SS_MESSAGE

	// client
#define REGISTER_CLIENT_MESSAGE(msg_idx,cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ClientProcHandler::handler, ClientProcHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_CLIENT_MESSAGE(PRO_C2W_SWITCH_SCENE,C2WSwitchScene,ReqSwitchScene); // �л����� 

#undef REGISTER_CLIENT_MESSAGE


}


ForServerMsgHandler::~ForServerMsgHandler()
{ 
}

// �пͻ������ӻص�
void ForServerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	FOR_S_S_ON_MSG_ENTER(rSocket,ESERVER_TYPE_WS);
}

// �пͻ�����Ϣ�յ�
void ForServerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgHead* pMsg,int32 nSize)
{
	FOR_S_ON_MSG(rSocket,pMsg);
}

// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
void ForServerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{     
	//---------------------------------���������begin-------------------------------
	ServerSession* pSession = ServerSessionMgr::Instance()->GetSession(rSocket);
	int32 nServerID = pSession->ServerID();
	FOR_S_S_ON_MSG_EXIT(rSocket);
	ServerInfoMgr::Instance()->OnServerExit(nServerID);
	//---------------------------------���������end-------------------------------
}

void ForServerMsgHandler::ReqLogin(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	ServerSession* pServerSession = static_cast<ServerSession*>(pSession);
	if(pServerSession->Status() != ESERVER_STATUS_CONNETED)
		return;

	const SSReqLoginWs* pPacket = static_cast<const SSReqLoginWs*>(pMsg);

	int32 nServerID = pPacket->nServerID;
	int32 nServerType = pPacket->nServerType;

	// ״̬
	pServerSession->SetServerID(nServerID);
	pServerSession->SetRemoteServerType((EServerType)nServerType);
	pServerSession->SetStatus(ECLIENT_STATUS_LOGINED);

	// ��¼�µ��������server
	bool bResult = ServerInfoMgr::Instance()->OnServerLogin(pServerSession,pPacket->arrServerAddr,pPacket->nServerPort,nServerID,nServerType);
	if(!bResult)
	{
		FLOG_INFO("OnServerLogin fail serverid:%d",nServerID);
	}

	// ��¼serverID���Ӧ��session
	bResult = ServerSessionMgr::Instance()->InitSession(nServerID,pServerSession);
	if(!bResult)
	{
		FLOG_INFO("InitSession fail serverid:%d",nServerID);
	}

	// ���ص�¼�ɹ�
	pServerSession->LoginResult(bResult);

	// fep��dp�ķ�������Ϣ��Ҫ�㲥��ls��ss
	if(bResult)
	{
		ServerInfoMgr::Instance()->BoardcastDpAndFepServerInfo2LsAndSs(pPacket->nServerID);
	}
	//---------------------------------���������end-------------------------------

}

void ForServerMsgHandler::ReqRoadLest(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	const SSReqLoadLest* pPacket = static_cast<const SSReqLoadLest*>(pMsg);
	int32 nClientSessionID = pPacket->nClientSessionID;
	ServerSession* pFepSession = static_cast<ServerSession*>(pSession);

	// �ҳ�������С��(����һ�η���ģ��Ժ����Ż�)
	ServerInfoMgr* pServerInfoMgr = ServerInfoMgr::Instance();
	ServerSession* pLsSession = pServerInfoMgr->GetLoadLestSession(ESERVER_TYPE_LS);
	ServerSession* pDpSession = pServerInfoMgr->GetLoadLestSession(ESERVER_TYPE_DP);
	ASSERT(pLsSession && pDpSession);

	// ��һ�δ���ClientSesson����
	ClientSession* pClientSession = ClientSessionMgr::Instance()->AddSession(nClientSessionID);
	ASSERT(pClientSession);
	pClientSession->SetForWs1(pFepSession,pLsSession,pDpSession);

	// ͬ����ls,dp,fep
	SSSessionNofitySInfo sNofityInfo;
	sNofityInfo.nClientSessionID = nClientSessionID;
	sNofityInfo.nLsServerID = pLsSession->ServerID();
	sNofityInfo.nDpServerID = pDpSession->ServerID();
	sNofityInfo.nFepServerID = pFepSession->ServerID();

	// ֪ͨ�����Client��ServerID
	pClientSession->SendMsgToLs(&sNofityInfo,sNofityInfo.GetPackLength());
	pClientSession->SendMsgToDp(&sNofityInfo,sNofityInfo.GetPackLength());
	pClientSession->SendMsgToFep(&sNofityInfo,sNofityInfo.GetPackLength());

	// ����+1
	pServerInfoMgr->OnLoadAddOne(pLsSession->ServerID());
	pServerInfoMgr->OnLoadAddOne(pDpSession->ServerID());
	pServerInfoMgr->OnLoadAddOne(pFepSession->ServerID());
	//---------------------------------���������end-------------------------------

}

void ForServerMsgHandler::NofityClientExit(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	const SSNofityClientExit* pPacket = static_cast<const SSNofityClientExit*>(pMsg);
	int32 nClientSessionID = pPacket->nClientSessionID;

	ClientSession* pClientSession = ClientSessionMgr::Instance()->GetSession(nClientSessionID);
	ASSERT(pClientSession);

	// ͬ���򱣴���Ҫ���ݵ�dp

	// ֪ͨls,ss
	SSNofityClientExit sMsgExit;
	sMsgExit.nClientSessionID = nClientSessionID;

	pClientSession->SendMsgToLs(&sMsgExit,sMsgExit.GetPackLength());
	if(pClientSession->Status() == ECLIENT_STATUS_IN_SCENE)
	{
		pClientSession->SendMsgToSs(&sMsgExit,sMsgExit.GetPackLength());
	}else
	{
		// ��dpȥ�����˳�����
		pClientSession->SendMsgToDp(&sMsgExit,sMsgExit.GetPackLength());
	}

	// ɾ��
	ClientSessionMgr::Instance()->RemoveSession(nClientSessionID);

}



