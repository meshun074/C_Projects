#include<cs50.h>
#include<stdio.h>

int len;
void accept_input_numbers(int array[], int array_len)
{
    printf("Enter %i numbers \n",array_len);
    for(int i = 0; i < array_len; i++)
    {
        array[i] = get_int("");
    }
}

void print_sorted_array(int a[], int size)
{
    printf("Sorted aray\n");
    for(int i = 0; i < size; i++)
    {
        printf("%i ",a[i]);
    }
    printf("\n");
}

void merge(int arr[], int start, int middle, int end)
{
    int arrb[len];
    int m = middle + 1;
    int s = start;
    int b = start;
    while(s <= middle && m<= end)
    {
        if(arr[s]<arr[m])
        {
            arrb[b++]=arr[s++];
        }
        else if(arr[s]>arr[m])
        {
            arrb[b++]=arr[m++];
        }
        else
        {
            arrb[b++]=arr[s++];
            arrb[b++]=arr[m++];
        }
    }
    while(s <= middle)
    {
        arrb[b++]=arr[s++];
    }
    while(m <= end)
    {
        arrb[b++]=arr[m++];
    }
    for(int i = start; i <= end; i++)
    {
        arr[i] = arrb[i];
    }
    printf("start: %i end: %i middle: %i\n",start, end, middle);
    print_sorted_array(arr, len);

}

void mergesort(int c[], int start, int end)
{
    if(start < end)
    {
        int middle=(start+end)/2;
        mergesort(c, start, middle);
        mergesort(c, middle + 1, end);
        merge(c, start, middle, end);
    }
}




int main()
{
    len = get_int("Enter the size of number you want to sort: ");
    int b[len];
    accept_input_numbers(b, len);
    mergesort(b, 0, len-1);
    print_sorted_array(b, len);
}
