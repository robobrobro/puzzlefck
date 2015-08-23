#ifndef __PUZZLE_GFX_HPP__
#define __PUZZLE_GFX_HPP__

#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <gl/freeglut.h>
#include <vector>

namespace puzzle
{
	enum state
	{
		MENU = 0,
		PAUSED,
		PLAYING,
	};

    class grid;
	class menu;

    class gfx
    {
    public:
        gfx();
        gfx(int argc, char ** argv);
        ~gfx();

        static void g_draw();
		static void g_handle_keys(GLubyte key, GLint x, GLint y);
        static void g_handle_mouse(GLint button, GLint state, GLint x, GLint y);
        static void g_handle_mouse_movement(GLint x, GLint y);
        static void g_update();
        void run();

    private:
        void draw();
		void handle_keys(GLubyte key, GLint x, GLint y);
        void handle_mouse(GLint button, GLint state, GLint x, GLint y);
        void handle_mouse_movement(GLint x, GLint y);
        void update();

        GLuint window_id_;
		state state_;
        boost::shared_ptr<grid> grid_;
        boost::shared_ptr<menu> menu_;
    };   // class gfx
}   //  namespace puzzle

#endif // __PUZZLE_GFX_HPP__
