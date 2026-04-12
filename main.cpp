#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"

using namespace std;

void testGetters(OrderBook& book) {
    int nBuys = 0;
    int nSells = 0;
    int nTrans = 0;

    Order* buys = book.getBuyOrders(&nBuys);
    Order* sells = book.getSellOrders(&nSells);
    Transaction* trans = book.getTransactions(&nTrans);

    cout << "Total de Ordens de Compra em aberto: " << nBuys << endl;
    cout << "Total de Ordens de Venda em aberto: " << nSells << endl;
    cout << "Total de Transacoes executadas: " << nTrans << endl;

    delete[] buys;
    delete[] sells;
    delete[] trans;

    cout << "Memoria dos arrays dinamicos liberada com sucesso." << endl;
}

int main() {
    OrderBook book;

    // Inserindo uma compra por 10.0 e uma venda por 12.0 (nao devem dar match)
    book.submit(Order(1, 'B', 10.0, 1));
    book.submit(Order(2, 'S', 12.0, 2));
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // Inserindo venda por 10.0, deve casar imediatamente com a compra de ID 1
    bool executed = book.submit(Order(3, 'S', 10.0, 3));
    cout << "Ordem executada: " << executed << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // Cadastrando varias vendas com precos diferentes
    book.submit(Order(7, 'S', 9.5, 4));
    book.submit(Order(8, 'S', 8.0, 5));
    book.submit(Order(9, 'S', 8.0, 6)); 
    
    // Inserindo compra por 10.0. Deve casar com o ID 8 (menor preco e menor timestamp)
    book.submit(Order(10, 'B', 10.0, 7));
    book.printSellOrders();
    book.printTransactions();

    book.submit(Order(11, 'B', 5.0, 8)); // Iria pegar o ID 9 se não fosse cancelado
    cout << "Compras antes de cancelar:" << endl;
    book.printBuyOrders();
    
    bool cancelled = book.cancel(11);
    cout << "Ordem cancelada: " << cancelled << endl;
    cout << "Compras apos o cancelamento:" << endl;
    book.printBuyOrders();

    // Executando o teste dos metodos get...
    testGetters(book);

    return 0;
}