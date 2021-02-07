#include "screen_buffer.h"
#include "snake.h"

int main()
{
    // Create screen buffer
    std::unique_ptr<char[]> screen_buffer(new char[screen_width * screen_height]);

    // Setup
    ClearScreen(screen_buffer);
    HANDLE console{CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)};
    SetConsoleActiveScreenBuffer(console);
    unsigned long bytes_written{0};

    // Run game
    Run(console, screen_buffer, bytes_written);

    return 0;
}