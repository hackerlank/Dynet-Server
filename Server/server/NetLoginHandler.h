#ifndef _NET_LOGIN_HANDLER_H_
#define _NET_LOGIN_HANDLER_H_

class Player;
struct NetMsgHead;

/*
 *
 *	Detail: ����Ͽ�
 *   
 *  Created by hzd 2015-1-20
 *
 */
void NetRequestClose( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ���������Կ��Ϣ
 *   
 *  Created by hzd 2014-12-10
 *
 */
void NetLoginEncryptInfoHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ��¼
 *   
 *  Created by hzd 2014-9-27
 *
 */
void NetLoginAccountHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ��ɫ�б�
 *   
 *  Created by hzd 2014-9-27
 *
 */
void NetLoginCharacterListHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ѡ���ɫ�������Ϸ
 *   
 *  Created by hzd 2014-9-27
 *
 */
void NetLoginSelectCharacterHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: �����½�ɫ
 *   
 *  Created by hzd 2014-9-27
 *
 */
void NetLoginCreateCharacterHandler( Player& rPlayer , NetMsgHead* pHead );


/*
 *
 *	Detail: ��Դ�������
 *   
 *  Created by hzd 2014-9-27
 *
 */
void NetLoginResourcesLoaded( Player& rPlayer , NetMsgHead* pHead );

#endif

