/*
 * �����뿴 http://blog.csdn.net/socho/article/details/51584187
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
 * ����
 */
void swap(int arr[], int i, int j)
{
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[j] ^ arr[i];
}

/*
 * @param arr �����������
 * @param n �����С
 */
void bubble_sort(int arr[], int n)
{
    int i, j, temp;
    for (j = 0; j < n - 1; j++) // ������е�Ԫ���ظ����ɨ��Ĳ��裬�������һ����
    {
        for (i = 0; i < n - 1 - j; i++) // ��ÿһ������Ԫ�����Ƚϣ��ӿ�ʼ��һ�Ե���β n - 1 - j �����һ�ԡ���������ð��Ư�Ƶ������������Ԫ�ؾ�������������
        {
            if(arr[i] > arr[i + 1]) // �Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
            {
                swap(arr, i, i+1);
            }
        }
        // �����־
        printf("��%d��ɨ�裬��������%dð�ݵ�λ��arr[%d]�����Ա�%d��:\n", j+1, arr[n-1-j], n-1-j, n-1-j);
        printArr(arr, n);
        printf("\n\n");
    }

}

int main()
{
    int number[SIZE] = {101, -1, 16, 87, 84, 0, 25, 11, 2};
    int i;
    printf("ԭ����:\n");
    printArr(number, SIZE);
    printf("\n\n");
    bubble_sort(number, SIZE);
}