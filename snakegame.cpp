#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
const int CELL_SIZE = 20;

struct Point {
    int x, y;
};

vector<Point> snake = {{WIDTH / 2, HEIGHT / 2}};
Point food;
char direction = 'R';
bool gameOver = false;

void spawnFood() {
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

void handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W && direction != 'D') direction = 'U';
        else if (event.key.code == sf::Keyboard::S && direction != 'U') direction = 'D';
        else if (event.key.code == sf::Keyboard::A && direction != 'R') direction = 'L';
        else if (event.key.code == sf::Keyboard::D && direction != 'L') direction = 'R';
    }
}

void updateLogic() {
    Point head = snake[0];
    Point newHead = head;

    if (direction == 'U') newHead.y--;
    else if (direction == 'D') newHead.y++;
    else if (direction == 'L') newHead.x--;
    else if (direction == 'R') newHead.x++;

    // Wall collision
    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
        gameOver = true;
        return;
    }

    // Self collision
    for (auto s : snake) {
        if (s.x == newHead.x && s.y == newHead.y) {
            gameOver = true;
            return;
        }
    }

    snake.insert(snake.begin(), newHead);

    if (newHead.x == food.x && newHead.y == food.y) {
        spawnFood(); // Grow
    } else {
        snake.pop_back(); // Move forward
    }
}

void draw(sf::RenderWindow &window) {
    window.clear();

    // Draw snake
    for (auto s : snake) {
        sf::RectangleShape segment(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
        segment.setPosition(s.x * CELL_SIZE, s.y * CELL_SIZE);
        segment.setFillColor(sf::Color::Green);
        window.draw(segment);
    }

    // Draw food
    sf::RectangleShape foodShape(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    foodShape.setPosition(food.x * CELL_SIZE, food.y * CELL_SIZE);
    foodShape.setFillColor(sf::Color::Red);
    window.draw(foodShape);

    window.display();
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    spawnFood();

    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), "Snake Game");

    sf::Clock clock;
    float delay = 0.15f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            handleInput(event);
        }

        if (clock.getElapsedTime().asSeconds() > delay && !gameOver) {
            updateLogic();
            draw(window);
            clock.restart();
        }

        if (gameOver) {
            window.clear();
            sf::Font font;
            if (!font.loadFromFile("arial.ttf")) return -1;

            sf::Text text("Game Over! Score: " + to_string(snake.size() - 1), font, 24);
            text.setFillColor(sf::Color::White);
            text.setPosition(50, HEIGHT * CELL_SIZE / 2 - 20);
            window.draw(text);
            window.display();
        }
    }

    return 0;
}