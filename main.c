#include <stdio.h>
#include "matdin.h"
#include "utils.h"
#include "jogo.h"
#include "menu.h"

int main() {
    int opt;
    //char mat[9][3][3];  //9 indices, cada um com 3 linhas e 3 colunas
    char ***mat;
    mat = criaTabuleiro(9,3,3);
    opt = menu();

    if(opt == 1){
        opt = menu_jogo();
        if(opt == 1) {
            comeca_jogo(mat, 1);
        }else{
            comeca_jogo_bot(mat);
        }
    }
    if(opt == 2){
        printf("Por implementar!!");
    }
    if(opt == 9){
        printf("Por implementar!!");
    }


    return 0;
}
