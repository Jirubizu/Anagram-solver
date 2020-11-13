#include <iostream>
#include <sstream>
#include "Timer.h"
#include "Solver.h"

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

[[noreturn]] void Menu()
{
    Timer timer;
    Solver solver("Words_75K_PreSubmissionTesting.csv");
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
                    currentString = solver.GetWord();
                    std::cout << "\033c";

                    break;
                case 2:

                    timer.Start();
                    solver.FindAnagram(currentString);
                    timeTaken = timer.Stop();

                    break;
                case 3:
                    timer.Start();
                    solver.LargestWordAvailable(currentString);
                    timeTaken = timer.Stop();

                    break;
                case 4:
                    timer.Start();
                    solver.FindAll3LetterAnagrams();
                    timeTaken = timer.Stop();

                    break;
                case 5:
                    timer.Start();
                    solver.FindAll5LetterAnagrams();
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