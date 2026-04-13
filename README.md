# Order Book

Sistema simples de gerenciamento de ordens de compra e venda de livros, lista-2 da disciplina de Estrutura de Dados.

## Descrição

O sistema recebe ordens de compra e venda e verifica automaticamente se existe compatibilidade entre elas. Quando uma ordem compatível é encontrada, a transação é executada imediatamente e ambas as ordens são removidas do sistema. Caso contrário, a ordem fica armazenada aguardando uma segunda compatível.

Uma ordem de compra é compatível com uma ordem de venda quando o preço de venda é menor ou igual ao preço de compra. Havendo múltiplas compatíveis, o sistema escolhe a de melhor preço e, em caso de empate, a de menor timestamp.

## Organização interna

As ordens de compra, ordens de venda e transações são armazenadas em três listas encadeadas separadas. Cada nó da lista guarda o dado correspondente (uma Order ou Transaction) e um ponteiro para o próximo nó. O OrderBook mantém apenas um ponteiro para o início de cada lista.

Essa estrutura foi escolhida por ser simples de implementar sem uso de STL e por permitir inserção e remoção eficientes sem necessidade de realocar memória.

## Compilação

g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book

./order_book

## Arquivos

- main.cpp - casos de teste
- OrderBook.hpp / OrderBook.cpp - gerenciamento das ordens e transações
- Order.hpp / Order.cpp - representação de uma ordem
- Transaction.hpp / Transaction.cpp - representação de uma transação executada
