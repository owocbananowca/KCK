#pragma once

#include "Ship.h"
#include "BorderMan.h"

class Planet
{
public:
	Planet();
	Planet(float x, float y, float numer);
	~Planet();

	int getX();
	int getY();

	void display();

	void SetPrice(int pprice);
	int GetPrice();
	void SetBoolTrue();
	void SetBoolFalse();
	bool CanWeShop();

	bool onPlanet(Ship& statek);
	
	void welcome(Ship& statek, BorderMan& b);
	void shopingTime(Ship& statek);
	void positiveAns(int i, Ship& statek);
	void negativeAns(Ship& statek);
	bool visited;
	bool interactive;
	void byeBye(Ship& s);
	bool isMotherPlanet;

protected:
	int pprice;

	void setTexture(unsigned numer);
	void setPosition(float x, float y);


	

	
	 sf::Texture planetTexture;
	 sf::Sprite planetSprite;
};

