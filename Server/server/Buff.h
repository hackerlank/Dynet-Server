#ifndef __BUFF_H_
#define __BUFF_H_

#include "CommonDefine.h"
#include "def_buff.h"
#include "ObjPool.h"

class Creature;

struct Buff
{
	Buff(const BuffData& rRes, Creature* _pFrom)
		: rResData(rRes), pFrom(_pFrom), nTimeElapse(0) {}

	const BuffData&		rResData;									// ��Դ��Ϣ
	Creature*			pFrom;										// ʩ����
	int32				nTimeElapse;								// �ѳ���ʱ��
	int32				arrReverseValue[MAX_BUFF_EFFECT_NUM];		// ����ֵ
};

void Reverse(Buff& rBuff, Creature* pOwner);

extern ObjPool<Buff> g_cBuffFactory;

#endif