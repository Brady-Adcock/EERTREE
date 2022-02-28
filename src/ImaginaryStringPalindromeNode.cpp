#include "ImaginaryStringPalindromeNode.h"

ImaginaryStringPalindromeNode::ImaginaryStringPalindromeNode() : PalindromeNode(INDEX_IMAGINARY_STRING)
{
}

std::string ImaginaryStringPalindromeNode::getLabel()
{
	return "-1";
}

PalindromeNode *ImaginaryStringPalindromeNode::getLongestPalindromeSuffix()
{
	return this;
}

int ImaginaryStringPalindromeNode::getPalindromeLength()
{
	return -1;
}

bool ImaginaryStringPalindromeNode::isImaginaryStringPalindromeNode()
{
	return true;
}
