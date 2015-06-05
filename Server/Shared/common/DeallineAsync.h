#ifndef __DEALINE_ASYNC_H_
#define __DEALINE_ASYNC_H_

#include "BaseDefine.h"

using namespace boost;
using namespace boost::system;
using namespace boost::asio::ip;
using namespace boost::asio;


/*
 *
 *	Detail: ���ò������ģʽ����Ϊÿһ�ֵĶ�ʱ������һ����
 *	
 *   
 *  Created by hzd 2015-6-4
 *
 */


/*
 *
 *	Detail: �첽��ʱ��
 *   
 * Copyright (c) Created by hzd 2015-6-4.All rights reserved
 *
 */

typedef boost::function<void(int32 nSrvTimes)> DeallineAsyncHandler;

class DeallineAsync : public io_service
{
public:

	/*
	 *
	 *	Detail: �ص�ʱ��(����)���������ص�����
	 *   
	 *  Created by hzd 2015-6-4
	 *
	 */
	DeallineAsync(int32 nIntervalTime,int32 nCallTimes,DeallineAsyncHandler pHander);

	~DeallineAsync();

	/*
	 *
	 *	Detail: ��ʼ����
	 *   
	 *  Created by hzd 2015-6-4
	 *
	 */
	void Start();

	/*
	 *
	 *	Detail: �����̻ص����һ��
	 *   
	 *  Created by hzd 2015-6-4
	 *
	 */
	void Cancel(); 

private:

	void DoHandler();

private:

	int32   m_nIntervalTime;	// ÿ�μ��ʱ��(����)
	int32	m_nMaxCallTimes;    // �����ô���(0���޴Σ�1��)
	int32	m_nHadCallTimes;    // �Ѿ����ô���

	DeallineAsyncHandler	m_fAsyncHandler;  // �ص�����
	deadline_timer			m_ctimer;

};



#endif

