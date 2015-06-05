#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_

#include "Config.h"
#include "BaseSingle.h"
#include "BaseMsgHandler.h"

/*
 *
 *	Detail: ����dp,ss,ls(��),fep���������Э��
 *   
 * Copyright (c) Created by hzd 2015-4-28.All rights reserved
 *
 */

class NetSocket;
struct NetMsgHead;

// ���еķ������б�


class ForServerMsgHandler : public BaseMsgHandler , public BaseSingle<ForServerMsgHandler>
{
public:
	ForServerMsgHandler();
	~ForServerMsgHandler();


	// �пͻ������ӻص�
	void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ�
	void OnNetMsg(NetSocket& rSocket, NetMsgHead* pMsg,int32 nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
	void OnNetMsgExit(NetSocket& rSocket);

	// ��¼ls,fep,dp,ss��¼ws 
	void ReqLogin(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);

	// �����÷���ĸ�����͵ķ�����ID
	void ReqRoadLest(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);

	// �ͻ����˳�֪ͨ
	void NofityClientExit(BaseSession* pSession, const NetMsgHead* pMsg,int32 nSize);


};

#endif


