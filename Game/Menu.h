#pragma once
#include <SFML/Graphics.hpp>
#include "userInterface.h"
#include "projectile.h"
#include "enemy.h"
#include <SFML/Audio.hpp>


#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>


class Menu {
public:
	Menu(float width, float height);
	~Menu();

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedKey() { return selected; };

private:
	int selected;
	sf::Font font;
	sf::Text text[2];

};