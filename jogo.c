// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "jogo.h"
#include "matdin.h"
#include "utils.h"
#include "listas.h"
#include "ficheiros.h"
#include "menu.h"

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
//recebe o jogador a começar e uma flag que indica se existe um jogo anterior
void comeca_jogo(int jogador,int flag_fich) {
    int mini_tab, pos = 0, x, y, resul, ganhou, res = 1, n_jogada = 1, n, flag = 0; //n->num de jogadas para ver
    pJogada lista = NULL;//lista ligada que vai guardar as jogadas
    char ***mat, **vencedores;
    vencedores = criaMat(3,3);//armazena o vencedor de cada mini-tab

    if (flag_fich == 1) { //continua jogo anterior
        printf("\nA continuar o jogo anterior\n");
        mat = reconstroi_tabuleiro("jogo.bin",vencedores);
        flag = 1;//para não perguntar em qual tab quer começar
        ultima_jogada("jogo.bin", &mini_tab, &jogador, &n_jogada);//mini-tab e jogador da ultima jogada
        jogador = jogador % 2 + 1;
        //recontruir lista ligada
        lista = reconstroi_lista("jogo.bin", lista);
    } else {//caso não seja pretendido continuar o jogo
        mat = criaTabuleiro(9, 3, 3);
    }



    //recebe mat e o jogador a jogar
    mostraTabuleiro(mat);

    if(flag == 0) {//para apenas perguntar qunado é um novo jogo
        do {
            printf("Jogador %d, em qual mini-tabuleiro deseja comecar?(1-9):",jogador);
            res = scanf("%d", &mini_tab);
            fflush(stdin);
        } while (mini_tab < 1 || mini_tab > 9 || res == 0);
    }
    printf("\nJogador %d, esta a jogar no tabuleiro %d\n",jogador,mini_tab);

    do {
        int jogada = menu_jogada();
        //Ver jogadas anteriores
        if(jogada == 2) {
            if (n_jogada != 1) {//para nao perguntar quando ainda não foram efetuadas jogadas
                    do {
                        printf("Quantas jogadas deseja ver? (maximo 10):");
                        scanf("%d", &n);
                        fflush(stdin);
                    } while (n < 1 || n > 10);
                    mostra_n_jogadas_anteriores(lista, n, n_jogada);
            }
        }
        if(jogada == 3){
            //Para o jogo;
            guarda_lista_bin(lista,n_jogada-1,0);
            liberta_lista(lista);
            return;
        }
        //Fazer uma jogadas
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

        //guarda a jogada na lista
        lista = insere_final(lista,n_jogada,mini_tab,pos,jogador);
        //verificar se alguem ganhou um mini-tab
        ganha_mini_tabuleiro(mat,mini_tab,3,jogador,vencedores);
        //atualizar para o novo mini-tabuleiro
        mini_tab = pos;

        printf("\n");//para os mini-tabuleiros não desformatarem

        mostraTabuleiro(mat);

        //verificar se algum jogador ganhou o jogo
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
                    resul = converte_posicao(mini_tab, &x, &y);
                } while (vencedores[x][y] != '_' || res == 0 ||resul == 1);//para n voltar para um tab já ganho
            }
            printf("\nJogador %d, esta a jogar no tabuleiro %d\n", jogador, mini_tab);

        }
        n_jogada++;

    } while (ganhou != 1);
    //guardar num fich de texto
    if(escolhe() == 1){
        guarda_lista_txt(lista);
    }
    if(flag_fich == 1) //se existir um ficheiro
        if(remove("jogo.bin"))
            printf("Erro a remover o ficheiro");
    liberta_lista(lista);
    libertaMat(vencedores,3);
    libertaTabuleiro(mat,9,3);
}
//jogo contra o computador
void comeca_jogo_bot(int flag_fich) {
    int jogador = 1, mini_tab, pos = 0, x, y,n, resul, ganhou, res = 1, flag = 0, n_jogada = 1;
    char ***mat, **vencedores;
    pJogada lista = NULL;//lista ligada que vai guardar as jogadas
    vencedores = criaMat(3, 3);//armazena o vencedor de cada mini-tab
    if (flag_fich == 1) { //continua jogo anterior
        printf("\nA continuar o jogo anterior\n");
        mat = reconstroi_tabuleiro("jogo.bin",vencedores);
        //verificar se alguem ganhou algum mini-tabuleiro
        flag = 1;//para não perguntar em qual tab quer começar
        ultima_jogada("jogo.bin", &mini_tab, &jogador, &n_jogada);//mini-tab e jogador da ultima jogada
        jogador = jogador % 2 + 1;
        //recontruir lista ligada
        lista = reconstroi_lista("jogo.bin", lista);
    } else{//caso não seja pretendido continuar o jogo
        mat = criaTabuleiro(9, 3, 3);
    }



    //recebe mat e o jogador a jogar
    mostraTabuleiro(mat);

    if (flag == 0) {//para apenas perguntar qunado é um novo jogo
        do {
            printf("Em qual mini-tabuleiro deseja comecar?(1-9):");
            res = scanf("%d", &mini_tab);
            fflush(stdin);//limpa o buffer |sem isso fica em ciclo infinito
        } while (mini_tab < 1 || mini_tab > 9 || res == 0);
    }
    printf("\nJogador %d, esta a jogar no tabuleiro %d\n",jogador,mini_tab);

    do {
        if(jogador == 1) {
            //mostra_lista(lista);
            int jogada = menu_jogada();
            //Ver jogadas anteriores
            if (jogada == 2) {
                if (n_jogada != 1) {//para n perguntar quando ainda não foram efetuadas jogadas
                    do {
                        printf("Quantas jogadas deseja ver? (maximo 10):");
                        scanf("%d", &n);
                        fflush(stdin);
                    } while (n < 1 || n > 10);
                    mostra_n_jogadas_anteriores(lista, n, n_jogada);
                }
            }
            if (jogada == 3) {
                //Para o jogo;
                guarda_lista_bin(lista, n_jogada - 1, 1);
                liberta_lista(lista);
                return;
            }
        }
        //Fazer uma jogadas
        do{
            if(jogador == 1) {
                printf("Em que posicao deseja jogar:");
                res = scanf("%d", &pos);
                fflush(stdin);
                resul = converte_posicao(pos, &x, &y);//converter para as coordenadas no array
            }else{
                pos = intUniformRnd(1,9);
                resul = converte_posicao(pos, &x, &y);//converter para as coordenadas no array
            }
        }while(mat[mini_tab-1][x][y] != '_' || resul == 1 || res == 0);

        if(jogador == 1)
            setPos(mat, mini_tab - 1, x, y, 'X');
        else
            setPos(mat, mini_tab - 1, x, y, 'O');

        //guarda a jogada na lista
        lista = insere_final(lista,n_jogada,mini_tab,pos,jogador);

        //verificar se alguem ganhou um mini-tab
        if(jogador == 2) {
            ganha_mini_tabuleiro(mat, mini_tab, 3, 4, vencedores);//jogador 4 == bot
        }else{
            ganha_mini_tabuleiro(mat, mini_tab, 3, jogador, vencedores);
        }

        //atualizar para o novo mini-tabuleiro
        mini_tab = pos;

        printf("\n");//para os mini-tabuleiros não desformatarem
        mostraTabuleiro(mat);
        printf("\n\n");
        if(jogador == 2) {
            ganhou = ganha_quadro_final(vencedores, 4);// 4->bot
        }else{
            ganhou = ganha_quadro_final(vencedores, jogador);
        }
        if(ganhou != 1) {
            //troca o jogador
            jogador = jogador % 2 + 1;

            //caso o mini tab esteja encerrado
            if (vencedores[x][y] != '_') {
                printf("\nTabuleiro %d fechado!", mini_tab);
                do {
                    if(jogador == 1) {
                        printf("\nJogador %d,em qual tabuleiro deseja jogar?", jogador);
                        res = scanf("%d", &mini_tab);
                        fflush(stdin);
                        resul = converte_posicao(mini_tab, &x, &y);
                    }else{
                        mini_tab = intUniformRnd(1,9);
                        resul = converte_posicao(mini_tab, &x, &y);
                    }
                } while (vencedores[x][y] != '_' || res == 0 || resul == 1);//para n voltar para um tab já ganho
            }
            if(jogador == 1)
                printf("\nJogador %d, esta a jogar no tabuleiro %d\n", jogador, mini_tab);
            //verificar se algum jogador ganhou o jogo
        }
        n_jogada++;
    } while (ganhou != 1);
    //guardar num fich de texto
    if(escolhe() == 1){
        guarda_lista_txt(lista);
    }
    if(flag_fich == 1) //se existir um ficheiro
        if(remove("jogo.bin"))
            printf("Erro a remover o ficheiro");
    liberta_lista(lista);
    libertaMat(vencedores,3);
    libertaTabuleiro(mat,9,3);
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
    int i,j;
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
void ganha_mini_tabuleiro(char **mat[],int mini_tab,int lin,int jogador, char **vencedores){
    int Linha = linha(mat,mini_tab,lin);
    int Coluna = coluna(mat,mini_tab,lin);
    int DiagUm = diagonalUm(mat,mini_tab,lin);
    int DiagDois = diagonalDois(mat,mini_tab,lin);
    int emp;
    if(Linha == 1 || Coluna == 1 || DiagUm == 1 || DiagDois == 1){
        if(jogador == 4) {
            printf("O computador ganhou o tabuleiro %d", mini_tab);
            encerra_mini_tabuleiro(mat, mini_tab, 2, vencedores);
        }else{
            printf("O jogador %d ganhou o tabuleiro %d", jogador, mini_tab);
            encerra_mini_tabuleiro(mat, mini_tab, jogador, vencedores);
        }
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
        if(vencedores[i][0] != '_' && vencedores[i][0] != 'E'){
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
        if(vencedores[0][i] != '_' && vencedores[0][i] != 'E'){
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
    if(vencedores[0][0] != '_' && vencedores[0][0] != 'E') {
        for(i=0,j=0; i<col-1; i++,j++){
            if(vencedores[i][j] != vencedores[i+1][j+1])
                return 0;
        }
        return 1;
    }
}
//verifica se foi completada uma diagonal no quadro final
int diagonal2_final(char **vencedores){
    if (vencedores[0][2] != '_' && vencedores[0][2] != 'E'){
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
        if(jogador == 4) {
            printf("O computador ganhou o jogo!!");
            return 1;
        }else{
            printf("O jogador %d ganhou o jogo!!", jogador);
            return 1;
        }
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