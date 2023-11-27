#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <functional>

template <class T>
struct TreeNode {
    T value;
    TreeNode<T>* parent;
    std::vector<TreeNode<T>*> children;

    void addChild(TreeNode* node) {
        node->parent = this;
        children.push_back(node);
    }

    TreeNode* addChild(T value) {
        TreeNode<T>* node = new TreeNode<T>(value);
        node->parent = this;
        children.push_back(node);
        return node;
    }

    TreeNode() {};

    TreeNode(T value) {
        this->value = value;
        this->parent = NULL;
        this->children = {};
    }
};

template <class T>
class Tree {
public:
    TreeNode<T>* root;

    Tree() : root(NULL) {}

    ~Tree() {
        freeCascade(root);
    }

    void print() {
        printCascase(root, 0);
    }
private:

    void forEachCascade(TreeNode<T>* root, int depth, std::function<void(TreeNode<T>*, int)> action) {
        if (root == NULL) {
            return;
        }

        for (int i = 0; i < root->children.size(); ++i) {
            action(root, depth);
            forEachCascade(root->children[i], depth + 1, action);
        }
    }

    void printCascase(TreeNode<T>* root, int depth) {
        if (root == NULL) {
            return;
        }

        for (int i = 0; i < depth; ++i) {
            std::cout << "-";
        }

        std::cout << root->value << "\n";

        for (int i = 0; i < root->children.size(); ++i) {
            printCascase(root->children[i], depth + 1);
        }
    }

    void freeCascade(TreeNode<T>* root) {
        if (root == NULL) {
            return;
        }

        for (int i = 0; i < root->children.size(); ++i) {
            freeCascade(root->children[i]);
        }
        delete root;
    }
};