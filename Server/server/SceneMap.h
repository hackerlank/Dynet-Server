#ifndef __SCENEMAP_H_
#define __SCENEMAP_H_

#include "SceneRegion.h"

#include <vector>
#include <set>
#include <typedef.h>
#include "UnorderedMap.h"
#include "CommonDefine.h"

//��ͼ��Ϣ
class SceneMap
{
public:

	SceneMap(uint32 nMapId,Point2D sTopLeftCoordinate, int32 nXAmount, int32 nZAmount, int32 nXCellLength, int32 nZCellLength,
		const std::vector<std::vector<bool>>& vecUseableInfo);

	~SceneMap(void);

	// ��������������и���
	void Update();

	// �����rEntity�ཻ�������entitys
	void GetNeighborsEntity(Entity& rEntity ,std::vector<Entity*>& o_setEnities);

	// ��õ�ͼID
	uint32 MapID()
	{
		return m_nMapId;
	}

private:

	// ��ӵ�ͼʵ��
	void AddMapEntity(Entity& rEntity);

	// ɾ����ͼʵ��
	void DelMapEntity(Entity& rEntity);

private:

	uint32					m_nMapId;			// ��ͼID

	SceneRegionManager		m_oRegionManager;	//�������
	std::set<Entity*>		m_setEntities;		//ʵ�����

	friend class			SceneMapManager;

};

// ��ɫ��ͼ��Ϣ
struct CharacterMapInfo
{
	uint32 nLandMapId;		// ����ͼID
	uint32 nInstanceMapId;  // ������ͼID
};

//��ͼ������
class SceneMapManager : public BaseSingle<SceneMapManager>
{
		typedef std::map<uint32,SceneMap*>			SceneMapMapType;
		typedef UNORDERED_MAP<Entity*,SceneMap*>	EntityUMapType;
public:

	SceneMapManager();
	~SceneMapManager();

	// ���ӵ�ͼ��Ϣ
	void	AddSceneMap(uint32 nMapId,Point2D sTopLeftCoordinate, int32 nXAmount, int32 nZAmount, int32 nXCellLength, int32 nZCellLength,const std::vector<std::vector<bool>>& vecUseableInfo);

	//��õ�ͼ��Ϣ
	SceneMap* GetSceneMap(uint32 nMapId) ;

	//������ڵĵ�ͼ
	SceneMap* GetEntitySceneMap(Entity& rEntity);

	//��ͼ�����һ��ʵ��
	bool AddSceneEnity(uint32 nMapId, Entity& rEntity);

	//ɾ��һ����ͼ��ʵ��
	bool DelSceneEnity(Entity& rEntity);

	// ��ͼ����
	void Update();

	// ������ڵ�ͼID
	uint32 GetOnMapId(Entity& entity);

private:

	SceneMapMapType								m_mapSceneMaps;					// ��ͼ������Ϣ
	UNORDERED_MAP<Entity*,SceneMap*>			m_umapEntities;					// ʵ�����ڵ�ͼ
	static ObjPool<SceneMap>					s_cSceneMapFactory;				// ��ͼ����

};

#endif

