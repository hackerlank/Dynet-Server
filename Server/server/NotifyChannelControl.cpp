#include "Server_PCH.h"
#include "NotifyChannelControl.h"

#include "Player.h"

#include <sstream>

using namespace std;

ObjPool<ChannelPosition>	NotifyChannelControl::s_cChanelPositionFactory;
ObjPool<ChannelCreature>	NotifyChannelControl::s_cChanelCreatureFactory;

NotifyChannelControl::NotifyChannelControl(Player& rPlayer):m_rPlayer(rPlayer),m_nPositionCount(0),m_nCreatureCount(0)
{

	for (int32 i = 0; i < MAX_POSITION_COUNT; ++i )
	{
		m_arrPosition[i] = s_cChanelPositionFactory.CreateObj();
	}
	
	for (int32 i = 0; i < MAX_CREATURE_COUNT; ++i )
	{
		m_arrCreature[i] = s_cChanelCreatureFactory.CreateObj();
	}
	
}

NotifyChannelControl::~NotifyChannelControl(void)
{
}

bool NotifyChannelControl::SendMsg(NetMsgHead* pMsg) const
{
	if(m_rPlayer.GetStatus() == ECLIENT_STATUS_OK )
	{
		 m_rPlayer.SendMsg(pMsg);
		 return true;
	}
	return false;
}

//���λ����Ϣ
void NotifyChannelControl::InsertPosition(const ChannelPosition& rPosition)
{
	if(m_nPositionCount < MAX_POSITION_COUNT)
	{
		memcpy(m_arrPosition[m_nPositionCount],&rPosition,sizeof(ChannelPosition));
		m_nPositionCount++;
	}
}

//�������������Ϣ
void NotifyChannelControl::InsertCreature(const ChannelCreature& rCreature)
{
	if(m_nCreatureCount < MAX_CREATURE_COUNT)
	{
		memcpy(m_arrCreature[m_nCreatureCount],&rCreature,sizeof(ChannelCreature));
		m_nCreatureCount++;
	}
}

// ��Ӽ�����Ϣ
void NotifyChannelControl::InsertSpell(const ChannelSpell& rSpell)
{

}

// ���Buff��Ϣ
void NotifyChannelControl::InsertBuff(const ChannelBuff& rBuff)
{

}

//����λ����Ϣ
void NotifyChannelControl::NotifyPosition()
{



}

//��������������Ϣ
void NotifyChannelControl::NotifyCreature()
{

}

// ���¼�����Ϣ
void NotifyChannelControl::NotifySpell()
{

}

// ����Buff��Ϣ
void NotifyChannelControl::NotifyBuff()
{

}

