#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>

int width = 30;
int height = 30;
int appleX, appleY;
int len_snake = 3;

struct Snake
{
    int x, y;
} snake[100];

enum sDirection
// directions of the snake
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

sDirection snake_dir;

void Apple_spawn()
// spawn the apple on a random location of the grid
{
    appleX = std::rand() % width;
    appleY = std::rand() % height;
}

void Setup()
// initialize the state of the game
{
    snake_dir = RIGHT;

    snake[0].x = width / 2;
    snake[0].y = height / 2;

    Apple_spawn();
}

void Snake_step()
// manage the snake body from t to t+1 time
{   
    // body part i takes the spot of body part i + 1
    for (int i = len_snake; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    // head movement
    if (snake_dir == RIGHT)
    {
        snake[0].x += 1;
    }
    else if (snake_dir == UP)
    {
        snake[0].y -= 1;
    } else if (snake_dir == LEFT)
    {
        snake[0].x -= 1;
    } else if (snake_dir == DOWN)
    {
        snake[0].y += 1;
    }

    // loop the grid left/right and top/bottom
    if (snake[0].x < 0)
    {
        snake[0].x = 30;
    } else if (snake[0].x > 30)
    {
        snake[0].x = 0;
    }

    if (snake[0].y < 0)
    {
        snake[0].y = 30;
    } else if (snake[0].y > 30)
    {
        snake[0].y = 0;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width * width, height * height), "Snake");

    sf::RectangleShape block;
    block.setSize(sf::Vector2f(width, height));
    block.setFillColor(sf::Color::Black);
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Yellow);

    sf::RectangleShape snake_block;
    snake_block.setSize(sf::Vector2f(width, height));
    snake_block.setFillColor(sf::Color::Green);

    sf::RectangleShape apple_block;
    apple_block.setSize(sf::Vector2f(width, height));
    apple_block.setFillColor(sf::Color::Red);

    Setup();

    sf::Clock clock;
    float chrono = 0;
    float dt = 0.1;

    while (window.isOpen())
    {
        float time  = clock.getElapsedTime().asSeconds();
        clock.restart();
        chrono += time;

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyReleased)
            {
                if (e.key.code == sf::Keyboard::Left)
                {
                    snake_dir = LEFT;
                } else if (e.key.code == sf::Keyboard::Down)
                {
                    snake_dir = DOWN;
                } else if (e.key.code == sf::Keyboard::Up)
                {
                    snake_dir = UP;
                } else if (e.key.code == sf::Keyboard::Right)
                {
                    snake_dir = RIGHT;
                }            
            }
        }   
        if (chrono > dt)
        {
            chrono = 0;
            Snake_step();
        }
        if ((snake[0].x == appleX) && (snake[0].y == appleY))
        {
            len_snake ++;
            Apple_spawn();
        }
        window.clear();
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                block.setPosition(i * width, j * width);
                window.draw(block);
            }
        }
        for (int i = 0; i < len_snake; i++)
        {
            snake_block.setPosition(snake[i].x * width, snake[i].y * height);
            window.draw(snake_block);   
        }
        apple_block.setPosition(appleX * width, appleY * height);
        window.draw(apple_block);

        window.display();
    }
    return 0;
}