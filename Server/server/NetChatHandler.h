#ifndef _NETCHATHANDLER_H_
#define _NETCHATHANDLER_H_


class Player;
struct NetMsgHead;

/*
 *
 *	Detail: ��������
 *   
 *  Created by hzd 2014-9-27
 *
 */
void NetChatWorldMsgHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: �������졢İ���ˡ����Ѿ��ɣ�����һ����������¼�б�
 *   
 *  Created by hzd 2014-10-22
 *
 */
void NetChatPrviteMsgHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: �������졢�Լ������ڵ�����
 *   
 *  Created by hzd 2014-10-22
 *
 */
void NetChatTeamMsgHandler( Player& rPlayer , NetMsgHead* pHead );

#endif

