/*
 * @file search_binary.c
 * ?????? http://blog.csdn.net/socho/article/details/51684422
 */
#include #define N 10
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
    printf("??%d?????,low %d,high %d :", count, low, high);
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
    //???????R[0..n-1]?��??��??????????????????��???????????-1
    int low = 0, high = n-1, mid = 0, count = 0;//?????????????????????
        while(low <= high)
        {
            //printf("??%d?��??? low:%d mid:%d high:%d\n", ++count, low, mid, high);
            if(Key == A[low])
                return low;
            if(Key == A[high])
                return high;
            //???????????A[low..high]???
            mid = low + ((high-low)/2); //???(low+high)/2?????????????????
            //?????????????low+high?????????????????????????????????
            //?????????????????/2???????????????????low+((high-low)/2)?????????????
            if(Key == A[mid])
                return mid;//??????????
            if(A[mid] < Key)
            {
                low = mid + 1;//??????A[mid+1..high]?��???
            }
            else
            {
                high = mid - 1;//??????A[low..mid-1]?��???
            }
            printSearch(A, n, ++count, low, high);
        }
        if(low>high)
            return -1;//??low>high??????????????????��???????????
}
int main(){
    int A[N] = { -10, 0, 1, 5, 7, 24, 31, 58, 59, 99};  //???????
    int pos = 0;
    printf("?????:");
    printA(A, N);
    printf("????1????��??\n");
    pos = search_binary(A, N, 1);
    printf("1????��???? %d:\n", pos);
    printf("????12????��??\n");
    pos = search_binary(A, N, 12);
    printf("12????��???? %d:\n", pos);
    return 0;
}