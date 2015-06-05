#ifndef CLIENT_NET_HANDLER_H_
#define CLIENT_NET_HANDLER_H_

/*
 *
 *	Detail: �ͻ���Handler�¼�
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class ClientNetHandler
{
public:

	ClientNetHandler(void);
	~ClientNetHandler(void);

	// �����ɷ����������Ͽ�
	static void SendRequestClose(ClientPlayer* gPlayer);

	/////////////////////////////����/////////////////////////////////////////////
	static void SendEncrypt(ClientPlayer* gPlayer);
	static void SendLogin(ClientPlayer* gPlayer);
	static void SendCharacterList(ClientPlayer* gPlayer);
	static void SendRegister(ClientPlayer* gPlayer);
	static void SendChar2World(ClientPlayer* gPlayer);
	static void SendLoadResed(ClientPlayer* gPlayer);

	/////////////////////////////����/////////////////////////////////////////////

	static void RecvEncryptInfo(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);
	static void RecvLoginReadyFinish(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);

	static void RevcCharacterList(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);
	static void RevcLoginResult(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);
	static void RecvSelectResult(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);
	static void RecvRegisterResult(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);
	static void RecvCharacterInfo(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);
	static void RecvChatInfo(ClientPlayer* gPlayer,NetMsgHead* pHead,int32 nSize);


};

#endif

