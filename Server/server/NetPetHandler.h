#ifndef _NET_PET_HANDLER_H_
#define _NET_PET_HANDLER_H_

#include "NetMsgHandler.h"

/*
 *
 *	Detail: �������ӿ�
 *   
 *  Created by hzd 2014-10-2
 *
 */

/*
 *
 *	Detail: �����б�
 *   
 *  Created by hzd 2014-10-22
 *
 */
void	NetPetListHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ������ϸ��Ϣ
 *   
 *  Created by hzd 2014-10-22
 *
 */
void	NetPetInfoHandler( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: �����������Ը�ı�
 *    
 *  Created by hzd 2014-10-22
 *
 */
void	NetPetEducation( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ����ѵ�������ӳ��ﾭ�飬�����ȼ�
 *   
 *  Created by hzd 2014-10-22
 *
 */
void	NetPetTrainning( Player& rPlayer , NetMsgHead* pHead );

/*
 *
 *	Detail: ���������ĸϵ���䡢���͸ı䣬��Ҫ������
 *   
 *  Created by hzd 2014-10-22
 *
 */
 void	NetPetAdvanced( Player& rPlayer , NetMsgHead* pHead );                            

/*
 *
 *	Detail: ������졢ĸϵ�ı䣬��Ҫȫ�嵤
 *   
 *  Created by hzd 2014-10-22
 *
 */
void	NetPetVariation( Player& rPlayer , NetMsgHead* pHead );


void	NetPetAdd( Player& rPlayer , NetMsgHead* pHead );

#endif
