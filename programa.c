#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

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
Questao obterQuestao(int pontuacao);
Questao obterPergunta(ListaQuestoes lista);
void adicionarQuestao(ListaQuestoes *lista, Questao questao);
ListaQuestoes criarQuestoesMuitoFaceis();
ListaQuestoes criarQuestoesFaceis();
ListaQuestoes criarQuestoesMedias();
ListaQuestoes criarQuestoesDificeis();
ListaQuestoes criarQuestoesMuitoDificeis();
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

        Questao questao = obterQuestao(jogador.pontuacao);
        embaralharAlternativas(questao, alternativas);
        mostrarQuestao(questao, alternativas);
        int contador = 0;
        do
        {
            if (contador > 0)
            {
                printf("Alternativa invalida! Digite novamente: \n");
            }
            printf(" > Letra: ");
            scanf(" %c", &jogador.resposta);
            jogador.resposta = toupper(jogador.resposta);
            if (jogador.resposta < 65 || jogador.resposta > 68)
            {
                contador++;
            }
        } while (jogador.resposta < 65 || jogador.resposta > 68);

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

Questao obterQuestao(int pontuacao)
{
    if (pontuacao == 0)
    {
        puts("> Dificuldade: Muito facil");
        ListaQuestoes lista = criarQuestoesMuitoFaceis();
        Questao questaoMuitoFacil = obterPergunta(lista);
        return questaoMuitoFacil;
    }
    else if (pontuacao == 1)
    {
        puts("> Dificuldade: Facil");
        ListaQuestoes lista = criarQuestoesFaceis();
        Questao questaoFacil = obterPergunta(lista);
        return questaoFacil;
    }
    else if (pontuacao == 2)
    {
        puts("> Dificuldade: Media");
        ListaQuestoes lista = criarQuestoesMedias();
        Questao questaoMedia = obterPergunta(lista);
        return questaoMedia;
    }
    else if (pontuacao == 3)
    {
        puts("> Dificuldade: Dificil");
        ListaQuestoes lista = criarQuestoesDificeis();
        Questao questaoDificil = obterPergunta(lista);
        return questaoDificil;
    }
    else if (pontuacao == 4)
    {
        puts("> Dificuldade: Muito dificil");
        ListaQuestoes lista = criarQuestoesMuitoDificeis();
        Questao questaoMuitoDificil = obterPergunta(lista);
        return questaoMuitoDificil;
    }
    else
    {
        fprintf(stderr, "Erro: dificuldade inválida.\n");
        exit(EXIT_FAILURE);
    }
}

Questao obterPergunta(ListaQuestoes lista)
{
    srand(time(NULL));
    int i = rand() % lista.quantidadeQuestoes;
    return lista.questoes[i];
}

void adicionarQuestao(ListaQuestoes *lista, Questao questao)
{
    lista->questoes[lista->quantidadeQuestoes] = questao;
    lista->quantidadeQuestoes++;
}

ListaQuestoes criarQuestoesMuitoFaceis()
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "Qual eh o tipo de dado usado para armazenar valores inteiros em C?");
    strcpy(q1.opcaoCerta, "int");
    strcpy(q1.opcaoErrada1, "char");
    strcpy(q1.opcaoErrada2, "bool");
    strcpy(q1.opcaoErrada3, "float");
    adicionarQuestao(&lista, q1);

    Questao q2;
    strcpy(q2.pergunta, "Qual funcao padrao da linguagem C eh usada para ler a entrada do usuario?");
    strcpy(q2.opcaoCerta, "scanf");
    strcpy(q2.opcaoErrada1, "printf");
    strcpy(q2.opcaoErrada2, "input");
    strcpy(q2.opcaoErrada3, "puts");
    adicionarQuestao(&lista, q2);

    Questao q3;
    strcpy(q3.pergunta, "Qual simbolo eh usado para comentar uma linha de codigo em C?");
    strcpy(q3.opcaoCerta, "//");
    strcpy(q3.opcaoErrada1, "/*");
    strcpy(q3.opcaoErrada2, "#");
    strcpy(q3.opcaoErrada3, "--");
    adicionarQuestao(&lista, q3);

    return lista;
}

ListaQuestoes criarQuestoesFaceis()
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "Como declarar um array de 5 numeros inteiros em C?");
    strcpy(q1.opcaoCerta, "int array[5];");
    strcpy(q1.opcaoErrada1, "array int[5];");
    strcpy(q1.opcaoErrada2, "int[] array = new int[5];");
    strcpy(q1.opcaoErrada3, "int array = {5};");
    adicionarQuestao(&lista, q1);

    Questao q2;
    strcpy(q2.pergunta, "Qual estrutura de repeticao eh ideal quando o numero de iteracoes eh conhecido?");
    strcpy(q2.opcaoCerta, "for");
    strcpy(q2.opcaoErrada1, "while;");
    strcpy(q2.opcaoErrada2, "do-while");
    strcpy(q2.opcaoErrada3, "repeat");
    adicionarQuestao(&lista, q2);

    Questao q3;
    strcpy(q3.pergunta, "Para que serve a diretiva #include?");
    strcpy(q3.opcaoCerta, "Incluir bibliotecas externas.");
    strcpy(q3.opcaoErrada1, "Declarar variaveis.");
    strcpy(q3.opcaoErrada2, "Definir funcoes.");
    strcpy(q3.opcaoErrada3, "Declarar variaveis constantes no programa.");
    adicionarQuestao(&lista, q3);

    return lista;
}

ListaQuestoes criarQuestoesMedias()
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "O que o seguinte trecho de codigo imprime?\nchar *str = \"Hello\";\nprintf(\"%c\", *(str + 2));\n");
    strcpy(q1.opcaoCerta, "l");
    strcpy(q1.opcaoErrada1, "H");
    strcpy(q1.opcaoErrada2, "e");
    strcpy(q1.opcaoErrada3, "o");
    adicionarQuestao(&lista, q1);

    Questao q2;
    strcpy(q2.pergunta, "O que a funcao sizeof retorna em C?");
    strcpy(q2.opcaoCerta, "O numero de bytes ocupado por um tipo ou variavel.");
    strcpy(q2.opcaoErrada1, "A quantidade de variáveis declaradas.");
    strcpy(q2.opcaoErrada2, "A capacidade máxima de memória do computador.");
    strcpy(q2.opcaoErrada3, "O valor armazenado em uma variável.");
    adicionarQuestao(&lista, q2);

    Questao q3;
    strcpy(q3.pergunta, "Qual operador bitwise eh usado para inverter os bits de um numero?");
    strcpy(q3.opcaoCerta, "~ (NOT)");
    strcpy(q3.opcaoErrada1, "| (OR)");
    strcpy(q3.opcaoErrada2, "& (AND)");
    strcpy(q3.opcaoErrada3, "^ (XOR)");
    adicionarQuestao(&lista, q3);

    return lista;
}

ListaQuestoes criarQuestoesDificeis()
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "Qual tipo de memoria eh usada para armazenar variaveis locais dentro de funcoes em C?");
    strcpy(q1.opcaoCerta, "Pilha (stack).");
    strcpy(q1.opcaoErrada1, "Heap.");
    strcpy(q1.opcaoErrada2, "Memoria global.");
    strcpy(q1.opcaoErrada3, "Memoria flash.");
    adicionarQuestao(&lista, q1);

    Questao q2;
    strcpy(q2.pergunta, "Qual a importancia do uso de const em parametros de funcoes?");
    strcpy(q2.opcaoCerta, "Garantir que o parametro nao sera modificado.");
    strcpy(q2.opcaoErrada1, "Aumentar a velocidade da funcao.");
    strcpy(q2.opcaoErrada2, "Permitir que o valor seja alterado.");
    strcpy(q2.opcaoErrada3, "Memoria flash.");
    adicionarQuestao(&lista, q2);

    Questao q3;
    strcpy(q3.pergunta, "Qual eh o principal risco de usar recursao em profundidade (ex: calculo fatorial para 'n' grande) em C?");
    strcpy(q3.opcaoCerta, "Stack overflow devido ao excesso de chamadas aninhadas");
    strcpy(q3.opcaoErrada1, "Integer overflow no resultado");
    strcpy(q3.opcaoErrada2, "Corrupcao de memoria no heap");
    strcpy(q3.opcaoErrada3, "Loop infinito se a condicao de parada for mal definida");
    adicionarQuestao(&lista, q3);

    return lista;
}

ListaQuestoes criarQuestoesMuitoDificeis()
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "Como funciona a 'Stack' e o 'Heap' em um programa C?");
    strcpy(q1.opcaoCerta, "Stack eh para variaveis locais, Heap eh para dados dinamicos.");
    strcpy(q1.opcaoErrada1, "Stack eh para dados dinamicos e Heap para dados automaticos.");
    strcpy(q1.opcaoErrada2, "Stack eh para alocacao dinamica, Heap eh para variaveis locais.");
    strcpy(q1.opcaoErrada3, "Stack e Heap sao usados da mesma forma.");
    adicionarQuestao(&lista, q1);

    Questao q2;
    strcpy(q2.pergunta, "O que eh 'undefined behavior' em C?");
    strcpy(q2.opcaoCerta, "Quando o programa se comporta de forma imprevisivel.");
    strcpy(q2.opcaoErrada1, "Um erro de compilacao.");
    strcpy(q2.opcaoErrada2, "Um warning que nao afeta o programa.");
    strcpy(q2.opcaoErrada3, "Um modo de otimizar codigo.");
    adicionarQuestao(&lista, q2);

    Questao q3;
    strcpy(q3.pergunta, "Qual eh o resultado do seguinte codigo em C?\n\nint matriz[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};\nint *ptr = (int *)matriz;\nprintf(\"%d\", *(ptr + 5));");
    strcpy(q3.opcaoCerta, "6");
    strcpy(q3.opcaoErrada1, "5");
    strcpy(q3.opcaoErrada2, "4");
    strcpy(q3.opcaoErrada3, "7");
    adicionarQuestao(&lista, q3);

    return lista;
}

void mostrarPontosEVidas(Jogador jogador)
{
    printf("Pontos: %d\n", jogador.pontuacao);
    printf("Vidas restantes: %d\n\n", jogador.vidas);
}