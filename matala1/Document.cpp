#include "Document.h"
#include "vector"
#include <sstream>  // for a string action
#include <iostream> // input/output
#include <algorithm>
#include <fstream> // for files

namespace doc
{

    void Document::insertData(std::vector<std::string> temp, int flag)
    {

        if (flag == 1) // insert before
        {

            vec.insert(vec.begin() + this->numOfLine, temp.begin(), temp.end());
        }
        else if (!flag)
        { // insert after
            vec.insert(vec.begin() + this->numOfLine + 1, temp.begin(), temp.end());
        }
        // replace the current line with the following text
        else
        {
            // first overring the first line
            // std::cout << numOfLine << std::endl;
            // std::cout << temp[0] << std::endl;
            vec[numOfLine] = temp[0];
            numOfLine++;
            // insert the rest of the content.
            vec.insert(vec.begin() + numOfLine, temp.begin() + 1, temp.end());

            //vec.insert(vec.begin()+this->numOfLine,temp.begin(),temp.begin())
        }

        // taking the pointer to the end of the vector

        this->numOfLine = vec.size() - 1;
    }

    void Document::readFromFile(std::string context)
    {

        std::string line;
        std::ifstream myfile(context);
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                // to avoid empty line casued by function getLine
                if (!(line.compare("") == 0))
                    vec.emplace_back(line);
            }
            myfile.close();
        }

        else
            std::cout << "Unable to open file";

        this->numOfLine = vec.size() - 1;
    }

    void Document::move(std::string context)
    {
        // want only the number without + or -
        std::string str = context.substr(1, context.length() - 1);

        // converting string to int
        // object from the class stringstream
        std::stringstream convert(str);

        // The object has the value 12345 and stream
        // it to the integer x
        int num = 0;
        convert >> num;

        // move forwards
        if (context[0] == '+')
        {

            if (numOfLine + num > vec.size())
            {
                std::cout << "?" << std::endl;
            }
            else
            {
                this->numOfLine += num;
            }
        }

        //move backwards
        else
        {
            if (numOfLine - num < 0)
            {
                std::cout << "?" << std::endl;
            }
            else
            {
                this->numOfLine -= num;
            }
        }
    }

    bool Document::isNumber(std::string input)

    {

        for (char i : input)
        {
            if (!(i >= '0' && i <= '9'))
            {
                return false;
            }
        }

        return true;
    }

    bool Document::searchAWord(std::string wordToSearch)
    {

        // first searching from current position to the end

        for (auto line = vec.begin() + numOfLine; line != vec.end(); ++line)
        {
            std::string str = *line;
            int it;
            it = str.find(wordToSearch);
            if (it != std::string::npos)
            {
                std::cout << *line << std::endl;
                return true;
            }
        }
        // if not we try to find from begining tto the current positin

        for (auto line = vec.begin(); line != vec.begin() + numOfLine; ++line)
        {
            std::string str = *line;
            int it;
            it = str.find(wordToSearch);
            if (it != std::string::npos)
            {
                std::cout << *line << std::endl;
                return true;
            }
        }

        std::cout << "?" << std::endl;
        return false;
    }

    bool Document::replaceOldInNew(std::string oldWord, std::string newWord)
    {

        //checking if the word exists first
        std::string str = vec[numOfLine];
        int it;
        it = str.find(oldWord);
        if (it != std::string::npos)
        {
            // found word
            vec[numOfLine].replace(it, oldWord.length(), newWord);
            return true;
        }

        return false;
    }

    void Document::concatLines()
    {
        if (numOfLine + 1 < vec.size())
        {
            vec[numOfLine] += " ";
            vec[numOfLine] += vec[numOfLine + 1];
            vec.erase(vec.begin() + numOfLine + 1);
        }
    }

    bool Document::writeData(std::string fileName)
    {
         std::cout << "here";
        std::ofstream myfile(fileName);
        if (myfile.is_open())
        {

            for (std::string line : vec)
                myfile << line + "\n";
            myfile.close();
            return true;
        }
        else
            std::cout << "Unable to open file";
        return false;
    }

} // namespace doc