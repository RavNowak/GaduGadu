#include <Windows.h>
#include "GaduGadu.h"

int main()
{
    system("chcp 1250 > nul");
    HWND hwnd = GetConsoleWindow();
    GaduGadu communicator(hwnd);
    communicator.run();

    return 0;
}






