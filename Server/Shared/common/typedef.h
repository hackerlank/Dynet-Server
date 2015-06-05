#ifndef __TWP_DEF_APP_TYPEDEF_HEADER__
#define __TWP_DEF_APP_TYPEDEF_HEADER__

#include "CompilerDefs.h"
#include "BaseDefine.h"

namespace twp {
    namespace app {

#pragma pack(push,1)
        struct DateTime
        {
            uint32	year;
            uint32	month;
            uint32	day;
            uint32	hour;
            uint32	minute;
            uint32	second;

			unsigned long second_part;
			uint32 reserve1,reserve2;
        };

		struct Position3D
		{
			int32 x;
			int32 y;
			int32 z;


			bool operator == (const Position3D & o) const
			{
				return distances(o) < 1;
			}
			bool operator != (const Position3D & o) const
			{
				return !(*this==o);
			}
			//�ݲ�ʹ��
			operator size_t() const
			{
				return (size_t)(z * 100000000 + y * 10000 + x);
			}
			bool operator < (const Position3D & o) const
			{
				if( y != o.y)
				{
					return y < o.y;
				}
				return x < o.x;
			}
			//����ƽ��
			uint32 distances (const Position3D & o) const
			{
				return (y - o.y) * (y - o.y) + (x - o.x) * (x - o.x) + (z - o.z) * (z - o.z);
			}
			//��Բ��
			bool in_circle (const Position3D & o, uint32 dis) const
			{
				return distances(o) < dis*dis;
			}
			//�Ƿ�ͬ��
			static const int32 SCENE_RADIS = 14 ;
			bool is_same_scene (const Position3D & o) const
			{
				return inarea (o, SCENE_RADIS, SCENE_RADIS, SCENE_RADIS);
			}

			//��������
			bool inarea (const Position3D & o, int32 radis_x, int32 radis_y, int32 radis_z) const
			{
				if ((x - o.x) * (x - o.x) > radis_x * radis_x )
				{
					return false;
				}
				if ((y - o.y) * (y - o.y) > radis_y * radis_y )
				{
					return false;
				}
				if ((z - o.z) * (z - o.z) > radis_z * radis_z )
				{
					return false;
				}

				return true;
			}


			template<class Archive>
			inline void serialize(Archive & ar, const unsigned int version)
			{
				ar & x;
				ar & y;
				ar & z;
			}

			static const int32 INVALID_P = 0 ;
			bool is_invalid() const
			{
				return x == INVALID_P && y == INVALID_P && z == INVALID_P;
			}

			void set_invalid()
			{
				x = INVALID_P;
				y = INVALID_P;
				z = INVALID_P;
			}
		};

        struct Position2D
        {
            int32 x;
            int32 y;

            //support for hash
            operator size_t() const
            {
                return ( ( (y << 16) & 0xFFFF0000 ) | x ) & 0x0000FFFF;
            }
            bool operator == (const Position2D & o) const
            {
                return y == o.y && x == o.x;
            }
            bool operator != (const Position2D & o) const
            {
                return !(*this==o);
            }

            bool operator < (const Position2D & o) const
            {
                if( y != o.y)
                {
                    return y < o.y;
                }
                return x < o.x;
            }

            template<class Archive>
            inline void serialize(Archive & ar, const unsigned int version)
            {
                ar & x;
                ar & y;
            }

            static const int32 INVALID_X = 0x8000000;
            bool is_invalid() const
            {
                return x == INVALID_X;
            }

            void set_invalid()
            {
                x = INVALID_X;
            }
        };

        /*struct Position
        {
            union
            {
                struct
                {
                    int32 x,y;
                };
                Position2D	pos2d;
            };

            int32 z;

            template<class Archive>
            inline void serialize(Archive & ar, const unsigned int version)
            {
                ar & pos2d;
                ar & z;
            }

            bool is_invalid() const
            {
                return pos2d.is_invalid();
            }

            void set_invalid()
            {
                pos2d.set_invalid();
            }
        };*/

        struct Position : public Position3D
        {
            Position()
            {
               set_invalid();
            }

            explicit Position(const Position3D& pos_3d)
            {
                x = pos_3d.x;
                y = pos_3d.y;
				z = pos_3d.z;
            }

            template<class Archive>
            inline void serialize(Archive & ar, const unsigned int version)
            {
                ar & x;
                ar & y;
			    ar & z;
            }

            bool is_invalid() const
            {
                return Position3D::is_invalid();
            }

            void set_invalid()
            {
                Position3D::set_invalid();
            }

            void get_pos3d(Position3D& pos3d)const
            {
                pos3d.x = x;
                pos3d.y = y;
				pos3d.z = z;
            }
        };

        /*
			The Position2D (left,bottom) belongs to the RECTANGLE,but the Position2D(right,top) dosn't belong to the RECTANGLE.
			width = right - left;
			height = top - bottom;
		*/
        /*struct Rectangle
        {
            union
            {
                struct
                {
                    int32 left;
                    int32 bottom;
                    int32 right;
                    int32 top;
                };
                struct
                {
                    Position3D	begin;
                    Position3D	end;
                };
            };
        };*/

        /*struct Direction
        {
            float x;
            float y;
            float z;

            template<class Archive>
            inline void serialize(Archive & ar, const unsigned int version)
            {
                ar & x;
                ar & y;
                ar & z;
            }
        };*/

        typedef uint16 Direction;

		// ����
        typedef Position3D MapBlockCoord;


		// 
		// ����
		//
		struct RewardMod
		{
			// ����id
			uint16 reward_char_mod_type;
			// ����ֵ
			int32 reward_char_mod_value;

			inline bool operator != (const RewardMod& quest_reward) const
			{
				return reward_char_mod_type != quest_reward.reward_char_mod_type || reward_char_mod_value != quest_reward.reward_char_mod_value;
			}

		};

		//
		// ������Ʒ
		//
		struct RewardItem
		{
			// ������Ʒid
			uint32 item_type_idx;
			// ����
			uint16 item_count;

			inline bool operator != (const RewardItem& quest_reward_item ) const
			{
				return item_type_idx != quest_reward_item.item_type_idx || item_count != quest_reward_item.item_count;
			}

		};

        //
        //	��־λ����
        //
#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)		( ((value) & (query_flags)) != 0 ? true : false )

        // 64λ����
#define MAKE_PAIR64(l, h)  uint64( uint32(l) | ( uint64(h) << 32 ) )
#define PAIR64_HIPART(x)   (uint32)((uint64(x) >> 32) & 0x00000000FFFFFFFFLL)
#define PAIR64_LOPART(x)   (uint32)(uint64(x)         & 0x00000000FFFFFFFFLL)
        // 32λ����
#define MAKE_PAIR32(l, h)  uint32( uint16(l) | ( uint32(h) << 16 ) )
#define PAIR32_HIPART(x)   (uint16)((uint32(x) >> 16) & 0x0000FFFF)
#define PAIR32_LOPART(x)   (uint16)(uint32(x)         & 0x0000FFFF)
		//��־ǰ׺
#define  __PRINT_MSG__ __FUNCTION__ << " " << __FILE__ << ":" << __LINE__ 

#ifdef _MSC_VER
#	define SERVER_DECL __declspec(dllexport)
#	define SCRIPT_DECL __declspec(dllimport)
#	define TWP_DLL_EXPORT extern "C" __declspec(dllexport)
#	define TWP_DLL_DECL __declspec(dllexport)
#else
#	define SERVER_DECL
#	define SCRIPT_DECL
#	define TWP_DLL_EXPORT extern "C"
#endif

#pragma pack(pop)

    } // namespace app
} // namespace twp

#endif // __TWP_APP_TYPEDEF_HEADER__
