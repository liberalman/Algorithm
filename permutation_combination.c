/*
 * �����뿴 http://blog.csdn.net/socho/article/details/51586749
 */
#include <stdio.h>
#include <stdlib.h>

int array[] = {1,2,3,4};

#define N  4
#define M  3
int results[N] = {0}; //�����Ѿ��ҵ��Ľ��ǰ׺����
int results_end = 0; //���ǰ׺������Ч�����±�
int is_used[N] = {0}; //�Ƿ��Ѿ����й��˵ı�־

/**
 * ����
 * @param deep �ݹ����
 * @param n ������󳤶�
 */
void perm(int deep, int n)
{
    int i;
    if (deep > n) // Խ��ݹ����
    {
        return;
    }

    if (deep == n) // �ҵ��������ӡ���ݹ����
    {
        for (i = 0; i < n; i++)
        {
            printf("%d", results[i]);
        }
        printf("\t");
        return ;
    }

    for (i = 0; i < n; i++)
    {
        if (is_used[i] == 0)
        {
            is_used[i] = 1;
            results[deep] = array[i];
            perm(deep+1, n);
            is_used[i] = 0;
        }
    }
}

/**
 * ���
 * @param deep �ݹ����
 * @param n ������󳤶�
 * @param m Ҫ���ҵ���ϵĳ���
 */
void comb(int deep, int n, int m)
{
    int i = 0;
    if (deep > n) // Խ��ݹ����
        return ;
    if (results_end == m) // �ҵ��������ӡ���ݹ����
    {
        for (i = 0; i < m; i++)
        {
            printf("%d", results[i]);
        }
        printf("\t");
        return ;
    }
    results[results_end++] = array[deep];
    comb(deep+1, n, m); //����һ���ݹ�
    results_end--;
    comb(deep+1, n, m); //����һ���ݹ�
}

int main()
{
    int i = 0;
    printf("ȫ����:\n");
    perm(0, N);
    printf("\n1~%d���������:\n", N);
    for(i=1; i<=N; i++){
        comb(0, N, i);
    }
    printf("\n");
    return 0;
}