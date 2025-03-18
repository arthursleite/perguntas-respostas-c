#include <stdio.h>

int main()
{
    printf("bem vindo ao jogo");
}

void perguntasFaceis()
{
    char pergunta1[1000] = "essa eh a pergunta 1 sobre algoritmos: ";
    char resposta1 = "";
    char opcao;

    printf("essa eh a pergunta facil 1: ");
    printf("A - aviao\nB - bola\nC - casa\nD - dado");
    scanf("%c", &opcao);
    switch (opcao)
    {
    case 'A':

        break;

    default:
        break;
    }
}

struct questao criarQuestaoFacil()
{
    struct questao questao1;

}

struct questao
{
    char pergunta[1000];
    char resposta;
    char opcao1;
    char opcao2;
    char opcao3;
    char opcao4;
};



void criarQuestao(char dificuldade[15])
{
    switch (dificuldade)
    {
    case constant expression:
        criarQuestaoFacil();
        break;
    
    default:
        break;
    }
}