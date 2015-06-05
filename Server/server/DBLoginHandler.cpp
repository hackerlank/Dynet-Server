#include "Server_PCH.h"
#include "DBLoginHandler.h"
#include "NetLoginHandler.h"
#include "Player.h"

#include "GameDB.h"
#include "GlobalVar.h"

#include "../DyNetMysql/DbRecordSet.h"

void DBLoginRepAccount(void* pData ,const void* pDbRecordSet)
{

	Player& rPlayer = *static_cast<Player*>(pData);
	
	const DbRecordSet& rDbSet = *static_cast<const DbRecordSet*>(pDbRecordSet);
	if(rDbSet.CountRecord())
	{
		const DBAccountLoginResult& rLogin = *static_cast<const DBAccountLoginResult*>(rDbSet.GetRecordBuff(0));
		FLOG_INFO("Login successful %s",rLogin.arrUsername);
		rPlayer.SetAccountID(rLogin.nID);
		rPlayer.SetStatus(ECLIENT_STATUS_LOGINED);

		// ���Ҹ��ʺŵ����н�ɫ
		if (IDbSession* pDB = g_rDbDatabaseMgr.GetMainDB())
		{
			SPRINTF(SQL_BUFFER, "SELECT `type_idx`,`nick`,`type` FROM `swa_data`.`character` WHERE  `type_idx`=%ld AND `deleted`=0 LIMIT 4;", rLogin.nID);
			SQL_BUFFER[MAX_SQL_BUFFER - 1] = '\0';
			pDB->ExecuteAsyncSQL(SQL_BUFFER, &rPlayer, DBSelectRoleList);
			return;
		}
	}else
	{
		FLOG_INFO("Not Find This Account");
	}

}

void DBSelectRoleList(void* pData ,const void* pDbRecordSet)
{

	Player& rPlayer = *static_cast<Player*>(pData);

	const DbRecordSet& rDbSet = *static_cast<const DbRecordSet*>(pDbRecordSet);

	S2CCharacterList sMsg;
	sMsg.nCount = 0;
	for (int32 i = 0; i < rDbSet.CountRecord(); ++i)
	{
		const S2CCharacterList::CharacterInfo& rLogin = *static_cast<const S2CCharacterList::CharacterInfo*>(rDbSet.GetRecordBuff(0));
		memcpy(&(sMsg.arrCharacterList[i]),&rLogin,sizeof(S2CCharacterList::CharacterInfo));
		sMsg.nCount++;
	}

	rPlayer.SendMsg(&sMsg);
}

// ѡ���ɫ����
void DBLoginRepSelectRole(void* pData ,const void* pDbRecordSet)
{
	Player& rPlayer = *static_cast<Player*>(pData);
	const DbRecordSet& rDbSet = *static_cast<const DbRecordSet*>(pDbRecordSet);
	for (int32 i = 0 ; i < rDbSet.CountRecord(); ++i)
	{
		const DBSelectedResult& pResult = *static_cast<const DBSelectedResult*>(rDbSet.GetRecordBuff(0));

		S2CSelectedCharacterResult sMsg;
		sMsg.nResult = pResult.nRes;

		if(pResult.nRes == 1)// �ҵ� 
		{
			DBCharacherData* pCharacterData = (DBCharacherData*)(&(pResult.nCharAddr));
			sMsg.nLandId = pCharacterData->nLandId;
			rPlayer.LoadData(*pCharacterData);	// �������ݵ��ڴ�
			rPlayer.SetStatus(ECLIENT_STATUS_SELECTED);// ���
		}else // δ�ҵ� 
		{
			FLOG_INFO("Not Found The Selected Character!");
		}

		rPlayer.SendMsg(&sMsg);// ���ؽ��
		return;
	}
}

void NoDBCharacterLoadAllDataFinished(void* pData)
{

}

void DBLoginRepCreateCharacter(void* pData ,const void* pDbRecordSet)
{
	Player& rPlayer = *static_cast<Player*>(pData);
	const DbRecordSet& rDbSet = *static_cast<const DbRecordSet*>(pDbRecordSet);
	if(rDbSet.CountRecord())
	{
		const DBCreateRoleResult& rCreateResult = *static_cast<const DBCreateRoleResult*>(rDbSet.GetRecordBuff(0));

		{
			// ���ʹ�����ɫ���
			S2CCreateRoleResult sMsg;
			if(rCreateResult.nResult > 3)
			{
				sMsg.eResult = S2CCreateRoleResult::E_CREATE_RESULT_SUCCESS;
			} else
			{
				sMsg.eResult = S2CCreateRoleResult::E_CREATE_RESULT_FAIL;
				sMsg.eReason = (S2CCreateRoleResult::ECreateFailReason)rCreateResult.nResult;
			}

			rPlayer.SendMsg(&sMsg);
		}

		// �ɹ�����Ĭ��ǰ��ѡ��ý�ɫ������Ϸ
		if(rCreateResult.nResult  > 3) 
		{
			C2SSelectCharacter sMsg;
			sMsg.nID = rCreateResult.nResult;
			NetLoginSelectCharacterHandler(rPlayer,&sMsg);
			return;
		}
	}

}


