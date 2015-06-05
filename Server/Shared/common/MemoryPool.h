#ifndef SWA_MEMORY_POOL_H_
#define SWA_MEMORY_POOL_H_

#include "BaseSingle.h"

namespace SWA
{
	typedef unsigned int muint32;

#define DEBUG_SWITCH_INIT_MEMORY	true	//debug�����ڴ��ʼ��

#define MEMORY_BLOCK_MASK	((muint32)0x59EF0000)
#define MEMORY_BLOCK_INUSE	((muint32)0x80000000)
#define MEMORY_BLOCK_LENGTH_SECTION	((muint32)0x0000FFFF)

#define SET_UNUSE_BLOCK_HEAD(length)		(((muint32)length) | MEMORY_BLOCK_MASK)
#define EXCHANGE_BLOCK_INUSE(head)			(((muint32)head) |= MEMORY_BLOCK_INUSE)
#define EXCHANGE_BLOCK_UNUSE(head)			(((muint32)head) &= ~MEMORY_BLOCK_INUSE)

#define GET_BLOCK_LENGTH(head)	(((muint32)head) & MEMORY_BLOCK_LENGTH_SECTION)
#define IS_INUSE(head)		(bool)(((muint32)head) & MEMORY_BLOCK_INUSE)
#define IS_MASK_OK(head)	(MEMORY_BLOCK_MASK == (((muint32)head) & ~(MEMORY_BLOCK_INUSE|MEMORY_BLOCK_LENGTH_SECTION)))

	// ���ڴ�Ϊ 4096*16 = 
	// ��Ӧ���ڴ���С 	4096	// *1 ...
	// �ڴ�ֶ�����
#define CHUNK_POOL_SIZE		16		// 16��32��48��64��80��96��112��128��144��160��176��192��208��224��240��256
	// ��Ӧ���ڴ������             // 256��240��224��208��192��176��160��144��128��112��96��80��64��48��32��16
	// ��С�ڴ���С
#define BLOCK_MIN_SIZE		16		// +16��+16��+16
	// �ڴ��С��ȡChunkPool����
#define GET_CHUNKPOOL_INDEX(length)	(muint32)( ( length + sizeof(muint32) - 1 ) / BLOCK_MIN_SIZE)

	// �ڴ��
	struct malloc_block
	{
		muint32			_head;	//��ǰ������
		malloc_block*	_next;	//��һ������ڴ���ַ[���е�ʱ��ʹ��]
	};

	struct malloc_chunk
	{
		void	*_ptr;	//������ڴ浥Ԫͷָ��
		muint32	_chunkSize;	//��ǰ�ڴ浥Ԫ�ܴ�С

		muint32 _blockSize;	//ÿ���ڴ���С
		unsigned int	_blockCount;	//�ڴ������
		malloc_block*	_blockHead;	//ͷ
		malloc_block*	_blockFoot;	//β

		malloc_chunk*	_next;	//��һ���ڴ浥Ԫָ��

		// ���������
		void construct();
		void deconstruct();
		// �����ڴ��
		bool InitializeChunk(muint32 chunkSize = 0x1000, muint32 blockSize = 0x10);

		// �����ڴ浥Ԫ���ݿ�
		// ��  ���������ڴ������βָ��
		// ����ֵ�������µ��ڴ�����ӱ�βָ��
		malloc_block* JoinChunk(malloc_block *&head);
	};

	class ChunkPool
	{
	public:
		ChunkPool();
		~ChunkPool();

		// ��ʼ���ڴ��
		// msize chunkSize = 0x1000	//Ĭ���ڴ浥Ԫ��С4K
		// msize blockSize = 0x10,		//Ĭ�Ͽ��ڴ��С16�ֽڣ������ڴ�12�ֽڣ�ͷheadռ��4�ֽڣ�
		bool InitializeMallocChunk(muint32 chunkSize = 0x1000, muint32 blockSize = 0x10);

		// �����ڴ��
		void *malloc();
		// �ͷ��ڴ��
		void free(void *ptr);

		// �����ڴ��ϵͳHeap
		void realloc();

	private:
		muint32			m_blockSize;
		muint32			m_chunkSize;

		malloc_chunk*	m_pMallocChunk;	//�ڴ浥ԪChunk�б�

		malloc_block*	m_pBlockHead;	//ͷ
		malloc_block*	m_pBlockFoot;	//β
	};

	class IMemoryPool
	{
	public:
		virtual ~IMemoryPool() {}
		virtual void* malloc(muint32 size) = 0;
		virtual void  free(void *p, muint32 size) = 0;
	};

	// Ӧ�ÿ��Լ̳и��࣬��չ����
	class MemoryPool : public IMemoryPool , public BaseSingle<MemoryPool>
	{
	public:
		MemoryPool();
		~MemoryPool();

		// ��ʼ���ڴ��
		bool Init();

		void* malloc(muint32 size);
		void  free(void *p, muint32 size = 0);

	private:

		ChunkPool m_pChunkPool[CHUNK_POOL_SIZE];
		// ��ʱ���õ�
		//malloc_chunk* m_pHeapChunk;	//���̶�ʹ���ڴ�����
	};

#define gMemoryPool MemoryPool::Instance()

};// namespace

#endif