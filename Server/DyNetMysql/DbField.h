#ifndef SWA_DB_FIELD_H_
#define SWA_DB_FIELD_H_

#include "DbConfig.h"

struct DLLAPI DbFieldInfo
{
	string strName;
	uint32 nType;
	uint32 nAttr;
	ulong  nLen;
};

class DLLAPI DbField : public DbIData
{
	friend class DbRecord;

public:

	DbField( const DbFieldInfo sInfo  , DbRecord& rDbRecord);
	DbField( const DbField& rField );
	virtual ~DbField();

	DbField& operator = ( const DbField& rField );

public:

	virtual void Release();
	virtual operator char() const;
	virtual operator uchar() const;
	virtual operator int16() const;
	virtual operator uint16() const;
	virtual operator int32() const;
	virtual operator uint32() const;
	virtual operator int64() const;
	virtual operator uint64() const;
	virtual operator float32() const;
	virtual operator float64() const;
	virtual operator char*() const;
	virtual operator const char*() const;

	virtual DbIData& operator = ( char chOp );
	virtual DbIData& operator = ( uchar chOp );
	virtual DbIData& operator = ( int16 nOp );
	virtual DbIData& operator = ( uint16 unOp );
	virtual DbIData& operator = ( int32 iOp );
	virtual DbIData& operator = ( uint32 uOp );
	virtual DbIData& operator = ( int64 uOp );
	virtual DbIData& operator = ( uint64 uOp );
	virtual DbIData& operator = ( float32 fltOp );
	virtual DbIData& operator = ( float64 dblOp );
	virtual DbIData& operator = ( const char* szVal );

public:

	const char* GetName() const;
	uint32 GetType() const;
	uint32 GetAttr() const;
	ulong GetLen() const;
	bool IsChanged() const;
	void TagChanged( bool bChange );
	bool SetValue( const char* pszValue );
	char* GetValue();

private:
	static void FireError();
private:

	const DbFieldInfo	m_Info;			// �ֶ���Ϣ 
	bool				m_bChanged;		// �Ƿ����ı�
	DbRecord&			m_rDbRecord;	// ���ڵ���
	uint16				m_nBufStart;	// ����buff�����ݵ���ʼλ�� 

};

#endif

