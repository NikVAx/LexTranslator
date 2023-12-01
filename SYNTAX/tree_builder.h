#pragma once

#include "constants.h"
#include "../Core/tree.h"

#include <vector>; 

//class TreeBuilder {
//	std::list<SyntaxNode> syntaxNodes;
//	std::list<SyntaxNode> rulesStack = {};
//
//	void buildTree(TreeNode<SyntaxNode>* current, TreeNode<SyntaxNode>* parent) {
//
//		std::vector<SyntaxChar> nonterminals = current->value.syntaxRule.buildRule.getNonTerminalItems();
//
//		std::reverse(nonterminals.begin(), nonterminals.end());
//
//		if (nonterminals.size() == 0) {
//			return;
//		}
//
//		for (SyntaxChar nonterminal : nonterminals) {
//			if (rulesStack.empty()) {
//				return;
//			}
//			if (nonterminal == SyntaxChars::IDENTIFIER) {
//				return;
//			}
//			else {
//				SyntaxNode node = rulesStack.back();
//				rulesStack.pop_back();
//				TreeNode<SyntaxNode>* nextNode = new TreeNode<SyntaxNode>(node);
//				current->addChild(nextNode);
//				buildTree(nextNode, current);
//			}
//		}
//	}
//
//public:
//	TreeBuilder(std::list<SyntaxNode> syntaxNodes) : syntaxNodes(syntaxNodes) {};
//
//	Tree<SyntaxNode> build() {
//		Tree<SyntaxNode>* tree = new Tree<SyntaxNode>();
//
//		rulesStack = syntaxNodes;
//
//		SyntaxNode root = rulesStack.back();
//		rulesStack.pop_back();
//
//		TreeNode<SyntaxNode>* rootNode = new TreeNode<SyntaxNode>(root);
//
//		rootNode->parent = NULL;
//		tree->root = rootNode;
//
//		buildTree(rootNode, nullptr);
//
//		return *tree;
//	}
//};