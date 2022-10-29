#include "Message.h"
#include<iostream>
Message::Message(char *msg): buffer(msg) {}



char*  Message::getMessage() {

    char *msg = new char[buffer.length()];
    for(int i = 0; i < buffer.size(); i++) {

        msg[i] = buffer[i];

    }

    return msg;

}

void Message::setMessage(char *msg) {

    std::string copyBuff(msg);

    buffer = copyBuff;

}