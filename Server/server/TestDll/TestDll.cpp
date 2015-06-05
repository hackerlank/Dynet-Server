// TestDll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../../DyNetServer/NetServer.h"
#include "../../DyNetMysql/DbSession.h"
#include "../../DyNetMysql/DbRecordSet.h"

#include <iostream>
using namespace std;

NetServer*	gNetServerForClient;
IDbSession*	gDataBase;



void OnNetMsgEnter( NetSocket& rSocket );
void OnNetMsgExit( NetSocket& rSocket );
void OnNetMsg( NetSocket& rSocket , NetMsgHead* pHead );


#pragma pack(push,1)
struct CharacterInfo
{
	int64 type_idx;
	char nick[32];
	int32 level;
};
#pragma pack(pop)

void DBCallbase(void* pUser, const void* pMsg)
{
	const DbRecordSet* pRecordSet = static_cast<const DbRecordSet*>(pMsg);
	for (int32 i = 0 ; i < pRecordSet->CountRecord();++i )
	{
		const CharacterInfo* pInfo = static_cast<const CharacterInfo*>(pRecordSet->GetRecordBuff(i));
		printf("id:%ld nick:%s level:%d \n",pInfo->type_idx,pInfo->nick,pInfo->level);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	// ����msyql
	gDataBase = DbSessionMgr::Instance()->AddDatabase("127.0.0.1", "root", "root", "swa_data", false);
	ASSERT(gDataBase);

	// ��ʼ��Scoket����
	gNetServerForClient = NetServerMgr::Instance()->AddNetServer();
	gNetServerForClient->SetAddress("127.0.0.1", 4321);
	//gNetServer->SetHandler(OnNetMsgEnter, OnNetMsg, OnNetMsgExit);
	gNetServerForClient->SetHandlerDefault();

	// ����Socket����
	gNetServerForClient->Start();

	//gDataBase->ExecuteAsyncSQL("SELECT `type_idx`,`nick`,`level` FROM `character`",NULL,DBCallbase);
	while (true)
	{
		Sleep(1);
		NetServerMgr::Instance()->Update(0); //�߼�����
		DbSessionMgr::Instance()->Update(0); //SQL�����ص�
	}
	return 0;
}

void OnNetMsgEnter(NetSocket& rSocket)
{
	int a = 1;
}

void OnNetMsg(NetSocket& rSocket, NetMsgHead* pHead)
{
	int a = 1;
}

void OnNetMsgExit(NetSocket& rSocket)
{
	int a = 1;
}