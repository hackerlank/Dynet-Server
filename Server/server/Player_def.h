#ifndef PLAYER_DEF_H_
#define PLAYER_DEF_H_


//�����ĺ�����Ϣ���ǰ�˷����Ǵ洢
struct FrindRelationInfo
{
	suint64 fri_uid;//���ѣ�İ���ˣ�ID
	suint32 relation;//��ϵ��ʶ(0ɾ��,1����,2İ����)
	suint32 level;
	sbyte	nick[MAX_NICK_LENGTH + 1];
};


#endif