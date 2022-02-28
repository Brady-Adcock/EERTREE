#include "PalindromeNode.h"
#include <string>
#include <vector>
#include <format>
#include <sstream>


PalindromeNode::PalindromeNode(int index)
{
	this->index = index;
}

bool PalindromeNode::isImaginaryStringPalindromeNode()
{
	return false;
}

int PalindromeNode::getIndex()
{
	return index;
}

void PalindromeNode::setIndex(int index)
{
	this->index = index;
}

int PalindromeNode::getPalindromeLength()
{
	return label.length();
}

std::string PalindromeNode::getLabel()
{
	return label;
}

void PalindromeNode::setLabel(const std::string &label)
{
	this->label = label;
}

PalindromeNode *PalindromeNode::getLongestPalindromeSuffix()
{
	return longestPalindromeSuffix;
}

void PalindromeNode::setLongestPalindromeSuffix(PalindromeNode *longestPalindromeSuffix)
{
	this->longestPalindromeSuffix = longestPalindromeSuffix;
}

std::string PalindromeNode::toString()
{
	std::string outgoingnodes = "";
	for (auto i : outgoingNodes) {
		outgoingnodes += i.second->getLabel();
		outgoingnodes += " ";
	}

	std::stringstream ss;
	for (size_t i = 0; i < string_from.size(); ++i)
	{
		if (i != 0)
			ss << ",";
		ss << string_from[i];
	}
	std::string s = ss.str();

	return "PalindromeNode[Label=" + this->label + ", Length = " + std::to_string(getPalindromeLength()) + ", OutgoingNodes = [" + outgoingnodes + "], LongestPalindromeSuffix = " + getLongestPalindromeSuffix()->getLabel() + ", Strings:" + s + "]\n";
}

std::unordered_map<std::string, PalindromeNode*>* PalindromeNode::getOutgoingNodes()
{
	return &outgoingNodes;
}

void PalindromeNode::setOutgoingNodes(std::unordered_map<std::string, PalindromeNode*> &outgoingNodes)
{
	this->outgoingNodes = outgoingNodes;
}

void PalindromeNode::setParent(PalindromeNode* p) {
	this->parentPalindromeNode = p;
}

PalindromeNode* PalindromeNode::getParent() {
	return this->parentPalindromeNode;
}
