
#ifndef _NET_TASK_HANDLER_H_
#define _NET_TASK_HANDLER_H_


#include "NetMsgHandler.h"


// �����б�
void	NetTaskListHandler( Player& rPlayer , NetMsgHead* pHead );

// �������
void	NetTaskAcceptHandler( Player& rPlayer , NetMsgHead* pHead );

// �������(�ύ)
void	NetTaskFinishHandler( Player& rPlayer , NetMsgHead* pHead );












#endif




