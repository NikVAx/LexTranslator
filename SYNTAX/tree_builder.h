#pragma once

#include "constants.h";
#include "../Utils/utils.h"

#include <vector>; 

class TreeBuilder {
	std::vector<SyntaxNode> rules;
	std::vector<SyntaxNode> rulesStack = {};

	void buildTree(TreeNode<SyntaxNode>* current, TreeNode<SyntaxNode>* parent) {
		
		std::vector<SyntaxTokenMeta> items = current->value.rule.rule.items;
		std::vector<SyntaxTokenMeta> nonterminals = current->value.rule.rule.getNonTerminalItems();

		std::reverse(nonterminals.begin(), nonterminals.end());
		std::reverse(items.begin(), items.end());

		//if (nonterminals.size() == 0) {
		//	return;
		//}

		for (SyntaxTokenMeta meta : items) {
		
		}

		for (SyntaxTokenMeta nonterminal : nonterminals) {
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
	TreeBuilder(std::vector<SyntaxNode> rules) 
		: rules(rules)
		, rulesStack(rules)
	{
	};

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
	std::vector<SyntaxNode> rules;

	std::vector<SyntaxNode> rulesStack = {};

	void buildTree(TreeNode<SyntaxNode>* current, TreeNode<SyntaxNode>* parent) {

		std::vector<SyntaxTokenMeta> nonterminals = current->value.rule.rule.getNonTerminalItems();

		std::reverse(nonterminals.begin(), nonterminals.end());

		if (nonterminals.size() == 0) {
			return;
		}

		for (SyntaxTokenMeta nonterminal : nonterminals) {
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
	TreeBuilder2(std::vector<SyntaxNode> rules) : rules(rules) {};

	Tree<SyntaxNode> build() {
		Tree<SyntaxNode>* tree = new Tree<SyntaxNode>();

		rulesStack = rules;

		SyntaxNode root = rulesStack.back();
		rulesStack.pop_back();

		TreeNode<SyntaxNode>* rootNode = new TreeNode<SyntaxNode>(root);

		rootNode->parent = NULL;
		tree->root = rootNode;

		buildTree(rootNode, nullptr);

		return *tree;
	}
};