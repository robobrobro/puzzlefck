#include "grid.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace puzzle
{
    grid::grid()
        : nodes_x_(defs::grid::MAX_NODES_X)
        , nodes_y_(defs::grid::MAX_NODES_Y)
		, visible_nodes_(0)
		, mouse_x_(-1)
		, mouse_y_(-1)
		, mouse_clicked_x_(-1)
		, mouse_clicked_y_(-1)
		, mouse_state_(GLUT_UP)
		, clicked_(false)
		, erasing_(false)
    {
		width_ = defs::grid::NODE_SIZE * nodes_x_;
		height_ = defs::grid::NODE_SIZE * nodes_y_;
		x_ = glutGet(GLUT_WINDOW_WIDTH) / 2.0f - width_ / 2;
		y_ = glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - height_ / 2;

		srand((unsigned int) time(0));
    }

    grid::~grid()
    {
    }

    void grid::draw()
    {
        glPushMatrix();
        glLoadIdentity();

        glTranslatef(x_ - 1, y_ - 1, 0.0f);

		glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(width_ + 2, 0.0f);
			glVertex2f(width_ + 2, height_ + 2);
			glVertex2f(0.0f, height_ + 2);
		glEnd();
        glColor3f(0.75f, 0.75f, 0.75f);
        glBegin(GL_LINE_LOOP);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(width_ + 2, 0.0f);
			glVertex2f(width_ + 2, height_ + 2);
			glVertex2f(0.0f, height_ + 2);             
        glEnd();

        glTranslatef(1.0f, 1.0f, 0.0f);

        for (GLuint x = 0; x < nodes_x_; ++x)
        {
            for (GLuint y = 0; y < nodes_y_; ++y)
            {
				if (nodes_[x][y].exists || nodes_[x][y].highlighted)
				{
					glColor3fv(nodes_[x][y].fill_color);
					glBegin(GL_QUADS);
						glVertex2f(x * defs::grid::NODE_SIZE, y * defs::grid::NODE_SIZE);
						glVertex2f((x + 1) * defs::grid::NODE_SIZE, y * defs::grid::NODE_SIZE);
						glVertex2f((x + 1) * defs::grid::NODE_SIZE, (y + 1) * defs::grid::NODE_SIZE);
						glVertex2f(x * defs::grid::NODE_SIZE, (y + 1) * defs::grid::NODE_SIZE);                
					glEnd();
					glColor3fv(!nodes_[x][y].highlighted ? nodes_[x][y].outline_color : nodes_[x][y].highlight_color);
					glBegin(GL_LINE_LOOP);
						glVertex3f(x * defs::grid::NODE_SIZE, y * defs::grid::NODE_SIZE, !nodes_[x][y].highlighted ? 0.0f : 1.0f);
						glVertex3f((x + 1) * defs::grid::NODE_SIZE, y * defs::grid::NODE_SIZE, !nodes_[x][y].highlighted ? 0.0f : 1.0f);
						glVertex3f((x + 1) * defs::grid::NODE_SIZE, (y + 1) * defs::grid::NODE_SIZE, !nodes_[x][y].highlighted ? 0.0f : 1.0f);
						glVertex3f(x * defs::grid::NODE_SIZE, (y + 1) * defs::grid::NODE_SIZE, !nodes_[x][y].highlighted ? 0.0f : 1.0f);                
					glEnd();
				}
            }
        }

        glPopMatrix();
    }

	void grid::handle_mouse(GLint button, GLint state, GLint x, GLint y)
	{
        if (button == GLUT_LEFT_BUTTON)
        {
			if (mouse_state_ == GLUT_DOWN && state == GLUT_UP)
			{
				clicked_ = true;
			}
			else if (mouse_state_ == GLUT_UP && state == GLUT_DOWN)
			{
				clicked_ = false;
			}

			mouse_state_ = state;
			mouse_clicked_x_ = x;
			mouse_clicked_y_ = y;
		}
	}

    void grid::handle_mouse_movement(GLint x, GLint y)
	{
		mouse_x_ = x;
		mouse_y_ = y;
	}

    void grid::update()
    {
		if (visible_nodes_ < nodes_x_ * nodes_y_)
		{
			if (rand() / (double) RAND_MAX < defs::grid::SPAWN_RATE)
			{
				GLuint x = 0;
				GLuint y = 0;
				boost::posix_time::time_duration spin_time;
				boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
				do
				{
					x = rand() % nodes_x_;
					y = rand() % nodes_y_;
					spin_time = boost::posix_time::microsec_clock::local_time() - start_time;
				} while (nodes_[x][y].exists && spin_time.total_nanoseconds() / 1000000 < defs::window::UPDATE_INTERVAL);

				if (!nodes_[x][y].exists)
				{

					nodes_[x][y].exists = true;

					node * neighbors[8] = { 0 }; // 0 - top-left, ... 7 - left
					neighbors[0] = (x - 1 >= 0 && x - 1 < nodes_x_ && y - 1 >= 0 && y - 1 < nodes_y_) ? &nodes_[x - 1][y - 1] : NULL;
					neighbors[1] = (y - 1 >= 0 && y - 1 < nodes_y_) ? &nodes_[x][y - 1] : NULL;
					neighbors[2] = (x + 1 >= 0 && x + 1 < nodes_x_ && y - 1 >= 0 && y - 1 < nodes_y_) ? &nodes_[x + 1][y - 1] : NULL;
					neighbors[3] = (x + 1 >= 0 && x + 1 < nodes_x_) ? &nodes_[x + 1][y] : NULL;
					neighbors[4] = (x + 1 >= 0 && x + 1 < nodes_x_ && y + 1 >= 0 && y + 1 < nodes_y_) ? &nodes_[x + 1][y + 1] : NULL;
					neighbors[5] = (y + 1 >= 0 && y + 1 < nodes_y_) ? &nodes_[x][y + 1] : NULL;
					neighbors[6] = (x - 1 >= 0 && x - 1 < nodes_x_ && y + 1 >= 0 && y + 1 < nodes_y_) ? &nodes_[x - 1][y + 1] : NULL;
					neighbors[7] = (x - 1 >= 0 && x - 1 < nodes_x_) ? &nodes_[x - 1][y] : NULL;

					bool alone = true;
					for (GLushort idx = 0; idx < 8 && alone; ++idx)
					{
						if (neighbors[idx] && neighbors[idx]->exists)
							alone = false;
					}
					
					// if no neighbors, select random color
					if (alone)
					{
						for (GLushort idx = 0; idx < 3; ++idx)
						{
							nodes_[x][y].fill_color[idx] = rand() / (float) RAND_MAX;
							nodes_[x][y].highlight_color[idx] = 1.0f - nodes_[x][y].fill_color[idx];
						}
					}
					// neighbor(s) exist, so choose color of one of the neighbors
					else
					{
						GLushort neighbor_idx = 0;
						do
						{
							neighbor_idx = rand() % 8;
						} while (!neighbors[neighbor_idx] || !neighbors[neighbor_idx]->exists);

						memcpy(nodes_[x][y].fill_color, neighbors[neighbor_idx]->fill_color, sizeof(nodes_[x][y].fill_color));
						for (GLushort idx = 0; idx < 3; ++idx)
						{
							nodes_[x][y].highlight_color[idx] = 1.0f - nodes_[x][y].fill_color[idx];
						}
					}

					++visible_nodes_;
				}
			}
		}

        for (GLuint x = 0; x < nodes_x_; ++x)
        {
            for (GLuint y = 0; y < nodes_y_; ++y)
            {
				if (mouse_x_ - x_ >= x * defs::grid::NODE_SIZE && 
					mouse_x_ - x_ < (x + 1) * defs::grid::NODE_SIZE &&
					mouse_y_ - y_ >= y * defs::grid::NODE_SIZE &&
					mouse_y_ - y_ < (y + 1) * defs::grid::NODE_SIZE)
				{
					nodes_[x][y].highlighted = true;
				}
				else
				{
					nodes_[x][y].highlighted = false;
				}

				if (clicked_ && nodes_[x][y].exists &&
					mouse_clicked_x_ - x_ >= x * defs::grid::NODE_SIZE && 
					mouse_clicked_x_ - x_ < (x + 1) * defs::grid::NODE_SIZE &&
					mouse_clicked_y_ - y_ >= y * defs::grid::NODE_SIZE &&
					mouse_clicked_y_ - y_ < (y + 1) * defs::grid::NODE_SIZE)
				{
					erase_colors_.push_back(color(nodes_[x][y].fill_color));
					clicked_ = false;
				}
			}
		}

		// TODO this has the (albeit rare) potential to erase nodes that aren't even neighbors
		// to the clicked node if the nodes are of the same color as the clicked node! (FIX)
		if (!erase_colors_.empty())
		{
			for (GLuint x = 0; x < nodes_x_; ++x)
			{
				for (GLuint y = 0; y < nodes_y_; ++y)
				{
					for (std::size_t idx = 0; idx < erase_colors_.size(); ++idx)
					{
						if (nodes_[x][y].fill_color[0] == erase_colors_[idx].r &&
							nodes_[x][y].fill_color[1] == erase_colors_[idx].g &&
							nodes_[x][y].fill_color[2] == erase_colors_[idx].b)
						{
							nodes_[x][y].exists = false;
							nodes_[x][y].highlighted = false;
							memcpy(nodes_[x][y].fill_color, defs::color::BLACK, sizeof(nodes_[x][y].fill_color));
							memcpy(nodes_[x][y].highlight_color, defs::color::WHITE, sizeof(nodes_[x][y].highlight_color));

							--visible_nodes_;
						}
					}
				}
			}

			// TODO how do i know when all colors are gone? need to track count
			// because when all matching colors are gone, remove that color from erase_colors
			erase_colors_.clear();
		}
    }

    GLfloat grid::x()
    {
        return x_;
    }

    GLfloat grid::y()
    {
        return y_;
    }

    GLfloat grid::width()
    {
        return width_;
    }

    GLfloat grid::height()
    {
        return height_;
    }
}   // namespace puzzle
