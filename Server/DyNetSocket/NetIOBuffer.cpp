
/*
 *
 *	Detail: �ֶ�����������
 *
 * Copyright (c) Created by hzd 2015.All rights reserved
 *
 */

#include "NetIOBuffer.h"


NetIOBuffer::NetIOBuffer():m_nBegin(0),m_nLen(0),m_pBuffer(NULL),m_nMax(0)
{
}

NetIOBuffer::~NetIOBuffer()
{
}

void NetIOBuffer::InitBuffer(uint32 nMax)
{
	m_nMax = nMax;
	if(m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
	m_pBuffer = new char[nMax];
}


void NetIOBuffer::ReleaseBuffer()
{
	if(m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

bool NetIOBuffer::Write(char* recvBuf, uint32 bodyLen)
{
	mutex::scoped_lock lock(m_cMutex);
	if(bodyLen > m_nMax - m_nBegin - m_nLen)
	{
		lock.unlock();
		return false;
	}
	memcpy(m_pBuffer + m_nBegin + m_nLen, recvBuf, bodyLen);
	m_nLen += bodyLen;
	lock.unlock();
	return true;
}


void NetIOBuffer::Read(void** pMsg, uint32 nLen)
{
	if(nLen > m_nLen)
		return;

	*pMsg = m_pBuffer + m_nBegin;
}

uint32 NetIOBuffer::ReadRemove(void* pMsg,uint32 nLen)
{
	if(!m_nLen)
		return m_nLen;
	mutex::scoped_lock lock(m_cMutex);
	int nGetLen = 0;
	if(nLen < m_nLen)
	{
		nGetLen = nLen;
	}else
	{
		nGetLen = m_nLen;
	}
	memcpy(pMsg, m_pBuffer + m_nBegin, nGetLen);
	m_nLen -= nGetLen;
	if(m_nLen == 0)
	{
		m_nBegin = 0;
	}else
	{
		m_nBegin += nGetLen;
	}
	lock.unlock();
	return nGetLen;
}


void NetIOBuffer::RemoveBuffer(uint32 nLen)
{
	mutex::scoped_lock lock(m_cMutex);
	m_nBegin += nLen;
	m_nLen -= nLen;
	if(m_nLen == 0)
		m_nBegin = 0;
	lock.unlock();
}

uint32 NetIOBuffer::GetLen()
{
	return m_nLen;
}
uint32 NetIOBuffer::GetSpace()
{
	return m_nMax - m_nBegin - m_nLen;
}
void* NetIOBuffer::GetBuffer()
{
	return m_pBuffer;
}
void* NetIOBuffer::GetStart()
{
	return m_pBuffer + m_nBegin;
}
void* NetIOBuffer::GetBufferEnd()
{
	return m_pBuffer + m_nBegin + m_nLen;
}

void NetIOBuffer::ClearBuffer()
{
	m_nBegin = 0;
	m_nLen = 0;
	memset(m_pBuffer, 0, m_nMax);
}

void NetIOBuffer::MoveBuffer()
{
	memcpy(m_pBuffer, m_pBuffer + m_nBegin, m_nLen);
	m_nBegin = m_nLen;
}




