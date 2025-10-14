package main

import (
	"log"
	"net/http"
)

func main() {
	router := http.NewServeMux()
	router.HandleFunc("/item/{id}", func(w http.ResponseWriter, r *http.Request) {
		id := r.PathValue("id")
		w.Write([]byte("recieved request for item: " + id))
	})

	server := http.Server{
		Addr: ":8080",
		Handler: router,
	}
	
	log.Println("Starting server on port : 8080")
	if err := server.ListenAndServe(); err != nil {
		log.Fatal(err)
	}
}