#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <bitset>
#include <assert.h>

#include "Geometry2D.h"
#include "SceneChannel.h"
#include "ObjPool.h"
#include "UnorderedSet.h"
#include "def_entity.h"
#include "def_attribute.h"
#include "def_creature.h"

class SceneRegion;
class SceneMap;

class Entity : public IChannelRegist, public IChannelOperate(ChannelPosition)
{
public:
	Entity(EntityType eEntityType,int32 nResId,bool bListen, int32 nRegistChannelFlags);

	// �Ƿ�ע��ָ��Ƶ��
	virtual bool IsRegist(ChannelRegistType eType) const
	{
		return (m_nChannelRegistFlag & eType) != 0;
	}

	const uint64 ID() const
	{
		return m_nID;
	}

	const Vector2DEx& Heading() const
	{
		return m_sHeading;
	}

	void SetHeading(const Vector2D& sHeading)
	{
		// ȡ��������Ϊ��λ����
		m_sHeading = sHeading;
		m_sHeading.Normalize();
		m_sChannelPosition.nHeadingX = sHeading.nX;
		m_sChannelPosition.nHeadingZ = sHeading.nZ;
	}

	const Point2D& Position() const
	{
		return m_sPosition;
	}

	void SetPosition(const Point2D& sPosition)
	{
		m_sPosition = sPosition;
		m_sChannelPosition.nPositionX = sPosition.nX;
		m_sChannelPosition.nPositionZ = sPosition.nZ;

		m_sInViewRange.sTopLeft.nX		= m_sPosition.nX + m_nInViewRange;
		m_sInViewRange.sTopLeft.nZ		= m_sPosition.nZ - m_nInViewRange;
		m_sInViewRange.sBottomRight.nX	= m_sPosition.nX - m_nInViewRange;
		m_sInViewRange.sBottomRight.nZ	= m_sPosition.nZ + m_nInViewRange;

		m_sOutViewRangle.sTopLeft.nX		= m_sPosition.nX + m_nOutViewRangle;
		m_sOutViewRangle.sTopLeft.nZ		= m_sPosition.nZ - m_nOutViewRangle;
		m_sOutViewRangle.sBottomRight.nX	= m_sPosition.nX - m_nOutViewRangle;
		m_sOutViewRangle.sBottomRight.nZ	= m_sPosition.nZ + m_nOutViewRangle;

	}

	const RectangleRange& InViewRange() const
	{
		return m_sInViewRange;
	}

	const  RectangleRange& OutViewRange() const
	{
		return m_sOutViewRangle;
	}

	bool IsListen() const
	{
		return m_bListen;
	}

	// �����޸�
	bool SetAttribute(AttributeType eAttributeType, const ValueType& vNewValue);
	bool GetAttribute(AttributeType i_eAttributeType, ValueType& o_vValue);

	// ״̬�л�
	void StatusToggle(CreatureStatus eCreatureStatus);

protected:
	

	// �����޸�
	bool SetAttribute(AttributeType eAttributeType, const ValueType& vNewValue, bool bEnforce);

protected:
	AttributeOffset								m_sAttributeOffset[ATTRIBUTE_MAX];		// ����ƫ����Ϣ

private:

	//��ʼ����Աλ��ƫ��
	virtual void InitAttributeOffet();

	// ������Ұ��Χ�޸�
	void OnInViewChange(const ValueType& vOldValue, const ValueType& vNewValue);

	// �뿪��Ұ��Χ�޸�
	void OnOutViewChange(const ValueType& vOldValue, const ValueType& vNewValue);

private:
	uint64										m_nID;									// ʵ��ID	
	Point2D										m_sPosition;							// λ������
	Vector2DEx									m_sHeading;								// ����(��֤����Ϊ��λ����)
	int32										m_nInViewRange;							// ������Ұ����
	int32										m_nOutViewRangle;						// �뿪��Ұ����
	RectangleRange								m_sInViewRange;							// ������Ұ��Χ
	RectangleRange								m_sOutViewRangle;						// �뿪��Ұ��Χ

	const bool									m_bListen;								// �Ƿ����Ƶ��
	int64										m_nChannelRegistFlag;					// ע���־
};

#endif

