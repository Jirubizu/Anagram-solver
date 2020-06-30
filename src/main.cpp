#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <map>
#include <sstream>

using namespace std::chrono;

#define cDATAFILE "Words_75K_PreSubmissionTesting.csv"

typedef std::map<std::string, std::vector<std::string>> SortedWordListMap;

struct LargeToSmallCompare
{
    bool operator()(const std::string &first, const std::string &second)
    {
        return first.size() > second.size();
    }
};

bool PopulateWordList(const char *filename, SortedWordListMap &map, size_t length = 0)
{
    map.clear();
    std::ifstream file(filename);
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

std::string GetWord(void)
{
    std::string localString;
    std::cout << "Please enter a word/phrase to manipulate" << std::endl;

    std::cin.ignore();
    std::getline(std::cin, localString);
    return localString;
}

int DisplayAnagram(std::vector<std::string> &anagrams, std::string &originalString, char option = 'A')
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
                if (anagrams.size() >= 1)
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

void CreateCombinations(std::string searchString, std::string res, std::vector<std::string> &combinations)
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

std::vector<std::string> GenerateAnagrams(std::string &originalString)
{
    LargeToSmallCompare largeToSmall;
    std::string localString = originalString;

    if (localString.empty())
    {
        return std::vector<std::string>();
    }
    else
    {
        localString.erase(std::remove(localString.begin(), localString.end(), ' '), localString.end());
        SortedWordListMap mymap;
        PopulateWordList(cDATAFILE, mymap);
        std::vector<std::string> anagrams;
        std::vector<std::string> combinations;
        combinations.clear();
        CreateCombinations(localString, "", combinations);

        for (std::string const &searchWord :combinations)
        {
            if (mymap.count(searchWord) == 1)
            {
                if (mymap[searchWord].size() == 1)
                {
                    anagrams.push_back(mymap[searchWord].front());
                }
                else
                {
                    for (auto it = mymap[searchWord].begin(); it != mymap[searchWord].end(); ++it)
                    {
                        anagrams.push_back(*it);
                    }
                }
            }
        }
        std::sort(anagrams.begin(), anagrams.end(), largeToSmall);
        anagrams.erase(std::remove_if(anagrams.begin(), anagrams.end(), [&localString](const std::string &word) {
            return word == localString;
        }), anagrams.end());
        return anagrams;
    }
}

void FindAnagram(std::string &originalString)
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

void LargestWordAvailable(std::string &originalString)
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

void FindAll3LetterAnagrams()
{
    SortedWordListMap mymap;
    PopulateWordList(cDATAFILE, mymap, 3);
    std::string outputString;
    for (auto it = mymap.begin(); it != mymap.end(); it++)
    {
        if (mymap[it->first].size() > 1)
        {
            outputString += "Anagram key '";
            outputString += it->first;
            outputString += "': ";
            for (std::string word :mymap[it->first])
            {
                outputString += word + ", ";
            }
            outputString += "\n";
        }
    }
    std::cout << outputString << std::endl;
}

void FindAll5LetterAnagrams()
{
    SortedWordListMap mymap;
    PopulateWordList(cDATAFILE, mymap, 5);
    std::string outputString;
    for (auto it = mymap.begin(); it != mymap.end(); it++)
    {
        if (mymap[it->first].size() > 1)
        {
            outputString += "Anagram key '";
            outputString += it->first;
            outputString += "': ";
            for (std::string word :mymap[it->first])
            {
                outputString += word + ", ";
            }
            outputString += "\n";
        }
    }
    std::cout << outputString << std::endl;
}

void QuitNow()
{
    std::string confirm;
    std::cout << "Are you sure you want to quit?\n";
    std::cin >> confirm;
    if (confirm == "y" || confirm == "Y" || confirm == "yes")
    {
        std::cout << "Thank you for using the program\n";
        exit(EXIT_SUCCESS);
    }
}

class Timer
{
public:
    void Start()
    {
        _start = high_resolution_clock::now();
    }

    double Stop()
    {
        auto finish = high_resolution_clock::now();
        double timeTaken = duration_cast<duration<double>>(finish - _start).count();
        return timeTaken;
    }

private:
    time_point<std::chrono::high_resolution_clock> _start;
};

[[noreturn]] void Menu()
{
    Timer timer;
    std::string currentString;
    double timeTaken = 0;
    std::string menuOption;
    while (true)
    {
        std::string outputString;
        outputString += "C++ String Manipulation Challenge \n\n";
        outputString += "\t1. Enter a word or phrase (current word/phrase is: " + currentString + ").\n";
        outputString += "\t2. Find an anagram of the word.\n";
        outputString += "\t3. Find the largest word containing (most of) these ""letters.\n";
        outputString += "\t4. Find all possible 3 letter words that are also ""anagrams.\n";
        outputString += "\t5. Find all possible 5 letter words that are also ""anagrams.\n";
        outputString += "\t0. Quit the program.\n\n";
        outputString += "\tTime taken to complete the last function was: ";
        std::ostringstream strs;
        strs << timeTaken;
        outputString += strs.str();
        outputString += "\n\nPlease enter a valid option (1 - 5 or 0 to quit): ";
        std::cout << outputString;
        std::cin >> menuOption;
        std::cout << "\033c";
        if (menuOption[0] > 53 || menuOption[0] < 48 || menuOption.size() > 1)
        {
            std::cout << menuOption << ": Is not a valid input please select a valid option provided \n";
        }
        else
        {
            menuOption[0] = menuOption[0] - '0';

            switch (menuOption[0])
            {
                case 1:
                    currentString = GetWord();
                    std::cout << "\033c";

                    break;
                case 2:

                    timer.Start();
                    FindAnagram(currentString);
                    timeTaken = timer.Stop();

                    break;
                case 3:
                    timer.Start();
                    LargestWordAvailable(currentString);
                    timeTaken = timer.Stop();

                    break;
                case 4:
                    timer.Start();
                    FindAll3LetterAnagrams();
                    timeTaken = timer.Stop();

                    break;
                case 5:
                    timer.Start();
                    FindAll5LetterAnagrams();
                    timeTaken = timer.Stop();

                    break;
                case 0:
                    QuitNow();
            }
        }
    }
}

int main()
{
    Menu();
}