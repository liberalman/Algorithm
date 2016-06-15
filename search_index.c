/*
 * �����뿴 http://blog.csdn.net/socho/article/details/51585522
 */
#include <stdio.h>

#define N 100 // ������󳤶�
#define M 30 // ��������󳤶�
int ROW_WIDTH = 10;
int index_cur_len = 0; // ������ǰ��Ч��������
int main_len = 0; // ������

/**
 * ����������ŵĹ�ϣ����
 */
#define hashindex(key) key / 100

/**
 * ������
 */
typedef struct
{
    int index; // ������ţ����ռ���̶���ÿ�г���index_width�����ݻ���Ϊһ�������Ρ�
    int start; // ������ʼλ�ã��Դ�Ϊ��׼�������������ݣ�start = (index - 1) * ROW_WIDTH��
    int length; // ��Ч���ݳ���
} IndexUnit;

/**
 * ����
 */
int main_table[N] = {
/*  177,189,100,123,111,0,0,0,0,0, // ����̶���ÿ�г��� ROW_WIDTH = 10������Ϊ0�Ĵ�����Ч����
    201,202,203,204,  0,0,0,0,0,0,
    301,302,303,  0,  0,0,0,0,0,0
*/
};


/**
 * ������
 */
IndexUnit index_table[M] = {
/*  {1, 0,5}, // ��һ�У���һ���������1���ڶ���������ʼλ�� 0 = (1 - 1) * 10����������Ч���ݳ�����5����
    {2,10,4}, // �ڶ��У���һ���������2���ڶ���������ʼλ��10 = (2 - 1) * 10����������Ч���ݳ�����4����
    {3,20,3}  // �����У���һ���������3���ڶ���������ʼλ��20 = (3 - 1) * 10����������Ч���ݳ�����3����
*/
};


void create_index(int *data, int length){
    int i = 0;
    int j = 0;
    // ��ʼ��������
    for (i = 0; i < M; i++){
        index_table[i].index = i + 1;
        index_table[i].start = i * ROW_WIDTH;
        index_table[i].length = 0;
    }
    // ������д�������������
    for (i = 0; i < length; i++){
        j = hashindex(data[i]);
        if(j > index_cur_len) //��¼�µ�ǰ��Ч��������
            index_cur_len = j;
        main_table[index_table[j-1].start + index_table[j-1].length++] = data[i];
    }
    main_len = index_cur_len * ROW_WIDTH;
}

/**
 * ���������㷨
 * @param key ����ֵ
 * @return ����ֵ�ڱ��е�λ��,����-1��ʾ�������в����ڸ�������
 */
int index_search(int key)
{
    int i = 0;
    int j = 0;
    int index = hashindex(key); // ���������

    //����������,�ҵ���Ӧ��������
    for (i = 0; i < index_cur_len; i++)
    {
        //�ҵ�������
        if (index_table[i].index == index)
        {
            //��Դ������˳����ң�Ҳ����ʹ�ö��ֲ��ҵ���������Ч�Ĳ��ҷ���������Ͳ���ʾ�ˣ�ֻ˵���������Ļ���ԭ��
            for (j = index_table[i].start; j < index_table[i].start + index_table[i].length; j++)
            {
                if (main_table[j] == key)
                {
                    return j;
                }
            }
            break;
        }
    }
    //�������в����ڸ�������
    return -1;
}

/**
 * ��������
 * @param key ����ֵ
 * @return 0,����ɹ�,����-1��ʾ�������в����ڸ�������
 */
int insert(int key)
{
    int i = 0;
    int index = hashindex(key); // ���������

    //����������,�ҵ���Ӧ��������
    for (i = 0; i < index_cur_len; i++)
    {
        if (index_table[i].index == index)
        {
            //�������ֵ���뵽�����У�����Ϊ�˽��͸��Ӷȣ�ֻ��ʾ����ĩβ׷�����ݡ�
            main_table[index_table[i].start + index_table[i].length] = key;
            //����������
            index_table[i].length++;
            return 0;
        }
    }
    //�������в����ڸ�������
    return -1;
}

int main()
{
    int test[20] = {177,202,189,123,111,302,201,203,301,204,303,100};
    int testlen = 12;
    int value = 245;
    int i = 0;

    printf("================= initial ===================\n");
    printf("ԭ����:\t");
    for(i = 0; i < testlen; i++){
        printf("%d\t", test[i]);
    }

    create_index(test, testlen);

    printf("\n����:");
    for(i = 0; i < main_len; i++){
        if(0 == i % 10)
            printf("\n");
        printf("%d\t", main_table[i]);
    }

    printf("\n������:\n");
    for(i = 0; i < index_cur_len; i++){
        printf("{index=%d, start=%d, length=%d}\n", index_table[i].index, index_table[i].start, index_table[i].length);
    }

    printf("\n================= insert ===================\n");
    printf("��������: %d\n", value);
    //����ɹ�
    if (0 == insert(value))
    {
        printf("��������:");
        for(i = 0; i < main_len; i++){
            if(0 == i % 10)
                printf("\n");
            printf("%d\t", main_table[i]);
        }
        printf("\n����������:\n");
        for(i = 0; i < index_cur_len; i++){
            printf("{index=%d, start=%d, length=%d}\n", index_table[i].index, index_table[i].start, index_table[i].length);
        }

        printf("\nͨ�������㷨���� %d ���������е�λ����:main_table[%d]\n", value, index_search(value));
    }
    return 0;
}
