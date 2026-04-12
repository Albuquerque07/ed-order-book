#include "Order.hpp"

// Construtor
Order::Order(int id, char type, float price, int timestamp) {
    this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}

// Destrutor
Order::~Order() {

}

// Getters
int Order::getId() {
    return this->id;
}

char Order::getType() {
    return this->type;
}

float Order::getPrice() {
    return this->price;
}

int Order::getTimestamp() {
    return this->timestamp;
}