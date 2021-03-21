
#include "vector"
#include "string"
#include "Document.h"

namespace edit
{

    class Editor
    {
    public:
        doc::Document document;

        std::string fileName;

        //constructor
        Editor(std::string fileName);

        Editor();

        void loop();

        void getInput(int flag);

        bool checkForSearch(std:: string str,int indBegin,int intEnd,int flag);
        void extractOldAndNew(std::string input);
     
    };
} // namespace edit