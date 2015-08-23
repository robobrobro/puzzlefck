#ifndef __PUZZLE_GAME_HPP__
#define __PUZZLE_GAME_HPP__

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>

namespace puzzle
{
	class grid;	

	class game
	{
		public:
			game();

			void run();

		private:
			sf::RenderWindow window_;
			boost::shared_ptr<grid> grid_;
	};	// class game
}	// namespace puzzle

#endif	// __PUZZLE_GAME_HPP__
