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
                float m_v_bullet = 200;
                float m_r;
                sf::Texture m_textureShip;
                sf::Sprite m_spriteShip;
                const int m_bulletR = 30;
                Bullet bullet;

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
			m_spriteShip.setOrigin(418, 700);
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
                float R() { return m_r; }
                float X() { return m_x; }
                float Y() { return m_y; }
                float V() { return m_v; }

             int getBulletColor()
              {
	          return bullet.getColor();
              }

		void Rotate(float dalpha)
		{
			m_alpha += dalpha;
			// Ограничение угла вращения, например, в пределах от - 45 до 45 градусов
			if (m_alpha < -40) m_alpha = -40;
			if (m_alpha > 40) m_alpha = 40;
			m_spriteShip.setRotation(m_alpha);
		}

				void Attack()
		{
			float alphaRad = acos(-1) * (m_alpha-90) / 180;
			bullet.Alfa(alphaRad);
		}
		//
		bool BulletAvailable()
		{
			return bullet.Available();
		}

		void BulletReset()
		{
			bullet.X(m_x);
			bullet.Y(m_y);
			bullet.Vx(0);
			bullet.Vy(0);
			bullet.setRandomColor();
		}

		int BulletX() { return bullet.X(); }
		int BulletY() { return bullet.Y(); }

		sf::Sprite Get()
		{
			return m_spriteShip;
		}

		sf::CircleShape GetBullet()
		{
			return bullet.Get();
		}
	};

}
