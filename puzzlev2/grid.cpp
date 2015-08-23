
#include "grid.hpp"

namespace puzzle
{
	grid::grid(const std::string & tileset)
	{
		init(tileset);
	}

	grid::grid(const std::string & tileset, sf::Uint16 width, sf::Uint16 height)
	{
		init(tileset, width, height);
	}

	grid::grid(const std::string & tileset, sf::Uint16 width, sf::Uint16 height, sf::Uint16 node_size)
	{
		init(tileset, width, height);
	}

	void grid::init(const std::string & tileset, 
		sf::Uint16 width, 
		sf::Uint16 height, 
		sf::Uint16 node_size)
	{
		tileset_.loadFromFile(tileset);
		size_.x = width;
		size_.y = height;
		position_.x = sf::VideoMode::getDesktopMode().width / 2.f - width * node_size / 2.f;
		position_.y = sf::VideoMode::getDesktopMode().height / 2.f - height * node_size / 2.f;
		num_nodes_ = width * height;
		visible_nodes_ = 0;
		spawn_interval_ = defs::grid::DEFAULT_SPAWN_INTERVAL;
		spawn_rate_ = defs::grid::DEFAULT_SPAWN_RATE;

		vertices_.setPrimitiveType(sf::Quads);
		vertices_.resize(width * height * 4);

		for (sf::Uint16 w = 0; w < width; ++w)
		{
			for (sf::Uint16 h = 0; h < height; ++h)
			{
				sf::Vertex * quad = &vertices_[(w + h * width) * 4];
				quad[0].position = position_ + sf::Vector2f(w * node_size, h * node_size);
				quad[1].position = position_ + sf::Vector2f((w + 1) * node_size, h * node_size);
				quad[2].position = position_ + sf::Vector2f((w + 1) * node_size, (h + 1) * node_size);
				quad[3].position = position_ + sf::Vector2f(w * node_size, (h + 1) * node_size);

				quad[0].color = sf::Color(0, 0, 0, 128);
				quad[1].color = sf::Color(0, 0, 0, 128);
				quad[2].color = sf::Color(0, 0, 0, 128);
				quad[3].color = sf::Color(0, 0, 0, 128);

                quad[0].texCoords = sf::Vector2f(0.f, 0.f);
				quad[1].texCoords = sf::Vector2f(node_size, 0.f);
                quad[2].texCoords = sf::Vector2f(node_size, node_size);
                quad[3].texCoords = sf::Vector2f(0.f, node_size);
			}
		}
	}

	void grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.texture = &tileset_;

		target.draw(vertices_, states);
	}

	void grid::update()
	{
		sf::Color delete_color = sf::Color::Black;
		sf::Vector2i mouse_pos = sf::Mouse::getPosition();
		for (sf::Uint16 w = 0; w < size_.x; ++w)
		{
			for (sf::Uint16 h = 0; h < size_.y; ++h)
			{
				sf::Vertex * quad = &vertices_[(w + h * size_.x) * 4];
				if (mouse_pos.x >= quad->position.x && 
					mouse_pos.x < quad[1].position.x &&
					mouse_pos.y >= quad->position.y &&
					mouse_pos.y < quad[2].position.y)
				{
					quad[0].color.a = 64;
					quad[1].color.a = 64;
					quad[2].color.a = 64;
					quad[3].color.a = 64;

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						delete_color = quad[0].color;
					}
				}
				else
				{
					quad[0].color.a = 255;
					quad[1].color.a = 255;
					quad[2].color.a = 255;
					quad[3].color.a = 255;
				}
			}
		}

		// delete nodes with same color as clicked node
		for (sf::Uint16 w = 0; w < size_.x; ++w)
		{
			for (sf::Uint16 h = 0; h < size_.y; ++h)
			{
				sf::Vertex * quad = &vertices_[(w + h * size_.x) * 4];
				if (quad->color.r != 0 && quad->color.g != 0 && quad->color.b != 0 &&
					quad->color.r == delete_color.r &&
					quad->color.g == delete_color.g &&
					quad->color.b == delete_color.b)
				{
					for (sf::Uint16 idx = 0; idx < 4; ++idx)
					{
						quad[idx].color = sf::Color::Black;
					}

					--visible_nodes_;
				}
			}
		}

		double p = rand() / (double) RAND_MAX;
		boost::posix_time::time_duration time_since_last_spawn = 
			boost::posix_time::microsec_clock::local_time() - last_spawn_time_;
		if (visible_nodes_ < num_nodes_ && p <= spawn_rate_ && 
			time_since_last_spawn.total_milliseconds() >= spawn_interval_)
		{
			bool found = false;
			boost::posix_time::ptime search_start_time = 
				boost::posix_time::microsec_clock::local_time();
			boost::posix_time::time_duration delta = 
				boost::posix_time::microsec_clock::local_time() - search_start_time;
			while (!found && delta.total_milliseconds() < 33)
			{
				// find an empty node
				sf::Uint16 w = rand() % (sf::Uint16) size_.x;
				sf::Uint16 h = rand() % (sf::Uint16) size_.y;
				sf::Vertex * quad = &vertices_[(w + h * size_.x) * 4];
				if (quad->color.r == 0 && 
					quad->color.g == 0 &&
					quad->color.b == 0)
				{
					// find its neighbors to determine its color
					sf::Vertex * neighbors[8];
					neighbors[0] = (w - 1 >= 0 && h - 1 >= 0 ? &vertices_[(w - 1 + (h - 1) * size_.x) * 4] : NULL);
					neighbors[1] = (h - 1 >= 0 ? &vertices_[(w + (h - 1) * size_.x) * 4] : NULL);
					neighbors[2] = (w + 1 < size_.x && h - 1 >= 0 ? &vertices_[(w + 1 + (h - 1) * size_.x) * 4] : NULL);
					neighbors[3] = (w + 1 < size_.x ? &vertices_[(w + 1 + h * size_.x) * 4] : NULL);
					neighbors[4] = (w + 1 < size_.x && h + 1 < size_.y ? &vertices_[(w + 1 + (h + 1) * size_.x) * 4] : NULL);
					neighbors[5] = (h + 1 < size_.y ? &vertices_[(w + (h + 1) * size_.x) * 4] : NULL);
					neighbors[6] = (w - 1 >= 0 && h + 1 < size_.y ? &vertices_[(w - 1 + (h + 1) * size_.x) * 4] : NULL);
					neighbors[7] = (w - 1 >= 0 ? &vertices_[(w - 1 + h * size_.x) * 4] : NULL);

					bool alone = true;
					for (sf::Uint16 idx = 0; alone && idx < 8; ++idx)
					{
						if (neighbors[idx] && (neighbors[idx]->color.r != 0 || neighbors[idx]->color.g != 0 || neighbors[idx]->color.b != 0))
						{
							alone = false;
						}
					}

					sf::Color color;
					if (!alone)
					{
						sf::Uint16 idx = rand() % 8;
						while (!neighbors[idx] || (neighbors[idx]->color.r == 0 && neighbors[idx]->color.g == 0 && neighbors[idx]->color.b == 0))
						{
							idx = rand() % 8;
						}

						color = neighbors[idx]->color;
					}
					else
					{
						color.r = rand() % 255 + 1;
						color.g = rand() % 255 + 1;
						color.b = rand() % 255 + 1;
					}
					
					quad[0].color = color;
					quad[1].color = color;
					quad[2].color = color;
					quad[3].color = color;
					++visible_nodes_;
					last_spawn_time_ = boost::posix_time::microsec_clock::local_time();
					
					found = true;
				}

				delta = 
					boost::posix_time::microsec_clock::local_time() - search_start_time;
			}

		}
	}

}	// namespace puzzle
