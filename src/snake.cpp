#include <chrono>
#include <list>
#include <random>
#include <thread>

#include "screen_buffer.h"
#include "snake.h"

using namespace std::chrono_literals;

std::random_device rd;
std::mt19937 gen(rd());

void Run(HANDLE& console, std::unique_ptr<char[]>& screen_buffer, unsigned long& bytes_written)
{
    bool game_over{false};

    while(true)
    {
        /* Initial state */
        Position food{8,14};
        std::list<Position> snake{{10,10},{10,11},{10,12},{10,13},{10,14}};
        SnakeDirection direction = SnakeDirection::RIGHT;
        int score{0};
        bool key_left{false}, key_right{false}, key_up{false}, key_down{false};
        bool food_eaten{false};

        while(!game_over)
        {
            /* Display world */
            std::string display_score = "Score: " + std::to_string(score);
            ClearScreen(screen_buffer);
            DrawBoarder(screen_buffer);
            DisplayMessage(2, 1, screen_buffer, display_score);
            std::chrono::milliseconds frame_rate = 200ms;
 
            // Display snake
            for (auto const& segment : snake)
            {
                screen_buffer[segment.x + segment.y * screen_width ] = '*';
            }

            // Display food
            if (food_eaten)
            {
                update_food_pos(screen_buffer, food);
                food_eaten = false;
            }
            screen_buffer[food.x + food.y * screen_width] = 'o';

            /* Get user input */

            // Hold enter to speed up
            if(GetKeyState(VK_RETURN) & 0x8000)
            {
                frame_rate = 30ms;
            }
            
            // Delay update time (i.e. snake speed)
            auto frame_start = std::chrono::steady_clock::now();
            while ((std::chrono::steady_clock::now() - frame_start) < frame_rate)
            {
                if((GetKeyState(VK_LEFT) & 0x8000) && (direction != SnakeDirection::RIGHT))
                {
                    direction = SnakeDirection::LEFT;
                }
                if((GetKeyState(VK_RIGHT) & 0x8000) && (direction != SnakeDirection::LEFT))
                {
                    direction = SnakeDirection::RIGHT;
                }
                if((GetKeyState(VK_UP) & 0x8000) && (direction != SnakeDirection::DOWN))
                {
                    direction = SnakeDirection::UP;
                }
                if((GetKeyState(VK_DOWN) & 0x8000) && (direction != SnakeDirection::UP))
                {
                    direction = SnakeDirection::DOWN;
                }
            }

            /* Move snake */
            auto head = snake.front();
            if(direction == SnakeDirection::LEFT)
            {
                head.x--;
            }
            else if(direction == SnakeDirection::RIGHT)
            {
                head.x++;
            }
            else if(direction == SnakeDirection::UP)
            {
                head.y--;
            }
            else if(direction == SnakeDirection::DOWN)
            {
                head.y++;
            }
            snake.push_front(head);
            snake.pop_back();

            /* Collision detection */
            // Food detection
            if ((snake.front().x == food.x) && (snake.front().y == food.y))
            {
                snake.push_back(snake.back());
                food_eaten = true;
                score += 5;
                continue;
            }

            // Snake body detection
            if(screen_buffer[snake.front().x + snake.front().y * screen_width] != ' ')
            {
                screen_buffer[snake.front().x + snake.front().y * screen_width] = 'X';
                game_over = true;

                std::string game_over_msg{"Hit spacebar to start again"};
                DisplayMessage((screen_width/2)-(game_over_msg.size()/2), screen_height/2, screen_buffer, game_over_msg);
            }

            /* Display frame */
            WriteConsoleOutputCharacter(console, screen_buffer.get(), screen_width * screen_height, {0,0}, &bytes_written);
        }

        // Play again
        if (GetKeyState(VK_SPACE) & 0x8000)
        {
            game_over = false;
        }
    }
}

void update_food_pos(std::unique_ptr<char[]>& screen_buffer, Position& food)
{
    std::uniform_int_distribution<int> x_distrib(0, screen_width-1);
    std::uniform_int_distribution<int> y_distrib(3, screen_height-1); // 3 is title bar position

    food.x = x_distrib(gen);
    food.y = y_distrib(gen);

    // Make sure its in an empty position
    if(screen_buffer[food.x + food.y * screen_width] != ' ')
    {
        update_food_pos(screen_buffer, food);
    }
}