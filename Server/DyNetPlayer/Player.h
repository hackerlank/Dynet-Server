#ifndef _GAMEPLAYER_H_
#define _GAMEPLAYER_H_

#include "Config.h"

class NetSocket;
struct NetMsgHead;

// ���״̬
enum EPlayerStatus
{
	EPLAYER_STATUS_INITED		 ,	// ��ʼ����� 
	EPLAYER_STATUS_CONNECTED	 ,  // �Ѿ�������������� 
	EPLAYER_STATUS_ENCRYPTED	 ,	// �����Կ�ɹ���� 
	EPLAYER_STATUS_LOGINED		 ,	// ��¼������ 
	EPLAYER_STATUS_SELECTED		 ,  // ѡ���ɫ��� 
	EPLAYER_STATUS_OK			 ,	// ���Խ������ݽ������  
};

// ��ɫ���� 
enum EPlayerRoleType
{
	EPLAYER_ROLE_TYPE_1,
	EPLAYER_ROLE_TYPE_2,
	EPLAYER_ROLE_TYPE_3,
	EPLAYER_ROLE_TYPE_4,
};

#define MAX_PLAYER_CONNECT 5000

/*
 *
 *	Detail: �����
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class Player
{
public:

	Player();
	virtual ~Player();

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
	void SetStatus(EPlayerStatus eStatus);
	
	/*
	 *
	 *	Detail: ���״̬
	 *   
	 *  Created by hzd 2015/01/21  
	 *
	 */
	EPlayerStatus GetStatus(){ return m_eStatus; };

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
	void Update(float64 nDelay);

	/*
	 *
	 *	Detail: ���ͽ�����Ϸ��ʼ����һ��������
	 *   
	 *  Created by hzd 2015-4-17
	 *
	 */
	void SendCharacterData();

protected:

private:

	void InitAttributeOffet();

private:

	int32				m_nAccountID;						// ƽ̨ID
	int32				mSendPackCount;						//����������У���˳�򡢶��������
	NetSocket*			m_pSocket;							// socket
	EPlayerStatus		m_eStatus;							// ��������״̬

};


/*
 *
 *	Detail: ��ҹ�����
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class PlayerMgr 
{
	 // UID => Player
	typedef map< uint64 , Player* >	UIDPlayerMap; 
	typedef map< uint64 , Player* >::iterator	UIDPlayerMapIter;

public:

	PlayerMgr();
	~PlayerMgr();

	static PlayerMgr* Instance();

	/*
	 *
	 *	Detail: ��ʼ�����еȴ����ӵ�Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void Init();	

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
	 *	Detail: ��ø�Player
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	Player&	GetPlayer(uint32 nIndex);
		  
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

	Player*			m_arrPlayerCache[MAX_PLAYER_CONNECT];	// ������һ���(������δ����)
	UIDPlayerMap	m_mapUIDPlayer;							// UID��ӦPlayer	
	static PlayerMgr* s_pInstance;
};

#endif

