#ifndef NET_PACK_HANDLER_H_
#define NET_PACK_HANDLER_H_

#include "NetMsgHandler.h"

/*
 *
 *	Detail: ��������
 *   
 *  Created by hzd 2014-12-9
 *
 */
void	NetPackReorganizeHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ����λ��
 *   
 *  Created by hzd 2014-12-9
 *
 */
void	NetPackExchangePosition( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ��������
 *   
 *  Created by hzd 2014-12-9
 *
 */
void	NetPackOpenGrid( Player& rPlayer , NetMsgHead* pHead );

#endif

