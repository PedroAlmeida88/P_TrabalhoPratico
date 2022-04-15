//
// Created by pedro on 15/04/2022.
//
#include <stdio.h>
#include "menu.h"

int menu(){
    int res,opc;
    do {
        printf("1-Novo Jogo\n");
        printf("2-Carregar Jogo\n");
        printf("9-Ajuda\n");
        res = scanf("%d",&opc);
        fflush(stdin);
    }while(res == 0);

}