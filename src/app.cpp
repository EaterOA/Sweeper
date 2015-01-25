#include <iostream>
#include "app.hpp"
#include "sweeper.hpp"
#include "gameConfig.hpp"
#include "gameResourceManager.hpp"

sf::RenderWindow window;
sf::Clock gameClock;
Sweeper game;

bool appInit()
{
    srand(time(0));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(800, 600), "Sweeper", sf::Style::Close | sf::Style::Resize, settings);
    window.setFramerateLimit(30);

    if (!config.init()) return false;
    if (!resource.init()) return false;
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
        else if (event.type == sf::Event::Resized) {
            sf::View view(sf::FloatRect(0, 0, event.size.width, event.size.height));
            window.setView(view);
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

        // do awesome stuff
        game.tick(events, elapsed);

        // display window
        game.draw();
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
