#ifndef _SERVER_HANDLER_H_
#define _SERVER_HANDLER_H_

#include "Config.h"
#include "BaseSingle.h"
#include "BaseMsgHandler.h"

/*
 *
 *	Detail: ������ws��ss,lsͨ����Ϣ
 *   
 * Copyright (c) Created by hzd 2015-4-27.All rights reserved
 *
 */

class NetSocket;
struct NetMsgHead;

class ForWorldMsgHandler : public BaseMsgHandler, public BaseSingle<ForWorldMsgHandler>
{

public:
	ForWorldMsgHandler();
	~ForWorldMsgHandler();

	// �пͻ������ӻص�
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ�
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgHead* pHead,int32 nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// ��¼���
	void RepLogined(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);

	// �������б� 
	void RepServerInfoList(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);

	// ͬ��client���ӵ�server��Ϣ
	void NofityClientSessionInfo(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);

private:


};

#endif


