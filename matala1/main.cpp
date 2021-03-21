#include "Editor.h"

int main(int argc, char *argv[])
{

    switch (argc)
    {

    case 1:
    {
        edit::Editor editor;
        editor.loop();
        break;
    }

    //opening existing file
    case 2:
    {
        edit::Editor editor(argv[1]);
        editor.loop();
        break;
    }
    }

    return 0;
}