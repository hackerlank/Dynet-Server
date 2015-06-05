#include "Server_PCH.h"
#include "Player.h"
#include "../DyNetServer/NetServer.h"


Player::Player(NetSocket& rSocket):Creature(ENTITY_TYPE_PLAYER,EPLAYER_ROLE_TYPE_1,true,CHANNEL_REGIST_TYPE_NULL),m_rSocket(rSocket),m_eStatus(ECLIENT_STATUS_INITED),m_rNotifyChannelControl(*this)
{
	memcpy(m_arrEncryptKey,EncryptDefualt,MAX_ENCRYPT_LENTH);
	InitAttributeOffet();
}

Player::~Player()
{
}

uint64	Player::UID()
{
	return m_rCharacterData.nUID;
}

void Player::LoadData(const DBCharacherData& rData)
{
	// ��ֵ
	memcpy(&m_rCharacterData,&rData,sizeof(DBCharacherData));
}

void Player::InitAttributeOffet()
{
	// ���õ��ֶν���ע�ắ�����޸ġ��ص��Ⱥ�����
}


void Player::SendMsg(NetMsgHead* pMsg)
{
	// ���ܴ���
	static char arrBuffer[MAX_SOCKET_BUFFER];

	// ����̬�����
	memcpy(&arrBuffer[0],pMsg,pMsg->GetPackLength());
	
	Encrypt::XorCode(pMsg->nSize,m_arrEncryptKey,&arrBuffer[sizeof(pMsg->nSize)],pMsg->nSize);
	pMsg = ( NetMsgHead*)&arrBuffer[0];

	m_rSocket.ParkMsg(pMsg,pMsg->GetPackLength());
	m_rSocket.SendMsg();
}


void Player::SetEncryptKey(char arrNewKey[MAX_ENCRYPT_LENTH])
{ 
	memcpy(m_arrEncryptKey,arrNewKey,MAX_ENCRYPT_LENTH); 
}

void Player::GetEncryptKey(char o_arrEncryptKey[MAX_ACCOUNT_LENG])
{
	memcpy(o_arrEncryptKey,m_arrEncryptKey,MAX_ENCRYPT_LENTH); 
}


void Player::SetStatus(EClientStatus eStatus)
{
	if (ECLIENT_STATUS_INITED == eStatus)
	{
		memcpy(m_arrEncryptKey, EncryptDefualt, MAX_ENCRYPT_LENTH);
	}
	m_eStatus = eStatus;
}



uint32 Player::AccountID()
{
	return m_nAccountID;
}

void Player::SetAccountID(int32 nAccountID)
{
	m_nAccountID = nAccountID;
}


void Player::Exist()
{
	m_rSocket.Disconnect();
}

void Player::Update(uint32 nDelay)
{
	m_rNotifyChannelControl.NotifyCreature();
}

void Player::SendCharacterData()
{

	S2CCharacterInitData sMsg;
	sMsg.nUID = m_rCharacterData.nUID;

	SendMsg(&sMsg);

	SetStatus(ECLIENT_STATUS_OK);
}

IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(Player, ChannelPosition)
{
	if(rsetValues.size() == 0)
		return;
	for(set<const ChannelPosition*>::const_iterator it = rsetValues.begin(); it != rsetValues.end(); ++it)
	{
		if(*it == NULL || (*it)->nID == ID())
			continue;
		m_rNotifyChannelControl.InsertPosition(**it);
	}
}

IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(Player, ChannelCreature)
{
	if(rsetValues.size() == 0)
		return;
	for(set<const ChannelCreature*>::const_iterator it = rsetValues.begin(); it != rsetValues.end(); ++it)
	{
		if(*it == NULL || (*it)->nID == ID())
			continue;
		m_rNotifyChannelControl.InsertCreature(**it);
	}
}

// �㲥��ɫ������Ϣ
IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(Player, ChannelWear)
{

}


// �㲥��ɫ������Ϣ
IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(Player, ChannelSpell)
{
	if(rsetValues.size() == 0)
		return;
	for(set<const ChannelSpell*>::const_iterator it = rsetValues.begin(); it != rsetValues.end(); ++it)
	{
		if(*it == NULL || (*it)->nID == ID() || (*it)->nSpellID == 0)
			continue;
		m_rNotifyChannelControl.InsertSpell(**it);
	}
}

// �㲥��ɫBuff��Ϣ
IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(Player, ChannelBuff)
{
	if(rsetValues.size() == 0)
		return;
	for(set<const ChannelBuff*>::const_iterator it = rsetValues.begin(); it != rsetValues.end(); ++it)
	{
		if(*it == NULL) // �����Լ�
			continue;
		m_rNotifyChannelControl.InsertBuff(**it);
	}
}


PlayerMgr::PlayerMgr()
{
}

PlayerMgr::~PlayerMgr()
{

}


void PlayerMgr::Init(NetServer& rNetServer)
{
	for(int32 i = 0; i < MAX_SOCKET_CONNECT; i++)
	{
		NetSocket& pSocket = rNetServer.GetSocket(i);
		ASSERT(pSocket.SID() == i);
		m_arrPlayerCache[i] = new Player(pSocket);
	}
}


void PlayerMgr::Release()
{
	for(int32 i = 0; i < MAX_SOCKET_CONNECT; i++)
	{
		delete m_arrPlayerCache[i];
	}

	delete s_pInstance;
	s_pInstance = NULL;
}


Player*	PlayerMgr::GetPlayer(uint64 nUid)
{
	UIDPlayerMapIter iter = m_mapUIDPlayer.find(nUid);
	if(iter == m_mapUIDPlayer.end())
	{
		return NULL;
	}
	return iter->second;
}


Player&	PlayerMgr::GetPlayer(NetSocket& rSocket)
{
	return *m_arrPlayerCache[rSocket.IndexID()];
}



void PlayerMgr::SendToAll(NetMsgHead* pMsg)
{
	UIDPlayerMapIter iter = m_mapUIDPlayer.begin();
	UIDPlayerMapIter iterend = m_mapUIDPlayer.end();

	for(; iter != iterend; ++iter)
	{
		iter->second->SendMsg(pMsg);
	}
}

void PlayerMgr::Update(uint32 nDelay)
{

	UIDPlayerMapIter it = m_mapUIDPlayer.begin();
	UIDPlayerMapIter itEnd = m_mapUIDPlayer.end();
	Player* pPlayer = NULL;
	for(; it != itEnd; ++it)
	{
		pPlayer = it->second;
		pPlayer->Update(nDelay);
	}

}

