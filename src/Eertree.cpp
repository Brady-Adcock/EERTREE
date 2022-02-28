#include "Eertree.h"
#include "ImaginaryStringPalindromeNode.h"
#include "EmptyStringPalindromeNode.h"


Eertree::Eertree(const std::vector<std::string>& str) 
{
	for (int i = 0; i < str.size(); i++) {
		std::vector<char> string = std::vector<char>(str.at(i).begin(), str.at(i).end());
		strings.push_back(string);
	}

}

void Eertree::initTree()
{
	ImaginaryStringPalindromeNode *imaginaryString = new ImaginaryStringPalindromeNode();
	//imaginaryString->string_from.push_back(current_str);
	quicklinks[imaginaryString->getLabel()] = imaginaryString;
	tree.push_back(imaginaryString);

	PalindromeNode *emptyString = new EmptyStringPalindromeNode(imaginaryString);
	//emptyString->string_from.push_back(current_str);
	tree.push_back(emptyString);
	quicklinks[emptyString->getLabel()] = imaginaryString;

	currentLongestPalindromeSuffixNodeIndex = emptyString->getIndex();
	initisdone = true;
}

void Eertree::build()
{
	current_str = 0;
	if (!initisdone) {
		initTree();
		stackofsuffixnodes.push({ 1, false });
	}
	else {
		currentLongestPalindromeSuffixNodeIndex = stackofsuffixnodes.top().first;
	}
	for (int j = 0; j < strings.size(); j++) {
		current_str = j;
		string = strings.at(j);
		for (int i = 0; i < string.size(); i++)
		{
			addLetter(i);
		}
		currentLongestPalindromeSuffixNodeIndex = 1;
	}
}

void Eertree::pop() {
	if (stackofsuffixnodes.size() == 1) {
		return;
	}
	if (stackofsuffixnodes.top().second) {
		currentLongestPalindromeSuffixNodeIndex = stackofsuffixnodes.top().first;
		stackofsuffixnodes.pop();
		PalindromeNode* toberemoved = tree[tree.size() - 1];
		quicklinks.erase(toberemoved->getLabel());
		PalindromeNode* toberemovedparent = toberemoved->getParent();
		std::string s(1, toberemoved->getLabel().back());
		(*(toberemovedparent->getOutgoingNodes())).erase(s);
		tree.pop_back();
		string.pop_back();
	}
	else {
		currentLongestPalindromeSuffixNodeIndex = stackofsuffixnodes.top().first;
		stackofsuffixnodes.pop();
		string.pop_back();
	}
	return;
}

bool Eertree::addLetterChar(char letter) {
	this->string.push_back(letter);
	return this->addLetter(string.size() - 1);
}

/**
 * Returning true or false if a new palindrome has been added to the eertree.
 * This returned boolean is not used in this example but it could be useful depending on the problem to which
 * the eertree is applied
 */
bool Eertree::addLetter(int letterIndex)
{
	if (!initisdone) {
		initTree();
		stackofsuffixnodes.push({ 1, false });
	}
	else {
		currentLongestPalindromeSuffixNodeIndex = stackofsuffixnodes.top().first;
	}

	Insertion *insertion = new Insertion(this->string, letterIndex);
	PalindromeNode *longestPalindromePrefix = getLongestPalindromePrefixForNextPalindromeNode(insertion);



	if (isDuplicatePalindrome(insertion->letter, longestPalindromePrefix))
	{
		//in this version of the algorithm (from the official paper) we do not keep track of duplicate palindromes.
		//If the problem requires it (e.g. to find out the total number of palindromes including duplicates),
		//you could need to keep track of the duplicate palindromes with a counter inside the PalindromeNode class
		currentLongestPalindromeSuffixNodeIndex = (*longestPalindromePrefix->getOutgoingNodes()).find(insertion->letter)->second->getIndex();

		stackofsuffixnodes.push({ currentLongestPalindromeSuffixNodeIndex, false });

		return false;
	}

	addNewPalindromeNode(longestPalindromePrefix, insertion);

	stackofsuffixnodes.push({ currentLongestPalindromeSuffixNodeIndex, true });

	return true;
}

void Eertree::addNewPalindromeNode(PalindromeNode* longestPalindromePrefix, Insertion* insertion)
{
	int nextNodeIndex = tree.size(); //current max node index is tree.size() - 1
	//I create a PalindromeNode with a null suffix, I'll update that later
	PalindromeNode *newNode = new PalindromeNode(nextNodeIndex);
	if (longestPalindromePrefix->isImaginaryStringPalindromeNode())
	{
		//we are ignoring the imaginary prefix (centered at the position -1 of the string) and what comes before
		// the suffix (i.e. an occurrence of addedLetter at the left of the imaginary string,
		// and we just add a new palindrome of length 1 and content 'addedLetter'
		newNode->setLabel(insertion->letter);
	}
	else
	{
		newNode->setLabel(insertion->letter + longestPalindromePrefix->getLabel() + insertion->letter);
	}
	newNode->string_from.push_back(current_str);
	tree.push_back(newNode);

	//adding the edge connecting the palindrome prefix to the new PalindromeNode
	(* longestPalindromePrefix->getOutgoingNodes())[insertion->letter] = newNode;

	newNode->setParent(longestPalindromePrefix);

	//suffix reference to imaginary string is not allowed, change it to the empty string
	if (longestPalindromePrefix->isImaginaryStringPalindromeNode())
	{
		newNode->setLongestPalindromeSuffix(tree.at(INDEX_EMPTY_STRING));
	}
	else
	{
		PalindromeNode *suffixForNewNode = getLongestPalindromeSuffixForNewNode(insertion, longestPalindromePrefix);
		newNode->setLongestPalindromeSuffix(suffixForNewNode);
	}

	PalindromeNode* temp1 = newNode->getLongestPalindromeSuffix();
	PalindromeNode* temp2 = newNode->getLongestPalindromeSuffix()->getLongestPalindromeSuffix();
	int index1;
	if (temp1->getPalindromeLength() == -1) {
		 index1 = string.size() - 1;
	}
	else {
		index1 = insertion->letterIndex - temp1->getPalindromeLength();
	}

	int index2;
	if (temp2->getPalindromeLength() == -1) {
		index2 = string.size() - 1;
	}
	else {
		index2 = insertion->letterIndex - temp2->getPalindromeLength();
	}
	if (string.at(index1) == string.at(index2)) {
		quicklinks[newNode->getLabel()] = quicklinks[newNode->getLongestPalindromeSuffix()->getLabel()];
	}
	else {
		quicklinks[newNode->getLabel()] = newNode->getLongestPalindromeSuffix()->getLongestPalindromeSuffix();
	}

	currentLongestPalindromeSuffixNodeIndex = newNode->getIndex();

}

bool Eertree::isDuplicatePalindrome(std::string letter, PalindromeNode *longestPalindromeSuffixForNextPalindrome)
{
	auto gen = *longestPalindromeSuffixForNextPalindrome->getOutgoingNodes();
	bool dup = gen.find(letter) != gen.end();

	if (dup) {
		PalindromeNode* dupnode = gen.find(letter)->second;
		if (dupnode->string_from[dupnode->string_from.size() - 1] != current_str) {
			dupnode->string_from.push_back(current_str);
		}
	}

	return dup;
}

PalindromeNode *Eertree::getLongestPalindromePrefixForNextPalindromeNode(Insertion *insertion)
{
	PalindromeNode *longestPalindromePrefix = tree.at(currentLongestPalindromeSuffixNodeIndex);
	int inital = insertion->letterIndex - longestPalindromePrefix->getPalindromeLength() - 1;
	int postinital = insertion->letterIndex - longestPalindromePrefix->getLongestPalindromeSuffix()->getPalindromeLength() - 1;
	if (!(inital < 0 || postinital < 0)) {
		if (string.at(inital) != insertion->letter[0] && string.at(postinital) != insertion->letter[0]) {
			longestPalindromePrefix = quicklinks.at(longestPalindromePrefix->getLabel());
		}
	}
	while (isNecessaryToKeepTraversingTheSuffixChain(insertion, longestPalindromePrefix))
	{
		longestPalindromePrefix = longestPalindromePrefix->getLongestPalindromeSuffix();
		int inital = insertion->letterIndex - longestPalindromePrefix->getPalindromeLength() - 1;
		int postinital = insertion->letterIndex - longestPalindromePrefix->getLongestPalindromeSuffix()->getPalindromeLength() - 1;
		if (!(inital < 0 || postinital < 0)) {
			if (string.at(inital) != insertion->letter[0] && string.at(postinital) != insertion->letter[0]) {
				longestPalindromePrefix = quicklinks.at(longestPalindromePrefix->getLabel());
			}
		}
	}
	return longestPalindromePrefix;
}

PalindromeNode *Eertree::getLongestPalindromeSuffixForNewNode(Insertion *insertion, PalindromeNode *longestPalindromePrefix)
{
	PalindromeNode *suffixForNewNode = longestPalindromePrefix->getLongestPalindromeSuffix();
	int inital = insertion->letterIndex - suffixForNewNode->getPalindromeLength() - 1;
	int postinital = insertion->letterIndex - suffixForNewNode->getLongestPalindromeSuffix()->getPalindromeLength() - 1;
	if (!(inital < 0 || postinital < 0)) {
		if (string.at(inital) != insertion->letter[0] && string.at(postinital) != insertion->letter[0]) {
			suffixForNewNode = quicklinks.at(suffixForNewNode->getLabel());
		}
	}

	while (isNecessaryToKeepTraversingTheSuffixChain(insertion, suffixForNewNode))
	{
		suffixForNewNode = suffixForNewNode->getLongestPalindromeSuffix();
		int inital = insertion->letterIndex - suffixForNewNode->getPalindromeLength() - 1;
		int postinital = insertion->letterIndex - suffixForNewNode->getLongestPalindromeSuffix()->getPalindromeLength() - 1;
		if (!(inital < 0 || postinital < 0)) {
			if (string.at(inital) != insertion->letter[0] && string.at(postinital) != insertion->letter[0]) {
				suffixForNewNode = quicklinks.at(suffixForNewNode->getLabel());
			}
		}

	}
	auto mapforedges = (*suffixForNewNode->getOutgoingNodes());
	if(!mapforedges.empty()){
		auto thing = mapforedges.find(insertion->letter);
		if(!(thing == mapforedges.end())){
			suffixForNewNode = thing->second;
		}
		
	}
	return suffixForNewNode;
}

bool Eertree::isNecessaryToKeepTraversingTheSuffixChain(Insertion *insertion, PalindromeNode *currentSuffix)
{
	 if (currentSuffix->isImaginaryStringPalindromeNode())
	 {
		 return false;
	 }
	//if B=suffixForNewNode is not imaginary, we need to check that inside the original string xBx is a palindrome
	int indexOfLetterPrecedingTheCurrentSuffix = insertion->letterIndex - currentSuffix->getPalindromeLength() - 1;
	if (indexOfLetterPrecedingTheCurrentSuffix < 0) {
		return true;
	}
	std::string s(1, string.at(indexOfLetterPrecedingTheCurrentSuffix));
	return insertion->letter != s;
}

void Eertree::print() {
	for (int i = 0; i < tree.size(); i++) {
		std::cout << tree.at(i)->toString() << std::endl;
	}
	std::cout << "This is the quicklink Tree" << std::endl;
	for (auto ql : quicklinks) {
		std::cout << "{" + ql.first + ", " + ql.second->getLabel() + ", " + std::to_string(ql.second->getIndex()) + "}" << std::endl;
	}
}

