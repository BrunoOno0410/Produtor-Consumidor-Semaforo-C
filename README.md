# README

Este é um código em C que implementa um problema clássico de produtor-consumidor usando threads e semáforos. O programa consiste em produtores que geram números aleatórios e os colocam em um buffer compartilhado, enquanto os consumidores retiram esses números do buffer e os exibem na tela.

## Requisitos

- Sistema operacional compatível com a biblioteca pthread.
- Compilador C compatível.

## Como compilar e executar

1. Abra um terminal.
2. Navegue até o diretório onde o arquivo do código-fonte está localizado.
3. Compile o código usando o seguinte comando:

```shell
gcc nome_do_arquivo.c -o nome_do_programa -lpthread
```

Certifique-se de substituir "nome_do_arquivo.c" pelo nome real do arquivo e "nome_do_programa" pelo nome desejado para o executável.

4. Após a compilação bem-sucedida, execute o programa:

```shell
./nome_do_programa
```

## Funcionamento

O programa utiliza as seguintes variáveis globais:

- `NUMCONS`: Número de consumidores.
- `NUMPROD`: Número de produtores.
- `BUFFERSIZE`: Tamanho do buffer.
- `buffer`: Array que representa o buffer compartilhado.
- `currentidx`: Índice atual do buffer.
- `buffer_mutex`: Mutex para controlar o acesso ao buffer.
- `buffer_full`: Semáforo para indicar que o buffer está cheio.
- `buffer_empty`: Semáforo para indicar que o buffer está vazio.

O programa principal `main()` realiza as seguintes etapas:

1. Inicializa as variáveis e estruturas necessárias, como mutex e semáforos.
2. Cria threads para os consumidores e produtores.
3. Aguarda a conclusão das threads dos consumidores.
4. Aguarda a conclusão das threads dos produtores.

As funções `produtor()` e `consumidor()` são executadas por suas respectivas threads. A função `produtor()` realiza as seguintes etapas:

1. Gera um número aleatório `n`.
2. Tenta adquirir o mutex do buffer.
3. Verifica se o buffer está cheio. Se estiver, libera o mutex e aguarda pelo semáforo `buffer_full`.
4. Caso contrário, adiciona o número `n` ao buffer, atualiza o índice `currentidx` e verifica se o buffer estava vazio. Se estiver vazio, libera o semáforo `buffer_empty`.
5. Libera o mutex do buffer.
6. Exibe na tela o número produzido.
7. Aguarda por um tempo aleatório antes de repetir o processo.

A função `consumidor()` realiza as seguintes etapas:

1. Tenta adquirir o mutex do buffer.
2. Verifica se o buffer está vazio. Se estiver, libera o mutex e aguarda pelo semáforo `buffer_empty`.
3. Caso contrário, retira o número do buffer, atualiza o índice `currentidx` e verifica se o buffer estava cheio. Se estiver cheio, libera o semáforo `buffer_full`.
4. Libera o mutex do buffer.
5. Exibe na tela o número consumido.
6. Aguarda por um tempo aleatório antes de repetir o processo.

O programa continuará a produzir e consumir números aleatórios enquanto estiver em execução. Os produtores e consumidores trabalham em paralelo, garantindo que o buffer seja preenchido pelos produtores e esvaziado pelos consumidores adequadamente.

## Personalização

- Você pode ajustar os valores das constantes `NUMCONS`, `NUMPROD` e `BUFFERSIZE` para alterar o número de consumidores, produtores e o tamanho do buffer, respectivamente.
- Os tempos de espera aleatórios podem ser ajustados alterando o valor multiplicativo em `sleep((int) (drand48() * 4.0))`. O valor 4.0 determina o intervalo máximo de espera em segundos.
