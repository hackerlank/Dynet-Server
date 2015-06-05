#ifndef SWA_DB_DATABASE_H_
#define SWA_DB_DATABASE_H_

#include "DbConfig.h"
#include "DbRequest.h"
#include "DbResult.h"

#include <time.h>
#include <queue>

const ulong DB_MAX_DBACCESSTIME	= 10;
const ulong DB_MAX_STRINGSIZE	= 256;

/*
*
*	Detail: ���ݿ������
*   
*  Created by hzd 2014-10-20
*
*/
class DLLAPI DbSession : public IDbSession
{
public:

	// ���������� 
	bool Open( const char* pHost, const char* pUsernName,const char* pPassword, const char* pDBName,bool bSQLChk = true );
		
	// �ر����� 
	void Close();
	
	// �ͷ��Լ� 
	virtual	void Release();

	// �������ID 
	virtual uint32 ID();
		
	// ͬ��ִ��sql���ؽ�� 
	virtual MYSQL_RES* ExecuteRsyncSQL( const char* pszSQL );

	// ����ִ��sql�Ƽ� 
	bool ExecuteAsyncSQL( const char* pszSQL , void* pUser , SQLResultHandler pCallback );

	// ��ý���� 
	virtual DbResult* GetAsyncResult();
	
	// ��������� 
	virtual uint32 GetRequestSize();

	// ��ý���� 
	virtual uint32 GetResultSize();

	// ����������Ӷ��� 
	MYSQL* GetDBHandle();

	// �Ƿ������
	bool IsOpen();

private:

	DbSession();
	virtual ~DbSession();

	// ���sql����Ƿ�Ϸ� 
	bool CheckSQL( const char* szSQL );

	// �������ݿ� 
	MYSQL* Connect(char* szHost , char* szUser , char* szPasswd , char* szDB , uint32 nPort = MYSQL_PORT , char* szSocket = NULL , int32 nTimeout = 1000 );

	// ���ݿ��߳�ִ�е�ѭ������ 
	virtual int32 OnThreadCreate();

	// ���ݿ��߳����ٺ���
	virtual int32 OnThreadDestroy();

	// ����sqlִ�к���
	virtual int32 OnThreadProcess();

private:

	uint32	m_nID;								// ���ݿ�����ID 

	MYSQL*	m_pDbc;								// ���ݿ����Ӷ��� 
	mutex	m_cDBMutex;							// ��������� 
	mutex	m_cQueueMutex;						// ִ�ж����� 

	bool	m_bOpen;							// �Ƿ���� (һ�㲻���жϣ�����)
	char	m_arrHost[DB_MAX_STRINGSIZE];		// ���ݿ�host
	char	m_arrUser[DB_MAX_STRINGSIZE];		// ���ݿ�username
	char	m_arrPasswd[DB_MAX_STRINGSIZE];		// ���ݿ�password
	char	m_arrDBName[DB_MAX_STRINGSIZE];		// ���ݿ��� 
		
	queue<DbRequest*>	m_queAsyncSQLRequest;	// sql������� 
	queue<DbResult*>	m_queAsyncSQLResult;	// sqlִ�н������

	friend class DbSessionMgr;

};

// ���ݹ����� 
class DLLAPI DbSessionMgr 
{
	typedef std::vector<IDbSession*> DbSessionVectorType;
public:
	
	/*
	 *
	 *	Detail: ��õ���ʵ��
	 *   
	 *  Created by hzd 2015-4-21
	 *
	 */
	static DbSessionMgr* Instance();
	
	/*
		*
		*	Detail: ���һ�����ݿ�����
		*   
		*  Created by hzd 2015-1-26
		*
		*/
	IDbSession* AddDatabase( const char* szDBServer , const char* szLoginName , const char* szPassword , const char* szDBName , bool bEnableSQLChk = false );

	/*
		*
		*	Detail: ���ĳ���ݿ�����
		*   
		*  Created by hzd 2015-1-26
		*
		*/
	IDbSession* GetDatabase(uint32 nDbID);

	/*
		*
		*	Detail: �����DB(Ĭ��Ϊ��һ������)
		*   
		*  Created by hzd 2015/01/29  
		*
		*/
	IDbSession* GetMainDB();

	/*
		*
		*	Detail: ������DB
		*   
		*  Created by hzd 2015/01/29  
		*
		*/
	void SetMainDB(IDbSession& rIDataBase);

	void Update(double nDelay);

private:

	DbSessionMgr();
	
private:
	static DbSessionMgr*	s_pInstance;		// ����ʵ��
	IDbSession*				m_pMainDB;			// ��DB��һ������
	DbSessionVectorType		m_vecDbDatabase;	// ������������ 
};


#endif

