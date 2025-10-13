package main

import (
	"fmt"
	"math/rand"
	"time"
	"sync"
)

var wg = sync.WaitGroup{}

var dbData = []string{"id1", "id2", "id3"}

func main() {
	t0 := time.Now()

	for i := 0; i < len(dbData); i++ {
		wg.Add(1)
		go dbCall(i)
	}
	wg.Wait()
	fmt.Printf("\nTotal Execution Time: %v\n", time.Since(t0))
}

func dbCall(i int) {
	var delay float32 = rand.Float32() * 2000
	time.Sleep(time.Duration(delay)*time.Millisecond)
	fmt.Println("The result is ", dbData[i])
	wg.Done()
}

