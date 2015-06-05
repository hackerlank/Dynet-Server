﻿#include "Server_PCH.h"
#include "GameConfig.h"
#include "NetMsgHandler.h"
#include "GameCommand.h"
#include "GameDB.h"
#include "Player.h"
#include "GlobalVar.h"
#include "ResourceMgr.h"
#include "GameConfig.h"

#include "../DyNetServer/NetServer.h"
#include "../DyNetMysql/DbSession.h"

/*
*
*	Detail: 程序主入口
*   
*  Created by hzd 2014-11-28
*
*/

NetServer*		gNetServerForClient;
GameCommand		gGameCommand;

bool gIsRun		= true;
bool gIsExit	= true;

char SQL_BUFFER[ MAX_SQL_BUFFER ];

bool DBServerInit(const GameConfigInfo& rGameCfgInfo);
void RunServerExit();
void Init();
void GameUpdate( uint32 nDelay );
void ServerStart(); 

int main(int argc, const char * argv[])
{
	// 初始化服务器所都要准备好的数据 
	Init();

	// 启动服务 
	ServerStart();

	// 执行退出的相关操作
	RunServerExit();

	return 0;

}

void RunServerExit()
{
	uint32 nSize = 0;
	while( gIsExit)
	{
		//nSize = gDbServer->GetDataDb()->GetRequestSize();
		FLOG_INFO( "db request %d." , nSize );
		if ( !nSize )
			gIsExit = false;
	}
}


bool DBServerInit(const GameConfigInfo& rGameCfgInfo)
{
	if(IDbSession* pDb = g_rDbDatabaseMgr.AddDatabase(rGameCfgInfo.arrDbdateHost,rGameCfgInfo.arrDbDataUsername,rGameCfgInfo.arrDbDataPassword,rGameCfgInfo.arrDbDataDbname))
	{
		//gDbServer->InitDataDb(pDb);
		FLOG_INFO( "DBServer Init.............Ok" );
		return true;
	}else{
		FLOG_INFO( "DBServer data faile." );
		return false;
	}
}

void Init()
{

	// 初始化化协议
	InitNetMsg();

	// 加载配置
	g_rGameCfg.LoadRes( "../conf/gameconfig.xml" );

	// 服务器相关配置
	const GameConfigInfo& rGameCfgInfo = g_rGameCfg.GetGameConfigInfo();

	// 加载服务器需要的资源
	g_rResourceMgr.LoadAllRes(rGameCfgInfo.arrConfigPath);

	// 初始化数据库
	if(DBServerInit(rGameCfgInfo))
	{
		// 初始化Scoket服务
		gNetServerForClient = NetServerMgr::Instance()->AddNetServer();
		gNetServerForClient->SetAddress( rGameCfgInfo.arrServerHost , rGameCfgInfo.nServerPort);
		gNetServerForClient->SetHandler( OnNetMsgEnter , OnNetMsg , OnNetMsgExit );

		// 初始化待连接玩家数据
		g_rPlayerMgr.Init(*gNetServerForClient);

		// 启动Socket服务
		gNetServerForClient->Start();

		FLOG_INFO( "SERVER STARTED." );

		// 辅助命令初始化
		gGameCommand.Init();
	}
}

/*
 *
 *	Detail: 游戏主循环
 *   
 *  Created by hzd 2015/01/26  
 *
 */
void GameUpdate( uint32 nDelay )
{
	//gDbServer->Update(nDelay);
	gNetServerForClient->Update(nDelay);
	g_rPlayerMgr.Update(nDelay);
	g_rSceneChannelManager.Update();
	g_rSceneMapMgr.Update();
}

/*
 *
 *	Detail: Socket启动（IO开始接收）
 *   
 *  Created by hzd 2015/01/26  
 *
 */
void ServerStart()
{	

	timer t;
	t.elapsed();
	double nNowTime = 0,nLastTime = 0;
	int32 nCount = 0 , nRunStatus = 0;
	while ( gIsRun )
	{
		if ( nCount > 1000 )
		{
			SSleep(1);
			nCount = 0;
		}
		nCount++; 
		nRunStatus++;
		GameUpdate( 0 );
		if( nRunStatus > 1000000 )
		{ 
			nNowTime = t.elapsed();
			double nDelay = nNowTime - nLastTime;
			nLastTime = nNowTime;
			// 统计服务器信息，在线人数
			int32 nConnectedNum = NetServerMgr::Instance()->GetNetServer(1)->ConnectedSockets();
			int32 nAccptingNum = NetServerMgr::Instance()->GetNetServer(1)->AcceptingSockets();
			FLOG_INFO("Server Info: Delay Time:%f  Connected Num:%d  Accepting Num:%d ",nDelay,nConnectedNum,nAccptingNum);	// 标识主线程还在做事中
			nRunStatus = 0;
		}
	}
}



