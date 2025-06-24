# Jogo de Perguntas e Respostas em C

Um jogo interativo de perguntas e respostas desenvolvido em linguagem C, com sistema de pontuação, vidas e níveis de dificuldade dinâmicos.

## Propósito do Projeto

Este projeto educacional foi desenvolvido como uma aplicação de quiz sobre programação em C, destinado ao aprendizado e consolidação de conhecimentos. O sistema apresenta questões de múltipla escolha com complexidade crescente, proporcionando uma experiência de aprendizado interativa e desafiadora.

O programa carrega questões automaticamente de arquivos externos e oferece uma interface de terminal intuitiva, onde o jogador navega através de diferentes níveis de conhecimento, testando suas habilidades em programação.

## Metas Técnicas Implementadas

Este projeto foi desenvolvido com foco em aplicar e demonstrar conceitos avançados de programação em C:

- **Gerenciamento Dinâmico de Memória**: Implementação de alocação e liberação eficiente de memória usando `realloc()` e `free()`
- **Estruturas de Dados Personalizadas**: Utilização de `struct` para organizar dados complexos e `enum` para controle de estados
- **Processamento de Arquivos Externos**: Leitura e interpretação automática de dados a partir de arquivos `.txt`
- **Interface Interativa de Terminal**: Desenvolvimento de menus navegáveis com feedback visual ao usuário  
- **Validação Robusta de Dados**: Sistema de controle de fluxo com verificação rigorosa de entradas do usuário

## Especificação do Projeto

### Funcionalidades Principais

- **Sistema de Questões Dinâmico**: Suporte a qualquer quantidade de alternativas por pergunta (não limitado a A, B, C, D)
- **Níveis de Dificuldade**: 5 níveis de dificuldade baseados na pontuação do jogador
- **Sistema de Pontuação**: Pontos acumulados a cada resposta correta
- **Sistema de Vidas**: 3 vidas por partida
- **Embaralhamento de Alternativas**: As alternativas são embaralhadas a cada pergunta
- **Leitura Dinâmica de Arquivos**: Detecta automaticamente a estrutura das questões nos arquivos
- **Gerenciamento de Memória**: Alocação dinâmica otimizada para textos de tamanho variável

### Níveis de Dificuldade

1. **Muito Fácil** (0 pontos) - `nivel_muito_facil.txt`
2. **Fácil** (1 ponto) - `nivel_facil.txt`
3. **Médio** (2 pontos) - `nivel_medio.txt`
4. **Difícil** (3 pontos) - `nivel_dificil.txt`
5. **Muito Difícil** (4+ pontos) - `nivel_muito_dificil.txt`

### Estrutura dos Arquivos de Questões

Os arquivos de questões seguem o formato:

```
Texto da pergunta aqui?
A) Primeira alternativa
B) Segunda alternativa
C) Terceira alternativa
D) Quarta alternativa
E) Quinta alternativa (opcional)
F) Sexta alternativa (opcional)
RESPOSTA:C

Próxima pergunta aqui?
A) Alternativa 1
B) Alternativa 2  
C) Alternativa 3
RESPOSTA:A
```

**Formato Flexível Suportado:**
- `A)`, `A:`, `A.` - Todos os separadores são aceitos
- Qualquer quantidade de alternativas (A-Z)
- Texto das alternativas de tamanho variável

## Como Usar

### Pré-requisitos

- Compilador GCC
- Sistema operacional: Windows, Linux ou macOS

### Compilação

```bash
gcc -o programa programa.c
```

### Execução

```bash
./programa
```

## Instruções de Jogo

1. **Início**: Execute o programa e escolha a opção "1 - Jogar"
2. **Cadastro**: Digite seu nome (ou pressione Enter para usar "Jogador")
3. **Gameplay**: 
   - Leia a pergunta apresentada
   - Escolha uma das alternativas digitando a letra correspondente
   - Pressione Enter para confirmar
4. **Pontuação**: 
   - Resposta correta: +1 ponto
   - Resposta errada: -1 vida
5. **Condições de Vitória/Derrota**:
   - **Vitória**: Alcançar 5 pontos
   - **Derrota**: Perder todas as 3 vidas

### Exemplo de Tela do Jogo

```
=== PERGUNTA ===
Qual linguagem de programação foi criada por Dennis Ritchie?

=== ALTERNATIVAS ===
A: Python
B: C
C: Java
D: JavaScript

 > Letra: B

Certa resposta!
Pontos: 1
Vidas restantes: 3
```

## Estrutura do Projeto

```
perguntas-respostas-c/
├── programa.c                    # Código fonte principal
├── README.md                     # Este arquivo
├── nivel_muito_facil.txt        # Questões nível muito fácil
├── nivel_facil.txt              # Questões nível fácil
├── nivel_medio.txt              # Questões nível médio
├── nivel_dificil.txt            # Questões nível difícil
└── nivel_muito_dificil.txt      # Questões nível muito difícil
```

## Características Técnicas

### Estruturas de Dados

- **Questao**: Contém pergunta, alternativas e resposta correta
- **Alternativa**: Letra, texto dinâmico e flag de correção
- **Jogador**: Nome, pontuação, vidas e resposta atual
- **ListaQuestoes**: Array dinâmico de questões

### Algoritmos Utilizados

- **Fisher-Yates**: Para embaralhamento das alternativas
- **Alocação Dinâmica**: Para otimização de memória
- **Parsing Flexível**: Para leitura de arquivos com formatos variados

### Gerenciamento de Memória

- Alocação dinâmica com `realloc()`
- Liberação automática de memória
- Otimização para textos de tamanho variável

## Adicionando Novas Questões

Para adicionar novas questões, edite os arquivos `.txt` correspondentes seguindo o formato:

```
Sua pergunta aqui?
A) Alternativa 1
B) Alternativa 2
C) Alternativa 3
D) Alternativa 4
RESPOSTA:B
```

**Dicas:**
- Mantenha uma linha em branco entre questões
- Use `RESPOSTA:` seguido da letra correta
- Suporte para até 26 alternativas (A-Z)
- Texto das alternativas pode ter qualquer tamanho

## Funcionalidades Avançadas

- **Detecção Automática**: O programa detecta automaticamente quantas alternativas cada pergunta possui
- **Validação de Entrada**: Aceita apenas letras válidas como resposta
- **Recuperação de Erros**: Tratamento de erros de leitura de arquivos e entrada inválida
- **Multiplataforma**: Suporte a Windows (`Sleep`) e Unix (`sleep`)

## Exemplo de Partida Completa

```
== Bem vindo ao Jogo de Perguntas e Respostas ==

======= MENU PRINCIPAL =======
1 - Jogar
2 - Sair
==============================
Escolha uma opcao: 1

Insira seu nome: 
 > João

Cadastro realizado! Boa sorte, João.

> Dificuldade: Muito facil

Como declarar um array de 5 numeros inteiros em C?
A: int array[5];
B: array int[5];
C: int[] array = new int[5];
D: int array = {5};

 > Letra: A

Certa resposta!
Pontos: 1
Vidas restantes: 3

[... continua até 5 pontos ou 0 vidas ...]
```

## Desenvolvimento

O projeto utiliza boas práticas de programação em C:
- Modularização com funções específicas
- Gerenciamento adequado de memória
- Tratamento de erros
- Código legível e bem estruturado

---
