//
//  Node.cpp
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#include <stdio.h>
#include "Node.h"
#include <assert.h>

using namespace std;

bool comp(const Point& a, const Point& b) {
    return a.y < b.y;
}

void Node::build_helper(vector<Point> v) {
    // v is sorted
    
    if (v.size() == 1) {
        this->isLeaf = true;
        this->val = v[0].x;
        this->p = v[0];
    } else {
        this->isLeaf = false;
        vector<Point> w(v);
        sort(w.begin(), w.end(), comp);
        assert(w.size() > 1);
        this->yroot = this->builtYTree(w);
        
        size_t split = v.size() / 2;
        this->left = new Node;
        this->left->build_helper(vector<Point>(v.begin(), v.begin()+split));
        this->right = new Node;
        this->right->build_helper(vector<Point>(v.begin()+split, v.end()));
        this->val = (v[split].x + v[split - 1].x) / 2;
    }
}


YNode* Node::builtYTree(vector<Point> w) {
    YNode* a = new YNode;
    if (w.size() == 0) return nullptr;
    if (w.size() == 1) {
        a->p = w[0];
        return a;
    }
    size_t split = w.size() / 2;
    a->p = w[split];
    a->left = builtYTree(vector<Point>(w.begin(), w.begin()+split));
    a->right = builtYTree(vector<Point>(w.begin()+split+1, w.end()));
    return a;
}
