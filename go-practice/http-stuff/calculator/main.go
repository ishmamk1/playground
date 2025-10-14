package main

import (
	"calculator/handler"
	"log"
	"net/http"
)

func main() {
	mux := http.NewServeMux()

	mux.HandleFunc("/hello", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("hello"))
	})

	mux.HandleFunc("/add", handler.Add)
	mux.HandleFunc("/subtract", handler.Subtract)

	server := http.Server{
		Addr: ":8080",
		Handler: mux,
	}
	
	if err := server.ListenAndServe(); err != nil {
		log.Fatal(err)
	}
}
