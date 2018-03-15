# Algorithm
基本算法分享，都是一些独立的小文件</br>
###数据结构
| 源文件名称 | 相关文章名称 | 相关文章链接 |
| -------------:|:-------------:| :----- |
| datastruct_heap.c | 《对”堆”的理解》 | http://blog.csdn.net/socho/article/details/51565498 |
###排序算法
| 源文件名称 | 相关文章名称 | 相关文章链接 |
| -------------:|:-------------:| :----- |
| permutation_combination.c | 《排列组合 C语言实现》 | http://blog.csdn.net/socho/article/details/51586749 |
| sort_bubble.c | 《冒泡排序》 | http://blog.csdn.net/socho/article/details/51584187 |
| sort_quick.c | 《快速排序》 | http://blog.csdn.net/socho/article/details/51591293 |
###搜索算法
| 源文件名称 | 相关文章名称 | 相关文章链接 |
| -------------:|:-------------:| :----- |
| search_index.c | 《索引查找》 | http://blog.csdn.net/socho/article/details/51585522 |
| search_binary.c | 《二分查找》 | http://blog.csdn.net/socho/article/details/51684422 |


## lbm_encryption.go
编译：
```
$ go build lbm_encryption.go
```
会在当前目录生成可执行文件 lbm_encryption

使用示例：

加密
```
./lbm_encryption -k 1234567890123456 -s libertyblog是一个有思想的博客站点
```
其中，-k表示加密用的key，必须16个字符以上，-s表示待加密的字符串。结果是一个base64的编码串

解密
```
./lbm_encryption -d -k 1234567890123456 -s mm8DtT7ekMpPl4rFmTEui0FOjqhS2OKD0SuEDaSE+/za9cdt7khB5FFzApq2p5VS
libertyblog是一个有思想的博客站点
```
可以看到参数多增加了一个-d，代表这是解密操作。-s输入的待解密字符串也是一个base64编码后的串。
