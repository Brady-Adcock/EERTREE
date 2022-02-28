

class Insertion
{
private:

public:
	std::string letter;
	int letterIndex;

	Insertion(std::vector<char> instring, int letterIndex) {
		std::string s(1, instring.at(letterIndex));
		this->letter = s;
		this->letterIndex = letterIndex;
	}
};
