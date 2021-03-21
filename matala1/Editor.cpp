#include "Editor.h"
#include <iostream>

namespace edit
{

    Editor::Editor(std::string fileName)
    {

        this->document.fileName = fileName;
        this->document.readFromFile(fileName);
    }

    Editor::Editor()
    {
        this->document.fileName = "";
        this->document.numOfLine = 0;
    }
    void Editor::loop()
    {

        //std::cout << document.numOfLine << std::endl;

        std::string input = "";

        while (std::getline(std::cin, input))
        {

            // user decided to end the program.
            if (input.compare("q") == 0)
            {
                break;
            }

            // if user just clicked "Enter"
            else if (input[0] == 13)
            {

                std::cout << "?" << std::endl;
            }
            // checking if user wants to move some lines or go back
            else if (input[0] == '+' || input[0] == '-')
            {
                //std::cout << "here" << std::endl;

                document.move(input);
                std::cout << document.vec[document.numOfLine] << std::endl;
            }

            // checking if its a number.
            else if (document.isNumber(input))
            {
                int num = stoi(input);
                // checking if the wanted line exists.
                if (document.vec.size() >= num)
                {
                    if (num == 0)
                    {
                        std::cout << '?' << std::endl;
                    }
                    else
                    {
                        std::cout << num << std::endl;
                        document.numOfLine = num - 1;
                        std::cout << document.vec[num - 1] << std::endl;
                        // std::cout << "  " << std::endl;
                    }
                }
                else
                {
                    std::cout << '?' << std::endl;
                }
            }
            // checking if user wants to search a word
            else if (checkForSearch(input, 0, input.size() - 1, 0))
            {
                // get rid of the / and then send to search it.
                std::string newStr = input.substr(1, input.size() - 2);
                document.searchAWord(newStr);
            }

            else
            {

                switch (input[0])
                {

                case 'i':
                    //insert before
                    getInput(1);
                    break;

                case 'a':
                    //insert after
                    getInput(0);
                    break;

                case '$':
                    //move to the last line
                    document.numOfLine = document.vec.size() - 1;
                    break;

                case 'd':
                    document.vec.erase(document.vec.begin() + document.numOfLine);
                    break;

                case 'c':
                    getInput(2);
                    break;

                case 's':
                    if (input[1] != '/')
                    {
                        std::cout << "?" << std::endl;
                    }
                    else
                    {
                        if (checkForSearch(input, 1, input.size() - 1, 1))
                        {
                            // now we get a word in the form of s/old/new - extract old and new
                            extractOldAndNew(input);
                        }
                        else
                        {
                            std::cout << "?" << std::endl;
                        }
                    }
                    break;
                case 'j':
                    document.concatLines();
                    break;
                case 'w':
                    // checking the after w we have space.

                    if (input.length() >= 3 && input[1] == 32)
                    {
                        std::string file = input.substr(2);
                        document.writeData(file);
                    }
                    else
                    {
                        std::cout << "?" << std::endl;
                    }

                    break;

                default:
                    std::cout << "?2" << std::endl;
                    break;
                    // // printing data
                    // for (auto &e : document.vec)
                    //     std::cout << e << std::endl;
                }
            }
        }
    }

    void Editor::getInput(int flag)

    {

        std::vector<std::string> temp;
        std::string input = "";
        while (std::getline(std::cin, input))
        {

            if (input.compare(".") == 0)
            {
                document.insertData(temp, flag);
                break;
            }
            // to avoid empty line casued by function getLine
            if (!(input.compare("") == 0))
                temp.emplace_back(input);
        }
    }

    bool Editor::checkForSearch(std::string str, int indBegin, int intEnd, int flag)
    {
        // if we want to check for / only in the begining and at the end of the string
        if (!flag)
            return str[indBegin] == '/' && str[intEnd] == '/';
        // want in addition to find a / in the middle of old/new
        else
        {
            if (!(str[indBegin] == '/' && str[intEnd] == '/'))
            {

                return false;
            }
            else
            {
                for (int i = 2; i < str.size() - 2; i++)
                {
                    if (str[i] == '/')
                    {
                        return true;
                    }
                }
            }

            return false;
        }
    }

    void Editor::extractOldAndNew(std::string input)
    {
        std::string oldWord = "", newWord = "";
        bool findOld = true;
        for (int i = 2; i < input.size(); i++)
        {
            if (input[i] == '/' && i == input.size() - 1)
            {
                break;
            }
            else if (input[i] == '/')
            {
                findOld = false;
            }
            else if (findOld)
            {
                oldWord += input[i];
            }
            else
            {

                newWord += input[i];
            }
        }

        document.replaceOldInNew(oldWord, newWord);
    }

 
} // namespace edit
