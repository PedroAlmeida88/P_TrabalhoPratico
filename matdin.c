// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#include "stdio.h"
#include "stdlib.h"


void libertaTabuleiro(char ***mat,int tabs,int nLin){
    for (int i = 0; i < tabs; i++)
    {
        for (int j = 0; j < nLin; j++) {
            free(mat[i][j]);
        }
        free(mat[i]);
    }
    free(mat);
}

char*** criaTabuleiro(int tabs,int nLin,int nCol){
    char*** mat = (char***)malloc(tabs * sizeof(char**));

    if (mat == NULL)
    {
        printf("Erro ao alocar memoria");
        libertaTabuleiro(mat,tabs,nLin);
        return NULL;
    }

    for (int i = 0; i < tabs; i++)
    {
        mat[i] = (char**)malloc(nLin * sizeof(char*));
        if (mat[i] == NULL)
        {
            printf("Erro ao alocar memoria");
            libertaTabuleiro(mat,tabs,nLin);
            return NULL;
        }
        for (int j = 0; j < nLin; j++)
        {
            mat[i][j] = (char*)malloc(nCol * sizeof(char));
            if (mat[i][j] == NULL)
            {
                printf("Erro ao alocar memoria");
                libertaTabuleiro(mat,tabs,nLin);
                return NULL;
            }
        }
    }
    for (int i = 0; i < tabs; i++)
    {
        for (int j = 0; j < nLin; j++)
        {
            for (int k = 0; k < nCol; k++) {
                mat[i][j][k] = '_';
            }
        }
    }
    return mat;
}

void libertaMat(char** p, int nLin){

    int i;

    for(i=0; i<nLin; i++)
        free(p[i]);
    free(p);
}

char** criaMat(int nLin, int nCol){
    char **p = NULL;
    int i, j;

    p = malloc(sizeof(char*) * nLin);
    if(p == NULL)
        return NULL;

    for(i=0; i<nLin; i++){
        p[i] = malloc(sizeof(char) * nCol);
        if(p[i] == NULL){
            libertaMat(p, i-1);
            return NULL;
        }
        for(j=0; j<nCol; j++)
            p[i][j] = '_';
    }
    return p;
}

void setPos(char **p[], int x, int y,int z, char c){
    p[x][y][z] = c;
}

char getPos(char **p[],int x, int y,int z){
    return p[x][y][z];
}

void mostraTabuleiro(char **mat[]){
    int k,j,i,x=0;
    //printa as 3 primeiras linhas
    printf("\n");
    for(int l=0;l<3;l++) {//linha
        for (j = 0; j < 1; j++) {//indice das linhas ->aumenta depois de printada uma linha
            for (k = 0; k < 3; k++) {//num do quadro
                if(x==3)
                    x=0;
                for (i = 0; i < 3; i++) {
                    printf("  %c  ", mat[k][j+x][i]);
                }
                if(k<2)
                    printf("  |  ");
            }
        }
        printf("\n");
        x++;

    }
    for(int y=0;y<54;y++)
        printf("-");
    printf("\n");

    //printa da 3 á 6 linha
    for(int l=0;l<3;l++) {//linha
        for (j = 0; j < 1; j++) {//indice das linhas ->aumenta depois de printada uma linha
            for (k = 0; k < 3; k++) {//num do quadro
                if(x==3)
                    x=0;
                for (i = 0; i < 3; i++) {
                    printf("  %c  ", mat[k+3][j+x][i]);
                }
                if(k<2)
                    printf("  |  ");
            }
        }
        printf("\n");
        x++;
    }
    for(int y=0;y<54;y++)
        printf("-");
    printf("\n");

    //printa da 6 á 9 linha
    for(int l=0;l<3;l++) {//linha
        for (j = 0; j < 1; j++) {//indice das linhas ->aumenta depois de printada uma linha
            for (k = 0; k < 3; k++) {//num do quadro
                if(x==3)
                    x=0;
                for (i = 0; i < 3; i++) {
                    printf("  %c  ", mat[k+6][j+x][i]);
                }
                if(k<2)
                    printf("  |  ");
            }
        }
        printf("\n");
        x++;
    }
    printf("\n");
}

//cria os 9 mini-tabuleiros(de forma não dinamica)
void cria_tabuleiros(char **mat[]){
    for (int i=0;i<9;i++){
        mat[i] = criaMat(3,3);
    }
}
void mostraMat(char **p, int nLin, int nCol){
    int i,j;

    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++)
            printf("%c", p[i][j]);
        putchar('\n');
    }
}