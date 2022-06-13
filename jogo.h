// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980

#ifndef TP_JOGO_H
#define TP_JOGO_H

//recebe a matriz e o jogador a começar
void comeca_jogo(int jogador,int flag_fich);
//jogo contra o computador
void comeca_jogo_bot(int flag_fich);
//converte uma posicao(1-9) para as coordenadas no array
int converte_posicao(int pos,int *x,int *y);
//verifica se foi completada uma linha
int linha(char **mat[],int min_tab,int lin);
//verifica se foi completada uma coluna
int coluna(char **mat[],int min_tab,int col);
//verifica se foi completada uma diagonal
int diagonalUm(char **mat[],int min_tab,int lin);
//verifica se foi completada uma diagonal
int diagonalDois(char **mat[],int min_tab,int lin);
//verifica se houve um empate num mini-tabuleiro
int empate(char **mat[],int mini_tab,int lin);
int ganha_mini_tabuleiro(char **mat[],int mini_tab,int lin,int jogador, char **vencedores);
//limpa um tabuleiro ganho
void encerra_mini_tabuleiro(char **mat[],int mini_tab,int jogador, char **vencedores);
//verifica se foi completada uma linha no quadro final
int linha_final(char **vencedores,char lin);
//verifica se foi completada uma coluna no quadro final
int coluna_final(char **vencedores,char col);
//verifica se foi completada uma diagonal no quadro final
int diagonal1_final(char **vencedores,char col);
//verifica se foi completada uma diagonal no quadro final
int diagonal2_final(char **vencedores);
//verifica se houve um empate no quadro final
int empate_final(char **vencedores,int lin);
//verifica se alguem ganhou ou se o jogo terminou empatado
int ganha_quadro_final(char **vencedores,int jogador);
#endif //TP_JOGO_H
