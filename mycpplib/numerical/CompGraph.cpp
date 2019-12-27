//
// Created by 左钰 on 2019/12/9.
//

#include "CompGraph.h"

CompGraph::Node *CompGraph::Node::getParent() {
    return parent;
}

void CompGraph::Node::setParent(CompGraph::Node *node) {
    parent = node;
}
