#ifndef __SCENEREGION_H_
#define __SCENEREGION_H_

#include <vector>
#include <set>

#include "Geometry2D.h"
#include "UnorderedMap.h"
#include "ObjPool.h"

struct IChannelRegist;

class Entity;
class Channel;

class SceneRegion
{
public:
	SceneRegion() {}

	SceneRegion(const Rectangle2D& rRange);

	// ע�᱾����Ƶ��
	void RegistReceiveChannels(IChannelRegist& rEntity);

	// ȡ��ע���ռ���Ϣ
	void CancelReceiveChannels(IChannelRegist& rEntity);

	// ����ʵ��
	void AddEntity(Entity& rEntity);

	// �Ƴ�ʵ��
	void DelEntity(Entity& rEntity);

	// ����Ƿ���������
	bool InScope(const Point2D& rPosition);

	// ��ø����������ʵ��
	const std::set<Entity*> GetEntities() ;

private:
	// ���Ƶ��
	void AddChannel(Channel& rChannel);

	// ע��㲥��
	void RegistBroadcasterChannels(IChannelRegist& rEntity);

	// ȡ���㲥��
	void CancelBroadcasterChannels(IChannelRegist& rEntity);

private:
	std::vector<Channel*>			m_vecChannels;		// Ƶ������
	std::set<Entity*>				m_setEntities;		// ʵ�弯��
	Rectangle2D						m_sScope;			// ����Χ

	friend class SceneRegionManager;
};

class SceneRegionManager
{
	typedef UNORDERED_MAP<Entity*,std::pair<SceneRegion* /*��������*/, std::set<SceneRegion*>/*�鿴����*/>>	EntitySceneRegionCollectUMapType;
public:
	/*
	* X������������,Z����������
	* @sTopLeftCoordinate:���Ͻ���ʼ����
	* @nXAmount:X�᷽��Cell����,@nZAmount:Z�᷽��Cell����
	* @nXCellLength:X�᷽��Cell����,@nZCellLength:Z�᷽��Cell����
	* vecUseableInfo:����Cell������Ϣ,[0][0]Ϊ���Ͻ�����
	*/
	SceneRegionManager(Point2D sTopLeftCoordinate, int32 nXAmount, int32 nZAmount, int32 nXCellLength, int32 nZCellLength,
		const std::vector<std::vector<bool>>& vecUseableInfo);

	~SceneRegionManager();

	// ��ӳ���ʵ��
	void AddSceneEntity(Entity& rEntity);

	// ɾ������ʵ��
	void DelSceneEntity(Entity& rEntity);

	// ����Ƶ��ע�ᡢ���������е�ʵ�弯��
	void Update();

	// �����ײ����
	void GetCollisionRegion(const Rectangle2D& i_rSrcRange, std::set<SceneRegion*>& o_setCollisionRegions);

protected:

protected:

private:
	// ���ָ������
	SceneRegion* GetSceneRegion(int32 nZIndex, int32 nXIndex) const;

	// �����������
	SceneRegion* GetBelongRegion(const Point2D& rSrcCoordinate);

private:
	Rectangle2D												m_sScope;					// ��Χ
	const int32												m_nXAmount;					// X�����������
	const int32												m_nZAmount;					// Z�����������
	const int32												m_nXCellLength;				// X�᷽�����򳤶�
	const int32												m_nZCellLength;				// Z�᷽�����򳤶�
	std::vector<std::vector<SceneRegion*>>					m_vecRegions;				// ��������
	
	EntitySceneRegionCollectUMapType						m_umapEntityRegions;		// ʵ���������

	static ObjPool<SceneRegion>								s_cSceneRegionFactory;		// ���򹤳�

};

#endif

