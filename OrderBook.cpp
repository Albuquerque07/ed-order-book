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