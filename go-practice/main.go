package main

import (
	"fmt"
	"os"
	"github.com/eiannone/keyboard"
	"strings"
)

func main() {
	currentDir, _ := os.Getwd() // Track current directory

	err := keyboard.Open()
	if err != nil {
		fmt.Println("Failed to open keyboard listener:", err)
		return
	}
	defer keyboard.Close()

	for {
		// Read files in the current directory
		files, err := os.ReadDir(currentDir)
		if err != nil {
			fmt.Println("Error reading directory:", err)
			return
		}
		selectedIndex := 0 // Reset selection on directory change

		for {
			// Clear the screen
			fmt.Print("\033[H\033[2J")
			fmt.Println("Current Directory:", currentDir)

			// Print the file list
			for i, file := range files {
				if i == selectedIndex {
					fmt.Println("→", file.Name()) // Highlight selected file
				} else {
					fmt.Println("  ", file.Name())
				}
			}
			fmt.Println("\nPress 'q' to quit, '←' to go back")

			// Listen for keyboard input
			char, key, err := keyboard.GetKey()
			if err != nil {
				fmt.Println("Keyboard error:", err)
				return
			}

			if key == keyboard.KeyArrowUp && selectedIndex > 0 {
				selectedIndex--
			} else if key == keyboard.KeyArrowDown && selectedIndex < len(files)-1 {
				selectedIndex++
			} else if key == keyboard.KeyEnter {
				selectedFile := files[selectedIndex]
				if selectedFile.IsDir() {
					currentDir = currentDir + "/" + selectedFile.Name()
					break // Reload directory contents
				}
			} else if key == keyboard.KeyArrowLeft {
				if currentDir != "/" {
					parentDir := currentDir[:len(currentDir)-len(currentDir[strings.LastIndex(currentDir, "/"):])]
					if parentDir == "" {
						parentDir = "/"
					}
					currentDir = parentDir
					break // Reload directory contents
				}
			} else if char == 'q' { // Quit on 'q'
				return
			}
		}
	}
}


