#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "imgui.h"
#include "imgui-SFML.h"

#include <windows.h>

void RemapToScreen(float values[], int size, float max, int windowHeight);

float MaxValue(float values[], int size);


void DrawRectangles(float values[], float size, float windowHeight, float windowWidth, float spacing, sf::RenderWindow* window, sf::RectangleShape rectangle, int current, sf::Vector3f cr, sf::Vector3f ccr);

int main()
{

	


	int windowHeight = 400;
	int windowWidth = 640;

	int numberOfValues = 200;

	srand(time(NULL));
	float value = rand() % 100;
	float *values = new float [numberOfValues];


	for (int i = 0; i < numberOfValues; i++)
	{
		value = rand() % 100;
		values[i] = value;
	}

	int size = numberOfValues;
	float maxValue = MaxValue(values, size);
	RemapToScreen(values, size, maxValue, windowHeight);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ShellSort Algorithm");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	//HWND hwnd = window.getSystemHandle();
	//hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, false);


	sf::RectangleShape rectangle;

	float spacing = 10.0f; // espaço entre as barras
	rectangle.setFillColor(sf::Color(255, 255, 255, 255)); // cor das barras

	float cd[3]{1};
	float cd2[3]{1};

	// variaveis que controlam o shellsort
	int i, j;
	int h = 1;
	int delay_number = 25;
	int delay = 24;
	int flag = 1;
	int update = 0;
	int updateColor[3]{0};
	int flag2 = 0;
	int randomizar = 0;

	cd[0] = 1;
	cd[1] = 1;
	cd[2] = 1;

	cd2[0] = 0.1;
	cd2[1] = 0.1;
	cd2[2] = 0.8;

	window.clear();
	window.display();

	sf::Vector3f ccr;
	sf::Vector3f cr = { 0, 255,0 };

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event events;

		while (window.pollEvent(events))
		{
			ImGui::SFML::ProcessEvent(events);
			if (events.type == sf::Event::Closed)
			{
				window.close();
		
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				flag = 1;
		}

		while (flag == 1)
		{

			
			ImGui::SFML::Update(window, clock.restart());

			ImGui::SFML::ProcessEvent(events);

			if (flag2 == 0)
			{
				ImGui::SetNextWindowPos(ImVec2(0, 0));
				ImGui::SetNextWindowSize(ImVec2(200, 280));
				flag2 = 1;
			}

			ImGui::Begin("Propriedades");
			
			update = numberOfValues;
			ImGui::LabelText("", "Elementos");
			ImGui::SliderInt("##", &numberOfValues, 10, 300);

			ImGui::LabelText("", "Cor principal");
			ImGui::ColorEdit3("##cd", cd, 0);
			ImGui::LabelText("", "Cor secundaria");
			ImGui::ColorEdit3("###cd", cd2, 0);
			randomizar = ImGui::Button("  Randomizar  ");
			flag = !ImGui::Button("  Executar Algoritmo  ");


			ImGui::End();

			cr.x = cd[0] * 255;
			cr.y = cd[1] * 255;
			cr.z = cd[2] * 255;

			ccr.x = cd2[0] * 255;
			ccr.y = cd2[1] * 255;
			ccr.z = cd2[2] * 255;
			
			if (update != numberOfValues || randomizar == 1)
			{
				randomizar = 0;
				if (numberOfValues > 300)
					numberOfValues = 300;
				size = numberOfValues;
				value = rand() % 100;
				delete[] values;
				values = new float[numberOfValues];
			
				for (int i = 0; i < numberOfValues; i++)
				{
					value = rand() % 100;
					values[i] = value;
				}
				float maxValue = MaxValue(values, size);
				RemapToScreen(values, size, maxValue, windowHeight);
			}
			
			window.clear();
			DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);
			ImGui::SFML::Render(window);
			window.display();
			

			while (window.pollEvent(events))
			{
				if (events.type == sf::Event::Closed)
				{
					window.close();
					return 0;
				}
			}

			while (h < size) {
				h = 3 * h + 1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				flag = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				numberOfValues++;
				if (numberOfValues > 300)
					numberOfValues = 300;
				size = numberOfValues;
				value = rand() % 100;
				delete[] values;
				values = new float[numberOfValues];

				for (int i = 0; i < numberOfValues; i++)
				{
					value = rand() % 100;
					values[i] = value;
				}
				float maxValue = MaxValue(values, size);
				RemapToScreen(values, size, maxValue, windowHeight);
				window.clear();
				ImGui::SFML::Render(window);
				DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);
				
				window.display();
					
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				numberOfValues--;
				if (numberOfValues < 10)
					numberOfValues = 10;
				size = numberOfValues;
				value = rand() % 100;
				delete[] values;
				values = new float[numberOfValues];

				for (int i = 0; i < numberOfValues; i++)
				{
					value = rand() % 100;
					values[i] = value;
				}
				float maxValue = MaxValue(values, size);
				RemapToScreen(values, size, maxValue, windowHeight);
				window.clear();
				ImGui::SFML::Render(window);
				DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);
				window.display();
			}
			//std::cout << numberOfValues << "\n";
		}
		window.clear();

		delay++;
		
		if (h > 0 && (delay % (delay_number + 1) == 0)) {

			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || flag == 1)
			{
				flag = 1;
				window.clear();
				DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);
				window.display();
				break;
			}

			for (i = h; i < size; i++) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || flag == 1)
				{
					flag = 1;
					window.clear();
					DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);

					window.display();
					break;
				}

				value = values[i];
				j = i;
				while (j > h - 1 && value <= values[j - h]) {

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == 1)
					{
						flag = 1;
						window.clear();
						DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);

						window.display();
						break;
					}

					values[j] = values[j - h];
					j = j - h;
					window.clear();

					DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, j, cr, ccr);

					while (window.pollEvent(events)) // eventos
					{
						if (events.type == sf::Event::Closed)
						{
							window.close();
						}
					}
					window.display();
				}
				values[j] = value;
				window.clear();

				while (window.pollEvent(events)) // eventos
				{
					if (events.type == sf::Event::Closed)
					{
						window.close();
					}
				}

				if(flag == 0)
					DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, j, cr, ccr);
				window.display();

			}
			h = h / 3;
		}

		if (h == 0)
		{
			flag = 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || flag == 1)
		{
			flag = 1;
			window.clear();
			DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);

			window.display();
		}

		// -----------------------------------------------
		DrawRectangles(values, size, windowHeight, windowWidth, spacing, &window, rectangle, -1, cr, ccr);

		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}

void RemapToScreen(float values[], int size, float max, int windowHeight)
{
	for (int i = 0; i < size; i++)
	{
		values[i] = (values[i] * windowHeight / max) * 0.9f; // multiplica por 0.9 para ter uma sobra na tela
	}
}

float MaxValue(float values[], int size)
{
	float max = values[0];

	for (int i = 0; i < size; i++)
	{
		if (values[i] > max)
			max = values[i];
	}
	return max;
}

void DrawRectangles(float values[], float size, float windowHeight, float windowWidth, float spacing, sf::RenderWindow* window, sf::RectangleShape rectangle, int current, sf::Vector3f cr, sf::Vector3f ccr)
{
	// Desenhar ------------------------------------------------------------------------------------------------------
	float width = float(windowWidth / size);
	for (int i = 0; i < size; i++)
	{

		if (current == i)
		{
			rectangle.setFillColor(sf::Color(ccr.x, ccr.y, ccr.z));
		}
		else
		{
			rectangle.setFillColor(sf::Color(cr.x, cr.y, cr.z));
		}

		rectangle.setSize(sf::Vector2f(width - 1, values[i]));
		//std::cout << "tamanho: " << width << '\n';
		//std::cout << "size vetor: " << size << '\n';
		rectangle.setPosition(sf::Vector2f(0, windowHeight - values[i]));
		rectangle.move(sf::Vector2f((windowWidth / size) * i, 0.0f));
		window->draw(rectangle);
	}
	// ----------------------------------------------------------------------------------------------------------------
}
