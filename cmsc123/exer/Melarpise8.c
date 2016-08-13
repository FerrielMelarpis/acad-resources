/*
* The MIT License (MIT)
* 
* Copyright (c) 2014 Ferriel Lisandro B. Melarpis
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
// defined ASCII characters for printing with color
#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define YEL "\x1b[33m"
#define BLU "\x1b[34m"
#define MAG "\x1b[35m"
#define CYN "\x1b[36m"
// defined ASCII characters for other effects in terminal
#define CLR "\x1b[m"
#define ITA "\x1b[3m"
#define UND "\x1b[4m"
#define BNK "\x1b[5m"
#define BRT "\x1b[1m"
// function for printing the array
void printArray(int *a, int size){
    int i;
    for(i=0;i<size-1;i++){
        if(a[i]==-1) printf(UND RED"%3d"CLR BLU"=>"CLR, a[i]);
        else printf(UND GRN"%3d"CLR BLU"=>"CLR, a[i]);
    }
    if(a[i]==-1) printf(UND RED"%3d"CLR"\n", a[i]);
    else printf(UND GRN"%3d"CLR"\n", a[i]);
}
// function for finding the maximum value in an array
int findMax(int *a, int size){
    int i, max=a[0];
    for(i=1;i<size;i++)
        max = max<a[i]? a[i]:max;
    return max;
}
// function for counting sort
int * count_sort(int *bucket, int bucket_size){
    int i, j, index, max=findMax(bucket, bucket_size);
    int *count=(int*)malloc(sizeof(int)*(max+1));
    for(i=0;i<=max;i++)
        count[i]=0;
    for(i=0;i<bucket_size;i++){
        if(bucket[i]!=-1)
            count[bucket[i]]++;
    }
    for(i=1;i<=max;i++){
        count[i]+=count[i-1];
    }
    int *ret=(int*)malloc(sizeof(int)*bucket_size);
    for(i=0;i<bucket_size;i++)
        ret[i]=-1;
    for(i=0;i<bucket_size;i++){
        if(bucket[i]!=-1){
            ret[count[bucket[i]]--]=bucket[i];
        }
    }
    return ret;
}

// function for sorting input array from user by using bucket and counting sorting algorithms
void bucket_sort(int *a, int array_size, int range, int bucket_size){
    int i, j, **bucket, b=(range/bucket_size);
    if(range%bucket_size!=0) b++;
    printf(CYN"Initializing buckets...\n"CLR);
    bucket=(int**)malloc(sizeof(int)*b);
    for(i=0;i<b;i++){
        bucket[i]=(int*)malloc(sizeof(int)*range);
        for(j=0;j<array_size;j++)
            bucket[i][j]=-1;
    }
    for(i=0;i<b;i++){
        printf(YEL"Bucket[%d] >> "CLR, i);
        printArray(bucket[i], array_size);
    }
    printf(CYN"Pushing inputs into the buckets...\n"CLR);
    for(i=0;i<array_size;i++){
        int bucket_index=a[i]/bucket_size;
        for(j=0;j<range;j++){
            if(bucket[bucket_index][j]==-1){
                bucket[bucket_index][j]=a[i];
                break;
            }
        }
    }
    for(i=0;i<b;i++){
        printf(YEL"Bucket[%d] >> "CLR, i);
        printArray(bucket[i], array_size);
    }
    printf(CYN BRT"Processing counting sort within buckets...\n"CLR);
    for(i=0;i<b;i++){
        bucket[i]=count_sort(bucket[i], array_size);
        printArray(bucket[i], array_size);
    }
    printf(CYN BRT"Concatenating sorted buckets...\n"CLR);
    for(i=0;i<b;i++){
        for(j=0;j<array_size;j++){
            if(bucket[i][j]!=-1) printf(UND GRN"\t[%d]"CLR, bucket[i][j]);    
        }
    }
    printf("\n");
}
// main
int main(int argc, char *argv[]){
    if(argc<2){
        fprintf(stderr,"\x1b[31mUsage: %s <number inputs>\x1b[m\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf(MAG BNK"______"CLR BRT MAG "Bucket-Counting Sort" CLR MAG BNK"______\n"CLR);
    int i, range, bsize, *input, size=argc-1;
    printf("Enter Max_Range: ");
    scanf("%d", &range);
    printf("Enter Bucket_Size: ");
    scanf("%d", &bsize);
    input=(int*)malloc(sizeof(int)*size);
    for(i=0;i<size;i++)
        input[i]=atoi(argv[i+1]);
    printf(CYN"Array Input by User...\n"CLR);
    printArray(input, size);
    bucket_sort(input, size, range, bsize);
    printf(BRT ITA RED"______END OF PROGRAM______\n"CLR);
    exit(EXIT_SUCCESS);
}