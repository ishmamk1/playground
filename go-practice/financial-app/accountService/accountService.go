package accountService

import (
	"errors"
	"finance/utils"
	"finance/account"
)

type AccountActions interface {
	Deposit(username string, password string, amount float64, accountMap map[string]account.Account)
	Withdraw(username string, password string, amount float64, accountMap map[string]account.Account)
	GetBalance(username string, accountMap map[string]account.Account)
}

func Deposit(username string, password string, amount float64, accountMap map[string]account.Account) (bool, error) {
	account, ok := accountMap[username]
	if !ok || account.Password != password {
		err := errors.New("wrong username/password")
		return false, err
	}

	if amount < 0 {
		err := errors.New("negative amount")
		return false, err
	}

	account.Balance += amount
	accountMap[username] = account
	
	written, err := utils.SaveData(accountMap)

	if err != nil {
		return false, err
	}

	return written, nil
}

func Withdraw(username string, password string, amount float64, accountMap map[string]account.Account) (bool, error) {
	account, ok := accountMap[username]
	if !ok || account.Password != password {
		err := errors.New("wrong username/password")
		return false, err
	}

	if amount < 0 {
		err := errors.New("negative amount")
		return false, err
	}

	if account.Balance < amount {
		err := errors.New("Overdraft")
		return false, err
	}

	account.Balance -= amount
	accountMap[username] = account
	
	written, err := utils.SaveData(accountMap)

	if err != nil {
		return false, err
	}

	return written, nil
}

func GetBalance(username string, accountMap map[string]account.Account) (float64, error) {
	account, ok := accountMap[username]

	if !ok {
		err := errors.New("invalid user")
		return 0, err
	}

	return account.Balance, nil
}