#include <SDL.h>
#include "RenderWindow.h"

int main(int argc, char* argv[])
{
    RenderWindow renderWindow = RenderWindow();
    renderWindow.Update();
    renderWindow.Render();

    return 0;
}
