#include "../util/MousePicking.h"
#include "../data/DataManager.h"

DataManager *dataMP = &DataManager::getInstance();

MousePicking::MousePicking(GameObject *objects, int height, int x, int y)
{
	this->objectsToCheck = objects;
	this->windowHeight = height;
	this->lastX = x;
	this->lastY = y;
	this->cursorCounter = 0;
	this->isCounting = false;
	this->isSettingsScreen = false;
	this->isChanges = false;
	this->timePassed = 0;
	this->cursorCounter = 0;
}

MousePicking::~MousePicking()
{
	
}

void MousePicking::checkSettings(int x, int y) 
{
	if ((y >= 20 && y <= 30 && x>=30 && x <= 190)||(y >= 250 && y <= 260 && x >= 580 && x <= 660)) {
		this->isCounting = true;
		this->isSettingsScreen = true;
	}
}

void MousePicking::checkChanges(int x, int y)
{
	if (y >= 350 && y <= 360 && x >= 580 && x <= 660) {
		this->isCounting = true;
		this->isChanges = true;
	}
}

void MousePicking::searchObject(int cursorX, int cursorY)
{
	float winZ;
	glReadPixels(cursorX, windowHeight - cursorY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	double modelMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	double projMatrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	double x, y, z;
	gluUnProject
	(
		cursorX,
		windowHeight - cursorY,
		winZ,
		modelMatrix,
		projMatrix,
		viewport,
		&x,
		&y,
		&z
	);
	const double xIcon = objectsToCheck->getPosition().x;
	const double yIcon = objectsToCheck->getPosition().y;
	const double zIcon = objectsToCheck->getPosition().z;
	const double sizeIcon = 0.5f;
	
	if ((xIcon + sizeIcon) > x && (xIcon - sizeIcon) < x &&
		(yIcon + sizeIcon) > y && (yIcon - sizeIcon) < y &&
		(zIcon + sizeIcon) > z && (zIcon - sizeIcon) < z)
	{
		isCounting = true;
	}
	else
	{
		
	}
}

void MousePicking::update(int cursorX, int cursorY, int height, float time) 
{
	//std::cout << "x,y: " << cursorX << " : " << cursorY << std::endl;
	if (!isCounting) {
		this->windowHeight = height;
		if (abs(cursorX - lastX) <= 2 && abs(cursorY - lastY) <= 2) {
			cursorCounter += time;
			if (cursorCounter >= 1.5f && timePassed <= 1.6f) {
				searchObject(cursorX, cursorY);
				checkSettings(cursorX, cursorY);
				if (dataMP->settingsActive == true) {
					checkChanges(cursorX, cursorY);
				}
				cursorCounter = 0;
			}
		}
		else {
			cursorCounter = 0;
		}
	}
	else {
		if (abs(cursorX - lastX) <= 5 && abs(cursorY - lastY) <= 5) {
			timePassed += time;
			if (timePassed >= 3.0f && timePassed <= 3.1f) {
				if (isSettingsScreen) {
					
						std::cout << "settings screen selected" << std::endl;
						if (dataMP->settingsActive == true) {
							dataMP->settingsActive = false;
						}
						else {
							dataMP->settingsActive = true;
						}
						isCounting = false;
						isSettingsScreen = false;
						timePassed = 0;
					
				}
				else if (isChanges) {
					std::cout << "changes activated" << std::endl;
					dataMP->settings.changeDifficulty();
					isCounting = false;
					isChanges = false;
					timePassed = 0;
				}
				else {
					isCounting = false;
					timePassed = 0;
					dataMP->stateHandler.setState(StateHandler::States::GAME);
				}
			}
			
		}
		else {
			isCounting = false;
			this->timePassed = 0;
		}
		DataManager::getInstance().scaleLoading = timePassed * 10;
	}
	
	lastX = cursorX;
	lastY = cursorY;
}

float MousePicking::getTimePassed() {
	return timePassed;
}