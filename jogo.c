//
// Created by pedro on 11/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "matdin.h"


//converte uma posicao(1-9) para as coordenadas no array
int converte_posicao(int pos,int *x,int *y){
    switch (pos) {
        case 1:
            *x = 0;//linha
            *y = 0;//coluna
            break;
        case 2:
            *x = 0;
            *y = 1;
            break;
        case 3:
            *x = 0;
            *y = 2;
            break;
        case 4:
            *x = 1;
            *y = 0;
            break;
        case 5:
            *x = 1;
            *y = 1;
            break;
        case 6:
            *x = 1;
            *y = 2;
            break;
        case 7:
            *x = 2;
            *y = 0;
            break;
        case 8:
            *x = 2;
            *y = 1;
            break;
        case 9:
            *x = 2;
            *y = 2;
            break;
        default:
            return 1;
    }
    return 0;
}
//recebe a matriz e o jogador a começar
void comeca_jogo(char **mat[],int jogador){
    int mini_tab,pos=0,x,y,resul,ganhou,res=1;
    char **vencedores;
    vencedores = criaMat(3,3);//armazena o vencedor de cada mini-tab
    //recebe mat e o jogador a jogar
    mostraTabuleiro(mat);

    do{
        res = 1;
        printf("Em qual mini-tabuleiro deseja comecar?(1-9):");
        res = scanf("%d",&mini_tab);
        fflush(stdin);//limpa o buffer |sem isso fica em ciclo infinito
    }while(mini_tab < 1 || mini_tab > 9 || res == 0);

    printf("\nJogador %d, esta a jogar no tabuleiro %d\n",jogador,mini_tab);

    do {
        do{
            printf("Em que posicao deseja jogar:");
            res = scanf("%d", &pos);
            fflush(stdin);
            resul = converte_posicao(pos,&x,&y);//converter para as coordenadas no array
        }while(mat[mini_tab-1][x][y] != '_' || resul == 1 || res == 0);

        if(jogador == 1)
            setPos(mat, mini_tab - 1, x, y, 'X');
        else
            setPos(mat, mini_tab - 1, x, y, 'O');

        //verificar se alguem ganhou um mini-tab
        ganha_mini_tabuleiro(mat,mini_tab,3,jogador,vencedores);
        //atualizar para o novo mini-tabuleiro
        mini_tab = pos;

        printf("\n");//para os mini-tabuleiros não desformatarem
        mostraTabuleiro(mat);

        ganhou = ganha_quadro_final(vencedores,jogador);
        if(ganhou != 1) {
            //troca o jogador
            jogador = jogador % 2 + 1;

            //caso o mini tab esteja encerrado
            if (vencedores[x][y] != '_') {
                printf("\nTabuleiro %d fechado!", mini_tab);
                do {
                    printf("\nJogador %d,em qual tabuleiro deseja jogar?", jogador);
                    res = scanf("%d", &mini_tab);
                    fflush(stdin);
                    converte_posicao(mini_tab, &x, &y);
                } while (vencedores[x][y] != '_' || res == 0);//para n voltar para um tab já ganho
            }
            printf("\nJogador %d, esta a jogar no tabuleiro %d\n", jogador, mini_tab);
            //verificar se algum jogador ganhou o jogo
        }
    } while (ganhou != 1);
}
//verifica se foi completada uma linha
int linha(char **mat[],int min_tab,int lin){
    int i,j;
    for(i=0; i<lin; i++)
        if(mat[min_tab-1][i][0] != '_'){
            for(j=0; j<lin-1 && mat[min_tab-1][i][j] == mat[min_tab-1][i][j+1]; j++)
                ;
            if(j==lin-1) {
                return 1;
            }
        }
    return 0;
}
//verifica se foi completada uma coluna
int coluna(char **mat[],int min_tab,int col){
    int i=0,j=0;
    for(i=0; i<col; i++)
        if(mat[min_tab-1][0][i] != '_'){
            for(j=0; j<col-1 && mat[min_tab-1][j][i] == mat[min_tab-1][j+1][i]; j++)
                ;
            if(j==col-1) {
                return 1;
            }
        }
    return 0;
}
//verifica se foi completada uma diagonal
int diagonalUm(char **mat[],int min_tab,int lin){
    int j,i;
    if(mat[min_tab-1][0][0] != '_'){
        for(i=0,j=0; i<lin-1; i++,j++){
            if(mat[min_tab-1][i][j] != mat[min_tab-1][i+1][j+1])
                return 0;
        }
        return 1;
    }
}
int diagonalDois(char **mat[],int min_tab,int lin) {
    if (mat[min_tab - 1][0][2] != '_'){
            if (mat[min_tab - 1][0][2] == mat[min_tab - 1][1][1] && mat[min_tab - 1][1][1] == mat[min_tab - 1][2][0] ) {
                return 1;
            }
    }
    return 0;
}
//verifica se houve um empate num mini-tabuleiro
int empate(char **mat[],int mini_tab,int lin){
    for(int i=0;i<lin;i++)
        for(int j=0;j<lin;j++){
            if(mat[mini_tab-1][i][j] == '_') {
                return 0;
            }
        }
    return 1;
}
int ganha_mini_tabuleiro(char **mat[],int mini_tab,int lin,int jogador, char **vencedores){
    int Linha = linha(mat,mini_tab,lin);
    int Coluna = coluna(mat,mini_tab,lin);
    int DiagUm = diagonalUm(mat,mini_tab,lin);
    int DiagDois = diagonalDois(mat,mini_tab,lin);
    int emp;
    if(Linha == 1 || Coluna == 1 || DiagUm == 1 || DiagDois == 1){
        printf("O jogador %d ganhou o tabuleiro %d",jogador,mini_tab);
        encerra_mini_tabuleiro(mat,mini_tab,jogador,vencedores);
    }
    else{//verificar se houve um empate
        emp = empate(mat,mini_tab,lin);
        if(emp == 1)
            encerra_mini_tabuleiro(mat,mini_tab,3,vencedores);
    }
}
//limpa um tabuleiro ganho
void encerra_mini_tabuleiro(char **mat[],int mini_tab,int jogador, char **vencedores){
    int contador,x,y;

    //limpar o mini-tabuleiro
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            mat[mini_tab-1][i][j] = ' ';

    if(jogador == 1) {
        setPos(mat, mini_tab - 1, 1, 1, 'X');
        //*(*vencedores + mini_tab - 1) = 'X';
        converte_posicao(mini_tab,&x,&y);
        vencedores[x][y] = 'X';
    }else if(jogador == 2){
        setPos(mat, mini_tab - 1, 1, 1, 'O');
        converte_posicao(mini_tab,&x,&y);
        vencedores[x][y] = 'O';
    }else if(jogador == 3){//empate
        setPos(mat, mini_tab - 1, 1, 1, 'E');
        converte_posicao(mini_tab,&x,&y);
        vencedores[x][y] = 'E';
    }
    printf("\n");
}
//verifica se foi completada uma linha no quadro final
int linha_final(char **vencedores,char lin){
    int i, j;

    for(i=0; i<lin; i++)
        if(vencedores[i][0] != '_'){
            for(j=0; j<lin-1 && vencedores[i][j] == vencedores[i][j+1]; j++)
                ;
            if(j==lin-1)
                return 1;
        }
    return 0;
}
//verifica se foi completada uma coluna no quadro final
int coluna_final(char **vencedores,char col){
    int i=0,j=0;
    for(i=0; i<col; i++)
        if(vencedores[0][i] != '_'){
            for(j=0; j<col-1 && vencedores[j][i] == vencedores[j+1][i]; j++)
                ;
            if(j==col-1) {
                return 1;
            }
        }
    return 0;
}
//verifica se foi completada uma diagonal no quadro final
int diagonal1_final(char **vencedores,char col){
    int j,i;
    if(vencedores[0][0] != '_'){
        for(i=0,j=0; i<col-1; i++,j++){
            if(vencedores[i][j] != vencedores[i+1][j+1])
                return 0;
        }
        return 1;
    }
}
//verifica se foi completada uma diagonal no quadro final
int diagonal2_final(char **vencedores){
    if (vencedores[0][2] != '_'){
        if (vencedores[0][2] == vencedores[1][1] && vencedores[1][1] == vencedores[2][0] ) {
            return 1;
        }
    }
    return 0;
}
//verifica se houve um empate no quadro final
int empate_final(char **vencedores,int lin){
    for(int i=0;i<lin;i++)
        for(int j=0;j<lin;j++){
            if(vencedores[i][j] == '_') {
                return 0;
            }
        }
    return 1;
}
//verifica se alguem ganhou ou se o jogo terminou empatado
int ganha_quadro_final(char **vencedores,int jogador){
    int Linha = linha_final(vencedores,3);
    int Coluna = coluna_final(vencedores,3);
    int DiagUm = diagonal1_final(vencedores,3);
    int DiagDois = diagonal2_final(vencedores);
    int emp;
    if(Linha == 1 || Coluna == 1 || DiagUm == 1 || DiagDois == 1){
        printf("O jogador %d ganhou o jogo!!",jogador);
        return 1;
    }
    else{//verificar se houve um empate
        emp = empate_final(vencedores,3);
        if(emp == 1) {
            printf("O jogo terminou empatado!!");
            return 1;
        }
    }
    return 0;
}