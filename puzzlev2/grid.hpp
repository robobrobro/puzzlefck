#ifndef __PUZZLE_GRID_HPP__
#define __PUZZLE_GRID_HPP__

#include <boost/date_time/posix_time/posix_time.hpp>
#include <SFML/Graphics.hpp>

#include "defs.hpp"

namespace puzzle
{
	class grid : public sf::Drawable
	{
		public:
			grid(const std::string & tileset);
			grid(const std::string & tileset, sf::Uint16 width, sf::Uint16 height);
			grid(const std::string & tileset, sf::Uint16 width, sf::Uint16 height, sf::Uint16 node_size);

			void update();

		private:
			virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
			void init(const std::string & tileset,
				sf::Uint16 width = defs::grid::DEFAULT_WIDTH, 
				sf::Uint16 height = defs::grid::DEFAULT_HEIGHT, 
				sf::Uint16 node_size = defs::grid::DEFAULT_NODE_SIZE);

			sf::VertexArray vertices_;
			sf::Texture tileset_;
			sf::Vector2f position_;
			sf::Vector2f size_;

			sf::Uint16 num_nodes_;
			sf::Uint16 visible_nodes_;
			boost::posix_time::ptime last_spawn_time_;
			sf::Uint16 spawn_interval_;
			double spawn_rate_;
	};	// class grid
}	// namespace puzzle

#endif	// __PUZZLE_GRID_HPP__
