#ifndef _DBLOGINHANDLER_H_
#define _DBLOGINHANDLER_H_


class Player;

using namespace SWA;

// ��¼ƽ̨�˺ŷ���
void DBLoginRepAccount(void* pData ,const void* pDbRecordSet);


// ������ɫ
void DBLoginRepCreateCharacter(void* pData ,const void* pDbRecordSet);

// ���ؽ�ɫ�б�
void DBSelectRoleList(void* pData ,const void* pDbRecordSet);

// ѡ���ɫ���� 
void DBLoginRepSelectRole(void* pData ,const void* pDbRecordSet);

// ���������еĽ�ɫ���ݻص�
void NoDBCharacterLoadAllDataFinished(void* pData);

#endif



