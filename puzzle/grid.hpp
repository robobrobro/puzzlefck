#ifndef __PUZZLE_GRID_HPP__
#define __PUZZLE_GRID_HPP__

#include <cstdlib>
#include <gl/freeglut.h>
#include <vector>

#include "defs.hpp"

namespace puzzle
{
    struct node
    {

        node()
            : exists(false)
			, highlighted(false)
        {
            for (GLuint idx = 0; idx < 3; ++idx)
            {
                fill_color[idx] = 0.0f;
				highlight_color[idx] = 1.0f;
                outline_color[idx] = 0.0f;
            }


        }

        GLfloat fill_color[3];
		GLfloat highlight_color[3];
        GLfloat outline_color[3];
        bool exists;
		bool highlighted;
    };  // struct node

    class grid
    {
    public:
        grid();
        ~grid();

        void draw();
        void handle_mouse(GLint button, GLint state, GLint x, GLint y);
        void handle_mouse_movement(GLint x, GLint y);
        void update();

        GLfloat x();
        GLfloat y();
        GLfloat width();
        GLfloat height();

    private:
        node nodes_[defs::grid::MAX_NODES_X][defs::grid::MAX_NODES_Y];
        GLfloat x_;
        GLfloat y_;
		GLfloat width_;
		GLfloat height_;
        GLuint nodes_x_;
        GLuint nodes_y_;
		GLuint visible_nodes_;
		GLint mouse_x_;
		GLint mouse_y_;
		GLint mouse_clicked_x_;
		GLint mouse_clicked_y_;
		GLint mouse_state_;
		bool clicked_;
		bool erasing_;
		std::vector<color> erase_colors_;
    };   // class grid
}   //  namespace puzzle

#endif // __PUZZLE_GRID_HPP__
