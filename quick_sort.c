/*
 * �����뿴 http://blog.csdn.net/socho/article/details/51591293
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
void quick_sort(int a[],int numsize) //a���������飬numsize��Ԫ�ظ��� 
{ 
    int i = 0, j = numsize-1;
    int val = a[0];//ָ���ο�ֵval��С
    if(numsize>1)//ȷ�����鳤������Ϊ2�������������� 
    {
        while(i<j)//ѭ����������
        {

            for( ; i < j; j--) //�Ӻ���ǰ������valС��Ԫ�أ��ҵ����a[i]�в�����ѭ�� 
                if(a[j]<val)
                {
                    a[i]=a[j];
                    printf("�ο�ֵ%d��ǰ <-- �� ��a[j--]<%d��Ԫ��| ", val, val);
                    printArr(a, numsize);
                    break;
                }
            for(;i<j;i++)//��ǰ����������val���Ԫ�أ��ҵ����a[j]�в�����ѭ�� 
                if(a[i]>val)
                {
                    a[j]=a[i];
                    printf("�ο�ֵ%d��ǰ --> �� ��a[i++]>%d��Ԫ��| ", val, val);
                    printArr(a, numsize);
                    break;
                }
        }
        a[i]=val; //��������val�е����ŵ�a[i]��
        printf("�ο�ֵ%d��������\t\t     | ", val);
        printArr(a, numsize);
        quick_sort(a,i); //�ݹ飬��ǰi�������� 
        quick_sort(a+i+1,numsize-1-i); //��i+1��numsize��numsize-1-i�������� 
    }

}
int main()
{
    quick_sort(A, N);
    return 0;
}