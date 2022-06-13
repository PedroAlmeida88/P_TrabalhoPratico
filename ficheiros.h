// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#ifndef TP_FICHEIROS_H
#define TP_FICHEIROS_H

void guarda_lista_txt(pJogada p);
void guarda_lista_bin(pJogada p,int n_jogadas,int tipo_jogo);
void le_lista_bin(pJogada p);
char ***reconstroi_tabuleiro(char *filename,char **vencedores);
int verifica_existencia_ficheiro(char *filename);
void ultima_jogada(char *filename,int *mini_tab,int *jogador,int *n_jogada);
int modo_jogo();

pJogada reconstroi_lista(char *filename,pJogada p);

#endif //TP_FICHEIROS_H
