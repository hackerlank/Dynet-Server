#ifndef __COMMON_INTERNAL_H_
#define __COMMON_INTERNAL_H_

/*
 *
 *	Detail: �ڲ�ͨ��Э��
 *   
 *  Created by hzd 2015-5-21
 *
 */

#include "CommonDefine.h"

enum EProReqInternal
{
	PRO_SS_REQ_LOGIN_WS		= PRO_INTERNAL_BASE + 0,	// ��¼��������,���з�������¼��ws
	PRO_SS_REQ_LOGIN_S		= PRO_INTERNAL_BASE + 1,	// ��¼��dp,fep
	PRO_SS_REQ_LOAD_LEST	= PRO_INTERNAL_BASE + 2,	// �����������Ϣ 
	PRO_SS_REQ_PING_S		= PRO_INTERNAL_BASE + 3,	// PINGЭ��ͻ���ping����ˣ�ping�󣬾�socket->setTimeout,�յ����ݣ���ȡ�� 
	PRO_SS_REQ_CLIENT_EXIT	= PRO_INTERNAL_BASE + 4,    // �ͻ����˳�
	
};

enum EProRepInternal
{
	PRO_SS_REP_LOGINED			= PRO_INTERNAL_BASE + 50, // ��¼��� 
	PRO_SS_REP_SERVERINFO_LIST	= PRO_INTERNAL_BASE + 51, // ��������Ϣ
	PRO_SS_NOFTTY_SERVERID		= PRO_INTERNAL_BASE + 52, // ���·�������Ϣ
	PRO_SS_REP_PING_S			= PRO_INTERNAL_BASE + 53, // ����������PING�Ľ������socketȡ����ʱ�� 
};


#pragma pack(push,1)


//------------------------req------------------------------

struct SSReqLoginWs : public NetMsgHead
{
	SSReqLoginWs():NetMsgHead(PRO_SS_REQ_LOGIN_WS)
	{
	}
	char arrServerAddr[32]; // ��������ַ 
	int32 nServerPort;		// �˿�
	int32 nServerID;		// ��������ʶID
	int32 nServerType;		// ����������
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct SSReqLoginS : public NetMsgHead 
{
	SSReqLoginS():NetMsgHead(PRO_SS_REQ_LOGIN_S)
	{

	}
	int32 nServerID;		// ��������ʶID
	int32 nServerType;		// ����������
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct SSReqLoadLest : public NetMsgHead
{
	SSReqLoadLest():NetMsgHead(PRO_SS_REQ_LOAD_LEST)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct SSNofityClientExit : public NetMsgHead
{
	SSNofityClientExit(): NetMsgHead(PRO_SS_REQ_CLIENT_EXIT)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


//--------------------------rep------------------------------------

struct SSRepLogined : public NetMsgHead
{
	SSRepLogined():NetMsgHead(PRO_SS_REP_LOGINED)
	{

	}

	enum 
	{
		SUCCESS,
		FAIL,
	};

	int32 nResult;

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// �������б���Ϣ
struct SSRepServerInfoList : public NetMsgHead
{
	SSRepServerInfoList() :NetMsgHead(PRO_SS_REP_SERVERINFO_LIST)
	{
		nCount = 0;
	}
	int32 nCount;
	ServerInfoData sServerInfoData[MAX_SERVERINFO_LIST];
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(sServerInfoData) + nCount * sizeof(ServerInfoData);
	}
};

struct SSSessionNofitySInfo : public NetMsgHead
{
	SSSessionNofitySInfo() :NetMsgHead(PRO_SS_NOFTTY_SERVERID)
	{
		nFepServerID = 0;
		nLsServerID = 0;
		nDpServerID = 0;
		nSsServerID = 0;
	}
	int32 nFepServerID;
	int32 nLsServerID;
	int32 nDpServerID;
	int32 nSsServerID;
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct SSRepPingS : public NetMsgHead
{
	SSRepPingS():NetMsgHead(PRO_SS_REP_PING_S)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)





#endif