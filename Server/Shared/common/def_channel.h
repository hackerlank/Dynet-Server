#ifndef __DEF_CHANNEL_H_
#define __DEF_CHANNEL_H_

#include <vector>

#include "Geometry2D.h"
#include "def_entity.h"


enum ChannelRegistType
{
	CHANNEL_REGIST_TYPE_NULL				= 0x0000000,	// ��
	CHANNEL_REGIST_TYPE_POSITION_BROADCAST	= 0x00000001,	// λ����Ϣ�㲥
	CHANNEL_REGIST_TYPE_POSITION_COLLECT	= 0x00000002,	// λ����Ϣ�ռ�
	CHANNEL_REGIST_TYPE_CREATURE_BROADCAST	= 0x00000004,	// ��������Ϣ�㲥
	CHANNEL_REGIST_TYPE_CREATURE_COLLECT	= 0x00000008,	// ��������Ϣ�ռ�
	CHANNEL_REGIST_TYPE_EQUIPMENT_BROADCAST = 0x00000010,   // װ���㲥
	CHANNEL_REGIST_TYPE_EQUIPMENT_COLLECT	= 0x00000020,   // װ���ռ�
	CHANNEL_REGIST_TYPE_SPELL_BROADCAST		= 0x00000040,	// ���ܹ㲥
	CHANNEL_REGIST_TYPE_SPELL_COLLECT		= 0x00000080,   // �����ռ�
	CHANNEL_REGIST_TYPE_BUFF_BROADCAST		= 0x00000100,	// Buff��Ϣ�㲥	
	CHANNEL_REGIST_TYPE_BUFF_COLLECT		= 0x00000200,	// Buff��Ϣ�ռ�
	CHANNEL_REGIST_TYPE_MAX
};

enum 
{
	MAX_CHANNEL_BUFF		= 15,	// ���Buff����	
	MAX_CHARACTER_NAME_LENGTH_C = 32 ,
};

enum
{
	MAX_POSITION_COUNT = 100, // ���ɴ���ܱ����λ������
	MAX_CREATURE_COUNT = 100, // ���ɴ���ܱ������������
};

#pragma pack(push,1)


// λ����Ϣ
struct ChannelPosition
{
	uint64			nID;			//ʵ��ID
	EntityType		nType;			//ʵ������
	uint32			nTypeID;		//ʵ��������ID
	int32			nPositionX;		//λ��x
	int32			nPositionZ;		//λ��z
	int32			nHeadingX;		//����X�Ѿ�������100
	int32			nHeadingZ;		//����X�Ѿ�������100
};

// ��������Ϣ
struct ChannelCreature
{
	uint64		nID;									// ʵ��ID
	int8		arrName[MAX_CHARACTER_NAME_LENGTH_C];	//�ǳ�
	int32		nRed;									// ��(Ѫ)
	int32		nRedMax;								// ������
	int32		nBlue;									// ��(����)
	int32		nBlueMax;								// ������
};

// װ����Ϣ
struct ChannelWear
{
	uint64		nID;				//ʵ��ID
	uint32		nClothesID;			//�·�ID
	uint32		nWeaponID;			//����װ��ID
};

// ������Ϣ
struct ChannelSpell
{
	uint64		nID;			// ʵ��ID
	uint32      nSpellID;		// ����ID
};

// Buff��Ϣ
struct ChannelBuff
{
	uint32		nNum;							// Buff����
	uint64		nID;							// ʵ��ID
	uint32		arrBuffID[MAX_CHANNEL_BUFF];    // BuffID 
};

#pragma pack(pop)

#define FUNCTION_CHANNEL_BROADCAST(InfoType)\
virtual void ChannelBroadcast(const std::set<const InfoType*>& rsetValues) {}
#define DEFINE_FUNCTION_CHANNEL_BROADCAST(InfoType)\
virtual void ChannelBroadcast(const std::set<const InfoType*>& rsetValues);
#define IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(ClassName, InfoType)\
void ClassName::ChannelBroadcast(const std::set<const InfoType*>& rsetValues)

#define FUNCTION_CHANNEL_COLLECT(InfoType)\
typedef const InfoType* P##InfoType;\
virtual void ChannelCollect(P##InfoType& o_rpInfo) { \
o_rpInfo = &m_s##InfoType; }
#define DEFINE_FUNCTION_CHANNEL_COLLECT(InfoType)\
virtual void ChannelCollect(P##InfoType& o_rpInfo);
#define IMPLEMENT_FUNCTION_CHANNEL_COLLECT(ClassName, InfoType)\
void ClassName::ChannelCollect(P##InfoType& o_rpInfo)


#endif