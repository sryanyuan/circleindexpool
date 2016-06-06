#include "CircleIndexPool.h"
#include <Windows.h>
//////////////////////////////////////////////////////////////////////////
CircelIndexPool::CircelIndexPool()
{
	m_nIndexTotalCount = 0;
	m_nIndexUsedCount = 0;
	m_pIndexPool = NULL;
	m_ppIndexUsedPool = NULL;
	m_pHeadItem = m_pTailItem = NULL;
}

CircelIndexPool::~CircelIndexPool()
{
	Free();
}

bool CircelIndexPool::Init(int _nCount)
{
	if(m_nIndexTotalCount != 0 ||
		_nCount < 0)
	{
		return false;
	}

	m_nIndexTotalCount = _nCount;

	m_pIndexPool = new CircelIndexItem[_nCount];
	for(int i = 0; i < _nCount; ++i)
	{
		m_pIndexPool[i].nIndex = i + 1;
		if(i == _nCount - 1)
		{
			//	last one
			m_pIndexPool[i].pNext = NULL;
		}
		else
		{
			m_pIndexPool[i].pNext = m_pIndexPool + i + 1;
		}
	}

	//	get head and tail item
	m_pHeadItem = &m_pIndexPool[0];
	m_pTailItem = &m_pIndexPool[m_nIndexTotalCount - 1];

	m_ppIndexUsedPool = new CircelIndexItem*[_nCount + 1];
	memset(m_ppIndexUsedPool, 0, sizeof(CircelIndexItem*) * (_nCount + 1));

	return true;
}

void CircelIndexPool::Free()
{
	m_nIndexTotalCount = m_nIndexUsedCount = 0;

	if(NULL != m_pIndexPool)
	{
		delete [] m_pIndexPool;
		m_pIndexPool = NULL;
	}
	if(NULL != m_ppIndexUsedPool)
	{
		delete [] m_ppIndexUsedPool;
		m_ppIndexUsedPool = NULL;
	}

	m_pHeadItem = m_pTailItem = NULL;
}

int CircelIndexPool::AllocateIndex()
{
	if(NULL == m_pHeadItem)
	{
		return 0;
	}

	CircelIndexItem* pUsedItem = m_pHeadItem;
	int nIndex = m_pHeadItem->nIndex;
	m_pHeadItem = m_pHeadItem->pNext;

	if(NULL == m_pHeadItem)
	{
		//	already reach tail
		m_pTailItem = NULL;
	}

	//	push to used index pool
	m_ppIndexUsedPool[nIndex] = pUsedItem;
	++m_nIndexUsedCount;

	return nIndex;
}

void CircelIndexPool::FreeIndex(int _nIndex)
{
	//	get the used index
	CircelIndexItem* pUsedItem = m_ppIndexUsedPool[_nIndex];
	if(NULL == pUsedItem)
	{
		return;
	}

	m_ppIndexUsedPool[_nIndex] = NULL;
	pUsedItem->pNext = NULL;

	if(NULL == m_pTailItem)
	{
		m_pHeadItem = pUsedItem;
		m_pTailItem = pUsedItem;
	}
	else
	{
		//	add to tail
		m_pTailItem->pNext = pUsedItem;
		m_pTailItem = pUsedItem;
	}

	--m_nIndexUsedCount;
}