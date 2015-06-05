#ifndef __COMMON_W2D_H_
#define __COMMON_W2D_H_


#include "CommonDefine.h"
#include "../DyNetSocket/NetConfig.h"


//-----------------------600~699-----------------

enum EProWS2DP
{
	PRO_W2DP_LOGINED = 600, // ��¼���
};

#pragma pack(push,1)

struct WS2DPLogined : public NetMsgHead
{

	WS2DPLogined() :NetMsgHead(PRO_W2DP_LOGINED)
	{

	}
	enum
	{
		SUCCESS,
		FAIL,
	};
	int32 nResult; // 0 �ɹ�,����ʧ��
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)


#endif