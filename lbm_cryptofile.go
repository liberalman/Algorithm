package main

import (
	"bytes"
	"fmt"
	"os"

	"github.com/isfonzar/filecrypt"
	"golang.org/x/crypto/ssh/terminal"
)

func main() {

	// If not enough args, return help text
	if len(os.Args) < 2 {
		printHelp()
		os.Exit(0)
	}

	function := os.Args[1]

	switch function {
	case "help":
		printHelp()
	case "encrypt":
		// encryptHandle() // 终端交互式加密
		encryptHandle1() // 密码直接写到命令行，不在终端交互
	case "decrypt":
		// decryptHandle() // 终端交互式解密
		decryptHandle1() // 密码直接写到命令行，不在终端交互
	default:
		fmt.Println("Run CryptoGo encrypt to encrypt a file, and CryptoGo decrypt to decrypt a file.")
		os.Exit(1)
	}

}

func printHelp() {
	fmt.Println("CryptoGo")
	fmt.Println("Simple file encrypter for your day-to-day needs.")
	fmt.Println("")
	fmt.Println("Usage:")
	fmt.Println("")
	fmt.Println("\tCryptoGo encrypt /path/to/your/file")
	fmt.Println("")
	fmt.Println("Commands:")
	fmt.Println("")
	fmt.Println("\t encrypt\tEncrypts a file given a password")
	fmt.Println("\t decrypt\tTries to decrypt a file using a password")
	fmt.Println("\t help\t\tDisplays help text")
	fmt.Println("")
}

func encryptHandle() {

	if len(os.Args) < 3 {
		println("Missing the path to the file. For more information run CryptoGo help")
		os.Exit(0)
	}

	file := os.Args[2]

	validateFile(file)

	password := getPassword()

	fmt.Println("\nEncrypting...")
	filecrypt.Encrypt(file, password)
	fmt.Println("\nFile successfully protected")

}

func getPassword() []byte {
	fmt.Print("Enter password: ")
	password, _ := terminal.ReadPassword(0)
	fmt.Print("\nConfirm password: ")
	password2, _ := terminal.ReadPassword(0)
	if !validatePassword(password, password2) {
		fmt.Print("\nPasswords do not match. Please try again.\n")
		return getPassword()
	}
	return password
}

func encryptHandle1() {

	if len(os.Args) < 4 {
		println("Missing the path to the file. For more information run CryptoGo help")
		os.Exit(0)
	}

	password := os.Args[2]

	file := os.Args[3]

	validateFile(file)

	fmt.Println("\nEncrypting...")
	filecrypt.Encrypt(file, []byte(password))
	fmt.Println("\nFile successfully protected")

}

func decryptHandle() {

	if len(os.Args) < 3 {
		println("Missing the path to the file. For more information run CryptoGo help")
		os.Exit(0)
	}

	file := os.Args[2]

	validateFile(file)

	fmt.Print("Enter password: ")
	password, _ := terminal.ReadPassword(0)

	fmt.Println("\nDecrypting...")
	filecrypt.Decrypt(file, password)
	fmt.Println("\nFile successfully decrypted.")

}

func decryptHandle1() {

	if len(os.Args) < 4 {
		println("Missing the path to the file. For more information run CryptoGo help")
		os.Exit(0)
	}

	password := os.Args[2]

	file := os.Args[3]

	validateFile(file)

	fmt.Println("\nDecrypting...")
	filecrypt.Decrypt(file, []byte(password))
	fmt.Println("\nFile successfully decrypted.")
}

func validatePassword(password1 []byte, password2 []byte) bool {
	if !bytes.Equal(password1, password2) {
		return false
	}

	return true
}

func validateFile(file string) bool {
	if fileInfo, err := os.Stat(file); os.IsNotExist(err) {
		panic("File not found")
		return false
	} else if fileInfo.Size() > 2*1024*1024 {
		panic(fmt.Sprintf("max file size is 2M, your's is %d.", fileInfo.Size()))
		return false
	}

	return true
}
