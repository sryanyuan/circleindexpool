# circle index pool
A golang package to implement circle index

# Purpose

If you want to create a limit array and get the index of it dynamic, and want to free the index dynamic, you may need the package.

The purpose of the package is to get the available index of the array, and free the index for next use.

# install

    go get github.com/sryanyuan/circleindexpool

# Usage

	package main
	
	import (
		"log"
	
		"github.com/sryanyuan/circleindexpool"
	)
	
	func main() {
		c := circleindexpool.NewCircleIndexPool(10)
	
		//	you can get index(1 ~ 10) from the pool
		for {
			i := c.AllocateIndex()
			if i == 0 {
				break
			}
	
			log.Println("Got index", i)
		}
	
		//	you can free the index and use it later
		for i := 1; i < 10; i += 2 {
			c.FreeIndex(i)
		}
	
		log.Println("After free:")
		for {
			i := c.AllocateIndex()
			if i == 5 {
				break
			}
	
			log.Println("Got index", i)
		}
	
		//	free all index
		for i := 1; i <= 10; i++ {
			c.FreeIndex(i)
		}
	
		log.Println("Total:")
		for {
			i := c.AllocateIndex()
			if i == 0 {
				break
			}
	
			log.Println("Got index", i)
		}
	}