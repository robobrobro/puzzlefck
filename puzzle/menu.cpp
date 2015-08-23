#include "menu.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace puzzle
{
	menu_item::menu_item()
		: x_(0.0f)
		, y_(0.0f)
		, width_(0)
		, height_(0)
		, texture_id_(0)
	{
	}

	menu_item::menu_item(const std::string & image_filenmae)
		: x_(0.0f)
		, y_(0.0f)
	{
		sf::Image image;
		if (!image.loadFromFile(image_filenmae.c_str()))
		{
			//throw new std::exception("failed to load image!");
			;
		}
		else
		{
			width_ = image.getSize().x;
			height_ = image.getSize().y;
			glGenTextures(1, &texture_id_);
			glBindTexture(GL_TEXTURE_2D, texture_id_);
			// TODO try glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData); instead
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}

	void menu_item::draw()
	{
		//glPushMatrix();
		
		glEnable(GL_TEXTURE_2D);

		//glScalef(1.0f, -1.0f, 1.0f);
		

		glBegin(GL_QUADS);
			glBindTexture(GL_TEXTURE_2D, texture_id_);
			glTexCoord2f(0, 0); glVertex2f(x_, y_ + height_);
			glTexCoord2f(0, 1); glVertex2f(x_,  y_);
			glTexCoord2f(1, 1); glVertex2f(x_ + width_, y_);
			glTexCoord2f(1, 0); glVertex2f(x_ + width_, y_ + height_);
		glEnd();
		
		glDisable(GL_TEXTURE_2D);

		//glPopMatrix();
	}
    
	menu::menu()
    {
		for (GLushort idx = 0; idx < defs::menu::NUM_IMAGES; ++idx)
		{
			boost::shared_ptr<menu_item> item = 
				boost::shared_ptr<menu_item>(new menu_item(defs::menu::IMAGE_FILENAMES[idx]));
			items_.push_back(item);
		}
    }

    menu::~menu()
    {
    }

    void menu::draw()
    {
        glPushMatrix();
        glLoadIdentity();

		for (size_t idx = 0; idx < items_.size(); ++idx)
		{
			items_[idx]->draw();
		}

        glPopMatrix();
    }

	void menu::handle_mouse(GLint button, GLint state, GLint x, GLint y)
	{
	}

    void menu::handle_mouse_movement(GLint x, GLint y)
	{
	}

    void menu::update()
    {
    }
}   // namespace puzzle
