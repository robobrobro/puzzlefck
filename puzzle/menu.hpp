#ifndef __PUZZLE_MENU_HPP__
#define __PUZZLE_MENU_HPP__

#include <cstdlib>
#include <gl/freeglut.h>
#include <string>
#include <vector>

#include "defs.hpp"

namespace puzzle
{
	class menu_item
	{
		public:
			menu_item();
			menu_item(const std::string & image_filename);

			void draw();

		private:
			GLfloat x_;
			GLfloat y_;
			GLint width_;
			GLint height_;

			GLuint texture_id_;
	};	// struct menu_item

    class menu
    {
    public:
        menu();
        ~menu();

        void draw();
        void handle_mouse(GLint button, GLint state, GLint x, GLint y);
        void handle_mouse_movement(GLint x, GLint y);
        void update();

    private:
		std::vector<defs::menu::menu_item_ptr> items_;
    };   // class menu
}   //  namespace puzzle

#endif // __PUZZLE_MENU_HPP__
