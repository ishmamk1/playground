package utils

import (
	"encoding/json"
	"finance/account"
	"os"
)

func LoadData(filePath string) (map[string]account.Account, error) {
	fileBytes, err := os.ReadFile(filePath)

	if err != nil {
		return nil, err
	}

	var accountMap map[string]account.Account

	err = json.Unmarshal(fileBytes, &accountMap)

	if err != nil {
		return nil, err
	}

	return accountMap, nil
}

func SaveData(accountMap map[string]account.Account) (bool, error) {
	filePath := "path"
	fileBytes, err := json.Marshal(accountMap)

	if err != nil {
		return false, err
	}

	err = os.WriteFile(filePath, fileBytes, 0644)

	if err != nil {
		return false, err
	}

	return true, nil

}
