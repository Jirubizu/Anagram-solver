//
// Created by Games Machine on 11/13/2020.
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Solver.h"

Solver::Solver(const char *wordListLocation) : listLoc(wordListLocation)
{}

bool Solver::PopulateWordList(const char *filename, SortedWordListMap &map, size_t length)
{
    map.clear();

    std::ifstream file("Words_75K_PreSubmissionTesting.csv");
    if (!file.is_open())
    {
        std::cout << "File not found\n";
        return false;
    }
    std::string word;

    if (length == 0)
    {

        while (std::getline(file, word))
        {
            std::string sorted = word;

            std::sort(sorted.begin(), sorted.end());
            if (map.count(sorted) == 0)
            {
                map[sorted] = std::vector<std::string>();
            }
            map[sorted].push_back(word);
        }
    }
    else
    {
        while (std::getline(file, word))
        {
            if (word.length() == length)
            {
                std::string sorted = word;
                std::sort(sorted.begin(), sorted.end());
                if (map.count(sorted) == 0)
                {
                    map[sorted] = std::vector<std::string>();
                }
                map[sorted].push_back(word);
            }
        }
    }
    file.close();
    return true;
}

std::string Solver::GetWord()
{
    std::string localString;
    std::cout << "Please enter a word/phrase to manipulate" << std::endl;

    std::cin.ignore();
    std::getline(std::cin, localString);
    return localString;
}

int Solver::DisplayAnagram(std::vector<std::string> &anagrams, std::string &originalString, char option)
{
    std::string localString = originalString;
    std::transform(localString.begin(), localString.end(), localString.begin(), ::tolower);
    std::string outputString;
    outputString.clear();
    if (!anagrams.empty())
    {
        switch (option)
        {
            case 'A':
                for (auto word = anagrams.begin(); word != anagrams.end(); ++word)
                {
                    if (*word != localString)
                    {
                        if (word == anagrams.end() - 1)
                        {
                            outputString += *word;
                        }
                        else
                        {
                            outputString += *word;
                            outputString += ", ";
                        }
                    }
                }
                std::cout << "All possible anagrams for " << originalString << ": " << outputString << std::endl;
                break;
            case 'L':
                if (!anagrams.empty())
                {
                    std::cout << "The largest anagram is: " << anagrams[(std::rand() % anagrams.size())] << ", with " << anagrams.size() - 1 << " other anagrams found" << std::endl;
                }
                break;
        }
    }
    else
    {
        std::cout << "No anagrams found\n";
    }
    return 0;
}

void Solver::CreateCombinations(std::string searchString, std::string res, std::vector<std::string> &combinations)
{
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    std::sort(res.begin(), res.end());
    combinations.push_back(res);

    for (size_t i = 0; i < searchString.length(); i++)
    {
        char c = searchString[i];
        CreateCombinations(searchString.erase(i, 1), res + c, combinations);
    }
}

std::vector<std::string> Solver::GenerateAnagrams(std::string &originalString)
{
    std::string localString = originalString;

    if (localString.empty())
    {
        return std::vector<std::string>();
    }
    else
    {
        localString.erase(std::remove(localString.begin(), localString.end(), ' '), localString.end());

        PopulateWordList(listLoc, sortedMap);
        std::vector<std::string> anagrams;
        std::vector<std::string> combinations;
        combinations.clear();
        CreateCombinations(localString, "", combinations);

        for (std::string const &searchWord :combinations)
        {
            if (sortedMap.count(searchWord) == 1)
            {
                if (sortedMap[searchWord].size() == 1)
                {
                    anagrams.push_back(sortedMap[searchWord].front());
                }
                else
                {
                    for (auto it = sortedMap[searchWord].begin(); it != sortedMap[searchWord].end(); ++it)
                    {
                        anagrams.push_back(*it);
                    }
                }
            }
        }
        std::sort(anagrams.begin(), anagrams.end(), comparer);
        anagrams.erase(std::remove_if(anagrams.begin(), anagrams.end(), [&localString](const std::string &word) {
            return word == localString;
        }), anagrams.end());
        return anagrams;
    }
}

void Solver::FindAnagram(std::string &originalString)
{
    std::vector<std::string> anagrams = GenerateAnagrams(originalString);

    if (!anagrams.empty())
    {
        anagrams.erase(std::remove_if(anagrams.begin(), anagrams.end(), [&originalString](const std::string &word) {
            return word.length() != originalString.length();
        }), anagrams.end());

        DisplayAnagram(anagrams, originalString);
    }
    else
    {
        std::cout << "Enter a search word first!\n";
    }
}

void Solver::LargestWordAvailable(std::string &originalString)
{
    std::vector<std::string> anagrams = GenerateAnagrams(originalString);
    if (!anagrams.empty())
    {
        std::vector<std::string> onlyLarge;
        for (std::string &anagram : anagrams)
        {
            if (anagram.size() == anagrams[0].size())
            {
                onlyLarge.push_back(anagram);
            }
        }
        std::sort(onlyLarge.begin(), onlyLarge.end());
        onlyLarge.erase(std::unique(onlyLarge.begin(), onlyLarge.end()), onlyLarge.end());

        DisplayAnagram(onlyLarge, originalString, 'L');
    }

    else if (!originalString.empty())
    {
        std::cout << "No anagrams found!\n";
    }
    else
    {
        std::cout << "Enter a search word first!\n";
    }
}

void Solver::FindAll3LetterAnagrams()
{
    PopulateWordList(listLoc, sortedMap, 3);
    std::string outputString;
    for (auto &it : sortedMap)
    {
        if (sortedMap[it.first].size() > 1)
        {
            outputString += "Anagram key '";
            outputString += it.first;
            outputString += "': ";
            for (const std::string &word :sortedMap[it.first])
            {
                outputString += word + ", ";
            }
            outputString += "\n";
        }
    }
    std::cout << outputString << std::endl;
}

void Solver::FindAll5LetterAnagrams()
{
    PopulateWordList(listLoc, sortedMap, 5);
    std::string outputString;
    for (auto &it : sortedMap)
    {
        if (sortedMap[it.first].size() > 1)
        {
            outputString += "Anagram key '";
            outputString += it.first;
            outputString += "': ";
            for (const std::string &word :sortedMap[it.first])
            {
                outputString += word + ", ";
            }
            outputString += "\n";
        }
    }
    std::cout << outputString << std::endl;
}
