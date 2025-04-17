#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[100];
    int pontuacao;
    int vidas;
} Jogador;

typedef struct
{
    char pergunta[1000];
    char resposta[1000];
    char opcaoA[1000];
    char opcaoB[1000];
    char opcaoC[1000];
    char opcaoD[1000];
} Questao;

typedef struct
{
    Questao questoes[3];
} ListaQuestoes;

Questao montarQuestao(char dificuldade[15]);
Questao fazerPerguntaMuitoFacil(ListaQuestoes lista);
ListaQuestoes criarQuestoesMuitoFaceis();

int main()
{
    printf("bem vindo ao jogo");
    printf("digite seu nome: ");
    Jogador jogador;
    scanf("%s", jogador.nome);
    jogador.pontuacao = 0;
    jogador.vidas = 3;
    while (jogador.vidas > 0)
    {
        char dificuldade[15];
        if (jogador.pontuacao = 0) //muito facil
        {
            strcopy(dificuldade, "muitoFacil");
            Questao questao = montarQuestao(dificuldade);
            printf("resposta: %s\n", questao.resposta);
            printf("opcao: ");
            char opcao;
            scanf(" %c", &opcao);
            if (opcao == questao.resposta[0])
            {
                jogador.pontuacao += 1;
                printf("acertou!\n");
            }
            else
            {
                jogador.vidas--;
                printf("errou! vidas restantes: %d\n", jogador.vidas);
            }
        }

        if (jogador.vidas == 0)
        {
            printf("game over\n");
            printf("sua pontuacao foi: %d\n", jogador.pontuacao);
            break;
        }
    }
}

Questao montarQuestao(char dificuldade[15])
{
    if (strcmp(dificuldade, "muitoFacil") == 0)
    {
        ListaQuestoes lista = criarQuestoesMuitoFaceis();
        Questao questaoFacil = fazerPerguntaMuitoFacil(lista);
        return questaoFacil;
    }
    else if (strcmp(dificuldade, "facil") == 0)
    {
        // criarQuestaoFacil();
    }
    else if (strcmp(dificuldade, "media") == 0)
    {
        // criarQuestaoMedia();
    } else if (strcmp(dificuldade, "dificil") == 0)
    {
        // criarQuestaoDificil();
    } else if (strcmp(dificuldade, "muitoDificil") == 0)
    {
        // criarQuestaoMuitoDificil();
    }
}

Questao fazerPerguntaMuitoFacil(ListaQuestoes lista)
{
    Questao questao = lista.questoes[0];
    printf("%s\n", questao.pergunta);
    printf("A - %s\nB - %s\nC - %s\nD - %s\n", questao.opcaoA, questao.opcaoB, questao.opcaoC, questao.opcaoD);
    char opcao;
    scanf(" %c", &opcao);
    return questao;
}

ListaQuestoes criarQuestoesMuitoFaceis()
{
    ListaQuestoes lista;

    strcpy(lista.questoes[0].pergunta, "essa eh a pergunta muito facil 1: ");
    strcpy(lista.questoes[0].opcaoA, "aviao");
    strcpy(lista.questoes[0].opcaoB, "bola");
    strcpy(lista.questoes[0].opcaoC, "casa");
    strcpy(lista.questoes[0].opcaoD, "dado");

    strcpy(lista.questoes[1].pergunta, "essa eh a pergunta muito facil 2: ");
    strcpy(lista.questoes[1].opcaoA, "aviao");
    strcpy(lista.questoes[1].opcaoB, "bola");
    strcpy(lista.questoes[1].opcaoC, "casa");
    strcpy(lista.questoes[1].opcaoD, "dado");

    strcpy(lista.questoes[2].pergunta, "essa eh a pergunta facil 3: ");
    strcpy(lista.questoes[2].opcaoA, "aviao");
    strcpy(lista.questoes[2].opcaoB, "bola");
    strcpy(lista.questoes[2].opcaoC, "casa");
    strcpy(lista.questoes[2].opcaoD, "dado");

    return lista;
}