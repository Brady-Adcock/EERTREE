#pragma once

#include "PalindromeNode.h"
#include <string>

/**
 * Imaginary String is a special node, with a different behaviour from the standard PalindromeNode:
 * - index fixed
 * - palindrome length -1
 * - autoloop as the longest palindrome suffix reference
 */
class ImaginaryStringPalindromeNode : public PalindromeNode
{

private:
	static constexpr int INDEX_IMAGINARY_STRING = 0;

public:
	ImaginaryStringPalindromeNode();

	std::string getLabel() override;

	PalindromeNode *getLongestPalindromeSuffix() override;

	int getPalindromeLength() override;

	bool isImaginaryStringPalindromeNode() override;

};
