
#include "../DyNetSocket/NetServer.h"

#include "LogManager.h"
#include "ForServerMsgHandler.h"
#include "ServerSession.h"
#include "ClientSession.h"
#include "CommonServerOpt.h"

#include "DeallineAsync.h"

/*
*
*  Detail: ws���������
*  (ls|fep|ss)->ws<-dp 
*  Created by hzd 2014-11-28
*
*/

NetServer*	gNetServerForClient;
DeallineAsync* gDeallien;

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

void InteravalUpdate(int32 nSrvTime)
{
	
	if(nSrvTime % 5 == 0) // 1�� 
	{
		ClientSessionMgr::Instance()->Update(nSrvTime);
	}else if(nSrvTime % 300 == 0) // 60��
	{
		// ping 
	}
	
}

void ServerStart()
{
	FLOG_NORMAL("SERVER STARTED.");
	int32 nRunTimes = 0;
	while(gIsRun)
	{
		SSleep(1);
		nRunTimes++;
		gNetServerForClient->Update(0);
		if(nRunTimes > RUN_PRINT_TIMES)
		{
			int32 nServerNum = gNetServerForClient->ConnectedSockets();
			int32 nClientNum = ClientSessionMgr::Instance()->ConnectedSessions();
			FLOG_INFO("Server Info: Server Connected Num:%d ,Client Connected Num:%d", nServerNum, nClientNum);// ��ʶ���̻߳���������
			nRunTimes = 0;
		}
	}
}

void RunServerExit()
{

}

void Init()
{
	bool bResult = NetServerOpt::Instance()->LoadServerConfig("ws_cfg.xml",ESERVER_TYPE_WS);
	if(!bResult)
	{
		FLOG_INFO("Load cfg fail");
		return;
	}

	// ��ʼ��Scoket����
	ServerInfoOpt& rLocalInfo = NetServerOpt::Instance()->GetLocalServerInfo();
	gNetServerForClient = new NetServer(MAX_WS_SOCKET_CONNECT);
	gNetServerForClient->SetTimeout(60);
	gNetServerForClient->SetAddress(rLocalInfo.strHost.c_str(), rLocalInfo.nPort);
	gNetServerForClient->SetHandler(boost::bind(&ForServerMsgHandler::OnNetMsgEnter, ForServerMsgHandler::Instance(), _1),
		boost::bind(&ForServerMsgHandler::OnNetMsg, ForServerMsgHandler::Instance(), _1, _2, _3), 
		boost::bind(&ForServerMsgHandler::OnNetMsgExit, ForServerMsgHandler::Instance(), _1));

	// ����Socket����
	gNetServerForClient->Start();

	// ������ʱ��
	//gDeallien = new DeallineAsync(3000, 0, InteravalUpdate);
	//gDeallien->Start();

}




