#ifndef __SERVER_INFO_MGR_H_
#define __SERVER_INFO_MGR_H_

#include "BaseDefine.h"
#include "BaseSingle.h"
#include "BaseSession.h"
#include "CommonDefine.h"

/*
 *
 *	Detail: ��������Ϣ����(������ת�����˳�)
 *   
 * Copyright (c) Created by hzd 2015-5-14.All rights reserved
 *
 */
class ServerSession;

struct ServerInfo
{
	ServerInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	char arrHosrt[32];
	int32 nPort;
	int32 nServerType;
	int32 nServerID;
	int32 nLoadCount;
	ServerSession* pServerSession;
};

typedef std::vector<ServerInfo> ServerInfoVecType;
typedef std::map<uint32, ServerInfo> ServerInfoMapType;


class ServerInfoMgr : public BaseSingle<ServerInfoMgr>
{
public:

	ServerInfoMgr();
	~ServerInfoMgr();

	// ���ĳ��������Ϣ
	const ServerInfo* GetServerInfo(uint32 nServerID);

	// ��¼һ�·�����
	bool OnServerLogin(ServerSession* pSession,const char arrHost[32],int32 nPort,int32 nServerID,uint32 nServerType);

	// ĳ�������˳�
	void OnServerExit(uint32 nServerID);

	// ����+1
	void OnLoadAddOne(uint32 nServerID);

	// ����-1
	void OnLoadSubOne(uint32 nServerID);

	// ��÷������б�
	void GetServerInfoList(int32 nServerType,ServerInfoVecType& o_rServerList);

	// ��ø������ٵķ�����
	ServerSession* GetLoadLestSession(int32 nServerType);

	// �㲥��������Ϣ
	void BoardcastDpAndFepServerInfo2LsAndSs(uint32 nLoginServerID);

private:

	ServerInfoMapType m_mapServerInfo; // �������б� 

};



#endif




