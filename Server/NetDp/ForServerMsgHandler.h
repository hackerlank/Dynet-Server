#ifndef __FOR_SERVER_MSG_HANDLER_H_
#define __FOR_SERVER_MSG_HANDLER_H_

#include "Config.h"
#include "BaseSingle.h"
#include "BaseMsgHandler.h"

class ForServerMsgHandler : public BaseMsgHandler, public BaseSingle<ForServerMsgHandler>
{
public:
	ForServerMsgHandler();
	~ForServerMsgHandler();


	// �пͻ������ӻص�
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ�
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgHead* pHead,int32 nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// �����¼
	void ReqLogined(BaseSession* pSessioin, const NetMsgHead* pHead,int32 nSize);
};


#endif // !



