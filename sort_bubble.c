/*
 * 详情请看 http://blog.csdn.net/socho/article/details/51584187
 */
#include <stdio.h>
#define SIZE 9

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

/*
 * 交换
 */
void swap(int arr[], int i, int j)
{
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[j] ^ arr[i];
}

/*
 * @param arr 待排序的数组
 * @param n 数组大小
 */
void bubble_sort(int arr[], int n)
{
    int i, j, temp;
    for (j = 0; j < n - 1; j++) // 针对所有的元素重复向后扫描的步骤，除了最后一个。
    {
        for (i = 0; i < n - 1 - j; i++) // 对每一对相邻元素作比较，从开始第一对到结尾 n - 1 - j 的最后一对。将最大的数冒泡漂移到最后，所以最后的元素就是是最大的数。
        {
            if(arr[i] > arr[i + 1]) // 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
            {
                swap(arr, i, i+1);
            }
        }
        // 输出日志
        printf("第%d次扫描，将最大的数%d冒泡到位置arr[%d]，共对比%d次:\n", j+1, arr[n-1-j], n-1-j, n-1-j);
        printArr(arr, n);
        printf("\n\n");
    }

}

int main()
{
    int number[SIZE] = {101, -1, 16, 87, 84, 0, 25, 11, 2};
    int i;
    printf("原序列:\n");
    printArr(number, SIZE);
    printf("\n\n");
    bubble_sort(number, SIZE);
}