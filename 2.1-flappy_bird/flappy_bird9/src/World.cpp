/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class World.
*/

#include <Settings.hpp>
#include <src/World.hpp>

World::World(bool _generate_pipes) noexcept
    : generate_pipes{_generate_pipes}, background{Settings::textures["background"]}, ground{Settings::textures["ground"]},
      pipes{}, rng{std::default_random_engine{}()}
{
    ground.setPosition(0, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);
    std::uniform_int_distribution<int> dist(0, 80);
    last_pipe_y = -Settings::PIPE_HEIGHT + dist(rng) + 20;
}

void World::reset() noexcept
{
    pipes.clear();
    background.setTexture(Settings::textures["background"]);
    background.setTexture(Settings::textures["ground"]);
    background_x = 0.f;
    ground_x = 0.f;
    pipes_spawn_timer = 0.f;
    float last_pipe_y = 0.f;
}

bool World::collides(const sf::FloatRect& rect) const noexcept
{
    if (rect.top + rect.height >= Settings::VIRTUAL_HEIGHT)
    {
        return true;
    }
    
    for (const auto& pipe_pair: pipes)
    {
        if (pipe_pair.collides(rect))
        {
            return true;
        }
    }

    return false;
}

bool World::update_scored(const sf::FloatRect& rect) noexcept
{
    for (auto& pipe_pair: pipes)
    {
        if (pipe_pair.update_scored(rect))
        {
            return true;
        }
    }

    return false;
}

void World::update(float dt) noexcept
{
    if (generate_pipes)
    {
        pipes_spawn_timer += dt;

        if (pipes_spawn_timer >= Settings::TIME_TO_SPAWN_PIPES)
        {
            pipes_spawn_timer = 0.f;

            std::uniform_int_distribution<int> dist{-20, 20};
            float y = std::max(-Settings::PIPE_HEIGHT + 10, std::min(last_pipe_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::PIPE_HEIGHT));

            last_pipe_y = y;

            pipes.push_back(PipePair{y});
        }
    }

    background_x += -Settings::BACK_SCROLL_SPEED * dt;

    if (background_x <= -Settings::BACKGROUND_LOOPING_POINT)
    {
        background_x = 0;
    }

    background.setPosition(background_x, 0);

    ground_x += -Settings::MAIN_SCROLL_SPEED * dt;

    if (ground_x <= -Settings::VIRTUAL_WIDTH)
    {
        ground_x = 0;
    }

    ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

    for (auto it = pipes.begin(); it != pipes.end(); )
    {
        if (it->is_out_of_game())
        {
            it = pipes.erase(it);
        }
        else
        {
            it->update(dt);
            ++it;
        }
    }
}

void World::render(sf::RenderTarget& target) const noexcept
{
    target.draw(background);

    for (const auto& pipe_pair: pipes)
    {
        pipe_pair.render(target);
    }

    target.draw(ground);
}