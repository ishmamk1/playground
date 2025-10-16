package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
	"net/http"
)

type Order struct {
	Id int
	Status string
	mu sync.Mutex
}

func main() {
	var wg sync.WaitGroup
	wg.Add(2)


	orderChan := make(chan *Order, 20)

	go func() {
		defer wg.Done()
		for _, order := range GenerateOrders(20) {
			orderChan <- order
		}
		
		close(orderChan)

		fmt.Println("Done with generating orders")
	}()

	go ProcessOrders(orderChan, &wg)


	wg.Wait()
	

	fmt.Println("All operations completed. Exiting...")
}



func ReportOrderStatus(orders []*Order) {
	time.Sleep(1 * time.Second)
	fmt.Println("\n--- Order Status Report ---")

	for _, order := range orders {
		fmt.Printf(
			"Order %d: %s\n",
			order.Id, order.Status,
		)
	}
	fmt.Println("--------------------------\n")
}

func ProcessOrders(orderChan <-chan *Order, wg *sync.WaitGroup) {
	defer wg.Done()

	for order := range orderChan {
		time.Sleep(
			time.Duration(rand.Intn(500)) *
			time.Millisecond,
		)
		fmt.Printf("Processing order %d\n", order.Id)
	}
}

func GenerateOrders(count int) []*Order {
	orders := make([]*Order, count)

	for i := range count {
		orders[i] = &Order{Id: i + 1, Status: "Pending"}
	}

	return orders
}