#include "gfx.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <GL/freeglut.h>

#include "defs.hpp"
#include "grid.hpp"
#include "menu.hpp"

namespace puzzle
{
    static gfx * GFX = NULL;
    static boost::posix_time::ptime g_last_draw_time;

    gfx::gfx()
    {
    }

    gfx::gfx(int argc, char ** argv)
        : window_id_(0)
		, state_(MENU)
    {
        GFX = this;
        g_last_draw_time = boost::posix_time::microsec_clock::local_time();

        glutInit(&argc, argv);
        glutInitWindowSize(defs::window::WIDTH, defs::window::HEIGHT);
        glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - defs::window::WIDTH / 2,
            glutGet(GLUT_SCREEN_HEIGHT) / 2 - defs::window::HEIGHT / 2);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        window_id_ = glutCreateWindow(defs::window::TITLE);
        glutDisplayFunc(gfx::g_draw);
		glutKeyboardFunc(gfx::g_handle_keys);
        glutMouseFunc(gfx::g_handle_mouse);
        glutMotionFunc(gfx::g_handle_mouse_movement);
        glutPassiveMotionFunc(gfx::g_handle_mouse_movement);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);


        grid_ = boost::shared_ptr<grid>(new grid());
		menu_ = boost::shared_ptr<menu>(new menu());
    }

    gfx::~gfx()
    {
    }

    void gfx::draw()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
        glMatrixMode(GL_MODELVIEW);

		switch (state_)
		{
			case MENU:
				menu_->draw();
				break;
			case PAUSED:
				break;
			case PLAYING:
				grid_->draw();
				break;
			default:
				break;
		}


        glutSwapBuffers();
    }

    /* static */ void gfx::g_draw()
    {
        if (GFX) GFX->draw();
    }

	/* static */ void gfx::g_handle_keys(GLubyte key, GLint x, GLint y)
	{
		if (GFX) GFX->handle_keys(key, x, y);
	}

    /* static */ void gfx::g_handle_mouse(GLint button, GLint state, GLint x, GLint y)
    {
        if (GFX) GFX->handle_mouse(button, state, x, y);
    }

    /* static */ void gfx::g_handle_mouse_movement(GLint x, GLint y)
    {
        if (GFX) GFX->handle_mouse_movement(x, y);
    }

    /* static */ void gfx::g_update()
    {
            if (GFX) GFX->draw();

            static boost::posix_time::ptime last_update_time = boost::posix_time::microsec_clock::local_time();
            boost::posix_time::time_duration delta = boost::posix_time::microsec_clock::local_time() - last_update_time;
            if (delta.total_nanoseconds() / 1000000 >= defs::window::UPDATE_INTERVAL)
            {
                if (GFX) GFX->update();
                last_update_time = boost::posix_time::microsec_clock::local_time();
            }
    }

	void gfx::handle_keys(GLubyte key, GLint x, GLint y)
	{
		switch (key)
		{
			case 27: // escape
				glutLeaveMainLoop(); // TODO bring up menu (if state is MENU, menu_->handle_keys(key, x, y))
				break;
			default:
				break;
		}
	}

    void gfx::handle_mouse(GLint button, GLint state, GLint x, GLint y)
    {
		switch (state_)
		{
			case MENU:
				menu_->handle_mouse(button, state, x, y);
				break;
			case PAUSED:
				break;
			case PLAYING:
				grid_->handle_mouse(button, state, x, y);
				break;
			default:
				break;
		}
    }

    void gfx::handle_mouse_movement(GLint x, GLint y)
	{
		switch (state_)
		{
			case MENU:
				menu_->handle_mouse_movement(x, y);
				break;
			case PAUSED:
				break;
			case PLAYING:
				grid_->handle_mouse_movement(x, y);
				break;
			default:
				break;
		}
    }

    void gfx::run()
    {
        glutIdleFunc(gfx::g_update);
        glutMainLoop();
    }

    void gfx::update()
    {
		switch (state_)
		{
			case MENU:
				menu_->update();
				break;
			case PAUSED:
				break;
			case PLAYING:
				grid_->update();
				break;
			default:
				break;
		}
    }
}   // namespace puzzle
