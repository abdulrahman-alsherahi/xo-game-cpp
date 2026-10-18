// XO Game (Tic Tac Toe) - GUI version with SFML

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "game.h"

// Window and board layout (in pixels)
const unsigned int WINDOW_WIDTH = 480;
const unsigned int WINDOW_HEIGHT = 620;

const float CELL_SIZE = 130.f;
const float CELL_GAP = 10.f;
const float BOARD_SIZE = 3 * CELL_SIZE + 2 * CELL_GAP;
const float BOARD_X = (WINDOW_WIDTH - BOARD_SIZE) / 2;
const float BOARD_Y = 110.f;

const sf::Vector2f BUTTON_SIZE(180.f, 46.f);
const sf::Vector2f BUTTON_POS((WINDOW_WIDTH - BUTTON_SIZE.x) / 2, 548.f);

// Colors
const sf::Color BACKGROUND(236, 239, 244);
const sf::Color CELL_COLOR(255, 255, 255);
const sf::Color WIN_CELL_COLOR(255, 236, 179);
const sf::Color TEXT_COLOR(45, 52, 64);
const sf::Color X_COLOR(52, 101, 164);
const sf::Color O_COLOR(222, 98, 68);
const sf::Color BUTTON_COLOR(45, 52, 64);
const sf::Color BUTTON_HOVER_COLOR(76, 86, 106);

// Tries a few common font locations (macOS, Linux, Windows)
bool loadFont(sf::Font& font) {
    const std::string paths[] = {
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/Library/Fonts/Arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };
    for (const std::string& path : paths) {
        if (font.openFromFile(path)) {
            return true;
        }
    }
    return false;
}

sf::Vector2f cellPosition(int cell) {
    int row = cell / 3;
    int col = cell % 3;
    return {BOARD_X + col * (CELL_SIZE + CELL_GAP), BOARD_Y + row * (CELL_SIZE + CELL_GAP)};
}

// Returns the cell (0-8) under the mouse, or -1 if the mouse is not on a cell
int cellAt(sf::Vector2f mouse) {
    for (int i = 0; i < 9; i++) {
        sf::FloatRect cellRect(cellPosition(i), {CELL_SIZE, CELL_SIZE});
        if (cellRect.contains(mouse)) {
            return i;
        }
    }
    return -1;
}

bool isOnButton(sf::Vector2f mouse) {
    return sf::FloatRect(BUTTON_POS, BUTTON_SIZE).contains(mouse);
}

// Draws text centered at the given point
void drawCenteredText(sf::RenderWindow& window, const sf::Font& font, const std::string& str,
                      unsigned int size, sf::Color color, sf::Vector2f center, bool bold) {
    sf::Text text(font, str, size);
    text.setFillColor(color);
    if (bold) {
        text.setStyle(sf::Text::Bold);
    }
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.position + bounds.size / 2.f);
    text.setPosition(center);
    window.draw(text);
}

// X = two rotated rectangles
void drawX(sf::RenderWindow& window, sf::Vector2f center) {
    for (float angle : {45.f, -45.f}) {
        sf::RectangleShape bar({100.f, 14.f});
        bar.setOrigin(bar.getSize() / 2.f);
        bar.setPosition(center);
        bar.setRotation(sf::degrees(angle));
        bar.setFillColor(X_COLOR);
        window.draw(bar);
    }
}

// O = circle with a thick outline and no fill
void drawO(sf::RenderWindow& window, sf::Vector2f center) {
    const float radius = 38.f;
    sf::CircleShape circle(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition(center);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(12.f);
    circle.setOutlineColor(O_COLOR);
    window.draw(circle);
}

bool isWinCell(const Game& game, int cell) {
    for (int i = 0; i < 3; i++) {
        if (game.winLine[i] == cell) {
            return true;
        }
    }
    return false;
}

void drawBoard(sf::RenderWindow& window, const Game& game) {
    for (int i = 0; i < 9; i++) {
        sf::RectangleShape cell({CELL_SIZE, CELL_SIZE});
        cell.setPosition(cellPosition(i));
        cell.setFillColor(isWinCell(game, i) ? WIN_CELL_COLOR : CELL_COLOR);
        window.draw(cell);

        sf::Vector2f center = cellPosition(i) + sf::Vector2f(CELL_SIZE / 2, CELL_SIZE / 2);
        if (game.board[i] == 'X') {
            drawX(window, center);
        }
        else if (game.board[i] == 'O') {
            drawO(window, center);
        }
    }
}

void drawStatus(sf::RenderWindow& window, const sf::Font& font, const Game& game) {
    std::string message;
    sf::Color color = TEXT_COLOR;

    if (game.gameOver && game.winner != ' ') {
        message = std::string("Player ") + game.winner + " wins!";
        color = (game.winner == 'X') ? X_COLOR : O_COLOR;
    }
    else if (game.gameOver) {
        message = "Draw!";
    }
    else {
        message = std::string("Player ") + game.currentPlayer + "'s turn";
        color = (game.currentPlayer == 'X') ? X_COLOR : O_COLOR;
    }

    drawCenteredText(window, font, "Tic-Tac-Toe", 30, TEXT_COLOR, {WINDOW_WIDTH / 2.f, 38.f}, true);
    drawCenteredText(window, font, message, 24, color, {WINDOW_WIDTH / 2.f, 80.f}, true);
}

void drawButton(sf::RenderWindow& window, const sf::Font& font, bool hover) {
    sf::RectangleShape button(BUTTON_SIZE);
    button.setPosition(BUTTON_POS);
    button.setFillColor(hover ? BUTTON_HOVER_COLOR : BUTTON_COLOR);
    window.draw(button);

    drawCenteredText(window, font, "New Game", 20, sf::Color::White,
                     BUTTON_POS + BUTTON_SIZE / 2.f, false);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tic-Tac-Toe",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!loadFont(font)) {
        std::cout << "Error: could not load a font.\n";
        return 1;
    }

    Game game;
    resetGame(game);

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (click->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mouse = window.mapPixelToCoords(click->position);

                    if (isOnButton(mouse)) {
                        resetGame(game);
                    }
                    else {
                        int cell = cellAt(mouse);
                        if (cell != -1) {
                            makeMove(game, cell);  // ignored if cell is taken or game is over
                        }
                    }
                }
            }
        }

        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        window.clear(BACKGROUND);
        drawStatus(window, font, game);
        drawBoard(window, game);
        drawButton(window, font, isOnButton(mouse));
        window.display();
    }

    return 0;
}
