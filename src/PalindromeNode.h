#pragma once

#include <string>
#include <unordered_map>

class PalindromeNode
{

private:
	std::string label;
	int index = 0;
	PalindromeNode *longestPalindromeSuffix;
	//Outgoing nodes representing the palindromes xAx that can be obtained adding a letter x to the current PalindromeNode A
	std::unordered_map<std::string, PalindromeNode*> outgoingNodes = std::unordered_map<std::string, PalindromeNode*>();
	PalindromeNode* parentPalindromeNode;
public:
	std::vector<int> string_from;

	virtual ~PalindromeNode()
	{
		delete longestPalindromeSuffix;
	}

public:
	PalindromeNode(int index);

	virtual bool isImaginaryStringPalindromeNode();

	virtual int getIndex();

	virtual void setIndex(int index);

	virtual int getPalindromeLength();

	virtual PalindromeNode* getParent();
	
	virtual void setParent(PalindromeNode* parent);

	virtual std::string getLabel();

	virtual void setLabel(const std::string &label);

	virtual PalindromeNode *getLongestPalindromeSuffix();

	virtual void setLongestPalindromeSuffix(PalindromeNode *longestPalindromeSuffix);


	/**
	 * Not required by the algorithm, it is just for outputting the Eertree in a human-friendly fashion
	 */
	virtual std::string toString();

	virtual std::unordered_map<std::string, PalindromeNode*>* getOutgoingNodes();

	virtual void setOutgoingNodes(std::unordered_map<std::string, PalindromeNode*> &outgoingNodes);
};
