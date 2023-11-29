#pragma once

#include "constants.h";
#include "../Core/tree.h"

#include <vector>; 

class TreeBuilder {
	std::vector<SyntaxNode> syntaxNodes;
	std::vector<SyntaxNode> rulesStack = {};

	void buildTree(TreeNode<SyntaxNode>* current, TreeNode<SyntaxNode>* parent) {
		
		std::vector<SyntaxCharMeta> items = current->value.rule.rule.items;
		std::vector<SyntaxCharMeta> nonterminals = current->value.rule.rule.getNonTerminalItems();

		std::reverse(nonterminals.begin(), nonterminals.end());
		std::reverse(items.begin(), items.end());


		for (SyntaxCharMeta meta : items) {
			
		}

		for (SyntaxCharMeta nonterminal : nonterminals) {
			if (rulesStack.empty()) {
				return;
			}
			if (nonterminal == SYNTAX_TOKENS::IDENTIFIER) {				
				return;
			}
			else {
				SyntaxNode node = rulesStack.back();
				rulesStack.pop_back();
				TreeNode<SyntaxNode>* nextNode = new TreeNode<SyntaxNode>(node);
				current->addChild(nextNode);
				buildTree(nextNode, current);
			}
		}
	}

public:
	TreeBuilder(std::vector<SyntaxNode> syntaxNodes) 
		: syntaxNodes(syntaxNodes)
		, rulesStack(syntaxNodes)
	{ };

	Tree<SyntaxNode> build() {
		Tree<SyntaxNode>* tree = new Tree<SyntaxNode>();

		SyntaxNode root = rulesStack.back();
		
		rulesStack.pop_back();

		TreeNode<SyntaxNode>* rootNode = new TreeNode<SyntaxNode>(root);

		rootNode->parent = NULL;
		tree->root = rootNode;

		buildTree(rootNode, nullptr);

		return *tree;
	}
};

class TreeBuilder2 {
	std::vector<SyntaxNode> syntaxNodes;

	std::vector<SyntaxNode> rulesStack = {};

	void buildTree(TreeNode<SyntaxNode>* current, TreeNode<SyntaxNode>* parent) {

		std::vector<SyntaxCharMeta> nonterminals = current->value.rule.rule.getNonTerminalItems();

		std::reverse(nonterminals.begin(), nonterminals.end());

		if (nonterminals.size() == 0) {
			return;
		}

		for (SyntaxCharMeta nonterminal : nonterminals) {
			if (rulesStack.empty()) {
				return;
			}
			if (nonterminal == SYNTAX_TOKENS::IDENTIFIER) {
				return;
			}
			else {
				SyntaxNode node = rulesStack.back();
				rulesStack.pop_back();
				TreeNode<SyntaxNode>* nextNode = new TreeNode<SyntaxNode>(node);
				current->addChild(nextNode);
				buildTree(nextNode, current);
			}
		}
	}

public:
	TreeBuilder2(std::vector<SyntaxNode> syntaxNodes) : syntaxNodes(syntaxNodes) {};

	Tree<SyntaxNode> build() {
		Tree<SyntaxNode>* tree = new Tree<SyntaxNode>();

		rulesStack = syntaxNodes;

		SyntaxNode root = rulesStack.back();
		rulesStack.pop_back();

		TreeNode<SyntaxNode>* rootNode = new TreeNode<SyntaxNode>(root);

		rootNode->parent = NULL;
		tree->root = rootNode;

		buildTree(rootNode, nullptr);

		return *tree;
	}
};