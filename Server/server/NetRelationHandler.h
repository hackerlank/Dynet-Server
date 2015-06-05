#ifndef NET_RELATION_HANDLER_H_
#define NET_RELATION_HANDLER_H_

#include "NetMsgHandler.h"

/*
 *
 *	Detail: �����б�
 *   
 *  Created by hzd 2014-12-11
 *
 */
void	NetRelationListHandler( Player* player , NetMsgHead* head );

/*
 *
 *	Detail: ��Ӻ���by uid or by nick
 *   
 *  Created by hzd 2014-12-11
 *
 */
void	NetRelationAddByUidsHandler( Player* player , NetMsgHead* head );

/*
 *
 *	Detail: ͨ���ǳ���Ӻ���
 *   
 *  Created by hzd 2014-12-11
 *
 */
void	NetRelationAddByNickHandler( Player* player , NetMsgHead* head );

/*
 *
 *	Detail: ɾ������
 *   
 *  Created by hzd 2014-12-11
 *
 */
void	NetRelationRemoveHandler( Player* player , NetMsgHead* head );

/*
 *
 *	Detail: ������ϸ��Ϣ
 *   
 *  Created by hzd 2014-12-11
 *
 */
void	NetRelationDetailHandler( Player* player , NetMsgHead* head );



#endif