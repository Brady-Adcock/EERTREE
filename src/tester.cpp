#include "Eertree.h"


#include <functional>
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <time.h>
#include <unordered_set>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;

bool isPalindrome(string S)
{
    for (int i = 0; i < S.length() / 2; i++) {
        if (S[i] != S[S.length() - i - 1]) {
            return false;
        }
    }
    return true;
}

unordered_set<string> findPalSlow(string str) {
    unordered_set<string> set;
    for (int i = 0; i < str.length(); i++) {
        string subStr;
        for (int j = i; j < str.length(); j++) {
            subStr += str[j];
            if (isPalindrome(subStr)) {
                set.insert(subStr);
            }
        }
    }
    return set;
}

void expand(string str, int low, int high, unordered_set<string>& set)
{
    while (low >= 0 && high < str.length() && str[low] == str[high])
    {
        set.insert(str.substr(low, high - low + 1));
        low--, high++;
    }
}

unordered_set<string> findPalFast(string str)
{
    unordered_set<string> set;

    for (int i = 0; i < str.length(); i++)
    {
        expand(str, i, i, set);
        expand(str, i, i + 1, set);
    }

    return set;
}

//else {
//    std::string s(eertree.string.begin(), eertree.string.end());
//    std::cout << s + " " + std::to_string(i) << std::endl;
//}

void calcRichString(int i, Eertree eertree, int answers[], int limit) {
    answers[i]++;
    if (i >= limit) {
        return;
    }
    if (eertree.addLetterChar('a')) {
        calcRichString(i + 1, eertree, answers, limit);
    }
    eertree.pop();

    if (eertree.addLetterChar('b')) {
        calcRichString(i + 1, eertree, answers, limit);
    }
    eertree.pop();
}

int main()
{
    int answers[100];

    for (int i = 0; i < 100; i++) {
        answers[i] = 0;
    }

    string str2 = "";

    vector<string> input2{ str2 };

    Eertree* eertree2 = new Eertree(input2);

    string str1 = "";
    vector<string> input1{ str1 };
    Eertree* eertree1 = new Eertree(input1);

    eertree1->addLetterChar('a');

    int length = 25;
    int size_of_sigma = 2;
    
    

    std::cout << "Time takes for the slow method: " << std::endl;


    auto started = std::chrono::high_resolution_clock::now();
    //calcRichString(0, *eertree2, answers, length);
    auto slow = std::chrono::high_resolution_clock::now();

    std::cout << "\n";
    std::cout << chrono::duration_cast<chrono::milliseconds>(slow - started).count();
    std::cout << "\n";
    std::cout << "\n";

    for (int i = 0; i < length+1; i++) {
        std::cout << answers[i] << std::endl;
    }



    for (int i = 0; i < 100; i++) {
        answers[i] = 0;
    }
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Time takes for the fast method: " << std::endl;
    auto started2 = std::chrono::high_resolution_clock::now();
    calcRichString(1, *eertree1, answers, length);
    auto slow2 = std::chrono::high_resolution_clock::now();
    std::cout << "\n";
    std::cout << chrono::duration_cast<chrono::milliseconds>(slow2 - started2).count();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "1" << std::endl;
    for (int i = 1; i < length+1; i++) {
        std::cout << answers[i]*size_of_sigma << std::endl;
    }


    return 0;

}