/*    
 *   A C program implementation of Prim's Algorithm that finds the minimum    
 *                    spanning tree of a given graph. 
 *   NOTE: Vertices of the graph are labeled with integers.
 *   Copyright (C) 2014  Ferriel Lisandro B. Melarpis 
 *                 (University of the Philippines Los Banos)
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
#include <stdio.h>// standard input and output C functions
#include <stdlib.h>// standard library of C memory accessing functions
// predefined ASCII characters for printing with colors
#define RED "\e[31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define MAG "\e[35m"
#define CYN "\e[36m"
#define CLR "\e[m"
#define BRT "\e[1m"
#define BRED "\e[41m"
// structure of adjacency matrix
typedef struct{
    int size;
    int **matrix;
}AdjMatrix;
// function for creating Adjacency Matrix
AdjMatrix * createAdjMatrix(int size){
    AdjMatrix *m=(AdjMatrix*)malloc(sizeof(AdjMatrix));
    m->size=size;
    m->matrix=(int**)malloc(sizeof(int)*size);
    int i,j;
    for(i=0;i<size;i++){
        m->matrix[i]=(int*)malloc(sizeof(int)*size);
        for(j=0;j<size;j++)
            m->matrix[i][j]=0;
    }
    return m;
}
// function for printing Adjacency Matrix
printMatrix(AdjMatrix *m){
    int i,j;
    printf(CYN"<<MATRIX>>\n"CLR);
    for(i=0;i<m->size;i++) printf(RED"\t%d"CLR, i);
    printf("\n");
    for(i=0;i<m->size;i++){
        printf(RED"%d\t"CLR, i);
        for(j=0;j<m->size;j++){
            if(m->matrix[i][j]==0)
                printf(YEL"__\t"CLR);
            else
                printf(GRN"%d\t"CLR, m->matrix[i][j]);
        }
        printf("\n"CLR);
    }
    printf(CLR);
}
// function for adding edge to the graph
void insertEdge(AdjMatrix *m, int x, int y, int weight){
    if(x==y){
        fprintf(stderr, BRED"Aesir"CLR RED": Invalid edge input.\n"CLR);
        return;
    }
    m->matrix[x][y]=m->matrix[y][x]=weight;
}
// function for getting the index of minimum value detected in a row
int getMinIndex(AdjMatrix *m, int col){
    int i;
    int min=0x418935;
    int index=-1;
    for(i=0;i<m->size;i++){
        if(m->matrix[i][col]!=0&&m->matrix[i][col]<min){
            min=m->matrix[i][col];
            index=i;
        }
    }
    return index;
}
// function for getting the index of minimum value detected in all the visited columns
int getMinVisitedIndex(AdjMatrix *m){
    int i,j;
    int min=0x418935;
    int index=-1;
    for(i=0;i<m->size;i++){
        for(j=0;j<m->size;j++){
            if(m->matrix[i][j]!=0&&m->matrix[i][j]<min){
                min=m->matrix[i][j];
                index=j;
            }
        }
    }
    return index;
}
// function that makes a row empty
void clearRow(AdjMatrix *m, int row){
    int i;
    for(i=0;i<m->size;i++) m->matrix[row][i]=0;
}
// function that finds the minimum spanning tree and computes the total weight of the tree
void prim(AdjMatrix *m, int vertex, int *totalWeight){
    int i,min,index, index_visited;
    clearRow(m,vertex);
    index=getMinIndex(m, vertex);
    if(index!=-1){ 
        printf(CYN"|%d"GRN" <==> "CYN"%d| "GRN"= "BLU BRT"%d\n"CLR, index, vertex, m->matrix[index][vertex]);
        *totalWeight+=m->matrix[index][vertex];
        prim(m, index, totalWeight);
    }else if((index_visited=getMinVisitedIndex(m))!=-1){
        prim(m, index_visited, totalWeight);
    }
}
// function that prints menu
int menu(){
    int choice;
    choose:
    printf("%s%s%s%s%s%s",
           CYN"________MENU________\n"CLR,
           CYN"[1]"GRN" Insert Edge\n",
           CYN"[2]"GRN" Print Matrix\n",
           CYN"[3]"GRN" Get Minimum Spanning Tree\n",
           CYN"[4]"RED" Exit\n",
           CYN"Aesir:"GRN"Enter choice>> "CLR
    );
    scanf("%d", &choice);
    if(choice<0||choice>4){
        printf(BRED"Aesir:"CLR RED"Invalid choice!\n"CLR);
        goto choose;
    }
    return choice;
}
// main function
int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, BRED"Aesir"CLR RED": USAGE: %s <size of matrix>\n"CLR, argv[0]);
        exit(EXIT_FAILURE);
    }
    printf(BRED BRT YEL"PROGRAM START\x1b[40m\n"CLR);
    int size=atoi(argv[1]);
    AdjMatrix *m=createAdjMatrix(size);
    int choice,totalWeight=0, u, v, weight;
    do{
        choice=menu();
        switch(choice){
            case 1:
                printf(CYN"Aesir:"GRN" Enter first vertex of edge>> "CLR);
                scanf("%d", &u);
                printf(CYN"Aesir:"GRN" Enter second vertex of edge>> "CLR);
                scanf("%d", &v);
                printf(CYN"Aesir:"GRN" Enter weight of edge>> "CLR);
                scanf("%d", &weight);
                if((u>=0&&u<size)&&(v>=0&&v<size))
                insertEdge(m, u, v, weight);
                break;
            case 2: 
                printMatrix(m);
                break;
            case 3: 
                prim(m, 0, &totalWeight);
                printf(CYN"Aesir"GRN": The total weight of the minimum spanning tree is "BRT BLU"%d"CLR GRN".\n"CLR, totalWeight);
                if(totalWeight==0)
                    printf(CYN"Aesir:"GRN" Hence, Matrix is still empty.\n"CLR);
                break;
        }
    }while(choice!=4);
    printf(BRT BRED YEL"END OF PROGRAM\n"CLR);
    return EXIT_SUCCESS;
}// end of program