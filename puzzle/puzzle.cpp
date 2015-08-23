#include "puzzle.hpp"

#include "gfx.hpp"

namespace puzzle
{
    game::game()
    {
    }

    game::game(int argc, char ** argv)
        : gfx_(new gfx(argc, argv))
    {
    }

    game::~game()
    {
    }

    void game::run()
    {
        gfx_->run();
    }
}   // namespace puzzle
