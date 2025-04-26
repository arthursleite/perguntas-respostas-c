#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include<windows.h>

typedef struct
{
    char nome[100];
    int pontuacao;
    int vidas;
    char resposta;
} Jogador;

typedef struct
{
    char pergunta[1000];
    char opcaoCerta[1000];
    char opcaoErrada1[1000];
    char opcaoErrada2[1000];
    char opcaoErrada3[1000];
} Questao;

typedef struct
{
    Questao questoes[100];
    int quantidadeQuestoes;
} ListaQuestoes;

typedef struct
{
    char letra;
    char texto[1000];
    int correta;
} Alternativa;

void embaralharAlternativas(Questao questao, Alternativa embaralhadas[4]);
void mostrarQuestao(Questao questao, Alternativa alternativas[4]);
int verificarResposta(Alternativa alternativas[4], char respostaUsuario);
Questao obterQuestao(char dificuldade[15]);
Questao obterPergunta(ListaQuestoes lista);
void adicionarQuestao(ListaQuestoes *lista, Questao questao);
ListaQuestoes criarQuestoesMuitoFaceis();
void mostrarPontosEVidas(Jogador jogador);

int main()
{

    printf("== Bem vindo ao Jogo de Perguntas e Respostas ==\n");
    printf("Insira seu nome: \n > ");
    Jogador jogador;
    scanf("%s", jogador.nome);
    printf("Cadastro realizado! Boa sorte, %s.\n\n", jogador.nome);
    Sleep(1000);
    jogador.pontuacao = 0;
    jogador.vidas = 3;
    while (jogador.vidas > 0)
    {
        char dificuldade[15];
        Alternativa alternativas[4];
        switch (jogador.pontuacao)
        {
        case 0:
            strcpy(dificuldade, "muitoFacil");
            break;
        case 1:
            strcpy(dificuldade, "facil");
            break;
        case 2:
            strcpy(dificuldade, "media");
            break;
        case 3:
            strcpy(dificuldade, "dificil");
            break;
        case 4:
            strcpy(dificuldade, "muitoDificil");
            break;
        default:
            break;
        }
        Questao questao = obterQuestao(dificuldade);
        embaralharAlternativas(questao, alternativas);
        mostrarQuestao(questao, alternativas);
        printf(" > Letra: ");
        scanf(" %c", &jogador.resposta);
        jogador.resposta = toupper(jogador.resposta);
        if (verificarResposta(alternativas, jogador.resposta) == 1)
        {
            jogador.pontuacao++;
            printf("\nCerta resposta!\n");
            mostrarPontosEVidas(jogador);
            Sleep(1000);
        }
        else
        {
            jogador.vidas--;
            printf("\nResposta errada!\n");
            mostrarPontosEVidas(jogador);
            Sleep(1000);
        }

        if (jogador.vidas == 0)
        {
            puts("=================================");
            printf("Game over - Voce ficou sem vidas\n");
            printf("Nome: %s\nPontuacao: %d\n", jogador.nome, jogador.pontuacao);
            puts("=================================");
            break;
        }
        else if (jogador.pontuacao == 5)
        {
            puts("==============================");
            printf("Parabens! Voce ganhou o jogo!\n");
            printf("Sua pontuacao foi: %d\n", jogador.pontuacao);
            puts("==============================");
            break;
        }
    }
}

void embaralharAlternativas(Questao questao, Alternativa embaralhadas[4])
{
    strcpy(embaralhadas[0].texto, questao.opcaoCerta);
    embaralhadas[0].correta = 1;
    strcpy(embaralhadas[1].texto, questao.opcaoErrada1);
    embaralhadas[1].correta = 0;
    strcpy(embaralhadas[2].texto, questao.opcaoErrada2);
    embaralhadas[2].correta = 0;
    strcpy(embaralhadas[3].texto, questao.opcaoErrada3);
    embaralhadas[3].correta = 0;

    srand(time(NULL));
    for (int i = 3; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Alternativa temp = embaralhadas[i];
        embaralhadas[i] = embaralhadas[j];
        embaralhadas[j] = temp;
    }
    for (int i = 0; i < 4; i++)
    {
        embaralhadas[i].letra = 'A' + i;
    }
}

void mostrarQuestao(Questao questao, Alternativa alternativas[4])
{
    printf("%s\n", questao.pergunta);
    for (int i = 0; i < 4; i++)
    {
        printf("%c: %s\n", alternativas[i].letra, alternativas[i].texto);
    }
}

int verificarResposta(Alternativa alternativas[4], char respostaUsuario)
{
    for (int i = 0; i < 4; i++)
    {
        if (alternativas[i].letra == respostaUsuario)
        {
            return alternativas[i].correta;
        }
    }
    return 0;
}

Questao obterQuestao(char dificuldade[15])
{
    if (strcmp(dificuldade, "muitoFacil") == 0)
    {
        puts("> Dificuldade: Muito facil");
        ListaQuestoes lista = criarQuestoesMuitoFaceis();
        Questao questaoFacil = obterPergunta(lista);
        return questaoFacil;
    }
    else if (strcmp(dificuldade, "facil") == 0)
    {
        puts("> Dificuldade: Facil");
        // criarQuestaoFacil();
    }
    else if (strcmp(dificuldade, "media") == 0)
    {
        puts("> Dificuldade: Media");
        // criarQuestaoMedia();
    }
    else if (strcmp(dificuldade, "dificil") == 0)
    {
        puts("> Dificuldade: Dificil");
        // criarQuestaoDificil();
    }
    else if (strcmp(dificuldade, "muitoDificil") == 0)
    {
        puts("> Dificuldade: Muito dificil");
        // criarQuestaoMuitoDificil();
    }
}

Questao obterPergunta(ListaQuestoes lista)
{
    srand(time(NULL));
    int i = rand() % lista.quantidadeQuestoes;
    return lista.questoes[i];
}

void adicionarQuestao(ListaQuestoes *lista, Questao questao) {
    lista->questoes[lista->quantidadeQuestoes] = questao;
    lista->quantidadeQuestoes++;
}

ListaQuestoes criarQuestoesMuitoFaceis()
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "essa eh a pergunta muito facil 1: ");
    strcpy(q1.opcaoCerta, "aviao");
    strcpy(q1.opcaoErrada1, "bola");
    strcpy(q1.opcaoErrada2, "casa");
    strcpy(q1.opcaoErrada3, "dado");
    adicionarQuestao(&lista, q1);

    Questao q2;
    strcpy(q2.pergunta, "essa eh a pergunta muito facil 1: ");
    strcpy(q2.opcaoCerta, "aviao");
    strcpy(q2.opcaoErrada1, "bola");
    strcpy(q2.opcaoErrada2, "casa");
    strcpy(q2.opcaoErrada3, "dado");
    adicionarQuestao(&lista, q2);

    Questao q3;
    strcpy(q3.pergunta, "essa eh a pergunta muito facil 1: ");
    strcpy(q3.opcaoCerta, "aviao");
    strcpy(q3.opcaoErrada1, "bola");
    strcpy(q3.opcaoErrada2, "casa");
    strcpy(q3.opcaoErrada3, "dado");
    adicionarQuestao(&lista, q3);

    return lista;
}

void mostrarPontosEVidas(Jogador jogador) {
    printf("Pontos: %d\n", jogador.pontuacao);
    printf("Vidas restantes: %d\n\n", jogador.vidas);
}