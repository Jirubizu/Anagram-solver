//
// Created by Games Machine on 11/13/2020.
//

#ifndef ANAGRAM_SOLVER_SOLVER_H
#define ANAGRAM_SOLVER_SOLVER_H

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::vector<std::string>> SortedWordListMap;

struct LargeToSmallCompare
{
    bool operator()(const std::string &first, const std::string &second)
    {
        return first.size() > second.size();
    }
};

class Solver
{
private:
    const char *listLoc;
    SortedWordListMap sortedMap;
    LargeToSmallCompare comparer;

public:
    Solver(const char *wordListLoc);

    bool PopulateWordList(const char *filename, SortedWordListMap &map, size_t length = 0);

    std::string GetWord();

    int DisplayAnagram(std::vector<std::string> &anagrams, std::string &originalString, char option = 'A');

    void CreateCombinations(std::string searchString, std::string res, std::vector<std::string> &combinations);

    std::vector<std::string> GenerateAnagrams(std::string &originalString);

    void FindAnagram(std::string &originalString);

    void LargestWordAvailable(std::string &originalString);

    void FindAll3LetterAnagrams();

    void FindAll5LetterAnagrams();
};


#endif //ANAGRAM_SOLVER_SOLVER_H
