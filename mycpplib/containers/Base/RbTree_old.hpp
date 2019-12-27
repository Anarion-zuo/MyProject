//
// Created by anarion on 2019/11/7.
//

#ifndef MYSTL_RBTREE_HPP
#define MYSTL_RBTREE_HPP

#include <utility>
#include <new>
#include "functors/binary_functor.hpp"
#include "allocator/Allocator.hpp"

template <typename Obj, typename Cmper = less_functor<Obj>, typename Equer = equal_functor<Obj>>
class RbTree {
#define RbRed 1
#define RbBlack 0
    typedef Obj* pObj;
    typedef Obj& rObj;
    typedef Obj&& rrObj;
    typedef unsigned long size_type;

    Equer equer;
    Cmper cmper;

    struct rb_node {
        pObj pobj;
        rb_node *left, *right, *parent;
        bool color;

        rb_node(const Obj& o, bool color, rb_node *left = nullptr, rb_node *right = nullptr, rb_node *parent = nullptr) : pobj(Allocator::allocate<Obj>()), left(left), right(right), color(color), parent(parent) {
            new (pobj) Obj(o);
        }

        rb_node(Obj&& o, bool color, rb_node *left = nullptr, rb_node *right = nullptr, rb_node *parent = nullptr) : pobj(Allocator::allocate<Obj>()), left(left), right(right), color(color), parent(parent) {
            new (pobj) Obj(std::forward<Obj>(o));
        }

        ~rb_node() {
            Allocator::deallocate<Obj>(pobj);
        }

        bool is_my_child(rb_node *node) {
            return node == left || node == right;
        }

        bool is_my_left(rb_node *node) {
            return node == left;
        }

        static rb_node *make_node(const Obj& obj, bool color) {
            rb_node *p = Allocator::allocate<rb_node>();
            new (p) rb_node(obj, color);
            return p;
        }

        static rb_node *make_node(Obj&& obj, bool color) {
            rb_node *p = Allocator::allocate<rb_node>();
            ::new (p) rb_node(std::forward<Obj>(obj), color);
            return p;
        }

        static bool is_black(rb_node *node) {
            if (node) {
                return node->color == RbBlack;
            }
            return true;
        }

        bool is_leaf() {
            return left == nullptr && right == nullptr;
        }

        bool is_full() {
            return left != nullptr && right != nullptr;
        }

        rb_node *left_most() {
            rb_node *node = this;
            while (node->left) {
                node = node->left;
            }
            return node;
        }

        rb_node *right_most() {
            rb_node *node = this;
            while (node->right) {
                node = node->right;
            }
            return node;
        }
    };

    static void left_rotate(rb_node *node) {
        if (node == nullptr) {
            return;
        }
        rb_node *p = node, *f = p->left, *v = p->right, *r = v->left, *x = v->right, *pp = p->parent;
        if (pp) {
            if (pp->is_my_left(p)) {
                pp->left = v;
            } else {
                pp->right = v;
            }
        }
        v->left = p;
        p->right = r;
        if (r)
            r->parent = p;
        p->parent = v;
        v->parent = pp;
    }

    static void right_rotate(rb_node *node) {
        if (node == nullptr) {
            return;
        }
        rb_node *p = node, *f = p->left, *v = p->right, *d = f->left, *k = f->right, *pp = p->parent;
        if (pp) {
            if (pp->is_my_left(p)) {
                pp->left = f;
            } else {
                pp->right = f;
            }
        }
        f->right = p;
        p->left = k;
        f->parent = pp;
        p->parent = f;
        if (k)
            k->parent = p;
    }

protected:
    rb_node *root = nullptr;
    size_type count = 0;

public:
    RbTree() = default;
    ~RbTree() {

    }

    size_type size() const {
        return count;
    }

    bool has(const Obj &obj) {
        rb_node *node = root;
        while (node) {
            if (equer(*node->pobj, obj)) {
                return true;
            }
            if (cmper(*node->pobj, obj)) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return false;
    }

    void update_root() {
        while (root->parent) {
            root = root->parent;
        }
    }

    void insert(const Obj &obj) {
        rb_node *node = rb_node::make_node(obj, RbRed);
        if (root == nullptr) {
            root = node;
            ++count;
            node->color = RbBlack;
            return;
        }
        // main procedure
        insert(node);
    }

    void insert(rb_node *node) {
        // find the node
        rb_node *cur = root, *parent;
        bool lr;
        while (cur) {
            if (equer(*cur->pobj, *node->pobj)) {
                // node exists, do nothing
                return;
            }
            // larger
            if (cmper(*cur->pobj, *node->pobj)) {
                parent = cur;
                cur = cur->right;
                lr = true;
            }
            // smaller
            else {
                parent = cur;
                cur = cur->left;
                lr = false;
            }
        }
        ++count;
        if (lr) {
            parent->right = node;
        } else {
            parent->left = node;
        }
        node->parent = parent;
        insert_fix(parent, lr);
        update_root();
    }

    void insert_fix(rb_node *parent, bool lr) {
        // black parent, balance not broken
        if (parent->color == RbBlack) {  // parent not possible nullptr
            return;
        }
        // red parent, complicated
        rb_node *grand = parent->parent, *uncle;
//        if (grand == nullptr) {
//
//        }
        if (grand->is_my_left(parent)) {  // set uncle
            uncle = grand->right;
        } else {
            uncle = grand->left;
        }
        // red uncle
        if (!rb_node::is_black(uncle)) {  // uncle can be nullptr, indirect predicate
            grand->color = RbRed;
            parent->color = RbBlack;
            uncle->color = RbBlack;
            rb_node *gp = grand->parent;
            if (gp == nullptr) {
                grand->color = RbBlack;
                return;
            }
            if (rb_node::is_black(gp)) {  // grand parent may be nullptr, as the case for root

            } else {
                insert_fix(gp, !gp->is_my_left(grand));  // recursive fix
            }
            return;
        }
        // black uncle, mirror
        if (!lr) {
            if (grand->is_my_left(parent)) {
                parent->color = RbBlack;
                grand->color = RbRed;
                right_rotate(grand);
                return;
            }
            // mirror
            right_rotate(parent);
            grand->right->color = RbBlack;
            grand->color = RbRed;
            left_rotate(grand);
            return;
        }
        if (grand->is_my_left(parent)) {
            left_rotate(parent);
            grand->left->color = RbBlack;
            grand->color = RbRed;
            right_rotate(grand);
            return;
        }
        // mirror
        parent->color = RbBlack;
        grand->color = RbRed;
        left_rotate(grand);
    }

    void remove(const Obj &obj) {
        if (root == nullptr) {
            // empty tree, do nothing
            return;
        }
        // find the node
        rb_node *cur = root;
        while (cur) {
            if (equer(*cur->pobj, obj)) {
                // node found, main procedure
                remove(cur);
                del_node(cur);
                --count;
                return;
            }
            // larger
            if (cmper(*cur->pobj, obj)) {
                cur = cur->right;
            }
            // smaller
            else {
                cur = cur->left;
            }
        }
        // node not found, do nothing
        return;
    }

    void swap_content(rb_node *n1, rb_node *n2) {
        Obj *p = n1->pobj;
        n1->pobj = n2->pobj;
        n2->pobj = p;
    }

    void remove(rb_node *node) {
        if (count == 1) {
            root = nullptr;
            return;
        }
        rb_node *nn;
        if (node->is_full()) {
            nn = node->left->right_most();
            // swap
            rb_node *np = node->parent, *nnp = nn->parent;
            if (np) {  // np->child = nn
                if (np->is_my_left(node)) {
                    np->left = nn;
                } else {
                    np->right = nn;
                }
            } else {
//                root = nn;
            }
            // parent
            nn->parent = np;
            nnp->right = node;
            node->parent = nnp;
            // childs
            rb_node *left = node->left, *right = node->right;
            node->left = nn->left;
            if (node->left)
                node->left->parent = node;
            node->right = nn->right;
            if (node->right)
                node->right->parent = node;
            nn->left = left;
            if (nn->left)
                nn->left->parent = nn;
            nn->right = right;
            if (nn->right)
                nn->right->parent = nn;
            // swap color
            bool t = node->color;
            node->color = nn->color;
            nn->color = t;
        }
        remove_main(node);
        update_root();
    }

    void del_node(rb_node *node) {
        rb_node *parent = node->parent;
        if (parent) {
            if (parent->is_my_left(node)) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        Allocator::deallocate(node);
    }

    void remove_case1(rb_node *node, rb_node *parent, rb_node *s, bool lr) {
        parent->color = RbRed;
        s->color = RbBlack;
        if (!lr) {  // left child
            left_rotate(parent);
        } else {  // right child
            right_rotate(parent);
        }
        // sibling becomes black
        if (!lr) {
            s = parent->right;
            if (s) {
                remove_case4(node, parent, s);
                return;
            }

        } else {
            s = parent->left;
            if (s) {
                remove_case4(node, parent, s);
                return;
            }
        }
    }

    void remove_case2(rb_node *node, rb_node *parent, rb_node *s, rb_node *sc, bool lr) {
        sc->color = RbBlack;
        // swap color
        bool t = s->color;
        s->color = parent->color;
        parent->color = t;
        // rotate
        if (!lr) {
            left_rotate(parent);
        } else {
            right_rotate(parent);
        }
//        del_node(node);
    }

    void remove_case3(rb_node *node, rb_node *parent, rb_node *s, rb_node *sc, bool lr) {
        s->color = RbRed;
        sc->color = RbBlack;
        if (!lr) {
            right_rotate(s);
        } else {
            left_rotate(s);
        }
        // case 2
        if (!lr) {
            s = parent->right;
            sc = s->right;
        } else {
            s = parent->left;
            sc = s->left;
        }
        remove_case2(node, parent, s, sc, lr);
    }

    void remove_case4(rb_node *node, rb_node *parent, rb_node *s) {
//        del_node(node);
        parent->color = RbBlack;
        s->color = RbRed;
    }

    void remove_case5(rb_node *node, rb_node *parent, rb_node *s, bool lr) {
        s->color = RbRed;
//        del_node(node);
        if (parent == root) {
            parent->color = RbBlack;
            return;
        }
        rb_node *left = parent->left, *right = parent->right;
        parent->left = nullptr;
        parent->right = nullptr;
        remove(parent);
        parent->left = left;
        parent->right = right;
    }

    void remove_main(rb_node *node) {
        // red node, nothing effected
        if (node->color == RbRed) {
//            del_node(node);
            // it is not possible for the red node to hold only a left or right subtree, not even a node, for it violates the property of same black count
            // therefore, i care not and simply delete it
            return;
        }
        // black node
        /*
         * as it might seem, the possible cases are limited to:
         * - deleting black leaf node
         * - deleting black node with a single red child
         * the latter is simpler, therefore comes first
         */
        rb_node *s, *parent = node->parent;
        bool lr;
        if (parent) {
            if (parent->is_my_left(node)) {
                lr = false;
                s = parent->right;
            } else {
                lr = true;
                s = parent->left;
            }
        } else {
            s = nullptr;
            lr = false;
        }
        // red child
        // it is only possible for the node to hold only one child, left or right
        if (!node->is_leaf()) {
            rb_node *child;
            if (node->left) {  // has left child
                child = node->left;
                node->left = nullptr;
                child->left = node;
            } else {  // has right child
                child = node->right;
                node->right = nullptr;
                child->right = node;
            }
            if (parent) {
                if (!lr) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            }
            child->parent = parent;
            node->parent = child;
            child->color = RbBlack;  // change replacing node color
            return;
        }
        remove_main_db(node, parent, s, lr);
    }

    void remove_main_db(rb_node *node, rb_node *parent, rb_node *s, bool lr) {

        // black leaf, complicated
        // red sibling
        if (!rb_node::is_black(s)) {
            remove_case1(node, parent, s, lr);
            return;
        }
        // black sibling
        // sc is the right/left child of the sibling
        rb_node *sc;
        if (!lr) {
            sc = s->right;
        } else {
            sc = s->left;
        }
        // red sr / sl
        if (!rb_node::is_black(sc)) {
            remove_case2(node, parent, s, sc, lr);
            return;
        }
        // black sr/sl
        if (!lr) {
            sc = s->left;
        } else {
            sc = s->right;
        }
        // red sl / sr
        if (!rb_node::is_black(sc)) {
            remove_case3(node, parent, s, sc, lr);
        }
        // red parent, node and sibling both black
        // under this circumstance the only possibility is that node and sibling are both leaf
        if (!rb_node::is_black(parent)) {
            remove_case4(node, parent, s);
            return;
        }
        // black parent
        remove_case5(node, parent, s, lr);
    }
};


#endif //MYSTL_RBTREE_HPP
