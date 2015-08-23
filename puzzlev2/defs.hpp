#ifndef __PUZZLE_DEFS_HPP__
#define __PUZZLE_DEFS_HPP__

#include <SFML/Graphics.hpp>

namespace puzzle
{
	namespace defs
	{
		namespace grid
		{
			static const sf::Uint16 DEFAULT_WIDTH = 50;
			static const sf::Uint16 DEFAULT_HEIGHT = 50;
			static const sf::Uint16 DEFAULT_NODE_SIZE = 30;
			static const sf::Uint16 DEFAULT_SPAWN_INTERVAL = 20; // milliseconds
			static const double DEFAULT_SPAWN_RATE = 0.9;
		}	// namespace grid
	}	// namespace
}	// namespace puzzle

#endif	// __PUZZLE_DEFS_HPP__
