#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <Circle.hpp>
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
		Cannon m_cannon;
		float circleRadius = 30.0f; // Фиксированный радиус для всех шариков
		int circlesPerRow = 16; // Количество шариков в одной строке
		float distanceBetweenCircles = 2.0f; // Расстояние между шариками
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
			if (!m_cannon.Setup(500, 800))
				return false;
			srand(time(0));
			m_c = new mt::Circle[m_n];
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
		/*void CheckAndChangeColor()
		{
			bool valid = false;
			while (!valid)
			{
				valid = true;
				// Проверяем шарики по горизонтали
				for (int i = 0; i < m_n; i++)
				{
					int row = i / circlesPerRow;
					int col = i % circlesPerRow;
					if (col <= circlesPerRow - 3)
					{
						if (m_c[i].Get().getFillColor() == m_c[i + 1].Get().getFillColor() &&
							m_c[i].Get().getFillColor() == m_c[i + 2].Get().getFillColor())
						{
							// Меняем цвет текущего шарика и следующих двух шариков
							m_c[i].Get().setFillColor(Circle::getRandomColor());
							m_c[i + 1].Get().setFillColor(Circle::getRandomColor());
							m_c[i + 2].Get().setFillColor(Circle::getRandomColor());
							valid = false;
						}
					}
				}

				// Проверяем шарики по вертикали
				for (int i = 0; i < m_n - 2 * circlesPerRow; i++)
				{
					if (m_c[i].Get().getFillColor() == m_c[i + circlesPerRow].Get().getFillColor() &&
						m_c[i].Get().getFillColor() == m_c[i + 2 * circlesPerRow].Get().getFillColor())
					{
						// Меняем цвет текущего шарика и следующих двух шариков в столбце
						m_c[i].Get().setFillColor(Circle::getRandomColor());
						m_c[i + circlesPerRow].Get().setFillColor(Circle::getRandomColor());
						m_c[i + 2 * circlesPerRow].Get().setFillColor(Circle::getRandomColor());
						valid = false;
					}
				}
			}
		}*/
		void DeletCircle()
		{
			// Проверяем шарики по горизонтали
			for (int i = 0; i < m_n; i++)
			{
				int row = i / circlesPerRow;
				int col = i % circlesPerRow;
				if (col <= circlesPerRow - 3) // Убедимся, что есть место для проверки следующих двух шариков
				{
					if (m_c[i].Get().getPosition().x == m_c[i + 1].Get().getPosition().x - (2 * circleRadius + distanceBetweenCircles) &&
						m_c[i].Get().getPosition().x == m_c[i + 2].Get().getPosition().x - 2 * (2 * circleRadius + distanceBetweenCircles))
					{
						// Меняем цвет текущего шарика
						m_c[i].Get().setFillColor(Circle::getRandomColor());
					}
				}
			}

			// Проверяем шарики по вертикали
			for (int i = 0; i < m_n - 2 * circlesPerRow; i++) // Убедимся, что есть место для проверки следующих двух шариков
			{
				if (m_c[i].Get().getPosition().y == m_c[i + circlesPerRow].Get().getPosition().y - (2 * circleRadius + distanceBetweenCircles) &&
					m_c[i].Get().getPosition().y == m_c[i + 2 * circlesPerRow].Get().getPosition().y - 2 * (2 * circleRadius + distanceBetweenCircles))
				{
					// Меняем цвет текущего шарика
					m_c[i].Get().setFillColor(Circle::getRandomColor());
				}
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
				}
				// Логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();
				//CheckAndChangeColor(); // Вызываем новый метод для проверки и изменения цвета шариков
				DeletCircle();
				m_cannon.Move();
				// Отображение
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_cannon.Get());
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());
				m_window.display();
			}
		}
	};
}
