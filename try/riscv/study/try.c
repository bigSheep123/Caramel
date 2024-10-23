#include<stdio.h>
void bubble_sort(int* arr,int n)
{
    for(int j = 0; j < n ;j++)
    {
        for(int i = 0; i < n -j -1; i++)
        {
            if(arr[i] > arr[i+1])
            {
                int tmp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

int main()
{
    int arr[] = {1,10,8,2,9,3,6,4,7,4,8,9,8};
    int len = sizeof(arr)/sizeof(arr[0]);
    // printf("%d",len);
    bubble_sort(arr,len);
    for(int i = 0; i < len; i++)
    {
        printf("%d  ",arr[i]);
    }

    return 0;
}
