#include "ForClientMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"

#include "Encrypt.h"
#include "LogManager.h"

#include "CommonC2S.h"
#include "CommonS2C.h"
#include "CommonC2F.h"
#include "CommonF2C.h"
#include "CommonC2W.h"

#include "ClientSession.h"
#include "ServerSession.h"

#include "CommonInternal.h"
#include "CommonServerOpt.h"

// ��fep�У�client��sessionIDΪsocketID

ForClientMsgHandler::ForClientMsgHandler()
{

	// fep
#define REGISTER_FEP_MESSAGE(msg_idx, cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls),boost::bind(&ForClientMsgHandler::handler, this, _1, _2,_3)); \
	}

	REGISTER_FEP_MESSAGE(PRO_C2F_ENCRYPT,C2FepEncryptInfo,ReqFepEncyptHandler);
	REGISTER_FEP_MESSAGE(PRO_C2F_CLOSE,C2FepClose,ReqFepCloseHandler);

#undef REGISTER_FEP_MESSAGE

	// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls)\
	{\
	RegisterMessage(msg_idx,sizeof(cls),boost::bind(&ForClientMsgHandler::ReqSendToLoginServer,this, _1, _2,_3));\
	}
	

#undef REGISTER_LS_MESSAGE

	// ws
#define REGISTER_WS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForClientMsgHandler::ReqSendToWorldServer, this, _1, _2,_3)); \
	}

	REGISTER_WS_MESSAGE(PRO_C2W_SWITCH_SCENE,C2WSwitchScene); // �л��³��� 

#undef REGISTER_WS_MESSAGE

	// ss
#define REGISTER_SS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForClientMsgHandler::ReqSendToSceneServer, this, _1, _2,_3)); \
	}

#undef REGISTER_SS_MESSAGE

}


ForClientMsgHandler::~ForClientMsgHandler()
{
}

void ForClientMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	if(ClientSession* pSession = ClientSessionMgr::Instance()->AddSession(rSocket.SID()))
	{
		ServerInfoOpt& rRemoteInfo = NetServerOpt::Instance()->GetRemoteServerInfo();
		ServerSession* pWsServerSession = ServerSessionMgr::Instance()->GetSession(rRemoteInfo.nID);
		if(pWsServerSession == NULL)
		{
			// ws��δ�����ϻ�Ͽ���
			pSession->Exist();
			return ;
		}
		pSession->SetForFep0(rSocket,pWsServerSession);
		pSession->SetStatus(ECLIENT_STATUS_CONNECTED);
		FLOG_INFO("OnNetMsgEnter SID: %d", rSocket.SID());
	}else
	{
		FLOG_INFO("Create clientsession fail!");
	}
}


void ForClientMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	if(ClientSession* pSession = ClientSessionMgr::Instance()->GetSession(rSocket.SID()))
	{
		// ���ܴ���
		static char msgBuffer[65536];
		memcpy(&msgBuffer[0], pMsg,nSize);
		static char arrEncrypt[MAX_ENCRYPT_LENTH];
		pSession->GetEncryptKey(arrEncrypt);
		Encrypt::XorCode(nSize, arrEncrypt, msgBuffer, nSize);
		pMsg = (NetMsgHead*)&msgBuffer[0];

		const MsgHandlerInfo* pMsgHandlerInfo = GetMsgHandler(pMsg->nType);
		if(pMsgHandlerInfo == NULL)
		{
			FLOG_INFO("Not Find Protocol:%d", pMsg->nType);
			rSocket.SetWillColse();
			return;
		}
		else
		{
			FLOG_INFO("OnNetMsg Protocol: %d", pMsg->nType);
			(pMsgHandlerInfo->rHandler)((BaseSession*)pSession, pMsg,nSize);
		}
	}else
	{
		FLOG_INFO("Cannot found clientsession:%d",rSocket.SID());
		rSocket.SetWillColse();
	}
	//---------------------------------���������end-------------------------------
}

void ForClientMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	//---------------------------------���������begin-------------------------------
	// �����������Ͽ��򱻿ͻ��Ͽ������Ǵ��������ȿ�ʼ����
	// socket��ʱ�����ٸ�Client������,socket�����Ѿ�ʧЧ
	int32 nClientSessionID = rSocket.SID();
	FLOG_INFO("OnNetMsgExit nClientSession: %d", nClientSessionID);
	
	// ֪ͨWs,Ws��֪ͨls,ss,ss֪ͨdp�������dp�յ�ss����Ϣ���������ݽ����Ƴ�client
	ClientSession* pClientSession = ClientSessionMgr::Instance()->GetSession(nClientSessionID);
	ASSERT(pClientSession);

	// �����ͻ����˳���Ϣ
	SSNofityClientExit sMsgExit;
	sMsgExit.nClientSessionID = nClientSessionID;
	pClientSession->SendMsgToWs(&sMsgExit, sMsgExit.GetPackLength());

	ClientSessionMgr::Instance()->RemoveSession(nClientSessionID);
	//---------------------------------���������end-------------------------------
}

// ���͵�ls
void ForClientMsgHandler::ReqSendToLoginServer(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	MSG_CLIENT_TO_LS(pSession, pMsg, nSize);
	//---------------------------------���������end-------------------------------
}

// ���͵�ss
void ForClientMsgHandler::ReqSendToSceneServer(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	MSG_CLIENT_TO_SS(pSession,pMsg,nSize);
	//---------------------------------���������end-------------------------------
}

// ���͵�ws
void ForClientMsgHandler::ReqSendToWorldServer(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	MSG_CLIENT_TO_WS(pSession,pMsg,nSize);
	//---------------------------------���������end-------------------------------
}

void ForClientMsgHandler::ReqFepEncyptHandler(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	ClientSession* pClientSession = static_cast<ClientSession*>(pSession);
	if(pClientSession->Status() == ECLIENT_STATUS_CONNECTED )
	{
		char arrRandKey[MAX_ENCRYPT_LENTH];
		Encrypt::RandKey(arrRandKey);
		
		F2CEncryptInfo sMsgEncrypt;
		memcpy(sMsgEncrypt.arrEncryptKey, arrRandKey, MAX_ENCRYPT_LENTH);
		pClientSession->SendMsgToClient(&sMsgEncrypt,sMsgEncrypt.GetPackLength());

		// Ҫ�ȷ����ݺ���ܸ�
		pClientSession->SetEncryptKey(arrRandKey);
		pClientSession->SetStatus(ECLIENT_STATUS_ENCRYPTED);

		// ������������ID
		SSReqLoadLest sMsgLoadLest;
		sMsgLoadLest.nClientSessionID = pClientSession->SessionID();
		pClientSession->SendMsgToWs(&sMsgLoadLest,sMsgLoadLest.GetPackLength());

	}else
	{
		FLOG_INFO("ClientSession Status Not Eq EPLAYER_STATUS_CONNECTED");
	}
	//---------------------------------���������end-------------------------------
}

void ForClientMsgHandler::ReqFepCloseHandler(BaseSession* pSession,const NetMsgHead* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	ClientSession* pClientSession = static_cast<ClientSession*>(pSession);
	pClientSession->Exist();
	//---------------------------------���������begin-------------------------------
}
