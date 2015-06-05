#ifndef __COMMON_C2F_H_
#define __COMMON_C2F_H_

#include "CommonDefine.h"

enum EProC2F
{

	PRO_C2F_ENCRYPT		= PRO_C2F_BASE + 0, // �����Կ
	PRO_C2F_CLOSE		= PRO_C2F_BASE + 1, // �����˳�
	

};


#pragma pack(push,1)

// ���ͼ������� 
struct C2FepEncryptInfo : public NetMsgHead
{
	C2FepEncryptInfo():NetMsgHead(PRO_C2F_ENCRYPT)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2FepClose : public NetMsgHead
{
	C2FepClose():NetMsgHead(PRO_C2F_CLOSE)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)





#endif