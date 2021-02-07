#if !defined(SCREEN_BUFFER_H)
#define SCREEN_BUFFER_H

#include <memory>
#include <string>

#include <Windows.h>

constexpr int screen_width{120};
constexpr int screen_height{30};

inline void ClearScreen(std::unique_ptr<char[]>& screen_buffer)
{
    // set every element of the screen buffer to a space character
    for(int i = 0; i < screen_width * screen_height; ++i)
    {
        screen_buffer[i] = ' ';
    }
}

inline void DisplayMessage(int x, int y, std::unique_ptr<char[]>& screen_buffer, std::string word)
{
    for (auto ch : word)
    {
        screen_buffer[x++ + y * screen_width ] = ch;
    }
}

inline void DrawBoarder(std::unique_ptr<char[]>& screen_buffer)
{
    for(int i = 0; i < screen_width; ++i)
    {
        screen_buffer[i] = '-';
        screen_buffer[2 * screen_width + i] = '-';
        screen_buffer[(screen_height - 1) * screen_width + i] = '-';
    }

    for(int i = 0; i < screen_height; ++i)
    {
        screen_buffer[screen_width * i] = '|';\
        screen_buffer[(screen_width * i) + (screen_width - 1)] = '|';
    }
}

#endif // SCREEN_BUFFER_H