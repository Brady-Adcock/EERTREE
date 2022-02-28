#include "EmptyStringPalindromeNode.h"

EmptyStringPalindromeNode::EmptyStringPalindromeNode(ImaginaryStringPalindromeNode *imaginaryStringPalindromeNode) : PalindromeNode(INDEX_EMPTY_STRING)
{
	setLongestPalindromeSuffix(imaginaryStringPalindromeNode);
	setLabel("");
}

std::string EmptyStringPalindromeNode::getLabel()
{
	return "";
}
