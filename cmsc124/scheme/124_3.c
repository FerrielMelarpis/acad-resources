#include <stdio.h>
void segregate(int *arr,int n)
{
  register int count=n-1,count1,i;

 for(i=n-1;i>=0;i--)
  if(arr[i]!=0)
   arr[count--]=arr[i];

 count1=count;

 while(count>=0)
  arr[count--]=0;

  count=n-1;
 for(i=n-1;i>count1;i--)
  if(arr[i]!=1)
   arr[count--]=arr[i];

 while(count>count1)
  arr[count--]=1;
}

void printarray(int *arr,int n)
{
 register int i;
 for(i=0;i<n;i++)
  printf("%d ",arr[i]);
}

int main(void) {
	// your code goes here
	int arr[50],n,i;
 scanf("%d",&n);
 for(i=0;i<n;i++)
  scanf("%d",&arr[i]);
 segregate(arr,n);
 printarray(arr,n);
	return 0;
}
