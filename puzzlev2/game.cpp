#include "grid.hpp"

#include "game.hpp"

#include <ctime>

namespace puzzle
{
	game::game()
	{
		srand((unsigned int) time(0));

		window_.create(sf::VideoMode::getFullscreenModes().front(), "puzzle v2", sf::Style::Fullscreen);
		grid_ = boost::shared_ptr<grid>(new grid("res/tileset.bmp", 40, 20, 5));
	}

	void game::run()
	{
		while (window_.isOpen())
		{
			sf::Event e;
			while (window_.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					window_.close();
				}
				else if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Escape)
					{
						window_.close();
					}
				}
			}

			grid_->update();

			window_.clear(sf::Color(25, 25, 25));
			window_.draw(*grid_);
			window_.display();
		}
	}

}	// namespace puzzle
