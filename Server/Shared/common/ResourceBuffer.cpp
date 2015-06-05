#include "ResourceBuffer.h"


ResourceBuffer::ResourceBuffer(const std::string& strFileName, uint32 nFlagsRow, uint32 nDataStartRow)
	: m_nFlagsRow(nFlagsRow), m_nDataStartRow(nDataStartRow), m_nCurrRowIndex(0), m_bValid(false), m_nCol(0), m_nUseColCount(0)
{
	if (load(strFileName.c_str()) && readFlagsRow() && NextRow())
	{
		m_bValid = true;
	}
}

ResourceBuffer::~ResourceBuffer()
{
	if (m_cFileStream.is_open())
		m_cFileStream.close();
}

bool ResourceBuffer::NextRow(int32 nLines)
{
	for (int32 i = 0; i < nLines; ++i)
	{
		m_nCol = 0;
		m_strLine.clear();
		m_vecCol.clear();

		if (std::getline(m_cFileStream, m_strLine))
		{
			if (m_strLine.empty())
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	if(strlen(m_strLine.c_str()) == 0 || strcmp(m_strLine.c_str(),"\n") == 0 || strcmp(m_strLine.c_str(),"\t") == 0 || strcmp(m_strLine.c_str(),"\r") == 0)
	{
		return false;
	}

	analyseLine(m_strLine, m_vecCol);

	if(m_vecCol.size() < 1)
	{
		return false;
	}
	return true;
}

bool ResourceBuffer::GetInt8(int8& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<int8>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetUInt8(uint8& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint8>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetInt16(int16& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<int16>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetUInt16(uint16& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint16>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetInt32(int32& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = atoi(m_vecCol[m_nCol - 1].c_str());
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetUInt32(uint32& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint32>(ATOL(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetInt64(int64& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = ATOL(m_vecCol[m_nCol - 1].c_str());
			return true;
		}
	}

	return false;
}

bool ResourceBuffer::GetFloat32(float32& o_fValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_fValue = ATOF(m_vecCol[m_nCol - 1].c_str());
			return true;
		}
	}
	return false;
}


bool ResourceBuffer::GetString(std::string& o_strValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_strValue = m_vecCol[m_nCol - 1];
			return true;
		}
	}

	return false;
}

const char* ResourceBuffer::GetCString()
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			return m_vecCol[m_nCol - 1].c_str();
		}
	}

	return 0;
}

bool ResourceBuffer::load(const char* cstrFileName)
{
	m_cFileStream.open(cstrFileName, std::ios::in);

	if (!m_cFileStream.is_open()	||
		m_cFileStream.fail()		||
		m_cFileStream.bad())
	{
		return false;
	}

	return true;
}

bool ResourceBuffer::readFlagsRow()
{
	m_vecFlags.clear();
	m_nUseColCount = 0;

	// ����ǰ���в���ȡ��־��
	if (!NextRow(m_nFlagsRow))
	{
		return false;
	}

	// ���ñ����
	for (uint32 i = 0; i < m_vecCol.size(); ++i)
	{
		switch (m_vecCol[i].c_str()[0])
		{
		case '2':
		case '3':
		{
			m_vecFlags.push_back(true);
			++m_nUseColCount;
		} break;
		default:
		{
			m_vecFlags.push_back(false);
		} break;
		}
	}

	return true;
}

void ResourceBuffer::analyseLine(const std::string& i_strLine, std::vector<std::string>& o_vecCol)
{
	o_vecCol.resize(0);

	std::string col;
	std::stringstream ss(i_strLine);

	while (true)
	{
		col.clear();
		ss >> col;
		if (col.empty())
		{
			break;
		}
		m_vecCol.push_back(col);
	}
}