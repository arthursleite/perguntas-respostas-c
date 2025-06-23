#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #define WAIT(x) Sleep((x) * 1000)
#else
    #include <unistd.h>
    #define WAIT(x) sleep(x)
#endif

const char* NOMES_DIFICULDADE[] = {
    "Muito facil",
    "Facil", 
    "Media",
    "Dificil",
    "Muito dificil"
};

const char* ARQUIVOS_DIFICULDADE[] = {
    "nivel_muito_facil.txt",
    "nivel_facil.txt",
    "nivel_medio.txt", 
    "nivel_dificil.txt",
    "nivel_muito_dificil.txt"
};

typedef enum {
    MENU_JOGAR = 1,
    MENU_SAIR = 2
} MenuOperacoes;

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
    char **alternativas;
    int numAlternativas;
    char respostaCorreta;
} Questao;

typedef struct
{
    Questao *questoes;
    int quantidadeQuestoes;
} ListaQuestoes;

typedef struct
{
    char letra;
    char texto[1000];
    int correta;
} Alternativa;

void embaralharAlternativas(Questao questao, Alternativa **embaralhadas, int *numAlternativas);
void mostrarQuestao(Questao questao, Alternativa *alternativas, int numAlternativas);
int verificarResposta(Alternativa *alternativas, int numAlternativas, char respostaUsuario);
Questao obterQuestao(int nivelDificuldade);
Questao obterPergunta(ListaQuestoes lista);
void adicionarQuestao(ListaQuestoes *lista, Questao questao);
ListaQuestoes lerQuestoesDeArquivo(char *nomeArquivo);
void liberarQuestao(Questao *questao);
void liberarListaQuestoes(ListaQuestoes *lista);
void mostrarPontosEVidas(Jogador jogador);
char lerRespostaValida(int numAlternativas);
void mostrarMenu();
int lerOpcaoMenu();
void jogar();

int main()
{
    printf("== Bem vindo ao Jogo de Perguntas e Respostas ==\n\n");
    
    int opcao;
    do {
        mostrarMenu();
        opcao = lerOpcaoMenu();
        
        switch (opcao) {
            case MENU_JOGAR:
                jogar();
                break;
            case MENU_SAIR:
                printf("\nObrigado por jogar! Ate a proxima!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n\n");
                break;
        }
    } while (opcao != MENU_SAIR);
    
    return 0;
}

void embaralharAlternativas(Questao questao, Alternativa **embaralhadas, int *numAlternativas)
{
    if (questao.numAlternativas == 0 || questao.alternativas == NULL) {
        *numAlternativas = 0;
        *embaralhadas = NULL;
        return;
    }
    
    *numAlternativas = questao.numAlternativas;
    *embaralhadas = (Alternativa *)realloc(NULL, questao.numAlternativas * sizeof(Alternativa));
    
    int indicePosicaoCorreta = questao.respostaCorreta - 'A';
    
    for (int i = 0; i < questao.numAlternativas; i++)
    {
        strcpy((*embaralhadas)[i].texto, questao.alternativas[i]);
        (*embaralhadas)[i].correta = (i == indicePosicaoCorreta) ? 1 : 0;
    }

    srand(time(NULL));
    for (int i = questao.numAlternativas - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Alternativa temp = (*embaralhadas)[i];
        (*embaralhadas)[i] = (*embaralhadas)[j];
        (*embaralhadas)[j] = temp;
    }
    for (int i = 0; i < questao.numAlternativas; i++)
    {
        (*embaralhadas)[i].letra = 'A' + i;
    }
}

void mostrarQuestao(Questao questao, Alternativa *alternativas, int numAlternativas)
{
    printf("%s\n", questao.pergunta);
    for (int i = 0; i < numAlternativas; i++)
    {
        printf("%c: %s\n", alternativas[i].letra, alternativas[i].texto);
    }
}

int verificarResposta(Alternativa *alternativas, int numAlternativas, char respostaUsuario)
{
    for (int i = 0; i < numAlternativas; i++)
    {
        if (alternativas[i].letra == respostaUsuario)
        {
            return alternativas[i].correta;
        }
    }
    return 0;
}

Questao obterQuestao(int nivelDificuldade)
{
    int numNiveis = sizeof(NOMES_DIFICULDADE) / sizeof(NOMES_DIFICULDADE[0]);
    if (nivelDificuldade < 0 || nivelDificuldade >= numNiveis) {
        nivelDificuldade = 0;
    }
    
    const char* nomeDificuldade = NOMES_DIFICULDADE[nivelDificuldade];
    const char* nomeArquivo = ARQUIVOS_DIFICULDADE[nivelDificuldade];
    
    printf("> Dificuldade: %s\n", nomeDificuldade);
    
    ListaQuestoes lista = lerQuestoesDeArquivo((char*)nomeArquivo);
    
    if (lista.quantidadeQuestoes == 0) {
        Questao questaoVazia = {0};
        return questaoVazia;
    }
    
    Questao questao = obterPergunta(lista);
    
    // Copiar a questão para não ter problemas com liberação de memória
    Questao questaoCopiada;
    strcpy(questaoCopiada.pergunta, questao.pergunta);
    questaoCopiada.numAlternativas = questao.numAlternativas;
    questaoCopiada.respostaCorreta = questao.respostaCorreta;
    
    // Alocar e copiar alternativas
    questaoCopiada.alternativas = (char**)realloc(NULL, questao.numAlternativas * sizeof(char*));
    for (int i = 0; i < questao.numAlternativas; i++) {
        questaoCopiada.alternativas[i] = (char*)realloc(NULL, strlen(questao.alternativas[i]) + 1);
        strcpy(questaoCopiada.alternativas[i], questao.alternativas[i]);
    }
    
    // Liberar a lista original
    liberarListaQuestoes(&lista);
    
    return questaoCopiada;
}

Questao obterPergunta(ListaQuestoes lista)
{
    if (lista.quantidadeQuestoes == 0) {
        printf("Erro: Nenhuma questao encontrada no arquivo!\n");
        Questao questaoVazia = {0};
        return questaoVazia;
    }
    
    srand(time(NULL));
    int i = rand() % lista.quantidadeQuestoes;
    return lista.questoes[i];
}

void adicionarQuestao(ListaQuestoes *lista, Questao questao) {
    lista->questoes = (Questao *)realloc(lista->questoes, (lista->quantidadeQuestoes + 1) * sizeof(Questao));
    lista->questoes[lista->quantidadeQuestoes] = questao;
    lista->quantidadeQuestoes++;
}

ListaQuestoes lerQuestoesDeArquivo(char *nomeArquivo)
{
    ListaQuestoes lista;
    lista.quantidadeQuestoes = 0;
    lista.questoes = NULL;
    
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return lista;
    }
    
    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = 0;
        
        if (strlen(linha) > 0 && linha[0] != 'A' && linha[0] != 'B' && linha[0] != 'C' && linha[0] != 'D' && strncmp(linha, "RESPOSTA:", 9) != 0)
        {
            Questao questao;
            strcpy(questao.pergunta, linha);
            
            questao.alternativas = NULL;
            questao.numAlternativas = 0;
            
            while (fgets(linha, sizeof(linha), arquivo))
            {
                linha[strcspn(linha, "\n")] = 0;
                
                if (strncmp(linha, "RESPOSTA:", 9) == 0)
                {
                    questao.respostaCorreta = linha[9];
                    break;
                }
                                 else if (strlen(linha) > 0 && (linha[0] == 'A' || linha[0] == 'B' || linha[0] == 'C' || linha[0] == 'D'))
                 {
                     questao.alternativas = (char **)realloc(questao.alternativas, (questao.numAlternativas + 1) * sizeof(char *));
                     questao.alternativas[questao.numAlternativas] = (char *)realloc(NULL, strlen(linha + 3) + 1);
                     strcpy(questao.alternativas[questao.numAlternativas], linha + 3);
                     questao.numAlternativas++;
                 }
            }
            
            adicionarQuestao(&lista, questao);
        }
    }
    
    fclose(arquivo);
    return lista;
}

void liberarQuestao(Questao *questao)
{
    for (int i = 0; i < questao->numAlternativas; i++)
    {
        free(questao->alternativas[i]);
    }
    free(questao->alternativas);
}

void liberarListaQuestoes(ListaQuestoes *lista)
{
    for (int i = 0; i < lista->quantidadeQuestoes; i++)
    {
        liberarQuestao(&lista->questoes[i]);
    }
    free(lista->questoes);
}

void mostrarPontosEVidas(Jogador jogador) {
    printf("Pontos: %d\n", jogador.pontuacao);
    printf("Vidas restantes: %d\n\n", jogador.vidas);
}

char lerRespostaValida(int numAlternativas)
{
    char resposta;
    do
    {
        printf(" > Letra: ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);
        if (resposta < 'A' || resposta > 'A' + numAlternativas - 1)
        {
            printf("Resposta inválida. Por favor, escolha uma letra válida.\n");
        }
    } while (resposta < 'A' || resposta > 'A' + numAlternativas - 1);
    return resposta;
}

void mostrarMenu()
{
    printf("======= MENU PRINCIPAL =======\n");
    printf("%d - Jogar\n", MENU_JOGAR);
    printf("%d - Sair\n", MENU_SAIR);
    printf("==============================\n");
}

int lerOpcaoMenu()
{
    int opcao;
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void jogar()
{
    printf("\nInsira seu nome: \n > ");
    Jogador jogador;
    scanf("%s", jogador.nome);
    printf("Cadastro realizado! Boa sorte, %s.\n\n", jogador.nome);
    WAIT(1);
    jogador.pontuacao = 0;
    jogador.vidas = 3;
    
    while (jogador.vidas > 0)
    {
        Alternativa *alternativas;
        int numAlternativas;
        
        Questao questao = obterQuestao(jogador.pontuacao);
        
        // Verificar se a questão é válida
        if (questao.numAlternativas == 0 || questao.alternativas == NULL) {
            printf("Erro: Questao invalida! Encerrando o jogo.\n");
            break;
        }
        
        embaralharAlternativas(questao, &alternativas, &numAlternativas);
        
        // Verificar se o embaralhamento foi bem-sucedido
        if (alternativas == NULL || numAlternativas == 0) {
            printf("Erro: Falha ao processar questao! Encerrando o jogo.\n");
            liberarQuestao(&questao);
            break;
        }
        
        mostrarQuestao(questao, alternativas, numAlternativas);
        
        jogador.resposta = lerRespostaValida(numAlternativas);
        
        if (verificarResposta(alternativas, numAlternativas, jogador.resposta) == 1)
        {
            jogador.pontuacao++;
            printf("\nCerta resposta!\n");
            mostrarPontosEVidas(jogador);
            WAIT(1);
        }
        else
        {
            jogador.vidas--;
            printf("\nResposta errada!\n");
            mostrarPontosEVidas(jogador);
            WAIT(1);
        }

        free(alternativas);
        liberarQuestao(&questao);

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
    
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
    getchar();
}