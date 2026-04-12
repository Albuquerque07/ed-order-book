#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"

// Nó que guarda uma Order na lista encadeada
struct OrderNode {
    Order order;
    OrderNode* next;

    OrderNode(Order o) : order(o) {
        this->next = nullptr;
    }
};

// Nó que guarda uma Transaction na lista encadeada
struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;

    TransactionNode(Transaction t) : transaction(t) {
        this->next = nullptr;
    }
};

class OrderBook {
private:

    OrderNode* buy_head;
    OrderNode* sell_head;
    TransactionNode* trans_head;

    void insertOrder(OrderNode*& head, Order order);
    void insertTransaction(Transaction transaction);
    void removeOrder(OrderNode*& head, OrderNode* target);
    OrderNode* findBestSell(float buy_price);
    OrderNode* findBestBuy(float sell_price);

public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();
};

#endif