#ifndef _INC_CIRCELINDEXPOOL_
#define _INC_CIRCELINDEXPOOL_
//////////////////////////////////////////////////////////////////////////
struct CircelIndexItem
{
	int nIndex;
	CircelIndexItem* pNext;
};

class CircelIndexPool
{
public:
	CircelIndexPool();
	~CircelIndexPool();

public:
	bool Init(int _nCount);
	void Free();

	int AllocateIndex();
	void FreeIndex(int _nIndex);

public:
	int m_nIndexUsedCount;
	int m_nIndexTotalCount;
	CircelIndexItem* m_pIndexPool;
	CircelIndexItem** m_ppIndexUsedPool;
	CircelIndexItem* m_pHeadItem;
	CircelIndexItem* m_pTailItem;
};
//////////////////////////////////////////////////////////////////////////
#endif