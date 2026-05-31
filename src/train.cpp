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
    if (first == nullptr) return 0;
    first->light = true; 
    Car* cur = first;
    int steps_forward = 0;
    while (true) {
        cur = cur->next;
        countOp++;
        steps_forward++;
        if (cur->light == true) {
            cur->light = false;
            Car* temp = cur;
            for (int i = 0; i < steps_forward; i++) {
                temp = temp->prev;
                countOp++;
            }
            if (temp->light == false) {
                return steps_forward;
            }
            for (int i = 0; i < steps_forward; i++) {
                temp = temp->next;
                countOp++;
            }
            cur->light = true;
        }
    }
}
