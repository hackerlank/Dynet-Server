#ifndef __CREATURE_H_
#define __CREATURE_H_

#include <map>

#include "Entity.h"
#include "def_creature.h"
#include "UnorderedSet.h"

struct Buff;

class Creature : public Entity, public IChannelOperate(ChannelCreature), public IChannelOperate(ChannelSpell) , public IChannelOperate(ChannelBuff)
{
public:
	Creature(EntityType eEntityType,uint32 nEntityTypeID,bool bListen,int32 registChannelFlags);

	// �ռ�������Ϣ
	DEFINE_FUNCTION_CHANNEL_COLLECT(ChannelSpell);

protected:
	
protected:

	std::multimap<int32, Buff*>		m_mapBuffs;					// ��������Buff
	std::queue<uint32>				m_queSpell;					// ����ʩ�Ŷ���

private:

	void InitAttributeOffet();

private:

	CreatureAttribute				m_sAttribute;									// ����������
};


class CreatureManager : public BaseSingle<CreatureManager>
{
	typedef UNORDERED_SET<Creature*> CreatureUSetType;
public:
	CreatureManager(){}
	~CreatureManager(){}
	
	//���������
	void AddCreature(Creature& rCreature);

	//��������ʧ
	void DelCreature(Creature& rCreature);

	// ����(nTimeElapse��λ:����)
	void Update(int32 nTimeElapse);

private:
	
	CreatureUSetType	m_usetCreaturies;			//��������������

};

#endif
