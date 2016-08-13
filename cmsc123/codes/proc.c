#include <stdio.h>
#include <stdlib.h>

typedef struct nodetag node;
struct nodetag{
    node *next;
    int x;
};

void printmachine(node *h){
    node *i= h->next;
    while(i!=NULL){
        printf("%d ",i->x);
        i=i->next;
    }
}

void addtail(node *h, int x){
    node *i = h;
    while(i->next!=NULL){i=i->next;};
    i->next=malloc(sizeof(node));
    i->next->x = x;
    i->next->next=NULL;
}

int pophead(node *h){
    int tmpx;
    node *tmp = h->next;
    
    if(h->next==NULL){
        return -1;
    }
    
    h->next=h->next->next;
    tmpx=tmp->x;
    free(tmp);
    return tmpx;
}

int getsum(node *h){
    int sum=0;
    node *i= h->next;
    while(i!=NULL){
        sum+=i->x;
        i=i->next;
    }
    return sum;
}

int getindexofmin(node **m, int s){
    int minind=-1,min=900000,i,tmp;
    for(i=0;i<s;i++){
        tmp=getsum(m[i]);
        if(tmp<min){
            minind=i;
            min=tmp;
        }
    }
    return minind;
}

int read(node *h, node ***m){
    FILE *fp = fopen("in.txt","r");
    int tmp,i;
    do{
        fscanf(fp,"%d, ", &tmp);
        addtail(h,tmp);
    }while(fgetc(fp)!='\n');
    fscanf(fp,"%d", &tmp);
    *m=(node**)malloc(sizeof(node*)*tmp);
    for(i=0;i<tmp;i++){
        (*m)[i]=malloc(sizeof(node));
    }
    fclose(fp);
    return tmp;
}

int main(){
    node **m,*list = malloc(sizeof(node));
    int tmp,size=read(list, &m);
    while((tmp=pophead(list))>=0){
        addtail(m[getindexofmin(m,size)], tmp);
    }
    for(tmp=0;tmp<size;tmp++){
        printf("Machine %d: ",tmp);
        printmachine(m[tmp]);
        printf("\n");
    }
}