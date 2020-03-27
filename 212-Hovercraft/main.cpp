#include "GameEngine.h"

int main()
{
    std::cout << "Use WASD to move the player" << std::endl;
    std::cout << "Use arrow keys to move the camera and the v and c key to go up and down" << std::endl;
    std::cout << "Press m to change between static camera and moving camera" << std::endl;

    GameEngine gameEngine("HoverCraft", 1920, 1080, 4, 6, false);

    //Main loop
    while(!gameEngine.GetWindowShouldClose())
    {
        //Update input--
        gameEngine.update();
        gameEngine.render();
    }
    return 0;
}