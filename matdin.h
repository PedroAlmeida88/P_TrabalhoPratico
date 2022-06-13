// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#ifndef MATDIN_H
#define MATDIN_H

#include <stdlib.h>
#include <stdio.h>
char*** criaTabuleiro(int tabs,int nLin, int nCol);
void libertaTabuleiro(char ***mat,int tabs,int nLin);
// Liberta uma matriz dinâmica de caracteres com nLin linhas
void libertaMat(char** p, int nLin);
// Devolve endereço inicial da matriz
char** criaMat(int nLin, int nCol);
// Coloca o caracter c na posição (z, y) num mini-tabuleiro x
void setPos(char **p[], int x, int y,int z, char c);
// Obtém o caracter armazenado na posição (y, z) de um mini-tabuleiro x
char getPos(char **p[],int x, int y,int z);
//cria os 9 mini-tabuleiros
void cria_tabuleiros(char **mat[]);
//mostra o tabuleiro completo
void mostraTabuleiro(char **mat[]);
void mostraMat(char **p, int nLin, int nCol);
#endif