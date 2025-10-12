package tools

import (
	"time"
)

type mockDB struct{}

var mockLoginDetails = map[string]LoginDetails {
	"ishmam" : {
		AuthToken: "abc",
		Username: "ishmam",
	},
}

var mockCoinDetails = map[string]CoinDetails {
	"ishmam" : {
		Coins: 100,
		Username: "ishmam",
	},
}

