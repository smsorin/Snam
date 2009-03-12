/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __LINK_H__
#define __LINK_H__

#include <vector>
#include "vector3.h"
#include "message.h"
#include <set>

class Node;

class Link {
  public:
    Link(const Node& from, const Node& to);
    ~Link();
    const Node& getFrom() const;
    const Node& getTo() const;
    int getCapacity() const;
    void setCapacity(int capacity);
    double getDelay() const;
    void setDelay(double delay);

    void Draw(double time) const;
    
    /* control Points mentance */
    void updateGeometry();
    void clearControlPoints();
    void addControlPoint(const Vector3&);

    /* message members */
    void addForwardMessage(const Message&);
    void addReverseMessage(const Message&);
    const std::multiset<Message>& getForwardStream() const;
    const std::multiset<Message>& getReverseStream() const;   

    double getFlyTime(const Message&) const;
  private:          
    Link(const Link&);
    Link& operator=(const Link&);

    std::multiset<Message> forward_stream, reverse_stream;
    mutable std::vector<Vector3> controlPoints;
    mutable std::vector<double> run_length;
    mutable float *geometry;
    mutable double length_;

    void setGeometryVertex(int pos, const Vector3& loc) const;
    void generateGeometry() const;

    int capacity_;
    double delay_;
    const Node& from_;
    const Node& to_;
};

#endif  // __LINK_H__
