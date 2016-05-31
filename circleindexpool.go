package circleindexpool

type CircleIndexItem struct {
	nIndex int
	pNext  *CircleIndexItem
}

type CircleIndexPool struct {
	nIndexUsedCount  int
	nIndexTotalCount int
	pIndexPool       []CircleIndexItem
	ppIndexUsedPool  []*CircleIndexItem
	pHeadItem        *CircleIndexItem
	pTailItem        *CircleIndexItem
}

func NewCircleIndexPool(count int) *CircleIndexPool {
	ins := &CircleIndexPool{}
	ins.Init(count)
	return ins
}

func (this *CircleIndexPool) Init(count int) bool {
	if count < 0 ||
		this.nIndexTotalCount != 0 {
		return false
	}

	this.nIndexTotalCount = count
	this.pIndexPool = make([]CircleIndexItem, count)
	//	init the pool
	for i, _ := range this.pIndexPool {
		this.pIndexPool[i].nIndex = i + 1
		if i == count-1 {
			//	last one
			this.pIndexPool[i].pNext = nil
		} else {
			this.pIndexPool[i].pNext = &this.pIndexPool[i+1]
		}
	}
	this.pHeadItem = &this.pIndexPool[0]
	this.pTailItem = &this.pIndexPool[count-1]
	this.ppIndexUsedPool = make([]*CircleIndexItem, count+1)

	return true
}

func (this *CircleIndexPool) Free() {
	this.nIndexTotalCount = 0
	this.nIndexUsedCount = 0

	if nil != this.pIndexPool {
		this.pIndexPool = nil
	}
	if nil != this.ppIndexUsedPool {
		this.ppIndexUsedPool = nil
	}

	this.pHeadItem = nil
	this.pTailItem = nil
}

func (this *CircleIndexPool) AllocateIndex() int {
	if nil == this.pHeadItem {
		return 0
	}

	pUsedItem := this.pHeadItem
	nIndex := this.pHeadItem.nIndex
	this.pHeadItem = this.pHeadItem.pNext

	if nil == this.pHeadItem {
		this.pTailItem = nil
	}

	this.ppIndexUsedPool[nIndex] = pUsedItem
	this.nIndexUsedCount++

	return nIndex
}

func (this *CircleIndexPool) FreeIndex(nIndex int) {
	pUsedItem := this.ppIndexUsedPool[nIndex]
	if nil == pUsedItem {
		return
	}

	this.ppIndexUsedPool[nIndex] = nil
	pUsedItem.pNext = nil

	if nil == this.pTailItem {
		this.pHeadItem = pUsedItem
		this.pTailItem = pUsedItem
	} else {
		this.pTailItem.pNext = pUsedItem
		this.pTailItem = pUsedItem
	}

	this.nIndexUsedCount--
}

func (this *CircleIndexPool) GetTotalIndexCount() int {
	return this.nIndexTotalCount
}

func (this *CircleIndexPool) GetUsedIndexCount() int {
	return this.nIndexUsedCount
}
