#ifndef __PUZZLE_HPP__
#define __PUZZLE_HPP__

#include <boost/shared_ptr.hpp>

namespace puzzle
{
    class gfx;

    class game
    {
    public:
        game();
        game(int argc, char ** argv);
        ~game();

        void run();

    private:
        boost::shared_ptr<gfx> gfx_;
    };   // class game
}   //  namespace puzzle

#endif // __PUZZLE_HPP__
