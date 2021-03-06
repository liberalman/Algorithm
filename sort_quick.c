/*
 * 详情请看 http://blog.csdn.net/socho/article/details/51591293
 */
#include <stdio.h>
#define N 9
int A[N] = { 10, -3 , 28, 76, 37, 55, -1, 99, 11};
void printArr(int arr[], int length)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void quick_sort(int a[],int numsize) //a是整形数组，numsize是元素个数 
{ 
    int i = 0, j = numsize-1;
    int val = a[0];//指定参考值val大小
    if(numsize>1)//确保数组长度至少为2，否则无需排序 
    {
        while(i<j)//循环结束条件
        {

            for( ; i < j; j--) //从后向前搜索比val小的元素，找到后填到a[i]中并跳出循环 
                if(a[j]<val)
                {
                    a[i]=a[j];
                    printf("参考值%d，前 <-- 后 找a[j--]<%d的元素| ", val, val);
                    printArr(a, numsize);
                    break;
                }
            for(;i<j;i++)//从前往后搜索比val大的元素，找到后填到a[j]中并跳出循环 
                if(a[i]>val)
                {
                    a[j]=a[i];
                    printf("参考值%d，前 --> 后 找a[i++]>%d的元素| ", val, val);
                    printArr(a, numsize);
                    break;
                }
        }
        a[i]=val; //将保存在val中的数放到a[i]中
        printf("参考值%d，整理结果\t\t     | ", val);
        printArr(a, numsize);
        quick_sort(a,i); //递归，对前i个数排序 
        quick_sort(a+i+1,numsize-1-i); //对i+1到numsize这numsize-1-i个数排序 
    }

}
int main()
{
    quick_sort(A, N);
    return 0;
}