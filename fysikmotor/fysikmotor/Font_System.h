#pragma once

#ifndef  _FONTSYSTEM_
#define _FONTSYSTEM_



#include "Sound_system.h"
#include "SFML\Graphics.hpp"

class Font_System
{
public:
	Font_System(std::string Textname, std::string output, float size, bool bold)
		:
		m_Filename(Textname)
	{
		if (!font.loadFromFile(m_Filename))
		{
		}
		else
			std::cout << "Loaded font " << Textname << "!\n";

		m_text.setFont(font);
		m_text.setString(output);
		m_text.setCharacterSize(size);

		if (bold = true)
			m_text.setStyle(sf::Text::Bold);
	};

	void setPosition(float posx, float posy)
	{
		m_text.setPosition(sf::Vector2f(posx, posy));
	}
	void setString(sf::String& newinput)
	{
		m_text.setString(newinput);
	}

	void SetRotation(float angle)
	{
		m_text.setRotation(angle);
	}

	void setCharacterSize(float size)
	{
		m_text.setCharacterSize(size);
	}

	void setBold(bool bold)
	{
		if (bold = true)
			m_text.setStyle(sf::Text::Bold);
	}
	void setUnderlined(bool underlined)
	{
		if (underlined = true)
			m_text.setStyle(sf::Text::Underlined);
	}

	void draw(sf::RenderWindow& renderwindow)
	{
		renderwindow.draw(m_text);
	}
	void setColor(int R, int G, int B, int alpha)
	{
		m_text.setFillColor(sf::Color(R, G, B, alpha));
	}



private:
	std::string m_Filename;
	sf::Text m_text;
	sf::Font font;
};
#endif // ! _FONTSYSTEM_