#include "OrderBook.hpp"
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