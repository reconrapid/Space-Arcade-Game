#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("Font/Freedom/FREEDOM.ttf"))
	{
		// error...
	}
	text[0].setFont(font);
	text[0].setString("PLAY");
	text[0].setCharacterSize(80);
	text[0].setFillColor(sf::Color::Red);

	text[0].setPosition(sf::Vector2f(1600 / 2.0f, 200));


	text[1].setFont(font);
	text[1].setString("EXIT");
	text[1].setCharacterSize(80);
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition(sf::Vector2f(1600 / 2.0f, 400));

	selected = 0;

}

Menu::~Menu() {

}

void Menu::Draw(sf::RenderWindow & window) {

	for (int i = 0; i < 2; i++) {
		window.draw(text[i]);
	}
}

void Menu::MoveUp() {
	if (selected - 1 >= 0) {
		text[selected].setFillColor(sf::Color::White);
		selected--;
		text[selected].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selected + 1 < 2) {
		text[selected].setFillColor(sf::Color::White);
		selected++;
		text[selected].setFillColor(sf::Color::Red);
	}
}


