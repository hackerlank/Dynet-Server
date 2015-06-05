#ifndef _GAMEPLAYER_H_
#define _GAMEPLAYER_H_

#include "Creature.h"
#include "NotifyChannelControl.h"
#include "GameDB.h"

class NetSocket;
struct NetMsgHead;

// ���״̬
enum EClientStatus
{
	ECLIENT_STATUS_INITED		 ,	// ��ʼ����� 
	ECLIENT_STATUS_CONNECTED	 ,  // �Ѿ�������������� 
	ECLIENT_STATUS_ENCRYPTED	 ,	// �����Կ�ɹ���� 
	ECLIENT_STATUS_LOGINED		 ,	// ��¼������ 
	ECLIENT_STATUS_SELECTED		 ,  // ѡ���ɫ��� 
	ECLIENT_STATUS_OK			 ,	// ���Խ������ݽ������  
};

// ��ɫ���� 
enum EPlayerRoleType
{
	EPLAYER_ROLE_TYPE_1,
	EPLAYER_ROLE_TYPE_2,
	EPLAYER_ROLE_TYPE_3,
	EPLAYER_ROLE_TYPE_4,
};

/*
 *
 *	Detail: �����
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class Player  : public Creature , public IChannelOperate(ChannelWear)
{
public:

	Player(NetSocket& rSocket);
	virtual ~Player();

	/*
	 *
	 *	Detail: ��������
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void LoadData(const DBCharacherData& rData);

	/*
	 *
	 *	Detail: ��ý�ɫID
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	uint64	UID();

	/*
	 *
	 *	Detail: ������Ϣ
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void SendMsg( NetMsgHead* pMsg);
	
	/*
	 *
	 *	Detail: ���ƽ̨�˺�
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	uint32 AccountID();

	/*
	 *
	 *	Detail: ����ƽ̨ID
	 *   
	 *  Created by hzd 2015/02/14  
	 *
	 */
	void SetAccountID(int32 nAccountID);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void SetStatus(EClientStatus eStatus);
	
	/*
	 *
	 *	Detail: ���״̬
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	EClientStatus GetStatus(){ return m_eStatus; };

	/*
	 *
	 *	Detail: ����ͨ����Կ
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void SetEncryptKey(char arrNewKey[MAX_ENCRYPT_LENTH]);

	/*
	 *
	 *	Detail: ���ͨ����Կ
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void GetEncryptKey(char o_arrEncryptKey[MAX_ACCOUNT_LENG]);

	/*
	 *
	 *	Detail: ����˳�
	 *   
	 *  Created by hzd 2015-1-21
	 *
	 */
	void Exist();

	/*
	 *
	 *	Detail: ��ʱѭ��������Ϊ��ʱ����
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	void Update(uint32 nDelay);

	/*
	 *
	 *	Detail: ���ͽ�����Ϸ��ʼ����һ��������
	 *   
	 *  Created by hzd 2015-4-17
	 *
	 */
	void SendCharacterData();

protected:

		// λ����Ϣ�㲥
		DEFINE_FUNCTION_CHANNEL_BROADCAST(ChannelPosition);

		// ��������Ϣ�㲥
		DEFINE_FUNCTION_CHANNEL_BROADCAST(ChannelCreature);

		// װ����Ϣ�㲥
		DEFINE_FUNCTION_CHANNEL_BROADCAST(ChannelWear);

		// ������Ϣ�㲥
		DEFINE_FUNCTION_CHANNEL_BROADCAST(ChannelSpell);

		// Buff��Ϣ�㲥
		DEFINE_FUNCTION_CHANNEL_BROADCAST(ChannelBuff);

private:

	void InitAttributeOffet();

private:

	int32				m_nAccountID;						// ƽ̨ID
	DBCharacherData		m_rCharacterData;					// ��ɫ����

	NetSocket&			m_rSocket;							// socket
	EClientStatus		m_eStatus;							// ��������״̬

	int32				mSendPackCount;						//����������У���˳�򡢶��������
	char				m_arrEncryptKey[MAX_ENCRYPT_LENTH];	//ͨ����Կ


	NotifyChannelControl		m_rNotifyChannelControl;	// Ƶ����Ϣ������


};


/*
 *
 *	Detail: ��ҹ�����
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class NetServer;

class PlayerMgr : public BaseSingle< PlayerMgr >
{

	typedef map< uint64 , Player* >	UIDPlayerMap;  // 
	typedef map< uint64 , Player* >::iterator	UIDPlayerMapIter;

public:

	PlayerMgr();
	~PlayerMgr();

	/*
	 *
	 *	Detail: ��ʼ�����еȴ����ӵ�Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void Init(NetServer& rNetServer);	

	/*
	 *
	 *	Detail: �ͷ�Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void Release();

	/*
	 *
	 *	Detail: ���Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	Player*	GetPlayer( uint64 nUid);

	/*
	 *
	 *	Detail: ��ø�Player(Player��Socket����Զ�󶨵ģ�������Ϊ�����Ч��)
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	Player&	GetPlayer(NetSocket& rSocket );
		  
	/*
	 *
	 *	Detail: �㲥��Ϣ
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void SendToAll( NetMsgHead* msg );

	/*
	 *
	 *	Detail: ����
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void Update(uint32 nDelay);

private:

	Player*			m_arrPlayerCache[MAX_SOCKET_CONNECT];	// ������һ���(������δ����)
	UIDPlayerMap	m_mapUIDPlayer;							// UID��ӦPlayer	

};

#endif

