/*    
 *   A C program that detects a if there is a cycle in a graph. 
 *   NOTE: Vertices of the graph are labeled with integers.
 *   Copyright (C) 2014  Ferriel Lisandro B. Melarpis
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// libraries
#include <stdio.h>
#include <stdlib.h>
// defined macro variable 'vert'
#define vert 6
// defined ASCII characters for printing with color
#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define YEL "\x1b[33m"
#define BLU "\x1b[34m"
#define MAG "\x1b[35m"
#define CYN "\x1b[36m"
#define CLR "\x1b[m"
#define ITA "\x1b[3m"
#define UND "\x1b[4m"
#define BNK "\x1b[5m"
#define BRT "\x1b[1m"
// structure for making Adjacency List
typedef struct node AdjList;
struct node{
    int value;
    int weight;
    AdjList *next;
};
// function for creating a vertex
AdjList * createVertex(int value, int weight){
    AdjList *v=(AdjList*)malloc(sizeof(AdjList));
    v->value=value;
    v->weight=weight;
    v->next=NULL;
    return v;
}
// function for creating the adjacency list
AdjList ** createAdjList(int n){
    int i;
    AdjList **a = (AdjList**)malloc(sizeof(AdjList*)*n);
    for(i=0;i<n;i++)
        a[i]=createVertex(i, 0);
    return a;
}
// function for inserting a vertex in the adjacency list
AdjList ** insertEdge(AdjList **a, int pos, int value, int weight){
    AdjList *v=createVertex(value, weight);
    AdjList *u=createVertex(pos, weight);
    if(a[pos]->next==NULL){
        a[pos]->next=v;
        if(a[value]->next==NULL)
            a[value]->next=u;
        else{
            AdjList *p=a[value]->next;
            for(;p->next!=NULL&&p->value!=value;p=p->next);
                if(p->value!=value)
                p->next=u;
        }
    }else{
        AdjList *p=a[pos]->next;
        for(;p->next!=NULL&&p->value!=value;p=p->next);
        if(p->value!=value)
            p->next=v;
        if(a[value]->next==NULL)
            a[value]->next=u;
        else{
            AdjList *pp=a[value]->next;
            for(;pp->next!=NULL&&pp->value!=value;pp=pp->next);
                if(pp->value!=value)
                pp->next=u;
        }
    }
    return a;
}
// function for printing the Adjacency List
void printAdjList(AdjList **a, int n){
    AdjList *t=NULL;
    int i;
    printf(BRT YEL" _______"UND"Adjacency List"CLR BRT YEL"_______...\n"CLR);
    for(i=0;i<n;i++){
        if(a[i]!=NULL){
            printf(BRT YEL"|"BRT MAG"%d => "CLR, a[i]->value);
            for(t=a[i]->next;t!=NULL;t=t->next){
                if(t->next==NULL) printf(GRN BRT ITA"%d "CLR CYN UND"(%d)"CLR, t->value, t->weight);
                else printf(GRN BRT ITA"%d "CLR CYN UND"(%d)"CLR BLU BRT" -> "CLR, t->value, t->weight);
            }
            printf("\n");
        }
    }
    printf(BRT YEL"_____________________________...\n"CLR);
}
// void printPath(AdjList *path);
// function for containing path in a list
void insert(AdjList **path, int val){
    AdjList *tmp=createVertex(val, 0);
    if(*path==NULL){
        *path=tmp;
//         printPath(*path);
    }else{
        AdjList *t=*path;
        while(t->next!=NULL){
            if(t->value==val) return;
            t=t->next;
        }
        if(t->value==val) return;
        t->next=tmp;
    }
}
// function for processing Depth First Search Algorithm
int DFS(AdjList **a, int n, int prev, int *container, AdjList **path){
    AdjList *tmp=a[n]->next;
    insert(path, n);
    container[n]++;
    while(tmp!=NULL){
        if(tmp->value==prev){tmp=tmp->next; continue;}
        if(container[tmp->value]==0){
            if(DFS(a, tmp->value, n, container, path)==1) return 1;
        }else{
            return 1;
        }
        tmp=tmp->next;
    }
    return 0;
}
// function for creating empty array contatiner
int *createArray(int size){
    int *a = (int*)malloc(sizeof(int)*size);
    int i;
    for(i=0;i<size;i++) a[i]=0;
    return a;
}
// function for printing the path
void printPath(AdjList *path){
    if(path!=NULL){
        printf("PATH: ");
        while(path->next!=NULL){
            printf(BRT BLU"%d => ", path->value);
            path=path->next;
        }printf(BRT BLU"%d\n"CLR, path->value);
    }
}
// main
int main(void){
    AdjList **a=createAdjList(vert);
    AdjList *path=NULL;
    a = insertEdge(a, 0, 1, 11);
    a = insertEdge(a, 1, 2, 11);
    a = insertEdge(a, 4, 5, 11);
    a = insertEdge(a, 3, 4, 11);
    a = insertEdge(a, 2, 3, 11);
    printAdjList(a, vert);
    if(DFS(a, 0, 0, createArray(vert), &path)){
        printf(RED UND ITA BNK"A cycle is detected.\n"CLR);
    }else{
        printf(GRN UND ITA BNK"No cycles detected.\n"CLR);
        printPath(path);
    }
    return 0;
}
