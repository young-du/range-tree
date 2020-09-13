//
//  Tree.cpp
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#include "Tree.h"
#include "Node.h"
#include <iostream>
using namespace std;

bool operator<(const Point& a, const Point& b) {
    return a.x < b.x;
}

void Tree::build(vector<Point> v) {
    if (v.empty()) {
        root = nullptr;
        return;
    }
    sort(v.begin(), v.end());
    this->root = new Node;
    root->build_helper(v);
}

vector<Point> Tree::search(Point upperLeft, Point lowerRight) {
    vector<Point> res;
    Node* split = this->findSpliteNode(root, upperLeft.x, lowerRight.x);
    if (split->isLeaf) {
        checkLeaf(split, upperLeft, lowerRight, res);
        return res;
    }
    checkLeft(split->left, upperLeft, lowerRight, res);
    checkRight(split->right, upperLeft, lowerRight, res);
    return res;
}

Node* Tree::findSpliteNode(Node* n, double x1, double x2) {
    if (n->isLeaf) return n;
    if (n->val <= x1) return findSpliteNode(n->right, x1, x2);
    if (n->val >= x2) return findSpliteNode(n->left, x1, x2);
    return n;
}

void Tree::checkRight(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res) {
    if (n->isLeaf) {
        checkLeaf(n, upperLeft, lowerRight, res);
        return;
    }

    if (n->val <= lowerRight.x) {
        // report all the left subtree & go right
        if (n->left->isLeaf) checkLeaf(n->left, upperLeft, lowerRight, res);
        else checkY(n->left->yroot, lowerRight.y, upperLeft.y, res);
        checkRight(n->right, upperLeft, lowerRight, res);
    } else {
        // go left
        checkRight(n->left, upperLeft, lowerRight, res);
    }
}

void Tree::checkLeft(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res) {
    if (n->isLeaf) {
        checkLeaf(n, upperLeft, lowerRight, res);
        return;
    }

    if (n->val >= upperLeft.x) {
        // report all the right subtree & go left
        if (n->right->isLeaf) checkLeaf(n->right, upperLeft, lowerRight, res);
        else checkY(n->right->yroot, lowerRight.y, upperLeft.y, res);
        checkLeft(n->left, upperLeft, lowerRight, res);
    } else {
        // go right
        checkLeft(n->right, upperLeft, lowerRight, res);
    }
}

void Tree::checkLeaf(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res) {
    if (n->p.y >= lowerRight.y && n->p.y <= upperLeft.y
         && n->p.x <= lowerRight.x && n->p.x >= upperLeft.x) {
        res.push_back(n->p);
    }
}

void Tree::printPoints(vector<Point> v) {
    for (auto el: v) {
        cout << "("<< el.x<<", " << el.y<< ")\n";
    }
}


YNode* Tree::findYSpliteNode(YNode* n, double y1, double y2) {
    if (n->left == nullptr && n->right == nullptr) return n;
    if (n->p.y <= y1) return findYSpliteNode(n->right, y1, y2);
    if (n->p.y >= y2) return findYSpliteNode(n->left, y1, y2);
    return n;
}

void Tree::reportYSubtree(YNode* n, vector<Point>& res) {
    if (n == nullptr) return;
    res.push_back(n->p);
    reportYSubtree(n->left, res);
    reportYSubtree(n->right, res);
}

void Tree::checkYLeft(YNode* n, double y1, double y2, vector<Point>& res) {
    if (n == nullptr) return;
    if (n->left == nullptr && n->right == nullptr) {
        if (y1 <= n->p.y && n->p.y <= y2) res.push_back(n->p);
        return;
    }
    if (n->p.y >= y1) {
        // report all the right subtree & go left
        reportYSubtree(n->right, res);
        checkYLeft(n->left, y1, y2, res);
    } else {
        // go right
        checkYLeft(n->right, y1, y2, res);
    }
}
void Tree::checkYRight(YNode* n, double y1, double y2, vector<Point>& res) {
    if (n == nullptr) return;
    if (n->left == nullptr && n->right == nullptr) {
        if (y1 <= n->p.y && n->p.y <= y2) res.push_back(n->p);
        return;
    }
    if (n->p.y <= y2) {
        // report all the left subtree & go right
        reportYSubtree(n->left, res);
        checkYRight(n->right, y1, y2, res);
    } else {
        // go left
        checkYRight(n->left, y1, y2, res);
    }
}

void Tree::checkY(YNode* n, double y1, double y2, vector<Point>& res) {
    if (n == nullptr) return;
    YNode* split = this->findYSpliteNode(n, y1, y2);
    if (y1 <= n->p.y && n->p.y <= y2) res.push_back(n->p);
    checkYLeft(split->left, y1, y2, res);
    checkYRight(split->right, y1, y2, res);
}
