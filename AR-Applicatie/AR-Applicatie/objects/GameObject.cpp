#include "GameObject.h"


GameObject::GameObject(const std::string &mesh, const std::string &texture)
{
	this->mesh = mesh;
	this->texture = texture;

	this->position = { 0.0f, 0.0f, 0.0f, 0.0f };
	this->rotation = { 0.0f, 0.0f, 0.0f, 0.0f };
	this->scale = { 1.0f, 1.0f, 1.0f, 0.0f };
}

void GameObject::addComponent(Component *component)
{
	component->setGameObject(this);
	components.push_back(component);
}

std::list<Component *> GameObject::getComponents() const
{
	return components;
}

void GameObject::draw(std::map<std::string, Graphics::mesh> &meshes, std::map<std::string, uint16_t> &textures)
{
	for (auto &c : components)
		c->draw(meshes, textures);
}

void GameObject::update(const float elapsedTime)
{
	for (auto &c : components)
		c->update(elapsedTime);
}

void GameObject::setPosition(Math::vec3d pos)
{
	this->position = pos;
}

void GameObject::setRotation(Math::vec3d rot)
{
	this->rotation = rot;
}

void GameObject::setScale(Math::vec3d scale)
{
	this->scale = scale;
}

Math::vec3d GameObject::getPosition() const
{
	return position;
}

Math::vec3d GameObject::getRotation() const
{
	return rotation;
}

Math::vec3d GameObject::getScale() const
{
	return scale;
}

std::string GameObject::getMesh() const
{
	return mesh;
}

std::string GameObject::getTexture() const
{
	return texture;
}
