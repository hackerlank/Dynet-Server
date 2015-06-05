#ifndef _SERVER_DP_H_
#define _SERVER_DP_H_

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

class ForServerMsgHandler : public BaseMsgHandler, public BaseSingle<ForServerMsgHandler>
{

public:
	ForServerMsgHandler();
	~ForServerMsgHandler();

	// �пͻ������ӻص�
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ�
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgHead* pMsg,int32 nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// ��¼���(fep��ls�ص����)
	void RepLogined(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);

private:


};

#endif


