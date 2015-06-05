#ifndef _GAMEDB_H_
#define _GAMEDB_H_

/*
 *
 *	Detail: �󲿷����ݣ�ֱ����mysql�򽻵���player������ݣ�ֻ�ǻ��棬����ÿ�δ�mysql�ж�ȡ����player��ֻ�ǻ��治̫��Ҫ������
 *  �Ͽ�����Ҳ�ᱣ�沿����Ҫ������
 *   
 *  Created by hzd 2014-10-7
 *
 */

const int32 MAX_SQL_BUFFER = 512;
extern char SQL_BUFFER[ MAX_SQL_BUFFER ];

#pragma pack(push,1)

// ƽ̨�˺ŵ�¼��� 
struct DBAccountLoginResult
{
	uint32 nID;
	char  arrUsername[32];
};

// ��ɫ������� 
struct DBCreateRoleResult
{
	uint64 nResult; // 1-3ʧ�ܣ�> 3 �ɹ���Ϊ��ɫID
};

struct DBSelectedResult
{
	int32 nRes;//0ʧ�ܣ����������Ч,1�ɹ������������Ч
	int32 nCharAddr; // ��ɫ��Ϣ���׵�ַ
};

struct DBCharacherData
{
	uint64 nUID;
	char arrNick[32];
	int32 nType;
	int32 nLevel;
	int32 nLandId;
	int32 nLandX;
	int32 nLandY;
};

#pragma pack(pop)


#endif

