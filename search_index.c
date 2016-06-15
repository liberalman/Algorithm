/*
 * 详情请看 http://blog.csdn.net/socho/article/details/51585522
 */
#include <stdio.h>

#define N 100 // 主表最大长度
#define M 30 // 索引表最大长度
int ROW_WIDTH = 10;
int index_cur_len = 0; // 索引表当前有效索引长度
int main_len = 0; // 主表长度

/**
 * 计算索引编号的哈希函数
 */
#define hashindex(key) key / 100

/**
 * 索引项
 */
typedef struct
{
    int index; // 索引编号，按照间隔固定的每行长度index_width个数据划分为一个索引段。
    int start; // 索引起始位置，以此为基准搜索本行内数据，start = (index - 1) * ROW_WIDTH；
    int length; // 有效数据长度
} IndexUnit;

/**
 * 主表
 */
int main_table[N] = {
/*  177,189,100,123,111,0,0,0,0,0, // 主表固定的每行长度 ROW_WIDTH = 10，后面为0的代表无效数据
    201,202,203,204,  0,0,0,0,0,0,
    301,302,303,  0,  0,0,0,0,0,0
*/
};


/**
 * 索引表
 */
IndexUnit index_table[M] = {
/*  {1, 0,5}, // 第一行：第一列索引编号1；第二列索引起始位置 0 = (1 - 1) * 10；第三列有效数据长度是5个；
    {2,10,4}, // 第二行：第一列索引编号2；第二列索引起始位置10 = (2 - 1) * 10；第三列有效数据长度是4个；
    {3,20,3}  // 第三行：第一列索引编号3；第二列索引起始位置20 = (3 - 1) * 10；第三列有效数据长度是3个；
*/
};


void create_index(int *data, int length){
    int i = 0;
    int j = 0;
    // 初始化索引表
    for (i = 0; i < M; i++){
        index_table[i].index = i + 1;
        index_table[i].start = i * ROW_WIDTH;
        index_table[i].length = 0;
    }
    // 将数据写入主表和索引表
    for (i = 0; i < length; i++){
        j = hashindex(data[i]);
        if(j > index_cur_len) //记录下当前有效索引长度
            index_cur_len = j;
        main_table[index_table[j-1].start + index_table[j-1].length++] = data[i];
    }
    main_len = index_cur_len * ROW_WIDTH;
}

/**
 * 索引查找算法
 * @param key 给定值
 * @return 给定值在表中的位置,返回-1表示索引表中不存在该索引项
 */
int index_search(int key)
{
    int i = 0;
    int j = 0;
    int index = hashindex(key); // 求索引编号

    //遍历索引表,找到对应的索引项
    for (i = 0; i < index_cur_len; i++)
    {
        //找到索引项
        if (index_table[i].index == index)
        {
            //在源数据中顺序查找，也可以使用二分查找等其他更高效的查找方法，这里就不演示了，只说明下索引的基本原理。
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
    //索引表中不存在该索引项
    return -1;
}

/**
 * 插入数据
 * @param key 给定值
 * @return 0,插入成功,返回-1表示索引表中不存在该索引项
 */
int insert(int key)
{
    int i = 0;
    int index = hashindex(key); // 求索引编号

    //遍历索引表,找到对应的索引项
    for (i = 0; i < index_cur_len; i++)
    {
        if (index_table[i].index == index)
        {
            //依索引项将值插入到主表中，这里为了降低复杂度，只演示了在末尾追加数据。
            main_table[index_table[i].start + index_table[i].length] = key;
            //更新索引表
            index_table[i].length++;
            return 0;
        }
    }
    //索引表中不存在该索引项
    return -1;
}

int main()
{
    int test[20] = {177,202,189,123,111,302,201,203,301,204,303,100};
    int testlen = 12;
    int value = 245;
    int i = 0;

    printf("================= initial ===================\n");
    printf("原数据:\t");
    for(i = 0; i < testlen; i++){
        printf("%d\t", test[i]);
    }

    create_index(test, testlen);

    printf("\n主表:");
    for(i = 0; i < main_len; i++){
        if(0 == i % 10)
            printf("\n");
        printf("%d\t", main_table[i]);
    }

    printf("\n索引表:\n");
    for(i = 0; i < index_cur_len; i++){
        printf("{index=%d, start=%d, length=%d}\n", index_table[i].index, index_table[i].start, index_table[i].length);
    }

    printf("\n================= insert ===================\n");
    printf("插入数据: %d\n", value);
    //插入成功
    if (0 == insert(value))
    {
        printf("插入主表:");
        for(i = 0; i < main_len; i++){
            if(0 == i % 10)
                printf("\n");
            printf("%d\t", main_table[i]);
        }
        printf("\n更新索引表:\n");
        for(i = 0; i < index_cur_len; i++){
            printf("{index=%d, start=%d, length=%d}\n", index_table[i].index, index_table[i].start, index_table[i].length);
        }

        printf("\n通过索引算法查找 %d ，在主表中的位置是:main_table[%d]\n", value, index_search(value));
    }
    return 0;
}
