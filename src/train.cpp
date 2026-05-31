// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

Train::~Train() {
    if (first == nullptr) return;
    Car* cur = first->next;
    while (cur != first) {
        Car* temp = cur;
        cur = cur->next;
        delete temp;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car(light);
    if (first == nullptr) {
        first = newCar;
        first->next = first;
        first->prev = first;
        return;
    }
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
}

void Train::resetCounter() {
    countOp = 0;
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    resetCounter();
    if (first == nullptr)
        return 0;
    Car* cur = first;
    int len = 1;
    cur = cur->next;
    countOp++;
    while (cur != first) {
        len++;
        cur = cur->next;
        countOp++;
    }
    return len;
}
