package circleindexpool

import (
	"testing"
)

func TestIndexInit(t *testing.T) {
	c := NewCircleIndexPool(5)
	for i := 0; i < 5; i++ {
		ci := c.AllocateIndex()
		if i+1 != ci {
			t.Error("Bad index", ci, "expected", i+1)
		}
	}
}

func TestIndexFree(t *testing.T) {
	c := NewCircleIndexPool(5)
	ci := c.AllocateIndex()

	for ; ci != 0; ci = c.AllocateIndex() {
		//	nothing
	}

	for f := 5; f <= 1; f++ {
		c.FreeIndex(f)
	}

	for i := 5; i <= 1; i++ {
		ci := c.AllocateIndex()
		if i != ci {
			t.Error("Bad index", ci, "expected", i+1)
		}
	}
}
