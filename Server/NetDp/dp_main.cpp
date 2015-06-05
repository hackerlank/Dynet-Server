#include "../DyNetSocket/NetServer.h"
#include "../DyNetSocket/NetClient.h"
#include "../DyNetMysql/DbSession.h"
#include "../DyNetMysql/DbRecordSet.h"

#include "LogManager.h"
#include "ServerSession.h"
#include "ClientSession.h"
#include "CommonServerOpt.h"
#include "ForWorldMsgHandler.h"
#include "ForServerMsgHandler.h"


/*
*
*	Detail: ���������
*
*  Created by hzd 2014-11-28
*
*/

NetClient*	gNetClientForWs		= NULL; // connected to ws
NetServer*	gNetServerForServer = NULL; // connected to other sever

DbSessionMgr* gDbServerMgr = DbSessionMgr::Instance(); // db 

bool gIsRun = true;

void Init();
void ServerStart();
void RunServerExit();

int main(int argc, const char * argv[])
{
	// ��ʼ������������Ҫ׼���õ����� 
	Init();

	// �������� 
	ServerStart();

	// ִ���˳�����ز���
	RunServerExit();

	return 0;
}

void ServerStart()
{
	int32 nRunTimes = 0;
	while(gIsRun)
	{
		SSleep(1);
		gNetClientForWs->Update(0);
		gNetServerForServer->Update(0);
		gDbServerMgr->Update(0.0);
		nRunTimes++;
		if(nRunTimes > RUN_PRINT_TIMES)
		{
			int32 nServerNum = ServerSessionMgr::Instance()->CountConnected();
			int32 nClientNum = ClientSessionMgr::Instance()->ConnectedSessions();
			FLOG_INFO("Server Info:Server Connected Num:%d , Client Connected Num:%d", nServerNum,nClientNum);	// ��ʶ���̻߳���������
			nRunTimes = 0;
		}
	}
}

void RunServerExit()
{
	// TODO������ͣ����ص����� 
}

void Init()
{

	
	bool bResult = NetServerOpt::Instance()->LoadServerConfig("dp_cfg.xml",ESERVER_TYPE_DP);
	if(!bResult)
	{
		FLOG_INFO("Load cfg fail");
		return;
	}
	
	// �������ݿ�
	DatabaseInfoOpt& rDbInfo = NetServerOpt::Instance()->GetDatabaseInfo();
	IDbSession* pDb = gDbServerMgr->AddDatabase(rDbInfo.strHost.c_str(),rDbInfo.strUser.c_str(),rDbInfo.strPass.c_str(),rDbInfo.strDbname.c_str());
	if(pDb == NULL)
	{
		FLOG_INFO("Connnect to Database fail!","");
		return;
	}

	// ����WS����
	ServerInfoOpt& rRemoteInfo = NetServerOpt::Instance()->GetRemoteServerInfo();
	gNetClientForWs = new NetClient();
	gNetClientForWs->SetAddress(rRemoteInfo.strHost.c_str(), rRemoteInfo.nPort);
	gNetClientForWs->SetHandler(boost::bind(&ForWorldMsgHandler::OnNetMsgEnter, ForWorldMsgHandler::Instance(), _1),
		boost::bind(&ForWorldMsgHandler::OnNetMsg, ForWorldMsgHandler::Instance(), _1, _2, _3),
		boost::bind(&ForWorldMsgHandler::OnNetMsgExit, ForWorldMsgHandler::Instance(), _1));
	gNetClientForWs->Start();

	// ��ʼ��ForServer����
	ServerInfoOpt& rLocalInfo = NetServerOpt::Instance()->GetLocalServerInfo();
	gNetServerForServer = new NetServer(MAX_SERVER_CONNECTED);
	gNetServerForServer->SetTimeout(60);
	gNetServerForServer->SetAddress(rLocalInfo.strHost.c_str(), rLocalInfo.nPort);
	gNetServerForServer->SetHandler(boost::bind(&ForServerMsgHandler::OnNetMsgEnter, ForServerMsgHandler::Instance(), _1),
		boost::bind(&ForServerMsgHandler::OnNetMsg, ForServerMsgHandler::Instance(), _1, _2, _3),
		boost::bind(&ForServerMsgHandler::OnNetMsgExit, ForServerMsgHandler::Instance(), _1));
	gNetServerForServer->Start();

}
