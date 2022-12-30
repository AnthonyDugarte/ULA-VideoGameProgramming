/*
    ISPPJ1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PipePair.
*/

#include <Settings.hpp>
#include <src/PipePair.hpp>

PipePair::PipePair(float _y) noexcept
    : x{Settings::VIRTUAL_WIDTH}, y{_y},
      top{x, y + Settings::PIPE_HEIGHT, true},
      bottom{x, y + Settings::PIPES_GAP + Settings::PIPE_HEIGHT, false}
{

}

void PipePair::update(float dt) noexcept
{
    x += -Settings::MAIN_SCROLL_SPEED * dt;

    top.update(x);
    bottom.update(x);
}

void PipePair::render(sf::RenderTarget& target) const noexcept
{
    top.render(target);
    bottom.render(target);
}

bool PipePair::is_out_of_game() const noexcept
{
    return x < -Settings::PIPE_WIDTH;
}
