#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <Circle.hpp>
#include <Cannon.hpp>
#include <Bullet.hpp>

namespace mt
{
	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Cannon m_cannon;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Setup(int n)
		{
			m_n = n;
			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);
			// Создание текстуры фона
			if (!m_textureBackground.loadFromFile("assets\\sky.jpg"))
			{
				std::cout << "Error while loading sky.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			if (!m_cannon.Setup(525, 970))  //Расположение пушки
				return false;

			srand(time(0));

			m_c = new mt::Circle[m_n];

			float circleRadius = 30.0f; // Фиксированный радиус для всех шариков
			int circlesPerRow = 16; // Количество шариков в одной строке
			float distanceBetweenCircles = 2.0f; // Расстояние между шариками
			float startX = circleRadius + distanceBetweenCircles; // Начальная позиция X для первого шарика
			float startY = circleRadius + distanceBetweenCircles; // Начальная позиция Y для первой строки

			// Создание шариков в нескольких строках
			for (int i = 0; i < m_n; i++)
			{
				int row = i / circlesPerRow; // Текущая строка
				int col = i % circlesPerRow; // Текущий столбец в строке
				float x = startX + col * (2 * circleRadius + distanceBetweenCircles); // Позиция X для шарика
				float y = startY + row * (2 * circleRadius + distanceBetweenCircles); // Позиция Y для шарика
				m_c[i].Setup(x, y, circleRadius);
			}
		}


		void LifeCycle()
		{
			sf::Clock clock;

			while (m_window.isOpen())
			{
				// Обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();

					//Управление пушкой с клавиатуры, поворот в стороны, для выбора траектории

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						m_cannon.Rotate(-1);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						m_cannon.Rotate(1);
					}
				}


				// Логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				m_cannon.Move();

				// Отображение
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_cannon.Get());   //Отрисовка пушки
				m_window.draw(m_fpsText);
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());
				m_window.display();
			}
		}
	};

}