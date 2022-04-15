#include <stdio.h>
#include "matdin.h"
#include "utils.h"
#include "jogo.h"
#include "menu.h"

int main() {
    int opt;
    //char mat[9][3][3];  //9 indices, cada um com 3 linhas e 3 colunas
    // mat[0][0][2] : [0]->1º"indice/tabuleiro" | [0]->linha indice 0 | [2]->coluna indice 2
    char **mat[10];
    //funcao criaTabuleiro -> criar o ***tab dinamicamente
    cria_tabuleiros(mat);//coloca 9 tabluiros dinamicos na mat4


    //opt = menu();
    comeca_jogo(mat, 1);

    return 0;
}
