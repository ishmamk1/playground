package main

import (
	"fmt"
	"net/http"
	"sync"
	"time"
)

type StatusPing struct {
	Status string
	WebsiteUrl string
	ResponseTime time.Duration
}

func PingWebsite(url string, httpClient *http.Client, websiteChan chan *StatusPing, wg *sync.WaitGroup) {
	defer wg.Done()

	startTime := time.Now()
	status := StatusPing {
		WebsiteUrl: url,
	}

	resp, err := httpClient.Get(url)

	if err != nil {
		fmt.Println(err)
		return
	}

	defer resp.Body.Close()

	status.Status = resp.Status
	status.ResponseTime = time.Since(startTime)

	websiteChan <- &status
}

func main() {
	totalStartTime := time.Now()
	websiteUrls := []string{
		"https://www.google.com/",
		"https://www.youtube.com/",
		"https://www.apple.com/",
		"https://www.reddit.com/",
		"https://www.overleaf.com/",
		"https://www.gradescope.com/",
	}

	httpClient := &http.Client{
		Timeout: 5 * time.Second,
	}

	var wg sync.WaitGroup
	wg.Add(len(websiteUrls))

	websiteChan := make(chan *StatusPing, len(websiteUrls))
	for _, websiteUrl := range websiteUrls {
		go PingWebsite(websiteUrl, httpClient, websiteChan, &wg)
	}

	go func() {
		wg.Wait()
		close(websiteChan)
	}()

	for websiteStatus := range websiteChan {
		fmt.Println(websiteStatus.Status, websiteStatus.WebsiteUrl, websiteStatus.ResponseTime)
	}
	fmt.Printf("Total execution time: %v\n", time.Since(totalStartTime))
}