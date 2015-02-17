#include "stdafx.h"
#include "Window.h"
#include "Planet.h"
#include "Console.h"
#include "BorderMan.h"
#include "Ship.h"
#include "Generator.h"


void Planet::display()
{
	Window::draw(planetSprite);
}

Planet::Planet()
{
	visited = false;
}


Planet::~Planet()
{

}

void Planet::setTexture(unsigned number)
{
	planetTexture.loadFromFile("planet" + to_string(number) + ".png");
	planetSprite.setTexture(planetTexture);
}

void Planet::setPosition(float x, float y)
{
	planetSprite.setPosition(x, y);
}

Planet::Planet(float x, float y, float number)
{
	interactive = true;
	visited = false;	//ważne
	setTexture(number);
	setPosition(x,y);
	SetPrice(35+Generator::generate(1,40));
	isMotherPlanet = false;
}



int Planet::getX()
{
	return planetSprite.getPosition().x;
}
int Planet::getY()
{
	return planetSprite.getPosition().y;
}

void Planet::SetPrice(int price) {
	this->pprice = price;
}

int Planet::GetPrice() {
	return pprice;
}

void Planet::SetBoolFalse() {
	interactive = false;
}

void Planet::SetBoolTrue() {
	interactive = true;
}

bool Planet::CanWeShop() {
	return interactive;
}

bool Planet::onPlanet(Ship& statek) {
	if (statek.getX() >= getX() &&
		statek.getX() <= getX() + 10 &&
		statek.getY() >= getY() &&
		statek.getY() <= getY() + 10
		
		) {
		//statek.isStuck = true;
		statek.isOnPlanet = true;
		return true;
	}
	else {
		return false;
	}
}

void Planet::welcome(Ship& statek, BorderMan& b) {

	if ((b.chance <= 50) && /*(statek.isStuck == true)*/(onPlanet(statek) == true) && BorderMan::busy == false) {
		b.action(statek,*this);
	}
	else{
		BorderMan::busy = false;

		if ((interactive == true) && /*(statek.isStuck == true)*/(onPlanet(statek) == true)) {
			Console::putTextLine(L"Obsługa Naziemna >> Witamy, chcesz nam coś sprzedać?");
		}
		if (visited)
		{
			Console::putTextLine(L"Obsługa Naziemna >> U nas już byłeś, leć dalej.");
		}
	}
}

void Planet::shopingTime(Ship& statek) {
	if (interactive == true) {
		wstring temp, temp2;
		temp2 = to_wstring(GetPrice());
		temp = L"Obsługa Naziemna >> Mozemy odkupic od Ciebie towar za " + temp2 + L".Chciałbyś sprzedać?";
		Console::putTextLine(temp);
	}
	/*else {
		Console::putTextLine(L"Obsługa Naziemna >> Przykro nam, nie jesteśmy zainteresowani.");
	}*/
}

void Planet::negativeAns(Ship & statek) {
	Console::putTextLine(L"Obsługa Naziemna >> Nie to nie, może następnym razem\n");
	visited = true;
	statek.isStuck = false;
	statek.isStuckv2 = false;
	statek.movementCounter = 0;
}

void Planet::positiveAns(int i, Ship& statek) {
	if (i <= statek.GetStuff() && interactive == true) {
		Console::putTextLine(L"Obsługa Naziemna >> Bierzemy\n");
		statek.SetStuff(statek.GetStuff() - i);
		statek.setMoney(statek.getMoney()+GetPrice()*i);
		visited = true;
		byeBye(statek);
		statek.isStuck = false;
		//interactive = false;
	}
	else{
		Console::putTextLine(L"Obsługa Naziemna >> Nie masz tyle\n");
	}
}

void Planet::byeBye(Ship& s) {
	Console::putTextLine(L"Obsluga Naziemna >> Żegnamy, mamy nadzieję że pobyt się udał i zapraszamy  ponownie.");
	Planet::visited = true;
	Planet::interactive = false;
	s.isStuck = false;
	s.isStuckv2 = false;
	s.stop();
}