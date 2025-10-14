package handler

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strconv"
)

type Vals struct {
	A float64 `json:"a"`
	B float64 `json:"b"`
}

func Add(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		w.WriteHeader(http.StatusMethodNotAllowed)
		w.Write([]byte("Invalid method"))
	}

	values, err := parseValues(r)

	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
	}

	sum := values.A + values.B

	sumStr := strconv.FormatFloat(sum, 'f', 2, 64)

	fmt.Println(sum)
	w.WriteHeader(http.StatusOK)
	w.Write([]byte(sumStr))

}

func Subtract(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		w.WriteHeader(http.StatusMethodNotAllowed)
		w.Write([]byte("Invalid method"))
	}

	values, err := parseValues(r)

	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
	}

	difference := values.A - values.B

	diffStr := strconv.FormatFloat(difference, 'f', 2, 64)
	fmt.Println(difference)

	w.WriteHeader(http.StatusOK)
	w.Write([]byte(diffStr))

}

func parseValues(r *http.Request) (Vals, error) {
	var values Vals
	err := json.NewDecoder(r.Body).Decode(&values)

	if err != nil {
		return values, err
	}

	return values, nil
}


