#include "Projectile.h"
#include "../util/ObjLoader.h"

Projectile::Projectile(float x, float xVelocity, float yVelocity)
{
	position = { x, 22, 1 };
	velocity = { xVelocity, yVelocity, 0 };
	gravity = 10;
	isActive = true;
}

void Projectile::update(float deltaTime)
{
	GameObject::update(deltaTime);

	velocity.y -= deltaTime * gravity;

	position.x += deltaTime * velocity.x;
	position.y += deltaTime * velocity.y;
	position.z += deltaTime * velocity.z;
}

void Projectile::hasHit()
{
	velocity.y = 5;
	velocity.z = 10;
	isActive = false;
}

bool Projectile::canBeDestroyed() const
{
	return position.y < 0;
}
