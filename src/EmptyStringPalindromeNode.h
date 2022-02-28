#pragma once

#include "PalindromeNode.h"
#include "ImaginaryStringPalindromeNode.h"

/**
 * Empty String is a special node whose suffix is always the imaginary string, and whose index fixed
 */
class EmptyStringPalindromeNode : public PalindromeNode
{

public:
	static constexpr int INDEX_EMPTY_STRING = 1;

	EmptyStringPalindromeNode(ImaginaryStringPalindromeNode *imaginaryStringPalindromeNode);
	std::string getLabel() override;

};
