#pragma once
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <SFML/Graphics.hpp>

class projectile {

public:

	float movementSpeed = 10;
	int damage = 2;
	int direction = 0; // 1 - up // 2 - down // 3 - left // 4 - right

	sf::Vector2f vol;


	float rot;

	 projectile();
	 void update();

	 //sf::Sprite spriteAttack;
	 //sf::Texture textureLaser;

	 sf::CircleShape bullet;



};


#endif
