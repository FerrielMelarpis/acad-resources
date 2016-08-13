 #include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;

int main()
{
    int arr[] = {0,1,2,2,1,0};
    int N = sizeof(arr)/sizeof(int);
    int i = 0, start = 0, end = N-1,no_of_swaps = 0;
    while(i<=end)
    {
        if(arr[i] == 0)//check for 0
        {   
            if(arr[start] != 0)
            {
                swap(arr[i], arr[start]);
                no_of_swaps++;
            }
            else
                i++;
            start++;
        }
        else if(arr[i] == 2)//check for 2
        {       
            if(arr[end] != 2)
            {
                swap(arr[i], arr[end]);
                no_of_swaps++;
            }
            end--;
        }
        else//do nothing for 1
            i++;
    }
    for(i = 0;i < N;i++)
    cout<<arr[i];
    cout<<endl;
    cout<<no_of_swaps<<endl;//printing how many swaps made
    return 0;
}
