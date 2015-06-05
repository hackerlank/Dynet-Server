#include "Server_PCH.h"
#include "Entity.h"

// ����һ��������ʵ��ID
static uint64 IncreaseEntityID()
{
	static uint64 nIncreaseEnitiyId = 0; //ʵ������ID
	++nIncreaseEnitiyId;
	if(nIncreaseEnitiyId == 0)
		nIncreaseEnitiyId = 1;
	return nIncreaseEnitiyId;
}

Entity::Entity(EntityType eEntityType,int32 nTypeID,bool bListen, int32 nRegistChannelFlags)
	: m_nID(0), m_bListen(bListen), m_nChannelRegistFlag(nRegistChannelFlags | CHANNEL_REGIST_TYPE_POSITION_COLLECT)
{
	m_nID = IncreaseEntityID();
	m_sChannelPosition.nID = m_nID;
	m_sChannelPosition.nType = eEntityType;
	m_sChannelPosition.nTypeID = nTypeID;
	InitAttributeOffet();
}

bool Entity::SetAttribute(AttributeType eAttributeType, const ValueType& vNewValue)
{
	// ����Ƿ���ƫ��ֵ
	if (m_sAttributeOffset[eAttributeType].nOffset && m_sAttributeOffset[eAttributeType].bCanSet)
	{
		SetAttribute(eAttributeType, vNewValue, false);

		return true;
	}
	else
	{
		return false;
	}
}

bool Entity::SetAttribute(AttributeType eAttributeType, const ValueType& vNewValue, bool bEnforce)
{
	// ����Ƿ���ƫ��ֵ
	if (m_sAttributeOffset[eAttributeType].nOffset && (m_sAttributeOffset[eAttributeType].bCanSet || bEnforce))
	{
		// �Ƚ��¾�ֵ
		if (memcmp(m_sAttributeOffset[eAttributeType].nOffset, &vNewValue, m_sAttributeOffset[eAttributeType].nSize))
		{
			// �����ֵ
			ValueType vOldValue;
			memcpy(&vOldValue, m_sAttributeOffset[eAttributeType].nOffset, m_sAttributeOffset[eAttributeType].nSize);

			// ������ֵ
			memcpy(m_sAttributeOffset[eAttributeType].nOffset, &vNewValue, m_sAttributeOffset[eAttributeType].nSize);

			// �ص�
			if (m_sAttributeOffset[eAttributeType].hHandler)
			{
				m_sAttributeOffset[eAttributeType].hHandler(vOldValue, vNewValue);
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool Entity::GetAttribute(AttributeType i_eAttributeType, ValueType& o_vValue)
{
	// ����Ƿ���ƫ��ֵ
	if (m_sAttributeOffset[i_eAttributeType].nOffset)
	{
		memcpy(&o_vValue, m_sAttributeOffset[i_eAttributeType].nOffset, m_sAttributeOffset[i_eAttributeType].nSize);

		return true;
	}
	else
	{
		return false;
	}
}

// ״̬�л�
void  Entity::StatusToggle(CreatureStatus eCreatureStatus)
{
	ValueType o_nStatusTmp;
	GetAttribute(ATTRIBUTE_STATUS,o_nStatusTmp);
	o_nStatusTmp.nUint32 ^= eCreatureStatus;
	SetAttribute(ATTRIBUTE_STATUS,o_nStatusTmp,true);
}

void Entity::InitAttributeOffet()
{
	// ���ƫ��ֵ
	memset(m_sAttributeOffset, 0, sizeof(m_sAttributeOffset));

#define	INIT_ATTRIBUTE_OFFSET(index, name, set, handler)	\
					{\
			m_sAttributeOffset[index].nOffset = &(this->name);\
			m_sAttributeOffset[index].nSize = sizeof(name);\
			m_sAttributeOffset[index].bCanSet = set;\
			m_sAttributeOffset[index].hHandler = handler;\
					}

	// ƫ����Ϣ
	INIT_ATTRIBUTE_OFFSET(ATTRIBUTE_INVIEWRANGE, m_nInViewRange, true, boost::bind(&Entity::OnInViewChange, this, _1, _2));
	INIT_ATTRIBUTE_OFFSET(ATTRIBUTE_OUTVIEWRANGE, m_nOutViewRangle, true, boost::bind(&Entity::OnOutViewChange, this, _1, _2));

#undef INIT_ATTRIBUTE_OFFSET
}

void Entity::OnInViewChange(const ValueType& vOldValue, const ValueType& vNewValue)
{
	//���뾶ֵ
	int32 nLess = vNewValue.nInt32 - vOldValue.nInt32;
	m_sInViewRange.sTopLeft.nX		= m_sPosition.nX + nLess;
	m_sInViewRange.sTopLeft.nZ		= m_sPosition.nZ - nLess;
	m_sInViewRange.sBottomRight.nX	= m_sPosition.nX - nLess;
	m_sInViewRange.sBottomRight.nZ	= m_sPosition.nZ + nLess;
}

void Entity::OnOutViewChange(const ValueType& vOldValue, const ValueType& vNewValue)
{
	//���뾶ֵ
	int32 nLess = vNewValue.nInt32 - vOldValue.nInt32;
	m_sOutViewRangle.sTopLeft.nX		= m_sPosition.nX + nLess;
	m_sOutViewRangle.sTopLeft.nZ		= m_sPosition.nZ - nLess;
	m_sOutViewRangle.sBottomRight.nX	= m_sPosition.nX - nLess;
	m_sOutViewRangle.sBottomRight.nZ	= m_sPosition.nZ + nLess;
}