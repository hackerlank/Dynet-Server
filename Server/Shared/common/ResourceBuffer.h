#ifndef __RESOURCE_BUFFER_H_
#define __RESOURCE_BUFFER_H_

// stl include
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// self include
#include "typedef.h"


/*
* ����ָ��ָ����������Դ�ļ�
*/
class ResourceBuffer
{
public:
	ResourceBuffer(const std::string& strFileName, uint32 nFlagsRow = 4, uint32 nDataStartRow = 6);

	~ResourceBuffer();

	/*
	* ��ȡ��ǰ�к���ĵ�nLines��
	*/
	bool NextRow(int32 nLines = 1);

	/*
	* ������ݿ�
	*/
	bool			GetInt8(int8& o_nValue);
	bool			GetUInt8(uint8& o_nValue);
	bool			GetInt16(int16& o_nValue);
	bool			GetUInt16(uint16& o_nValue);
	bool			GetInt32(int32& o_nValue);
	bool			GetUInt32(uint32& o_nValue);
	bool			GetInt64(int64& o_nValue);
	bool			GetFloat32(float32& o_fValue);
	bool			GetString(std::string& o_strValue);
	const char*		GetCString();

	// ��������
	int32 UseColCount()
	{
		return m_nUseColCount;
	}

	// �Ƿ����
	bool Valid()
	{
		return m_bValid;
	}

private:
	/*
	* ����Դ�ļ�
	*/
	bool load(const char* cstrFileName);

	/*
	* ��ʼ����־��
	*/
	bool readFlagsRow();

	/*
	* ����һ������
	*/
	void analyseLine(const std::string& i_strLine, std::vector<std::string>& o_vecCol);

private:
	int32						m_nFlagsRow;		// ��־��(1:��������ȡ,2:��ȡ,3:��ȡ)
	int32						m_nDataStartRow;	// ������ʼ��
	uint32						m_nCurrRowIndex;	// ��ǰ��ȡ������[0,xx)

	bool						m_bValid;			// �ļ��Ƿ����
	std::ifstream				m_cFileStream;		// �ļ�������
	std::vector<bool>			m_vecFlags;			// �п���״̬

	std::string					m_strLine;			// ��ǰ��ȡ��
	std::vector<std::string>	m_vecCol;			// ��ǰ��ȡ�и���ֵ
	uint32						m_nCol;				// ��ǰ��ȡ��������
	int32						m_nUseColCount;		// ����������
};

#endif