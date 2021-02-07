# Snake #
Classic snake game running inside Windows console

## Required ##
- Cmake
- MinGW (with posix thread)
- Windows OS - *<Windows.h>* header used

## Build ##
    mkdir build
    cd build
    cmake -G "MinGW Makefiles" ..
    make

## Run ##
Run *snake.exe* in build folder

## Controls ##
* Arrow key left - move snake left
* Arrow key down - move snake down
* Arrow key right - move snake right
* Arrow key up - move snake up
* Return/Enter key (hold) - increase speed of snake
* Spacebar - Start new game (when game ends)

![In Play](/images/in_play.png)

![Game Over](/images/game_over.png)
