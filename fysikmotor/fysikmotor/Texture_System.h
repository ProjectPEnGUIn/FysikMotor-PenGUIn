#pragma once

#include "SFML\Graphics.hpp"
#include <unordered_map>
#include <memory>
#include <cassert>
#include <iostream>

#ifndef  _TEXTURESYSTEM_
#define _TEXTURESYSTEM_



class Texture_System
{
public:
	Texture_System(const std::string& filename, const sf::Vector2f& origin, const sf::Vector2f& pos, const sf::IntRect clip, float scaleX, float scaleY, bool isSmooth, bool isRepeated)
		:
		m_Filename(filename),
		m_pTexture(nullptr),
		m_Sprite()
	{
		if (s_TextureCache.count(filename))
		{
			m_pTexture = s_TextureCache[filename];
		}
		else
		{
			auto& tex = s_TextureCache[filename];
			tex = std::make_unique<sf::Texture>();
			assert(tex != nullptr);

			if (!tex->loadFromFile(filename))
				std::cerr << "Failed to load texture " << filename << "!\n";
			else
				std::cout << "Loaded texture " << filename << "!\n";
			m_pTexture = tex;
		}
		assert(m_pTexture != nullptr);

		m_pTexture->setSmooth(isSmooth);
		m_pTexture->setRepeated(isRepeated);
		m_Sprite.setTexture(*m_pTexture);
		m_Sprite.setTextureRect(clip);
		m_Sprite.setOrigin(origin);
		m_Sprite.setPosition(pos);
		m_Sprite.setScale(scaleX, scaleY);
	};
	~Texture_System()
	{
		m_pTexture.reset();
		//Om detta är sista instansen av textur i "Cache" så ta bort den från "cache"
		if (s_TextureCache[m_Filename].unique())
		{
			s_TextureCache.erase(m_Filename);
			std::cout << "Deleted texture " << m_Filename << "!\n";
		}
	}

	sf::FloatRect getGlobalBounds() const
	{
		return m_Sprite.getGlobalBounds();
	};

	void setPosition(const sf::Vector2f& pos)
	{
		m_Sprite.setPosition(pos);
	}
	void setClip(const sf::IntRect& clip)
	{
		m_Sprite.setTextureRect(clip);
	}
	void setSmooth(bool isSmooth)
	{
		assert(m_pTexture != nullptr);
		m_pTexture->setSmooth(isSmooth);
	}
	void setRepeated(bool isRepeated)
	{
		assert(m_pTexture != nullptr);
		m_pTexture->setRepeated(isRepeated);
	}
	void setScale(float x, float y)
	{
		m_Sprite.setScale(x, y);
	}
	void setColor(sf::Color& color)
	{
		m_Sprite.setColor(color);
	}
	void setRotation(float rotation)
	{
		m_Sprite.setRotation(rotation);
	}
	void draw(sf::RenderWindow& renderWindow) const
	{
		renderWindow.draw(m_Sprite);
	}

private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> s_TextureCache;

	std::string m_Filename;
	std::shared_ptr<sf::Texture> m_pTexture;
	sf::Sprite m_Sprite;
};
#endif // ! _TEXTURESYSTEM_