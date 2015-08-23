#ifndef __PUZZLE_DEFS_HPP__
#define __PUZZLE_DEFS_HPP__

#include <boost/shared_ptr.hpp>
#include <gl/freeglut.h>
#include <string>

namespace puzzle
{
	struct color
	{
		color()
			: r(0.0f)
			, g(0.0f)
			, b(0.0f)
		{
		}

		color(GLfloat red, GLfloat green, GLfloat blue)
			: r(red)
			, g(green)
			, b(blue)
		{
		}

		color(GLfloat c[3])
			: r(c[0])
			, g(c[1])
			, b(c[2])
		{
		}

		GLfloat r;
		GLfloat g;
		GLfloat b;
	};
			
	class menu_item;

    namespace defs
    {
		namespace color
		{
			static const GLfloat BLACK[3] = { 0.0f, 0.0f, 0.0f };
			static const GLfloat LBLUE[3] = { 0.0f, 0.75f, 0.15f };
			static const GLfloat WHITE[3] = { 1.0f, 1.0f, 1.0f };
		}

        namespace grid
        {
            static const GLushort MAX_NODES_X = 36;
            static const GLushort MAX_NODES_Y = 20;
            static const GLfloat NODE_SIZE = 25.6f;
			static const GLdouble SPAWN_RATE = 0.90;
        }

		namespace menu
		{
			enum IMAGE_NAME
			{
				PLAY = 0,
				PUZZLE,
				QUIT,
				NUM_IMAGES
			};

			static const char * IMAGE_FILENAMES[] = 
			{
				"c:\\tmp\\play.png",
				"c:\\tmp\\puzzle.png",
				"c:\\tmp\\quit.png",
			};

			typedef boost::shared_ptr<menu_item> menu_item_ptr;
		}

        namespace window
        {
            static const GLushort WIDTH = 1024;
            static const GLushort HEIGHT = 576;
            static const char * TITLE = "puzzle";
            static const GLint UPDATE_INTERVAL = 33; // milliseconds
        }   // namespace window
    }   // namespace defs
}   //  namespace puzzle

#endif // __PUZZLE_DEFS_HPP__
