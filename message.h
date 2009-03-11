/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

class Message {
  public:
    Message(double send_time, int size);
    const double sendTime;
    const int size;
};

bool operator<(const Message& lhs, const Message& rhs);
bool operator<=(const Message& lhs, const Message& rhs);
bool operator==(const Message& lhs, const Message& rhs);
bool operator>(const Message& lhs, const Message& rhs);
bool operator>=(const Message& lhs, const Message& rhs);
bool operator!=(const Message& lhs, const Message& rhs);
#endif  // __MESSAGE_H__
