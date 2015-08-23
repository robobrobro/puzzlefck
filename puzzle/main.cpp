
#include "puzzle.hpp"

#include <windows.h>

int __stdcall WinMain(
                      HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine,
                      int nCmdShow
                      )
{
    int argc = 1;
    char * argv[] = {"puzzle"};
    puzzle::game game(argc, argv);
    game.run();
}
