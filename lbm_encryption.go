package main

import (
    "bytes"
    "crypto/aes"
    "crypto/cipher"
    "encoding/base64"
    "fmt"
    "flag"
    "os"
    "io/ioutil"
    //"strings"
)

func main() {
    if len(os.Args) < 2 {
        fmt.Println("at least 2 param. please -h")
        return
    }

    var key string
    var src string
    var file string
    flag.StringVar(&key, "k", "", "Key")
    flag.StringVar(&src, "s", "", "Source string")
    flag.StringVar(&file, "f", "", "Filenaame")
    isDecry := flag.Bool("d", false, "Is Decrypt String? in default, it will encry string, if it is true, will decry")
    help := flag.Bool("h", false, "help")
    flag.Parse()

    var result []byte
    var err error

    if *help {
        fmt.Print("-d in default,it will encrypt stirng,if you use this option, it will decript.\n-k key\n-s source string\n-f filename, use a file.")
        return
    }

    if "" != file {
        var fileBuff []byte
        fileBuff, err = ioutil.ReadFile(file)
        if err != nil {
            panic(err)
        }
        src = string(fileBuff)
    }

    if *isDecry {
        var data []byte
        data, err = base64.StdEncoding.DecodeString(src)
        if err != nil {
            panic(err)
        }
        result, err = AesDecrypt(data, key)
        if err != nil {
            panic(err)
        }
        fmt.Println(string(result))
    } else {
        result, err = AesEncrypt(src, key)
        if err != nil {
            panic(err)
        }
        fmt.Println(base64.StdEncoding.EncodeToString(result))
    }
}

func getKey(keyStr string) []byte {
    // AES-128。key长度：16, 24, 32 bytes 对应 AES-128, AES-192, AES-256
    keyLen := len(keyStr)
    if keyLen < 16 {
        /*//不够16的，0来填充
        b := make([]byte,16)
        strings.NewReader(keyStr).Read(b)
        return b*/
        panic("key 长度不能小于16个字符")
    }
    arrKey := []byte(keyStr)
    if keyLen >= 32 {
        //取前32个字节
        return arrKey[:32]
    }
    if keyLen >= 24 {
        //取前24个字节
        return arrKey[:24]
    }
    //取前16个字节
    return arrKey[:16]
}

func AesEncrypt(src string, keyStr string) ([]byte, error) {
    origData := []byte(src)
    key := getKey(keyStr)
    block, err := aes.NewCipher(key)
    if err != nil {
        return nil, err
    }
    blockSize := block.BlockSize()
    origData = PKCS5Padding(origData, blockSize)
    //origData = ZeroPadding(origData, block.BlockSize())
    blockMode := cipher.NewCBCEncrypter(block, key[:blockSize])
    crypted := make([]byte, len(origData))
    // 根据CryptBlocks方法的说明，如下方式初始化crypted也可以
    blockMode.CryptBlocks(crypted, origData)
    return crypted, nil
}

func AesDecrypt(crypted []byte, keyStr string) ([]byte, error) {
    key := getKey(keyStr)
    block, err := aes.NewCipher(key)
    if err != nil {
        return nil, err
    }
    blockSize := block.BlockSize()
    blockMode := cipher.NewCBCDecrypter(block, key[:blockSize])
    origData := make([]byte, len(crypted))
    blockMode.CryptBlocks(origData, crypted)
    origData = PKCS5UnPadding(origData)
    return origData, nil
}

func ZeroPadding(ciphertext []byte, blockSize int) []byte {
    padding := blockSize - len(ciphertext)%blockSize
    padtext := bytes.Repeat([]byte{0}, padding)
    return append(ciphertext, padtext...)
}

func ZeroUnPadding(origData []byte) []byte {
    length := len(origData)
    unpadding := int(origData[length-1])
    return origData[:(length - unpadding)]
}

func PKCS5Padding(ciphertext []byte, blockSize int) []byte {
    padding := blockSize - len(ciphertext)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    return append(ciphertext, padtext...)
}

func PKCS5UnPadding(origData []byte) []byte {
    length := len(origData)
    // 去掉最后一个字节 unpadding 次
    unpadding := int(origData[length-1])
    return origData[:(length - unpadding)]
}
