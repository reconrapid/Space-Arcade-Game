#include "projectile.h"

projectile::projectile() {

	//Laser Texture
	//if (!textureLaser.loadFromFile("Textures/Boss.png"))
	//{
		// error...
	//}

	//Laser
	//spriteAttack = sf::Sprite();

	//spriteAttack.setTexture(textureLaser);
	//spriteAttack.setPosition(0, 0);

	bullet.setFillColor(sf::Color::Red);
	bullet.setRadius(5.f);
	bullet.setPosition(0, 0);




}

void projectile::update() {
	if (direction == 1) {
		bullet.move(0, -movementSpeed);
	}
	if (direction == 2) {
		bullet.move(0, movementSpeed);
	}
	if (direction == 3) {
		bullet.move(-movementSpeed, 0);
	}
	if (direction == 4) {
		bullet.move(movementSpeed, 0);
	}
	bullet.move(rot, rot);
}
