//
// Created by 左钰 on 2019/12/9.
//

#ifndef MYCPPLIB_COMPGRAPH_H
#define MYCPPLIB_COMPGRAPH_H


class CompGraph {
public:
    class Node {
    protected:
        Node *parent;
    public:
        virtual ~Node() {}
        explicit Node(Node *parent) : parent(parent) {}

        virtual void compute() = 0;
        virtual void differentiate() = 0;
        Node *getParent();
        void setParent(Node *node);
    };
};


#endif //MYCPPLIB_COMPGRAPH_H
