 #include "FepServerProcHandler.h"
#include "BaseSession.h"
#include "../DyNetSocket/NetConfig.h"
#include "LogManager.h"
#include "ServerSession.h"
#include "CommonF2W.h"
#include "CommonW2F.h"
#include "ServerInfoMgr.h"

FepServerProcHandler::FepServerProcHandler()
{
}


FepServerProcHandler::~FepServerProcHandler()
{
}

void FepServerProcHandler::ReqLogin(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{

	//const Fep2WsLogin* pPacket = static_cast<const Fep2WsLogin*>(pMsg);
	//const LoginData2Ws& sLoginData = pPacket->sLoginData;
	//if(!CheckLogin(*pSession,sLoginData,ESERVER_TYPE_FEP))
	//{
	//	FLOG_ERROR("CheckLogin Fail!");
	//	return;
	//}

	//ServerSession* pClient = static_cast<ServerSession*>(pSession);

	//// ״̬
	//pClient->SetStatus(EPLAYER_STATUS_LOGINED);
	//pClient->SetServerType(ESERVER_TYPE_FEP);
	//pClient->SetServerID(sLoginData.nServerID);

	//// ���ص�¼�ɹ�
	//W2FepLogined sMsg;
	//sMsg.nResult = W2FepLogined::SUCCESS;
	//pClient->SendMsg(&sMsg, sMsg.GetPackLength());

	//// ��¼�µ��������server
	//bool bResult = ServerInfoMgr::Instance()->OnServerLogin(pSession,sLoginData.arrServerAddr,sLoginData.nServerPort,sLoginData.nServerID,ESERVER_TYPE_FEP);
	//if(!bResult)
	//{
	//	FLOG_ERROR("Login faile:from fep");
	//	return ;
	//}

	//// fep��dp�ķ�������Ϣ��Ҫ�㲥��ls��ss
	//ServerInfoMgr::Instance()->BoardcastDpAndFepServerInfo2LsAndSs(pPacket->sLoginData.nServerID);

}
