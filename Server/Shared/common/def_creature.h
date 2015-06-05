#ifndef __DEF_CREATURE_H_
#define __DEF_CREATURE_H_

#include "CommonDefine.h"

#define MAX_SPELL_CONTROL_NUM 4

enum CreatureStatus
{
	CREATURE_STATUS_NULL,

	CREATURE_STATUS_ALIVE = 0x00000001,	// ����
	CREATURE_STATUS_DEAD = 0x00000002,	// ����

	CREATURE_STATUS_DEHUANMAN	= 0x00000008,	// ������
	CREATURE_STATUS_XUANYUN		= 0x00000010,	// ѣ��
	CREATURE_STATUS_DEXUANYUN	= 0x00000020,	// ��ѣ��
	CREATURE_STATUS_HUNLUAN		= 0x00000040,	// ����
	CREATURE_STATUS_DEHUNLUAN	= 0x00000080,	// ������
	CREATURE_STATUS_DINGSHEN	= 0x00000100,	// ����
	CREATURE_STATUS_DEDINGSHEN	= 0x00000200,	// ������
	CREATURE_STATUS_CHENMO		= 0x00000400,	// ��Ĭ
	CREATURE_STATUS_DECHENMO	= 0x00000800,	// ����Ĭ
	CREATURE_STATUS_MIWU		= 0x00001000,	// ����
	CREATURE_STATUS_DEMIWU		= 0x00002000,	// ������
	CREATURE_STATUS_FUKONG		= 0x00004000,	// ����
	CREATURE_STATUS_DEFUKONG	= 0x00008000,	// ������
	CREATURE_STATUS_JIDAO		= 0x00010000,	// ����
	CREATURE_STATUS_DEJIDAO		= 0x00020000,	// ������
	CREATURE_STATUS_SHOUJI		= 0x00040000,	// �ܻ�
	CREATURE_STATUS_DESHOUJI	= 0x00080000,	// ���ܻ�
	CREATURE_STATUS_DEJITUI		= 0x00200000,	// ������
};

enum CreatureAttackType
{
	CREATURE_ATTACK_TYPE_NULL,

	CREATURE_ATTACK_TYPE_Melee		= 0x00000001,	// ��ս
	CREATURE_ATTACK_TYPE_Remote		= 0x00000002,	// Զ��
	CREATURE_ATTACK_TYPE_PHYSIC		= 0x00000004,	// ����
	CREATURE_ATTACK_TYPE_SPELL		= 0x00000008,	// ����
};

struct CreatureAttribute
{
	int32		nStatus;							// ״̬(CreatureStatus������λ����ֵ)
	int32		nLevel;								// �ȼ�

	int32		nRed;								// ��(Ѫ)
	int32		nRedMax;							// ������
	int32		nBlue;								// ��(����)
	int32		nBlueMax;							// ������

	int32		nExp;								// ����
	int32		nSpeed;								// �ٶ�
	int32		nRedRecover;						// ��ָ�
	int32		nBlueRecover;						// ���ָ�

	int32		nPhysicAttack;						// ������
	int32		nPhysicDefend;						// �������
	int32		nSpellAttack;						// ��������
	int32		nSpellDefend;						// ��������

	int32		nWuli;								// ����(�����ڼӳɺ���ʾ)
	int32		nShenshou;							// ����(�����ڼӳɺ���ʾ)
	int32		nNeili;								// ����(�����ڼӳɺ���ʾ)

	int32		nAttackType;						// ��������(CreatureAttackType�������������ֵ)

	int32		nMingzhonglv;						// ������
	int32		nShanbilv;							// ������
	int32		nBaoji;								// ����
	int32		nBaojilv;							// ������
	int32		nGedang;							// ����
	int32		nGedanglv;							// ������

	int32		nDeAttack;							// ���������˺�����
	int32		nDeMeleeAttack;						// ��ս�˺�����
	int32		nDeRemoteAttack;					// Զ���˺�����
	int32		nDeSpellCD;							// ����CD����

	int32		nAttackRedRecover;					// ���к�ָ�
	int32		nAttackBlueRecover;					// �������ָ�
};

struct SpellData
{
	uint32 nSpellID;	// ����ID
	int32 nPosition;    // Я��λ�� (-1δЯ��,0 - 4 Я���ڶ�Ӧ��λ����)
};

#endif