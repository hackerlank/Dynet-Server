#ifndef __NOTIFY_CONTROL_H_
#define __NOTIFY_CONTROL_H_

#include "def_channel.h"
#include "ObjPool.h"


/*
 *
 *	Detail: �����Ϣ����
 *   
 *  Created by hzd 2014-12-29
 *
 */

class Player;

/*
 *
 *	Detail: �ռ���֪ͨ������ܱ���Ϣ�Ŀ�����
 *   
 *  Created by hzd 2015-1-7
 *
 */

class NotifyChannelControl
{
public:
	NotifyChannelControl(Player& rPlayer);
	~NotifyChannelControl(void);

	// ���λ����Ϣ
	void InsertPosition(const ChannelPosition& rPosition);

	// �������������Ϣ
	void InsertCreature(const ChannelCreature& rCreature);

	// ��Ӽ�����Ϣ
	void InsertSpell(const ChannelSpell& rSpell);

	// ���Buff��Ϣ
	void InsertBuff(const ChannelBuff& rBuff);

	// ����λ����Ϣ
	void NotifyPosition();
	
	// ��������������Ϣ
	void NotifyCreature();

	// ���¼�����Ϣ
	void NotifySpell();

	// ����Buff��Ϣ
	void NotifyBuff();

public:

protected:

protected:

private:

	//������Ϣ
	bool SendMsg(NetMsgHead* pMsg) const;

private:

	Player&								m_rPlayer;

	int32								m_nPositionCount;
	ChannelPosition*					m_arrPosition[MAX_POSITION_COUNT];	//λ�ü�����Ϣ

	int32								m_nCreatureCount;
	ChannelCreature*					m_arrCreature[MAX_CREATURE_COUNT];	//����������Ϣ

	static ObjPool<ChannelPosition>		s_cChanelPositionFactory;			// λ�ü�����Ϣ����
	static ObjPool<ChannelCreature>		s_cChanelCreatureFactory;			// ���Ｏ����Ϣ����

};


#endif


