#pragma once

#include <SFML/Graphics.hpp>

#include <src/Bird.hpp>
#include <src/World.hpp>

class Game
{
public:
    Game();

    Game(const Game&) = delete;

    Game& operator = (Game) = delete;

    sf::RenderWindow& get_window() noexcept;

    void handle_inputs(const sf::Event& event) noexcept;

    void update(float dt) noexcept;

    void render() noexcept;

private:
    sf::RenderWindow render_window;
    sf::RenderTexture render_texture;
    sf::Sprite render_sprite;
    
    Bird bird;
    World world;

    bool bird_is_dead{false};
    int score{0};
};
