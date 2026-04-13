#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"
#include <iostream>
using namespace std;

// Construtor
OrderBook::OrderBook() {
    this->buy_head = nullptr;
    this->sell_head = nullptr;
    this->trans_head = nullptr;
}

// Destrutor
OrderBook::~OrderBook() {

    OrderNode* current = buy_head;
    while (current != nullptr) {
        OrderNode* next = current->next;
        delete current;
        current = next;
    }

    current = sell_head;
    while (current != nullptr) {
        OrderNode* next = current->next;
        delete current;
        current = next;
    }

    TransactionNode* tcurrent = trans_head;
    while (tcurrent != nullptr) {
        TransactionNode* next = tcurrent->next;
        delete tcurrent;
        tcurrent = next;
    }
}

// Insere uma ordem no início da lista
void OrderBook::insertOrder(OrderNode*& head, Order order) {
    OrderNode* novo = new OrderNode(order);
    novo->next = head;
    head = novo;
}

// Insere uma transação no início da lista de transações
void OrderBook::insertTransaction(Transaction transaction) {
    TransactionNode* novo = new TransactionNode(transaction);
    novo->next = trans_head;
    trans_head = novo;
}

// Remove um nó específico da lista de ordens
void OrderBook::removeOrder(OrderNode*& head, OrderNode* target) {

    if (head == target) {
        head = head->next;
        delete target;
        return;
    }

    OrderNode* current = head;
    while (current != nullptr && current->next != target) {
        current = current->next;
    }

    if (current != nullptr) {
        current->next = target->next;
        delete target;
    }
}

// Busca melhor venda para uma compra
OrderNode* OrderBook::findBestSell(float buy_price) {
    OrderNode* current = sell_head;
    OrderNode* best = nullptr;

    while (current != nullptr) {

        if (current->order.getPrice() <= buy_price) {
            if (best == nullptr) {
                best = current;
            } else if (current->order.getPrice() < best->order.getPrice()) {
                best = current;   
            } else if (current->order.getPrice() == best->order.getPrice() &&
                       current->order.getTimestamp() < best->order.getTimestamp()) {
                best = current;   
            }
        }
        current = current->next;
    }

    return best; 
}

// Busca melhor compra para uma venda
OrderNode* OrderBook::findBestBuy(float sell_price) {
    OrderNode* current = buy_head;
    OrderNode* best = nullptr;

    while (current != nullptr) {

        if (current->order.getPrice() >= sell_price) {
            if (best == nullptr) {
                best = current;
            } else if (current->order.getPrice() > best->order.getPrice()) {
                best = current; 
            } else if (current->order.getPrice() == best->order.getPrice() &&
                       current->order.getTimestamp() < best->order.getTimestamp()) {
                best = current;  
            }
        }
        current = current->next;
    }

    return best;  
}

bool OrderBook::submit(Order order) {

    if (order.getType() == 'B') {
        OrderNode* best = findBestSell(order.getPrice());

        if (best != nullptr) {
            Transaction t(order.getId(), best->order.getId(), best->order.getPrice());
            insertTransaction(t);
            removeOrder(sell_head, best);
            return true;

        } else {
            insertOrder(buy_head, order);
            return false;
        }
    }

    if (order.getType() == 'S') {
        OrderNode* best = findBestBuy(order.getPrice());

        if (best != nullptr) {
            Transaction t(best->order.getId(), order.getId(), best->order.getPrice());
            insertTransaction(t);
            removeOrder(buy_head, best);
            return true;

        } else {
            insertOrder(sell_head, order);
            return false;
        }
    }

    return false;
} 


bool OrderBook::cancel(int id) {
    
    // Busca na lista de Ordens de Compra
    OrderNode* current = buy_head;
    while (current != nullptr) {
        if (current->order.getId() == id) {
            removeOrder(buy_head, current);
            return true;
        }
        current = current->next;
    }

    // Busca na lista de Ordens de Venda
    current = sell_head;
    while (current != nullptr) {
        if (current->order.getId() == id) {
            removeOrder(sell_head, current);
            return true;
        }
        current = current->next;
    }

    return false;
}

Order* OrderBook::getBuyOrders(int* n){
    *n = 0;
    OrderNode* current = buy_head;
    if(current == nullptr){
        return nullptr;
    }
    while (current != nullptr){
        OrderNode* next = current->next;
        current = next;
        (*n)++;       //Fazendo a contagem de número de buys no array
    };

    Order* orders = new Order[*n];
    
    current = buy_head;
    int idx = 0;     // Criando um índice para saber qual transação que eu estou mudando
    while (current != nullptr){
        orders[idx] = current->order;
        idx++;        // Adicionando 1 no index
        OrderNode* next = current->next;
        current = next;
    }
    
    return orders;
}

Order* OrderBook::getSellOrders(int* n){
    *n = 0;
    OrderNode* current = sell_head;
    if(current == nullptr){
        return nullptr;
    }
    while (current != nullptr){
        OrderNode* next = current->next;
        current = next;
        (*n)++;       //Fazendo a contagem de número de sells no array
    };

    Order* orders = new Order[*n];
    
    current = sell_head;
    int idx = 0;     // Criando um índice para saber qual transação que eu estou mudando
    while (current != nullptr){
        orders[idx] = current->order;
        idx++;        // Adicionando 1 no index
        OrderNode* next = current->next;
        current = next;
    }
    
    return orders;
}

Transaction* OrderBook::getTransactions(int* n){
    *n = 0;
    TransactionNode* current = trans_head;
    if(current == nullptr){
        return nullptr;
    }

    while (current != nullptr){
        TransactionNode* next = current->next;
        current = next;
        (*n)++;       //Fazendo a contagem de número de transactions no array
    };

    Transaction* transactions = new Transaction[*n];
    
    current = trans_head;
    int idx = 0;     // Criando um índice para saber qual transação que eu estou mudando
    while (current != nullptr){
        transactions[idx] = current->transaction;
        idx++;        // Adicionando 1 no index
        TransactionNode* next = current->next;
        current = next;
    }
    
    return transactions;

}

void OrderBook::printBuyOrders(){
    int n;
    cout << "Buy Orders:" << endl;
    Order* orders = getBuyOrders(&n);
    if(orders == nullptr){
        cout << "(empty)" << endl;
        return;
    }
    for(int i = 0; i < n; i++){
        cout << endl
        << "["
        << orders[i].getId()
        << " | "
        << orders[i].getPrice()
        << " | "
        << orders[i].getTimestamp()
        << "]"
        << endl;
        
    }
    delete[] orders;
};

void OrderBook::printSellOrders(){
    int n;
    cout << "Sell Orders:" << endl;
    Order* orders = getSellOrders(&n);
    if(orders == nullptr){
        cout << "(empty)" << endl;
        return;
    }
    for(int i = 0; i < n; i++){
        cout << endl
        << "["
        << orders[i].getId()
        <<" | "
        << orders[i].getPrice()
        <<" | "
        << orders[i].getTimestamp()
        <<"]"
        << endl;
        
    }
    delete[] orders;
};

void OrderBook::printTransactions(){
    int n;
    cout << "Transactions:" << endl;
    Transaction* transacts = getTransactions(&n);
    if(transacts == nullptr){
        cout << "(empty)" << endl;
        return;
    }
    
    for(int i = 0; i < n; i++){
        cout << endl
        << "["
        << transacts[i].getBuyOrderId()
        <<", "
        << transacts[i].getSellOrderId()
        <<", "
        << transacts[i].getExecutionPrice()
        <<"]"
        << endl;
        
    }
    delete[] transacts;
};