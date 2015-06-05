#ifndef __SCENECHANNEL_H_
#define __SCENECHANNEL_H_


#include <Set>
#include "UnorderedSet.h"
#include "ObjPool.h"
#include "def_channel.h"
#include "CommonDefine.h"

class SceneRegion;

struct IChannelRegist
{
	// �Ƿ�ע��ָ��Ƶ��
	virtual bool IsRegist(ChannelRegistType eType) const = 0;
};

#define DEF_IChannelOperate(NotifyType)\
template<typename NotifyType>\
struct IChannelOperate##NotifyType\
{\
	FUNCTION_CHANNEL_BROADCAST(NotifyType)\
	FUNCTION_CHANNEL_COLLECT(NotifyType)\
protected:\
	NotifyType m_s##NotifyType;\
};

#define IChannelOperate(NotifyType) IChannelOperate##NotifyType<NotifyType>

class Channel
{
public:
	Channel(ChannelRegistType eBroadcastType, ChannelRegistType eCollectType)
		: m_eBroadcastType(eBroadcastType), m_eCollectType(eCollectType) {}

	// ������
	virtual void RegistReceiver(IChannelRegist& rRegister) = 0;
	virtual void CancelReceiver(IChannelRegist& rRegister) = 0;
	
	// �㲥��
	virtual void RegistBroadcaster(IChannelRegist& rRegister) = 0;
	virtual void CancelBroadcaster(IChannelRegist& rRegister) = 0;

	// ��㲥���ռ���Ϣ���㲥��������
	virtual void Update() = 0;

protected:
	const ChannelRegistType						m_eBroadcastType;				// �㲥����
	const ChannelRegistType						m_eCollectType;					// �ռ�����
};

#define DEF_SceneChannel(NotifyType)\
template<typename NotifyType>\
class SceneChannel##NotifyType : public Channel\
{\
public:\
	SceneChannel##NotifyType(ChannelRegistType eBroadcastType, ChannelRegistType eCollectType)\
		: Channel(eBroadcastType, eCollectType)\
	{}\
	virtual void RegistReceiver(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eBroadcastType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast<IChannelOperate(NotifyType)*>(&rRegister))\
			{\
				m_setChannnelReceivers.insert(pOperate);\
				std::cout << "RegistReceiver:m_setChannnelReceivers:" << m_setChannnelReceivers.size() << ",type:" << #NotifyType << std::endl; \
			}\
		}\
	}\
	virtual void CancelReceiver(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eBroadcastType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast<IChannelOperate(NotifyType)*>(&rRegister))\
			{\
				m_setChannnelReceivers.erase(pOperate);\
				std::cout << "CancelReceiver:m_setChannnelReceivers:" << m_setChannnelReceivers.size() << ",type:" << #NotifyType << std::endl; \
			}\
		}\
	}\
	virtual void RegistBroadcaster(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eCollectType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast<IChannelOperate(NotifyType)*>(&rRegister))\
			{\
				m_setChannnelBroadcasters.insert(pOperate);\
				std::cout << "RegistBroadcaster:m_setChannnelMsg:" << m_setChannnelBroadcasters.size() << ",type:" << #NotifyType << std::endl; \
			}\
		}\
	}\
	virtual void CancelBroadcaster(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eCollectType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast<IChannelOperate(NotifyType)*>(&rRegister))\
			{\
				m_setChannnelBroadcasters.erase(pOperate);\
				std::cout << "CancelBroadcaster:m_setChannnelMsg:" << m_setChannnelBroadcasters.size() << ",type:" << #NotifyType << std::endl; \
			}\
		}\
	}\
	virtual void Update()\
	{\
		std::set<const NotifyType*> setChannnelMsg;\
		{\
			std::set<IChannelOperate(NotifyType)*>::const_iterator iter_broadcaster;\
			for (iter_broadcaster = m_setChannnelBroadcasters.begin(); iter_broadcaster != m_setChannnelBroadcasters.end(); ++iter_broadcaster)\
			{\
				const NotifyType* pMsg;\
				(**iter_broadcaster).ChannelCollect(pMsg);\
				setChannnelMsg.insert(pMsg);\
			}\
		}\
		{\
			std::set<IChannelOperate(NotifyType)*>::const_iterator iter_receiver;\
			for (iter_receiver = m_setChannnelReceivers.begin(); iter_receiver != m_setChannnelReceivers.end(); ++iter_receiver)\
			{\
				(**iter_receiver).ChannelBroadcast(setChannnelMsg);\
			}\
		}\
	}\
private:\
	std::set<IChannelOperate(NotifyType)*>		m_setChannnelBroadcasters;\
	std::set<IChannelOperate(NotifyType)*>				m_setChannnelReceivers;\
};

#define SceneChannel(NotifyType) SceneChannel##NotifyType<NotifyType>

class SceneChannelManager : public BaseSingle<SceneChannelManager>
{
public:
	// ����Ƶ��
	void AddSceneChannel(Channel& rChannel);
	
	// ��������Ƶ��
	void Update();

protected:

protected:

private:

private:
	UNORDERED_SET<Channel*>		m_usetChannels;				// Ƶ��
};

DEF_IChannelOperate(ChannelPosition)
DEF_SceneChannel(ChannelPosition)
extern ObjPool<SceneChannel(ChannelPosition)> g_cPositionChannelFactory;		// λ����ϢƵ������

DEF_IChannelOperate(ChannelCreature)
DEF_SceneChannel(ChannelCreature)
extern ObjPool<SceneChannel(ChannelCreature)> g_cCreatureChannelFactory;			// ������������ϢƵ������

DEF_IChannelOperate(ChannelWear)
DEF_SceneChannel(ChannelWear)
extern ObjPool<SceneChannel(ChannelWear)> g_cWearChannelFactory;		// ��ɫ��װ����ϢƵ������

DEF_IChannelOperate(ChannelSpell)
DEF_SceneChannel(ChannelSpell)
extern ObjPool<SceneChannel(ChannelSpell)> g_cSpellChannelFactory;		// ��ɫ������ϢƵ������

DEF_IChannelOperate(ChannelBuff)
DEF_SceneChannel(ChannelBuff)
extern ObjPool<SceneChannel(ChannelBuff)> g_cBuffChannelFactory;		// ��ɫBuff��ϢƵ������

#endif

