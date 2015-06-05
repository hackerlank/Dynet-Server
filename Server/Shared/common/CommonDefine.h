
#ifndef PROTOCOL_DEFIEN_H_
#define PROTOCOL_DEFIEN_H_

#include "BaseDefine.h"
#include "../DyNetSocket/NetConfig.h"

#ifndef __COMMONDEF_H_
#define __COMMONDEF_H_

#include <memory>
union ValueType
{
	ValueType()
	{
		memset(this, 0, sizeof(*this));
	}

	template<typename T>
	ValueType(T v)
	{
		if (!(sizeof(*this) < sizeof(T)))
		{
			memcpy(this, &v, sizeof(T));
		}
	}
	int8	nInt8;
	int16	nInt16;
	int32	nInt32;
	int64	nInt64;
	uint8	nUint8;
	uint16	nUint16;
	uint32	nUint32;
	uint64	nUint64;
	float32	fFloat;
};

#endif


typedef vector< string > StringVector;
typedef vector< string >::iterator StringIter;

typedef vector< int32 > IntVector;
typedef vector< int32 >::iterator IntIter;

#define EncryptDefualt "1234567890ABCDEFGHIJKLMNOPQSRTWX"
#define RUN_PRINT_TIMES 2000

// 



/*���ó�������*/
enum 
{
	MAX_ACCOUNT_LENG				= 32,	// ƽ̨�˺���󳤶�
	MAX_PASSWORD_LENG				= 32,   // ƽ̨������󳤶�
	MAX_NICK_LENGTH					= 32,	// �ǳ���󳤶�
	MAX_ROLE_TYPE_COUNT				= 4,	// һ��ƽ̨�ʺ������������ɫ����
	MAX_CHAT_MSG_LENGTH				= 128,	// ����������󳤶�
	MAX_ENCRYPT_LENTH				= 32,	// ��Կ����
	MAX_SERVERINFO_LIST				= 32,   // ������������(��ws��)
};

//�ͻ��˵�ǰ״̬
enum ClientStatus
{
	CS_INVALID  = 0,
	CS_LOGIN_ING,			//	��¼��
	CS_LOGIN_OK	,			//	��¼���
	CS_REGISTER_ING,		//  ע����
	CS_REGISTER_OK,			//	ע��ɹ�
	CS_LOADDATA_ING,		//	��ʼ��������
	CS_LOADDATA_OK,			//	��ʼ���������
	CS_IN_GAME	,			//	������Ϸ(ѡ���ע���ɫ��)
	CS_RES_OK	,			//	ǰ����Դ�������
};


template <typename T> void Swap(T*  obj1,T* obj2)  
{  
	unsigned char * pObj1 = reinterpret_cast<unsigned char *>(obj1);  
	unsigned char * pObj2 = reinterpret_cast<unsigned char *>(obj2);  
	for (unsigned long x = 0; x < sizeof(T); ++x)  
	{  
		pObj1[x] ^= pObj2[x];  
		pObj2[x] ^= pObj1[x];  
		pObj1[x] ^= pObj2[x];  
	}  
}

// ���������Ͷ���
enum EServerType
{
	ESERVER_TYPE_NULL	= 0,
	ESERVER_TYPE_FEP	= 1,
	ESERVER_TYPE_LS		= 2,
	ESERVER_TYPE_WS		= 3,
	ESERVER_TYPE_SS		= 4,
	ESERVER_TYPE_DP		= 5,
	ESERVER_TYPE_MAX,
};

#pragma pack(push,1)

// �����¼��ws��ͨ�����ݽṹ
struct LoginData2Ws
{
	LoginData2Ws()
	{
	}
	char arrServerAddr[32]; // ��������ַ 
	int32 nServerPort;		// �˿�
	int32 nServerID;		// ��������ʶID
};

// ��������Ϣ
struct ServerInfoData
{
	ServerInfoData()
	{
		memset(this,0,sizeof(*this));
	}
	char arrHosrt[32];
	int32 nPort;
	int32 nServerType;
	int32 nServerID;
};

typedef std::vector<ServerInfoData> ServerInfoDataVecType;


// Э��ŷ�Χ����

enum 
{
	// �ڲ�Э��server��server֮ǰ��ͨ��ͨ��Э��
	PRO_INTERNAL_BASE = 100,

	// �̶�ֵ(1)+����form+����to+��λ�Զ���
	PRO_C2F_BASE = 10100,
	PRO_C2L_BASE = 10200,
	PRO_C2W_BASE = 10300,
	PRO_C2S_BASE = 10400,
	
	PRO_F2C_BASE = 11000,
	PRO_F2L_BASE = 11200,
	PRO_F2W_BASE = 11300,
	PRO_F2S_BASE = 11400,

	PRO_L2C_BASE = 12000,
	PRO_L2F_BASE = 12100,
	PRO_L2W_BASE = 12300,
	PRO_L2D_BASE = 12500,

	PRO_W2C_BASE = 13000,
	PRO_W2F_BASE = 13100,
	PRO_W2L_BASE = 13200,
	PRO_W2S_BASE = 13400,
	PRO_W2D_BASE = 13500,

	PRO_S2C_BASE = 14000,
	PRO_S2L_BASE = 14100,
	PRO_S2W_BASE = 14300,
	PRO_S2D_BASE = 14500,

	PRO_D2L_BASE = 15200,
	PRO_D2W_BASE = 15300,
	PRO_D2S_BASE = 15400,

};



#pragma pack(pop)


#endif