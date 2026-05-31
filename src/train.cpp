// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    first = nullptr;
    countOp = 0;
}

Train::~Train() {
    if (first == nullptr)
        return;
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
    Car* start = first;
    while (start->light) {
        start = start->next;
        countOp++;
    }
    start->light = true;
    int steps = 1;
    while (true) {
        Car* cur = start;
        for (int i = 0; i < steps; i++) {
            cur = cur->next;
            countOp++;
        }
        if (!cur->light) {
            cur->light = false;
            for (int i = 0; i < steps; i++) {
                cur = cur->prev;
                countOp++;
            }
            if (!cur->light)
                return steps;
            steps = 1;
        } else {
            steps++;
        }
    }
}
