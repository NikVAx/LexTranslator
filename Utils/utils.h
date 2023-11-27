#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <functional>

template <class T>
struct TreeNode {
    T value;
    std::vector<TreeNode*> children;

    void addChild(TreeNode* node) {
        children.push_back(node);
    }

    TreeNode(std::string value = "") {
        this->value = value;
        this->children = {};
    }
};

template <class T>
class Tree {
public:
    TreeNode<T>* root;

    Tree() {
        root = NULL;
    }

    ~Tree() {
        freeCascade(root);
    }

    static TreeNode<T>* create(std::string value) {
        TreeNode<T>* node = new TreeNode<T>;
        node->value = value;
        return node;
    }

    void forEarch(std::function<void(TreeNode<T>*, int)> action) {
    
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