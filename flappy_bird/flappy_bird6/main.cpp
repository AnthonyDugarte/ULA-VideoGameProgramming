#include <SFML/Window.hpp>

#include <Configuration.hpp>
#include <src/Game.hpp>

int main()
{
    Configuration::init();

    Game game{};

    sf::Texture texture{};

    sf::Clock clock;
    sf::Time dt;

    while (game.get_window().isOpen())
    {
        sf::Event event;

        while (game.get_window().pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                game.get_window().close();
            }
            else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
            {
                game.handle_inputs(event);
            }
        }

        game.update(dt.asSeconds());
        game.render();

        dt = clock.restart();
    }

    return EXIT_SUCCESS;
}
