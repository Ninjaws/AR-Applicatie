#include "WorldMap.h"
#include "../components/StaticComponent.h"
#include "../data/DataManager.h"

/*
Class which holds and manipulates the objects in the menu screen (Map)
*/

WorldMap::WorldMap()
{
	// The game object for the map
	this->map = new GameObject();
	this->map->addComponent(new StaticComponent("map", "map"));
	this->map->setPosition({ -1.5, 18, 26 });
	this->map->setRotation({ 0, 90, 0});

	// The game object for the skybox
	this->skybox = new GameObject();
	this->skybox->addComponent(new StaticComponent("skybox", "skybox_forest"));
	this->skybox->setPosition({ -0,0,0 });
	this->skybox->setRotation({ 0, 0, 0 });

	// The game object for the icon on castle black
	this->icon = new GameObject();
	this->icon->addComponent(new StaticComponent("icon", "none"));
	this->icon->setPosition({ 1.3563f, 18.50308f, 11});
	this->icon->setRotation({ 0, 90, 0 });

	// The game objecct for the second icon
	this->wIcon = new GameObject();
	this->wIcon->addComponent(new StaticComponent("wicon", "none"));
	this->wIcon->setPosition({ -1.5, 18.25, 17.25});
	this->wIcon->setRotation({ 0, 90, 0 });
	this->margin = 100;
	this->increment = 0.1f;
	this->icons = std::vector<GameObject*>();
	this->icons.push_back(this->icon);
	this->icons.push_back(this->wIcon);
	// Initialising the mouse picking
	this->mousePicking = new MousePicking(this->icons, 1080, 0,0);
}

WorldMap::~WorldMap()
{
	delete map;
	delete icon;
	delete wIcon;
}

void WorldMap::update(float deltaTime, int x, int y, int height)
{
	if(y <= margin && this->map->getPosition().z <= 24.5)
	{
		this->map->setPosition({ -1.5, 18, this->map->getPosition().z + increment });
		this->icon->setPosition({ 1.3563f, 18.50308f, this->icon->getPosition().z + increment });
		this->wIcon->setPosition({ -1.5, 18.25, this->wIcon->getPosition().z + increment });
	} else if(y >= height - margin && this->map->getPosition().z >= -7)
	{
		this->map->setPosition({ -1.5, 18, this->map->getPosition().z - increment });
		this->icon->setPosition({ 1.3563f, 18.50308f, this->icon->getPosition().z -increment });
		this->wIcon->setPosition({ -1.5, 18.25, this->wIcon->getPosition().z - increment });
	}
	this->x = x;
	this->y = y;
	this->height = static_cast<float>(height);
	this->deltatime = deltaTime;
	
}


void WorldMap::draw(std::map<std::string, Graphics::mesh>& meshes, std::map<std::string, uint16_t>& textures)
{
	// Loop through all objects and draw them
	for (auto o : getGameObjects())
	{
		for (auto c : o->getComponents())
		{
			c->draw(meshes, textures);
		}
	}
	this->mousePicking->update(x, y, static_cast<int>(this->height), this->deltatime);
}

std::vector<GameObject*> WorldMap::getGameObjects() const
{
	// Creating and returning a vector with all the objects in the worldmap
	std::vector<GameObject*> gameObjects;
	gameObjects.clear();
	gameObjects.push_back(map);
	gameObjects.push_back(icon);
	gameObjects.push_back(wIcon);
	gameObjects.push_back(skybox);
	return gameObjects;
}

MousePicking* WorldMap::getMousePicking() const
{
	return this->mousePicking;
}