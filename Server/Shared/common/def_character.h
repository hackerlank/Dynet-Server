#ifndef __DEF_CHARACTER_H_
#define __DEF_CHARACTER_H_

#include "CommonDefine.h"

enum CharacterType
{
	CHARACTER_TYPE_NULL		= 0,    // �Ƿ�
	CHARACTER_TYPE_SHAOLIN	= 1,	// ����
	CHARACTER_TYPE_MOJIAO	= 2,	// ħ��
	CHARACTER_TYPE_GUMU		= 3,	// ��Ĺ
	CHARACTER_TYPE_XIAOYAO	= 4,	// ��ң
};

enum CharacterConst
{
	MAX_CHARACTER_NAME_LENGTH		= 32,			// ��ɫ����󳤶�
	MAX_CHARACTER_NUM				= 8,			// ����ɫ����
};

#pragma pack(push, 1)
//
struct CharacterOperateInfo
{
	uint64			nCharacterID;						// ��ɫID
	int8			arrName[MAX_CHARACTER_NAME_LENGTH];	// ��ɫ��
	bool			bSelected;							// ��ѡ��
	CharacterType	eCharacterType;						// ��ɫ����[ְҵ]
	int32			nLevel;								// �ȼ�

	// װ���ȡ�
};

//for ws
struct CharacterData
{
	uint32 nLandMapId;			//�����ͼID
	uint32 nInstanceMapId;		//������ͼID
};

//for ss
struct CharacterDataForSS
{
	int8				arrName[MAX_CHARACTER_NAME_LENGTH];
	CharacterType		nRoleType;
	uint32				nLevel;
	uint32				nInViewDistance;
	uint32				nOutViewDistance;
	uint32				nLandMapId;
	int32				nLandMapX;
	int32				nLandMapZ;
	uint32				nInstanceMapId;
	int32				nInstanceMapX;
	int32				nInstanceMapZ;
};

//��ɫ���ϴ�������װ��
struct CharacterWearData
{
	uint64 nCharacterID; //��ɫID
	uint32 nClothesID;	//�·�ID
	uint32 nWeaponID;   //����ID
};

#pragma pack(pop)

#endif