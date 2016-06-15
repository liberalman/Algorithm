/*
 * @file search_binary.c
 * 详情请看 http://blog.csdn.net/socho/article/details/51684422
 */
#include <stdio.h>
#define N 10
void printA(int A[], char n){
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void printSearch(int A[], char n, int count, int low, int high){
    int i = 0;
    printf("第%d次折半,low %d,high %d :", count, low, high);
    for (i = 0; i < n; i++)
    {
        if (low == i)
            printf("[");
        printf(" %d ", A[i]);
        if (high == i)
            printf("]");
    }
    printf("\n");
}
int search_binary(int A[], int n, int Key)
{
    //在有序表R[0..n-1]中进行二分查找，成功时返回结点的位置，失败时返回-1
    int low = 0, high = n-1, mid = 0, count = 0;//置当前查找区间上、下界的初值
        while(low <= high)
        {
            //printf("第%d次查找 low:%d mid:%d high:%d\n", ++count, low, mid, high);
            if(Key == A[low])
                return low;
            if(Key == A[high])
                return high;
            //当前查找区间A[low..high]非空
            mid = low + ((high-low)/2); //使用(low+high)/2会有整数溢出的问题
            //（问题会出现在当low+high的结果大于表达式结果类型所能表示的最大值时，
            //这样，产生溢出后再/2是不会产生正确结果的，而low+((high-low)/2)不存在这个问题
            if(Key == A[mid])
                return mid;//查找成功返回
            if(A[mid] < Key)
            {
                low = mid + 1;//继续在A[mid+1..high]中查找
            }
            else
            {
                high = mid - 1;//继续在A[low..mid-1]中查找
            }
            printSearch(A, n, ++count, low, high);
        }
        if(low>high)
            return -1;//当low>high时表示所查找区间内没有结果，查找失败
}
int main(){
    int A[N] = { -10, 0, 1, 5, 7, 24, 31, 58, 59, 99};  //已排序好
    int pos = 0;
    printf("初始化:");
    printA(A, N);
    printf("查找1所在位置\n");
    pos = search_binary(A, N, 1);
    printf("1所在位置是 %d:\n", pos);
    printf("查找12所在位置\n");
    pos = search_binary(A, N, 12);
    printf("12所在位置是 %d:\n", pos);
    return 0;
}
