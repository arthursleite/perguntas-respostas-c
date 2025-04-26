#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
ListaQuestoes criarQuestoesFaceis();
ListaQuestoes criarQuestoesMedias();
ListaQuestoes criarQuestoesDificeis();
ListaQuestoes criarQuestoesMuitoDificeis();

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
        printf("Digite a letra da resposta (em maiusculas): ");
        scanf(" %c", &jogador.resposta);
        if (verificarResposta(alternativas, jogador.resposta) == 1)
        {
            jogador.pontuacao++;
            printf("acertou!\n");
        }
        else
        {
            jogador.vidas--;
            printf("errou! vidas restantes: %d\n", jogador.vidas);
        }

        if (jogador.vidas == 0)
        {
            printf("game over\n");
            printf("sua pontuacao foi: %d\n", jogador.pontuacao);
            break;
        }
        else if (jogador.pontuacao == 5)
        {
            printf("parabens, voce ganhou o jogo!\n");
            printf("sua pontuacao foi: %d\n", jogador.pontuacao);
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
        ListaQuestoes lista = criarQuestoesMuitoFaceis();
        Questao questaoFacil = obterPergunta(lista);
        return questaoFacil;
    }
    else if (strcmp(dificuldade, "facil") == 0)
    {
        // criarQuestaoFacil();
    }
    else if (strcmp(dificuldade, "media") == 0)
    {
        // criarQuestaoMedia();
    }
    else if (strcmp(dificuldade, "dificil") == 0)
    {
        // criarQuestaoDificil();
    }
    else if (strcmp(dificuldade, "muitoDificil") == 0)
    {
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
    strcpy(q3.pergunta, "Qual simbolo é usado para comentar uma linha de código em C?");
    strcpy(q3.opcaoCerta, "//");
    strcpy(q3.opcaoErrada1, "/*");
    strcpy(q3.opcaoErrada2, "#");
    strcpy(q3.opcaoErrada3, "--");
    adicionarQuestao(&lista, q3);

    return lista;
}

ListaQuestoes criarQuestoesFaceis() {
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
}

ListaQuestoes criarQuestoesMedias() {
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
    strcpy(q2.pergunta, "O que a função sizeof retorna em C?");
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
}

ListaQuestoes criarQuestoesDificeis() {
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;

    Questao q1;
    strcpy(q1.pergunta, "Qual tipo de memoria eh usada para armazenar variaveis locais dentro de funcoes em C?");
    strcpy(q1.opcaoCerta, "Pilha (stack).");
    strcpy(q1.opcaoErrada1, "Heap.");
    strcpy(q1.opcaoErrada2, "Memoria global.");
    strcpy(q1.opcaoErrada3, "Memoria flash.");
    adicionarQuestao(&lista, q1);
}