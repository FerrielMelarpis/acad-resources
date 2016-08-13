/*
 * The MIT License (MIT)
 * 
 * Copyright (c) <2014> <Ferriel Lisandro Baynosa Melarpis>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/
//libraries
#include <stdio.h>
#include <stdlib.h>
// function that creates a heap data type
int *create(int size){
    int *heap=(int*)malloc(sizeof(int)*size);
    int i;
    for(i=0;i<size;i++){
        heap[i]=-1;
    }
    return heap;
}
// function the returns the user's choice
int menu(){
    int choice;
    do{
        printf("%s%s%s%s%s%s%s",
            "**************MENU*************\n",
            "*[1] Insert element           *\n",
            "*[2] Delete the root of heap  *\n",
            "*[3] Heap Sort                *\n",
            "*[4] Exit                     *\n",
            "*******************************\n",
            "Enter choice: "
        );
        scanf("%d", &choice);
    }while(choice<1||choice>4);
    return choice;
}
// function for swapping 2 values
void swap(int *a, int *b){
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
}
// function for inserting to the heap
int heap_insert(int *a, int size, int x){
    int i;
    for(i=0;i<size;i++)
        if(a[i]==-1) break;
    if(i==size){
        fprintf(stderr,"Heap already full.\n");
        return;
    }
    a[i]=x;
    int j, ret=i, index=(i-1)/2;
    for(j=index;a[j]>a[i]||a[j]==-1;i=j, j=(j-1)/2)
        swap(&a[j], &a[i]);
    return ret;
}
// function for getting the user's input
int scan(){
    int num;
    printf("Enter number to insert: ");
    scanf("%d", &num);
    return num;
}
// function that deletes the minimum value and return it as integer
int deleteMin(int *a, int heap_size){
    int i;
    for(i=0;i<heap_size;i++)
        if(a[i]==-1) break;
    if(i==0) return -1;
    int index=i-1;
    int tmp=a[0];
    a[0]=a[index];
    a[index]=-1;
    int j=0;
    while(j*2+1<=index-1){
        if(a[j*2+1]!=-1&&a[j*2+2]!=-1){
            if(a[j]>=a[j*2+1]||a[j]>=a[j*2+2]){
                if(a[j*2+1]<=a[j*2+2]){
                    swap(&a[j],&a[j*2+1]);
                    j=(j*2)+1;
                }else if(a[j*2+2]<=a[j*2+1]){
                    swap(&a[j],&a[j*2+2]);
                    j=(j*2)+2;
                }
            }
        }else{
            if(a[j*2+1]==-1&&a[j*2+2]==-1){
                break;
            }else if(a[j*2+1]!=-1){
                if(a[j*2+1]<a[j])
                    swap(&a[j*2+1], &a[j]);
                else
                    break;
            }else{
                if(a[j*2+2]<a[j])
                    swap(&a[j*2+2], &a[j]);
                else
                 break;
            }
        }
    }
    return tmp;
}
// function that prints a sorted array from the values in the heap
void heapsort(int *a, int heap_size) {
    int i;
    int *b=create(heap_size);
    for(i=0;i<heap_size;i++)
        b[i]=a[i];
    for(i=0;i<heap_size;i++)
        printf("a[%d] = %d\n", i, deleteMin(b, heap_size));
    free(b);//free temporary copy of original heap
}
// function that prints the heap in a form of binary tree
void printHeap(int *a, int index, int tabs, int heap_size){
    int i;
    if(a!=NULL&&index<=heap_size){
        printHeap(a, index*2+1, tabs+1, heap_size);
        for(i=0;i<tabs;i++) printf("\t");
        printf("%d\n", a[index-1]);
        printHeap(a, index*2, tabs+1, heap_size);
    }
}
// main
int main(void){
    int heap_size;
    printf("Enter size of the heap: ");
    scanf("%d", &heap_size);
    int *a=create(heap_size);
    int choice, min;
    while((choice=menu())!=4){
        switch(choice){
            case 1:
                heap_insert(a, heap_size, scan());
                printHeap(a, 1, 1, heap_size);
                printf("--------------------------------------------------------\n");
                break;
            case 2:
                min=deleteMin(a, heap_size);
                if(min==-1) fprintf(stderr,"Heap is empty.\n");
                else
                    printHeap(a, 1, 1, heap_size);
                printf("--------------------------------------------------------\n");
                break;
            case 3:
                heapsort(a, heap_size);
                printf("--------------------------------------------------------\n");
                break;
        }
    }
    free(a);// free the heap
    return 0;
}
