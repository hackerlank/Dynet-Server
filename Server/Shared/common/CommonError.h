#ifndef _GAMEERROR_H_
#define _GAMEERROR_H_


#include "CommonDefine.h"

// ������

namespace error 
{

	enum
	{
	
		// ϵͳ������
		GAME_ERROR_CONFIG_NOEXIST			= 1001,		// ���ò�����
		GAME_ERROR_UID_REPEAT				= 1002,		// UID��¼�ظ�

		// �û�������
		GAME_ERROR_NOT_LOGIN				= 2001,		// δ��¼
		GAME_ERROR_PARAME_ERROR				= 2002,		// ��������%d
		GAME_ERROR_ROLE_MAX					= 2003,		// ������ɫ����������%d
		GAME_ERROR_SIGN_ERROR				= 2004,		// signֵ����
		GAME_ERROR_NOTGUEST_ID				= 2005,		// �Ƿ�ID����
		GAME_ERROR_ZONEID_ERROR				= 2006,		// zoneid����%d
		GAME_ERROR_NICK_EXIST				= 2007,		// �ý�ɫ�Ѿ�����
		GAME_ERROR_LOGIN_REPEAT				= 2008,		// �ظ������¼
		GAME_ERROR_LOGIN_OTHRE				= 2009,		// ����˺��ڱ𴦵�¼

	};

}




#endif


