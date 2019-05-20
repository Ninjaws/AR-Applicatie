#include "../util/MousePicking.h"

MousePicking::MousePicking(GameObject *objects, int height, int x, int y)
{
	this->objectsToCheck = objects;
	this->windowHeight = height;
	this->lastX = x;
	this->lastY = y;
	this->cursorCounter = 0;
	this->isCounting = false;
	this->timePassed = 0;
	this->cursorCounter = 0;
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
	std::cout << "xyz: " << x << ", " << y << ", " << z << std::endl;
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
	if (!isCounting) {
		this->windowHeight = height;
		if (abs(cursorX - lastX) <= 2 && abs(cursorY - lastY) <= 2) {
			cursorCounter += time;
			if (cursorCounter >= 2.0f && timePassed <= 2.1f) {
				searchObject(cursorX, cursorY);
				cursorCounter = 0;
			}
		}
		else {
			cursorCounter = 0;
		}
	}
	else {
		if (abs(cursorX - lastX) <= 2 && abs(cursorY - lastY) <= 2) {
			timePassed += time;
			if (timePassed >= 3.0f && timePassed <= 3.1f) {
				std::cout << "selected the game!!" << std::endl;
				isCounting = false;
				timePassed = 0;
			}
		}
		else {
			isCounting = false;
			this->timePassed = 0;
		}
	}
	lastX = cursorX;
	lastY = cursorY;
}

float MousePicking::getTimePassed() {
	return timePassed;
}