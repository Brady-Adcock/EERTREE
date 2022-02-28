#pragma once

#include "PalindromeNode.h"
#include "ArrayList.h"
#include <string>
#include <vector>
#include <iostream>
#include "ArrayList.h"
#include "Insertion.h"
#include <stack>


class Eertree
{

public:
	//backing data structure for eertree nodes, an ArrayList for convenience, but it could also have been an array or an HashMap
	std::vector<PalindromeNode*> tree = std::vector<PalindromeNode*>();
	std::unordered_map<std::string, PalindromeNode*> quicklinks = std::unordered_map<std::string, PalindromeNode*>();
	int currentLongestPalindromeSuffixNodeIndex = 0;
	std::stack<std::pair<int, bool>> stackofsuffixnodes = std::stack<std::pair<int, bool>>();
	bool initisdone;
public:
	static constexpr int INDEX_EMPTY_STRING = 1;
	int current_str;
	std::vector<std::vector<char>> strings;
	std::vector<char> string;
	Eertree(const std::vector<std::string>& str);

public:
	void initTree();

	void pop();

	void build();

public:
	virtual bool addLetter(int letterIndex);

	bool addLetterChar(char letter);

public:
	void print();

	void addNewPalindromeNode(PalindromeNode *longestPalindromePrefix, Insertion *insertion);

	bool isDuplicatePalindrome(std::string letter, PalindromeNode* longestPalindromeSuffixForNextPalindrome);

	//if there is already an outgoing node from the longestPalindromeSuffix with the same letter, it means
	//there is already a duplicate of the palindrome we have just found.

	//I start with the longest palindrome suffix of the previous PalindromeNode added to the eertree, then I go back
	// traversing the eertree using the PalindromeNode.getLongestPalindromeSuffix() references, until I find an appropriate node to use as a prefix
	// for my next PalindromeNode (in worst case I end up hitting the imaginary string)
	PalindromeNode *getLongestPalindromePrefixForNextPalindromeNode(Insertion *insertion);

	//I start with the longest palindrome suffix of the palindrome prefix I have just used to compute the new PalindromeNode, then I
	//go back traversing the eertree using the PalindromeNode.getLongestPalindromeSuffix() references until I find an
	//appropriate palindrome suitable as a suffix for the new PalindromeNode
	PalindromeNode *getLongestPalindromeSuffixForNewNode(Insertion *insertion, PalindromeNode *longestPalindromePrefix);

	bool isNecessaryToKeepTraversingTheSuffixChain(Insertion *insertion, PalindromeNode *currentSuffix);

public:
	static void main(std::vector<std::string> &args);
};
