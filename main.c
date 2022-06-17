// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#include <stdio.h>
#include "jogo.h"
#include "menu.h"
#include "listas.h"
#include "ficheiros.h"
#include "utils.h"
int main() {
    int opt,flag_fich,flag=0,jogador; //flag->é ativa quando um jogo é retomado
    initRandom();
    jogador = intUniformRnd(1,2);
    //char mat[9][3][3];  //9 indices, cada um com 3 linhas e 3 colunas

    if(verifica_existencia_ficheiro("jogo.bin")) { //verificar se existe um jogo anterior
        flag_fich = 1;//existe um jogo anterior e vai ser retomado
        if(menu_continua_jogo() == 1) {//se quiser continuar o jogo
            flag = 1;
            if (modo_jogo() == 0){
                comeca_jogo(jogador, flag_fich);
            }else{
                comeca_jogo_bot(flag_fich);
            }
        }else{
            if (remove("jogo.bin") == -1) {
                printf("Erro a remover o ficheiro");
            }
            flag_fich = 2;  //existe um jogo mas não vai ser retomado
        }
    }else {
        flag_fich = 0; //não existe um jogo anterior
    }

    do {
        if (flag == 0) { //mostra apenas quando o jogo não é retomado
            opt = menu();
            if (opt == 1) {
                opt = menu_jogo();
                if (opt == 1) {
                    comeca_jogo(jogador, flag_fich);
                } else {
                    comeca_jogo_bot(flag_fich);
                    opt = 1;
                }
            }
            if (opt == 2) {
                menu_regras();
            }
        }
    }while (opt == 2);



    return 0;
}
