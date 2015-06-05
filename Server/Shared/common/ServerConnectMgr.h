#ifndef __SERVER_CONNECTED_MGR_H_
#define __SERVER_CONNECTED_MGR_H_

#include "../DyNetSocket/NetClient.h"

#include "BaseDefine.h"
#include "BaseSingle.h"

struct NetClientInfo
{
	NetClientInfo()
	{
		nServerID	= 0;
		nServerType = 0;
		pNetClient	= NULL;
	}

	NetClient* pNetClient;
	uint32 nServerID;
	uint32 nServerType;

};

/*
 *
 *	Detail: �����ⲿ���������ӹ���
 *   
 *  Created by hzd 2015-5-25
 *
 */
class ServerConnectMgr : public BaseSingle<ServerConnectMgr>
{
	typedef vector<NetClientInfo*> NetClientInfoVecterType;
	typedef vector<uint32> DisconnectServerIDVectorType;
public:
	ServerConnectMgr();
	~ServerConnectMgr();

	typedef PNetServerEnterHandler NetMsgEnter;
	typedef PNetServerOnMsgHandler NetMsgOn;
	typedef PNetServerExistHandler NetMsgExit;

	// ���ӵ�һ���µķ����� 
	bool ConnectToServer(int32 nServerID,int32 nServerType, const char arrHost[32],int32 nPort,NetMsgEnter fEnter,NetMsgOn fMsg,NetMsgExit fExit);

	// ɾ��һ��Server
	void RemoveServer(int32 nServerID);

	// ����һ��NetClient
	NetClientInfo* GetNetClient(NetSocket& rSocket);

	// ͳ�Ʊ������� 
	int32 CountConnected();

	// update������NetClient�е�socket��Ϣ 
	void Update(int32 nSrvTime);

private:

	NetClientInfoVecterType			m_vecNetClientInfo;	// �����ⲿ��������Ϣ
	DisconnectServerIDVectorType	m_vecNetClient;		// �Ͽ����ӵķ�����ID

};


#endif


