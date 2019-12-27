//
// Created by 左钰 on 2019/12/9.
//

#ifndef MYCPPLIB_SINGLEPARAMVARIABLE_H
#define MYCPPLIB_SINGLEPARAMVARIABLE_H


#include <numerical/CompGraph.h>

class SingleParamVariable : public CompGraph::Node {
protected:
    double val;
public:
    explicit SingleParamVariable(Node *parent, double val) : Node(parent), val(val) {}
    void compute() override {}
};


#endif //MYCPPLIB_SINGLEPARAMVARIABLE_H
