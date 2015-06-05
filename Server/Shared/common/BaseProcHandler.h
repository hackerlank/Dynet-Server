#ifndef __BASE_PROC_HANDLER_H_
#define __BASE_PROC_HANDLER_H_


/*
 *
 *	Detail: �߼�������
 *   
 * Copyright (c) Created by hzd 2015-5-8.All rights reserved
 *
 */

#include "BaseDefine.h"
#include "BaseSingle.h"
#include "CommonDefine.h"
#include "BaseSession.h"
#include "../DyNetSocket/NetConfig.h"
#include "LogManager.h"
#include "ClientSession.h"

class BaseProcHandler
{
public:

	bool CheckLogin(BaseSession& pBaseSession, const LoginData2Ws& pLoginData,EServerType eServerType) 
	{
		// �����¼
		if(pBaseSession.Status() != ECLIENT_STATUS_CONNECTED)
		{
			FLOG_INFO("pBaseSession->Status() != EPLAYER_STATUS_CONNECTED");
			return false;
		}

		// ������Ҫ�����鹤������ֹ��ҵ�����

		return true;
	}
};











#endif

