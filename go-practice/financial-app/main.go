package main

import (
	"finance/account"
	"finance/accountService"
	"finance/utils"
	"fmt"
	"log"
)

func main() {
	fmt.Println("hello")
	
	dataFilePath := "path"
	data, err := utils.LoadData(dataFilePath)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(data)

	var newAcc account.Account
	newAcc.Password = "hi"
	newAcc.Balance = 10.30
	data["henry"] = newAcc

	written, err := utils.SaveData(data)


	if err != nil {
		log.Fatal(err)
	}

	if written {
		fmt.Println("Valid")
	} 

	written, err = accountService.Deposit("ishmam", "abc", 1000, data)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Deposited for ishmam", written)

	written, err = accountService.Withdraw("ishmam", "abc", 700, data)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Withdraw for ishmam", written)
}