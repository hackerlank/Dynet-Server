#ifndef DBEQUIPMENT_H
#define DBEQUIPMENT_H

#include "GameDB.h"

fvoid		DBEquipmentInit(dbResult* result);

/*
 *	����
 */
fvoid		DBEquipmentUpLevel(dbResult* result);

/*
 *	����
 */
fvoid		DBEquipmentUpStar(dbResult* result);

/*
 *	����
 */
fvoid		DBEquipmentUpStag(dbResult* result);

/*
 *	����
 */
fvoid		DBEquipmentMoveStarLevel(dbResult* result);

/*
 *	ϴ��
 */
fvoid		DBEquipmentExtendData(dbResult* result);

#endif