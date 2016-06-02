/*
 * 本源码是针对我的CSDN中的文章《对”堆”的理解》中的代码实现，连接http://blog.csdn.net/socho/article/details/51565498
 */
#include <stdio.h>
#define N 12
void printHeap(int A[]){
    printf("            -----------%d-----------\n", A[1]);
    printf("           /                       \\\n");
    printf("      ----%d-----               ----%d----\n", A[2], A[3]);
    printf("     /          \\             /          \\\n");
    printf("  --%d--     ---%d---     ---%d          %d\n", A[4], A[5], A[6], A[7]);
    printf(" /      \\   /        \\   /\n");
    printf("%d      %d %d        %d %d\n", A[8], A[9], A[10], A[11] , A[12]);
}
void printHeap1(int A[]){
    printf("            -----------%d-----------\n", A[1]);
    printf("           /                       \\\n");
    printf("      ----%d-----               ----%d----\n", A[2], A[3]);
    printf("     /          \\             /          \\\n");
    printf("  --%d--     ---%d---     ---%d---       %d\n", A[4], A[5], A[6], A[7]);
    printf(" /      \\   /        \\   /        \\\n");
    printf("%d      %d %d        %d %d        %d\n", A[8], A[9], A[10], A[11] , A[12], A[13]);
}
void swap(int A[], int t, int i){
    A[t] = A[t] ^ A[i];
    A[i] = A[t] ^ A[i];
    A[t] = A[i] ^ A[t];
}
/* 向下调整。
 * @param A 堆的线性存储方式，数组
 * @param n 节点总数
 * @param i 需要向下调整的节点编号
 */
void godown(int A[], int n, int i) //传入一个需要向下调整的结点编号i，这里传入1，即从堆的顶点开始向下调整 
{
    int t,flag=0,count=0;//flag用来标记是否需要继续向下调整 
    //当i结点有儿子的时候（其实是至少有左儿子的情况下）并且有需要继续调整的时候循环窒执行
    while( i*2<=n && flag==0 )
    {        
        //首先判断他和他左儿子的关系，并用t记录值较小的结点编号 
        if( A[i] > A[i*2] )
            t=i*2;
        else
            t=i; 
        //如果他有右儿子的情况下，再对右儿子进行讨论 
        if(i*2+1 <= n)
        {
            //如果右儿子的值更小，更新较小的结点编号  
            if(A[t] > A[i*2+1])
                t=i*2+1;
        }
        //如果发现最小的结点编号不是自己，说明子结点中有比父结点更小的  
        if(t!=i)
        {
            swap(A, t, i);//交换
            i=t;//更新i为刚才与它交换的儿子结点的编号，便于接下来继续向下调整
			printf("\n\n第 %d 次调整堆：\n", ++count);
			printHeap(A);
        }
        else
            flag=1;//则否说明当前的父结点已经比两个子结点都要小了，不需要在进行调整了,退出
    }
}
/* 向上调整。
 * @param A 堆的线性存储方式，数组
 * @param n 节点总数
 * @param i 需要向下调整的节点编号
 */
void goup(int A[], int n, int i) //传入一个需要向上调整的结点编号i
{
    int flag=0, count = 0; // flag用来标记是否需要继续向上调整
    if(1 == i)  return; //如果是堆顶，就返回，不需要调整了    
    //不在堆顶 并且 当前结点i的值比父结点小的时候继续向上调整 
    while(i!=1 && flag==0)
    {
        //判断是否比父结点的小 
		if (A[i]<A[i/2]) {
            swap(A, i, i/2);//交换和父节点的位置
			printf("\n\n第 %d 次调整堆：\n", ++count);
			printHeap1(A);
		}
        else
            flag=1;//表示已经不需要调整了，当前结点的值比父结点的值要大 
        i=i/2; //更新编号i为它父结点的编号，从而便于下一次继续向上调整 
    }
}


int main(){
    int A[N+2] = { 0, 2, 7, 24, 11, 67, 35, 25, 16, 19, 97, 80, 50}; // 这里为了直接展示调整堆算法，直接给出已经建好堆的数组，免去建堆这一步，A[0]是不使用的，堆从A[1]开始。
    printf("初始化堆:\n");
    printHeap(A);
    
    /*A[1] = 17; // 测试1，修改堆顶值
	printf("\n\n修改堆顶值为17:\n");
    printHeap(A);
    godown(A, N, 1);*/
    
    A[13] = 15; // 测试2，堆尾增加值
	printf("\n\n堆尾增加一个15:\n");
    printHeap1(A);
    goup(A, N, 13);
    
    return 0;
}
