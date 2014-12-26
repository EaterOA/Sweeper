#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameconfig.hpp"
#include "sweeper.hpp"

sf::RenderWindow window;
sf::Clock gameClock;
Sweeper game;

bool appInit()
{
    srand(unsigned(time(0)));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(800, 600), "Sweeper", sf::Style::Close, settings);
    window.setFramerateLimit(30);

    if (!config.init()) return false;
    if (!game.init()) return false;

    return true;
}


std::vector<sf::Event> processEvents()
{
    std::vector<sf::Event> inputEvents;
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }
        else inputEvents.push_back(event);
    }
    return inputEvents;
}

void appStart()
{
    // game loop
    while (window.isOpen()) {

        // collecting information
        sf::Time elapsed = gameClock.restart();
        std::vector<sf::Event> events = processEvents();
        sf::Vector2f cursor(sf::Mouse::getPosition(window));

        // do awesome stuff
        game.tick(events, elapsed, cursor);

        // display window
        game.draw(window);
        window.display();
    }
}

int main()
{
    if (!appInit()) {
        std::cerr << "Cannot initialize application. Aborting.\n";
        if (window.isOpen()) window.close();
    }
    else {
        appStart();
    }
}
