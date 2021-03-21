
#include "string"
#include "vector"

namespace doc
{
    class Document
    {
    public:
        //constructor
        // Document();

        // pointer to number of line in the vector
        int numOfLine;

        // file name (if exist) - because the user can edit an existing file or edit a new.
        std::string fileName;

        std::vector<std::string> vec;

        // function to move the pointer backwards or forwards.
        void move(std::string context);

        void readFromFile(std::string context);

        void insertData(std::vector<std::string> temp, int flag);

        bool isNumber(std::string input);

        bool searchAWord(std::string wordToSearch);
        bool replaceOldInNew(std::string oldWord, std::string newWord);
        void concatLines();
        bool writeData(std::string fileName);
       
    };
} // namespace doc
