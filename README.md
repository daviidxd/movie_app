# Introdução

O objetivo do projeto é desenvolver uma aplicação em consola, utilizando a linguagem C ANSI e a abordagem procedimental e modular, por forma a implementar um sistema que facilite a gestão de filmes que permita criar, armazenar, organizar e pesquisar informação relacionada com filmes. O sistema deve utilizar vetores, estruturas, manipulação de ficheiros, subprogramas e módulos. O programa deve permitir inserir filmes, listar os registos e efetuar múltiplos tipos de pesquisa sobre filmes: títulos, atores, géneros e realizadores.

# Detalhes da Implementação

Para cada filme deve ser registada informação sobre:

* code - código do filme (deve ser único, não pode ser alterado e nunca pode ser repetido)
* title - título do filme
* genres - géneros em que o filme se encontra listado (um filme pode ter um ou mais destes géneros):
    * ACTION
    * ADVENTURE
    * ANIMATION
    * BIOGRAPHY
    * COMEDY
    * CRIME
    * DRAMA
    * FAMILY
    * FANTASY
    * HISTORY
    * HORROR
    * MUSIC
    * MUSICAL
    * MYSTERY
    * ROMANCE
    * SCI-FI
    * SPORT
    * THRILLER
    * WAR
    * WESTERN
* description - descrição do filme
* director – realizador do filme
* actors – lista de atores do filme
* year – ano do filme
* duration – duração do filme (em minutos)
* rating – nota do filme (valor entre [0, 10])
* favorite – número de utilizadores que marcaram o filme como filme favorito
* revenue – receita do filme (em milhões)

## Menu

O Menu deve disponibilizar opções para:

1. Listar todos os filmes (em tabela, com todos os detalhes exceto a descrição):
    * Por ordem crescente do code
    * Por ordem decrescente do rating
    * Por ordem alfabética do title
2. Pesquisar filmes (com todos os detalhes exceto a descrição em tabela):
    * Mostrar todos os filmes cujos títulos contenham a string introduzida
    * Mostrar todos os filmes do género selecionado
    * Mostrar todos os filmes do realizador introduzido
    * Mostrar todos os filmes com o ator introduzido
3. Consultar informação de um filme (fornecer code)
4. Adicionar filme (o code deve ser único e atribuído automaticamente, os restantes detalhes são fornecidos pelo utilizador)
0. Sair da aplicação (solicita confirmação)

### Notas
A numeração do Menu deve ser mantida na aplicação. Podem adicionar outras funcionalidades que considerem que se justifiquem, mas sempre com numeração superior a 9.
Devem ser efetuadas todas as validações necessárias (por exemplo, verificar se os valores introduzidos são válidos, se têm o formato esperado, etc.).
Os dados relativos às capacidades máximas, por exemplo, número máximo de 2000 filmes deve ser definido como constante simbólica.

# Implementação e codificação

O programa deve ser desenvolvido utilizando a linguagem C ANSI, colocando em prática os conceitos fundamentais do paradigma procedimental e modular e é permitida a utilização das bibliotecas disponíveis.

Em relação às regras de codificação, siga as convenções adotadas normalmente no decorrer da UC de AFP:
* A notação camelCase para os nomes de subprogramas e dos seus parâmetros, de variáveis locais e de variáveis
* A notação PascalCase para os nomes dos novos tipos/estruturas
* Não utilize o símbolo ‘underscore’ nos identificadores, nem abreviaturas no início das mesmas

É necessário que o projeto cumpra o que é pedido no enunciado sendo deixado ao critério do programador qualquer pormenor de implementação que não seja referido (o qual deve ser devidamente documentado).

Nas funcionalidades desenvolvidas devem ser incluídas todas as validações necessárias para impedir um comportamento incorreto do sistema.

Sempre que fizer sentido, os subprogramas devem ser responsáveis por apresentar no ecrã mensagens de informação e/ou erro indicando o processamento que foi realizado.

As mensagens apresentadas pela aplicação podem ser escritas em português ou inglês.
