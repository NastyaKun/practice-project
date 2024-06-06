#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace mt
{

	class Cannon
	{
		float m_x, m_y;
		float m_alpha;
		float m_v;
		sf::Texture m_textureShip;
		sf::Sprite m_spriteShip;

	public:
		Cannon() = default;

		Cannon(float x, float y)
		{
			m_x = x;
			m_y = y;
		}

		bool Setup(float x, float y)
		{
			m_x = x;
			m_y = y;
			m_alpha = 0;
			m_v = 0;


			if (!m_textureShip.loadFromFile("assets\\ship_1.png"))
			{
				std::cout << "Error while loading ship_1.png" << std::endl;
				return false;
			}
			m_spriteShip.setTexture(m_textureShip);
			m_spriteShip.setScale(0.4f, 0.4f);     //Размеры пушки
			m_spriteShip.setOrigin(m_textureShip.getSize().x / 2, m_textureShip.getSize().y);
			m_spriteShip.setPosition(m_x, m_y);
			m_spriteShip.setRotation(m_alpha);
		}

		void setVelocity(float dv)
		{
			m_v += dv;
		}

		void Move()
		{
			float alphaRad = acos(-1) * m_alpha / 180;
			m_x += m_v * cos(alphaRad);
			m_y += m_v * sin(alphaRad);
			m_spriteShip.setPosition(m_x, m_y);
		}

		void Rotate(float dalpha)
		{
			m_alpha += dalpha;
			// Ограничение угла вращения, например, в пределах от - 45 до 45 градусов
			if (m_alpha < -40) m_alpha = -40;
			if (m_alpha > 40) m_alpha = 40;
			m_spriteShip.setRotation(m_alpha);
		}

		sf::Sprite Get()
		{
			return m_spriteShip;
		}
	};

}
