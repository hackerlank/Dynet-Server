#ifndef __COMMON_F2C_H_
#define __COMMON_F2C_H_

#include "CommonDefine.h"

enum EProF2C
{

	PRO_F2C_ENCRYPT_INFO			= PRO_F2C_BASE + 0,	// ������Կ��Ϣ
	PRO_F2C_LOGIN_READY_FINISH		= PRO_F2C_BASE + 1, // �������Լ�����¼����׼�����

};

#pragma pack(push, 1)


// ������Կ
struct F2CEncryptInfo : public NetMsgHead
{
	F2CEncryptInfo():NetMsgHead(PRO_F2C_ENCRYPT_INFO)
	{
		
	}
	char arrEncryptKey[MAX_ENCRYPT_LENTH];
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct F2CLoginReadyFinish : public NetMsgHead
{
	F2CLoginReadyFinish():NetMsgHead(PRO_F2C_LOGIN_READY_FINISH)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


#pragma pack(pop) 

#endif