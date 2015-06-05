#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

#include "BaseDefine.h"

/*
 *
 *	Detail: ����������
 *   
 *  Created by hzd 2015/01/26  
 *
 */
struct GameConfigInfo
{
	char	arrServerHost[32];
	uint16	nServerPort;

	char	arrConfigPath[64];
	char	arrDbdateHost[32];
	uint16	nDbDataPort;
	char	arrDbDataDbname[32];
	char	arrDbDataUsername[32];
	char	arrDbDataPassword[32];

};

class GameConfig : public BaseSingle< GameConfig >
{
public:

	/*
	 *
	 *	Detail: ���������ļ�
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	void LoadRes( const char* path );

	/*
	 *
	 *	Detail: ��÷��������� 
	 *   
	 *  Created by hzd 2015/01/26  
	 *
	 */
	const GameConfigInfo& GetGameConfigInfo()
	{
		return m_sServerCfg;
	}

private:
	GameConfigInfo	m_sServerCfg;
};

#endif

