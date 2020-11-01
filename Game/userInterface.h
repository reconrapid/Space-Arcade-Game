#pragma once
#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <SFML/Graphics.hpp>
class userInterface {

public:

	float movementSpeed = 10;
	int health = 10;

	void moveUp(sf::Sprite &sprite);
	void moveLeft(sf::Sprite &sprite);
	void moveRight(sf::Sprite &sprite);
	void moveDown(sf::Sprite &sprite);

	void isShipMoving(sf::Sprite &sprite);
	int direction = 0; // 1 - up // 2 - down // 3 - left // 4 - right

	int counterMove = 0;

	sf::Vector2f curPos;
	sf::Vector2i position;

};


#endif