#include "Message.h"
#include<iostream>
Message::Message(void *ptr): ptr(ptr) {}



void*  Message::getMessage() {

    return ptr;

}

void Message::setMessage(void *ptr) {

    this->ptr = ptr;

}