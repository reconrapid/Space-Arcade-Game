#include "userInterface.h"



void userInterface::moveUp(sf::Sprite &sprite){
	sprite.move(0, -movementSpeed);
	//sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}
void userInterface::moveDown(sf::Sprite &sprite) {
	sprite.move(0, movementSpeed);
	//sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	
}
void userInterface::moveLeft(sf::Sprite &sprite) {
	sprite.move(-movementSpeed, 0);
	//sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	//sprite.setTextureRect(sf::IntRect(0, 18, 16, 16));
}
void userInterface::moveRight(sf::Sprite &sprite){
	sprite.move(movementSpeed, 0);
	//sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	//sprite.setTextureRect(sf::IntRect(0, 34, 16, 16));
}
void userInterface::isShipMoving(sf::Sprite &sprite) {

	curPos = sprite.getPosition();

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	float rotation = (atan2(dy, dx)) * 180 / 3.14159265;

	sprite.setRotation(rotation - 90.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// W key is pressed: move our character up
		    direction = 1;
			moveUp(sprite);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// A key is pressed: move our character left
			direction = 3;
			moveLeft(sprite);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// S key is pressed: move our character down
			direction = 2;
			moveDown(sprite);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// D key is pressed: move our character right
			direction = 4;
			moveRight(sprite);
		}
}

