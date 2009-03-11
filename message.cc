/* Copyright 2009 Sorin Stancu-Mara */

#include "message.h"

Message::Message(double send_time, int size) 
    : sendTime(send_time), size(size) {}

bool operator<(const Message& lhs, const Message& rhs) {
    return lhs.sendTime < rhs.sendTime;
}
bool operator<=(const Message& lhs, const Message& rhs) {
    return lhs.sendTime <= rhs.sendTime;
}
bool operator==(const Message& lhs, const Message& rhs) {
    return lhs.sendTime == rhs.sendTime;
}
bool operator>(const Message& lhs, const Message& rhs) {
    return lhs.sendTime > rhs.sendTime;
}
bool operator>=(const Message& lhs, const Message& rhs) {
    return lhs.sendTime >= rhs.sendTime;
}
bool operator!=(const Message& lhs, const Message& rhs) {
    return lhs.sendTime != rhs.sendTime;
}

