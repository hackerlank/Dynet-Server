#include "DpServerProcHandler.h"
#include "BaseSession.h"
#include "../DyNetSocket/NetConfig.h"
#include "CommonW2D.h"
#include "CommonD2W.h"
#include "ServerSession.h"
#include "ServerInfoMgr.h"


DpServerProcHandler::DpServerProcHandler()
{
}


DpServerProcHandler::~DpServerProcHandler()
{
}

void DpServerProcHandler::ReqLogin(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize)
{

	//// ls�����¼
	//const Dp2WsLogin* pPacket = static_cast<const Dp2WsLogin*>(pMsg);
	//const LoginData2Ws& sLoginData = pPacket->sLoginData;
	//if(!CheckLogin(*pSession, sLoginData, ESERVER_TYPE_DP))
	//{
	//	FLOG_ERROR("CheckLogin Fail!");
	//	return;
	//}

	//ServerSession* pClient = static_cast<ServerSession*>(pSession);

	//// ״̬
	//pClient->SetStatus(EPLAYER_STATUS_LOGINED);
	//pClient->SetServerType(ESERVER_TYPE_DP);
	//pClient->SetServerID(sLoginData.nServerID);

	//// ��¼�µ��������server
	//if(!ServerInfoMgr::Instance()->OnServerLogin(pSession,sLoginData.arrServerAddr,sLoginData.nServerPort,sLoginData.nServerID,ESERVER_TYPE_DP))
	//{
	//	FLOG_ERROR("Login fail:form dp");
	//	return;
	//}

	//// �㲥�µ�server������server,
	//ServerInfoMgr::Instance()->BoardcastDpAndFepServerInfo2LsAndSs(pPacket->sLoginData.nServerID);

	//// ���ص�¼�ɹ�
	//WS2DPLogined sMsg;
	//sMsg.nResult = WS2DPLogined::SUCCESS;
	//pClient->SendMsg(&sMsg, sMsg.GetPackLength());

}