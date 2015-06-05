#include "Server_PCH.h"
#include "SceneRegion.h"

#include <assert.h>

#include "Entity.h"
#include "SceneChannel.h"
#include "GlobalVar.h"

ObjPool<SceneRegion> SceneRegionManager::s_cSceneRegionFactory;

using namespace std;

SceneRegion::SceneRegion(const Rectangle2D& rRange)
: m_sScope(rRange)
{

}

// ע�᱾����Ƶ��
void SceneRegion::RegistReceiveChannels(IChannelRegist& rEntity)
{
	//��ʵ��ע���Ӧ��Ƶ��
	for(int32 i = 0; i < m_vecChannels.size(); ++i)
	{
		m_vecChannels[i]->RegistReceiver(rEntity);
	}
	std::cout << "ע�������������:xz(" << m_sScope.sTopLeft.nX << "," << m_sScope.sTopLeft.nZ << "),(" << m_sScope.sBottomRight.nX << "," << m_sScope.sBottomRight.nZ << ")" << std::endl;
}

// ȡ��ע���ռ���Ϣ
void SceneRegion::CancelReceiveChannels(IChannelRegist& rEntity)
{
	//ȡ����Ӧ��ע��
	for(int32 i = 0; i < m_vecChannels.size(); ++i)
	{
		m_vecChannels[i]->CancelReceiver(rEntity);
	}
	std::cout << "ȡ������������:xz(" << m_sScope.sTopLeft.nX << "," << m_sScope.sTopLeft.nZ << "),(" << m_sScope.sBottomRight.nX << "," << m_sScope.sBottomRight.nZ << ")" << std::endl;
}

void SceneRegion::RegistBroadcasterChannels(IChannelRegist& rEntity)
{
	for(int32 i = 0; i < m_vecChannels.size(); ++i)
	{
		m_vecChannels[i]->RegistBroadcaster(rEntity);
	}
	std::cout << "ע��㲥������:xz(" << m_sScope.sTopLeft.nX << "," << m_sScope.sTopLeft.nZ << "),(" << m_sScope.sBottomRight.nX << "," << m_sScope.sBottomRight.nZ << ")" << std::endl;
}

void SceneRegion::CancelBroadcasterChannels(IChannelRegist& rEntity)
{
	for(int32 i = 0; i < m_vecChannels.size(); ++i)
	{
		m_vecChannels[i]->CancelBroadcaster(rEntity);
	}
	std::cout << "ȡ���㲥������:xz(" << m_sScope.sTopLeft.nX << "," << m_sScope.sTopLeft.nZ << "),(" << m_sScope.sBottomRight.nX << "," << m_sScope.sBottomRight.nZ << ")" << std::endl;
}

//����Ƶ��
void SceneRegion::AddChannel(Channel& rChannel)
{
	m_vecChannels.push_back(&rChannel);
	g_rSceneChannelManager.AddSceneChannel(rChannel);
}

// ����ʵ��
void SceneRegion::AddEntity(Entity& rEntity)
{
	std::set<Entity*>::iterator it = m_setEntities.find(&rEntity);
	if(it == m_setEntities.end())
	{
		m_setEntities.insert(&rEntity);
	}
	RegistBroadcasterChannels(rEntity);
}

// �Ƴ�ʵ��
void SceneRegion::DelEntity(Entity& rEntity)
{
	m_setEntities.erase(&rEntity);
	CancelBroadcasterChannels(rEntity);
}

// ����Ƿ���������
bool SceneRegion::InScope(const Point2D& rPosition)
{
	return CheckInside(rPosition, m_sScope);
}

const set<Entity*> SceneRegion::GetEntities()
{
	return m_setEntities;
}

SceneRegionManager::SceneRegionManager(Point2D sTopLeftCoordinate, int32 nXAmount, int32 nZAmount, int32 nXCellLength, int32 nZCellLength,
									   const vector<vector<bool>>& vecUseableInfo)
									   : m_nXAmount(nXAmount), m_nZAmount(nZAmount), m_nXCellLength(nXCellLength), m_nZCellLength(nZCellLength)
{
	assert(vecUseableInfo.size() == nZAmount && vecUseableInfo[0].size() == nXAmount);

	// ��ʼ����������
	m_vecRegions.resize(nZAmount);
	for(int32 iz = 0; iz < nZAmount; ++iz)
	{
		for(int32 ix = 0; ix < nXAmount; ++ix)
		{
			if(vecUseableInfo[iz][ix])
			{
				Rectangle2D sScope(sTopLeftCoordinate.nZ - iz * nZCellLength,
								   sTopLeftCoordinate.nX + ix * nXCellLength,
								   sTopLeftCoordinate.nZ - (iz + 1) * nZCellLength + 1,
								   sTopLeftCoordinate.nX + (ix + 1) * nXCellLength - 1);
				m_vecRegions[iz].push_back(s_cSceneRegionFactory.CreateObj(sScope));
			} else
			{
				m_vecRegions[iz].push_back(0);
			}
		}
	}

	//�������е�Ƶ��
	vector<Channel*> vecChannels;
	for(int32 iz = 0; iz < nZAmount; ++iz)
	{
		for(int32 ix = 0; ix < nXAmount; ++ix)
		{
			vecChannels.clear();
			if(m_vecRegions[iz][ix])
			{
				// λ����ϢƵ��
				if(Channel* pChannel = g_cPositionChannelFactory.CreateObj(CHANNEL_REGIST_TYPE_POSITION_BROADCAST, CHANNEL_REGIST_TYPE_POSITION_COLLECT))
					m_vecRegions[iz][ix]->AddChannel(*pChannel);

				// ��������Ϣ
				if(Channel* pChannel = g_cCreatureChannelFactory.CreateObj(CHANNEL_REGIST_TYPE_CREATURE_BROADCAST, CHANNEL_REGIST_TYPE_CREATURE_COLLECT))
					m_vecRegions[iz][ix]->AddChannel(*pChannel);

				// ������ϢƵ��
				if(Channel* pChannel = g_cSpellChannelFactory.CreateObj(CHANNEL_REGIST_TYPE_SPELL_BROADCAST, CHANNEL_REGIST_TYPE_SPELL_COLLECT))
					m_vecRegions[iz][ix]->AddChannel(*pChannel);

				//TODO Buff��Ϣ

			}
		}
	}

	// ������Χ
	m_sScope.sTopLeft = sTopLeftCoordinate;
	m_sScope.sBottomRight.nX = m_sScope.sTopLeft.nX + nXAmount * nXCellLength - 1;
	m_sScope.sBottomRight.nZ = m_sScope.sTopLeft.nZ - nZAmount * nZCellLength + 1;

}

SceneRegionManager::~SceneRegionManager()
{
	for(int32 iz = 0; iz < m_nZAmount; ++iz)
	{
		for(int32 ix = 0; ix < m_nXAmount; ++ix)
		{
			if(SceneRegion* pSceneRegion = m_vecRegions[iz][ix])
			{
				s_cSceneRegionFactory.DestroyObj(pSceneRegion);
			}
		}
	}
}

// ��ӳ���ʵ��
void SceneRegionManager::AddSceneEntity(Entity& rEntity)
{
	if(SceneRegion* pInRegion = GetBelongRegion(rEntity.Position()))
	{
		// ��ӵ���������
		pInRegion->AddEntity(rEntity);

		{// ע������������

			// �����ཻ����
			set<SceneRegion*> collisionRegions;
			GetCollisionRegion(rEntity.InViewRange(), collisionRegions);

			if(rEntity.IsListen())
			{
				set<SceneRegion*>::iterator it = collisionRegions.begin();
				set<SceneRegion*>::iterator it_end = collisionRegions.end();
				for(; it != it_end; ++it)
				{
					(*it)->RegistReceiveChannels(rEntity);
				}
			}

			// ��ӹ�����Ϣ
			m_umapEntityRegions.insert(make_pair(&rEntity, pair<SceneRegion*, set<SceneRegion*>>(pInRegion, collisionRegions)));
		}
	}
}

// ɾ������ʵ��
void SceneRegionManager::DelSceneEntity(Entity& rEntity)
{
	EntitySceneRegionCollectUMapType::iterator it = m_umapEntityRegions.find(&rEntity);
	if(it == m_umapEntityRegions.end())
		return;

	// ȡ������������
	if(rEntity.IsListen())
	{
		set<SceneRegion*>::iterator region_it = it->second.second.begin();
		set<SceneRegion*>::iterator region_it_end = it->second.second.end();
		for(; region_it != region_it_end; ++region_it)
		{
			(*region_it)->CancelReceiveChannels(rEntity);
		}
	}

	//ɾ�����ڵ�����
	it->second.first->DelEntity(rEntity);

	// �Ƴ�������Ϣ
	m_umapEntityRegions.erase(it);
}

// ����Ƶ��ע�ᡢ���������е�ʵ�弯��
void SceneRegionManager::Update()
{
	EntitySceneRegionCollectUMapType::iterator it = m_umapEntityRegions.begin();
	EntitySceneRegionCollectUMapType::iterator it_end = m_umapEntityRegions.end();

	//����ʵ��λ�ø��£��Լ������ľ���ָ��
	for(; it != it_end; ++it)
	{
		Entity* pEntity = it->first;
		SceneRegion* pLastBelongRegion = it->second.first;
		set<SceneRegion*>& rOldCollistionRegions = it->second.second;

		//�����������ָ���Ƿ�ı䣬���ı������
		if(!pLastBelongRegion->InScope(pEntity->Position()))
		{
			// ��ӵ���������
			if(SceneRegion* pNewBelongRegion = GetBelongRegion(pEntity->Position()))
			{
				// �Ӿ�������ɾ��
				pLastBelongRegion->DelEntity(*pEntity);
				std::cout << "ʵ���뿪:" << pEntity->ID() << "xz(" << pLastBelongRegion->m_sScope.sTopLeft.nX << "," << pLastBelongRegion->m_sScope.sTopLeft.nZ << "),(" << pLastBelongRegion->m_sScope.sBottomRight.nX << "," << pLastBelongRegion->m_sScope.sBottomRight.nZ << ")" << std::endl;

				// �����µ���������
				pNewBelongRegion->AddEntity(*pEntity);
				std::cout << "ʵ�����:" << pEntity->ID() << "xz(" << pNewBelongRegion->m_sScope.sTopLeft.nX << "," << pNewBelongRegion->m_sScope.sTopLeft.nZ << "),(" << pNewBelongRegion->m_sScope.sBottomRight.nX << "," << pNewBelongRegion->m_sScope.sBottomRight.nZ << ")" << std::endl;

				//�뿪����������
				{
					// �����ཻ����
					set<SceneRegion*> newCollisionRegions;
					GetCollisionRegion(pEntity->OutViewRange(), newCollisionRegions);

					static vector<SceneRegion*> vecLeaveRegions;
					vecLeaveRegions.resize(rOldCollistionRegions.size());
					vector<SceneRegion*>::iterator retEndPosTmp;

					retEndPosTmp = set_difference(rOldCollistionRegions.begin(), rOldCollistionRegions.end(), newCollisionRegions.begin(), newCollisionRegions.end(), vecLeaveRegions.begin());

					for(vector<SceneRegion*>::iterator iter = vecLeaveRegions.begin(); iter != retEndPosTmp; ++iter)
					{
						(*iter)->CancelReceiveChannels(*pEntity);
					}
				}

				{//����������
					// �����ཻ����
					set<SceneRegion*> newCollisionRegions;
					GetCollisionRegion(pEntity->OutViewRange(), newCollisionRegions);

					static vector<SceneRegion*> vecNewRegions;
					vecNewRegions.resize(newCollisionRegions.size());
					vector<SceneRegion*>::iterator retEndPosTmp;

					retEndPosTmp = set_difference(newCollisionRegions.begin(), newCollisionRegions.end(), rOldCollistionRegions.begin(), rOldCollistionRegions.end(), vecNewRegions.begin());

					for(vector<SceneRegion*>::iterator iter = vecNewRegions.begin(); iter != retEndPosTmp; ++iter)
					{
						(*iter)->RegistReceiveChannels(*pEntity);

					}

					// ���¹�����Ϣ
					it->second.first = pNewBelongRegion;
					it->second.second = newCollisionRegions;
				}

			}
		}
	}

}

SceneRegion* SceneRegionManager::GetSceneRegion(int32 nZIndex, int32 nXIndex) const
{
	if(nZIndex < m_nZAmount && nXIndex < m_nXAmount)
	{
		return m_vecRegions[nZIndex][nXIndex];
	}
	return 0;
}

void SceneRegionManager::GetCollisionRegion(const Rectangle2D& i_rSrcRange, std::set<SceneRegion*>& o_setCollisionRegions)
{
	o_setCollisionRegions.clear();

	// �ཻ����
	Rectangle2D sIntersectRegion;
	if(GetIntersect(m_sScope, i_rSrcRange, sIntersectRegion))
	{
		int32 nXStart = (m_sScope.sTopLeft.nX - sIntersectRegion.sTopLeft.nX /*+ 1 - 1*/) / m_nXCellLength;
		int32 nZStart = (sIntersectRegion.sTopLeft.nZ - m_sScope.sTopLeft.nZ /*+ 1 - 1*/) / m_nZCellLength;
		int32 nXEnd = (m_sScope.sTopLeft.nX - sIntersectRegion.sBottomRight.nX /*+ 1 - 1*/) / m_nXCellLength + 1;
		int32 nZEnd = (sIntersectRegion.sBottomRight.nZ - m_sScope.sTopLeft.nZ /*+ 1 - 1*/) / m_nZCellLength + 1;

		for(int32 nZ = nZStart; nZ < nZEnd; ++nZ)
		{
			for(int32 nX = nXStart; nX < nXEnd; ++nX)
			{
				if(SceneRegion* pRegion = GetSceneRegion(nZ, nX))
				{
					o_setCollisionRegions.insert(pRegion);
				}
			}
		}
	}
}


SceneRegion* SceneRegionManager::GetBelongRegion(const Point2D& rSrcCoordinate)
{
	if(CheckInside(rSrcCoordinate, m_sScope))
	{
		int32 nXIndex = (m_sScope.sTopLeft.nX - rSrcCoordinate.nX /*+ 1 - 1*/) / m_nXCellLength;
		int32 nZIndex = (rSrcCoordinate.nZ - m_sScope.sTopLeft.nZ /*+ 1 - 1*/) / m_nZCellLength;
		return GetSceneRegion(nZIndex, nXIndex);
	} else
	{
		return 0;
	}
}

