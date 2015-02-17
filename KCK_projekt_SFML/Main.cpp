#pragma once

#include "stdafx.h"

#include "Window.h"
#include "GameScreen.h"
#include "Ship.h"
#include "Planet.h"
#include "Console.h"
#include "Parameter.h"
#include "Pirate.h"
#include "Help.h"
#include "BorderMan.h"
#include "MotherPlanet.h"

void wykonaj_komende();
void zeruj();
Ship s; Pirate p1; BorderMan b;
map<wstring, Planet*> planets;
float dt;
pair<wstring, Planet*> currentPlanet;
pair<wstring, Planet*> mother;
bool shipOnPlanet = false;
bool shipOnMother = false;
bool busy = true;
bool busy2 = true;

int main(int argv, char* argc[])
{
	
	Window::Window();
	GameScreen::GameScreen();
	Console::Console();

	sf::Clock clock;
	
	Parameter money(15, 550, 580, "arial.ttf", L"Pieniądze: ");
	Parameter stuff(15, 550, 600, "arial.ttf", L"Towar: ");


	planets[L"Merkury"] = new Planet(115, 180, 1);
	planets[L"Uran"] = new Planet(50, 450, 2); //70,440,2 //550,550,2
	planets[L"Jowisz"] = new Planet(320, 110, 3);
	planets[L"Neptun"] = new Planet(394, 320, 4);
	planets[L"OrionV"] = new MotherPlanet(252, 244, 5);



currentPlanet = make_pair(L"Merkury", planets[L"Merkury"]);

dt = clock.restart().asSeconds();
while (Window::isOpen())
{

	//auto dt = clock.restart().asSeconds();
	Help::podaj_statek(&s, &dt, planets);

	//if (Help::flaga)
	//{
	wykonaj_komende();
	//	}
	if (!shipOnPlanet && !shipOnMother)
	{
		for (auto planet : planets)
		{
			if (planet.second->onPlanet(s) && planet.first != L"OrionV")
			{
				planet.second->welcome(s, b);
				currentPlanet = planet;
				shipOnPlanet = true;
			}
			if (planet.second->onPlanet(s) && planet.first == L"OrionV")
			{
				mother = planet;
				MotherPlanet* temp = (MotherPlanet*)planet.second;
				temp->powitanieDom();
				currentPlanet = planet;
				shipOnMother = true;
			}
		}
	}
	if (currentPlanet.second->onPlanet(s) == false)
	{
		shipOnPlanet = false;
		busy = false;
		busy2 = false;
		shipOnMother = false;
	}

	sf::Event event;
	while (Window::pollEvent(event))
	{
		Window::close(event);
		Window::halp();
		Window::ShowPlanetName(planets);
		Console::doYourJob(event);
	}

	Window::clear();
	GameScreen::display();
	Console::display();

	if (s.GetStuff() >= 500)
	{
		s.setTexture2();
	}
	else if (s.GetStuff() < 500)
	{
		s.setTexture2();
	}

	
	money.display(s.getMoney());
	stuff.display(s.GetStuff());

	for (const auto& planet : planets)
	{
		planet.second->display();
	}

	s.display();

	Window::display();
	if (s.getMoney() == 0 && s.GetStuff() == 0)
	{
		Console::putTextLine(L"GAME OVER");
		//exit(0);
	}

}
return 0;
}


void wykonaj_komende()
{
	if (Help::komenda == L"tak" && shipOnMother && !busy)
	{
		MotherPlanet* temp = (MotherPlanet*)mother.second;
		temp->kupowanie(s);
		busy = true;
	}
	if (Help::komenda == L"nie" && shipOnMother && !busy)
	{
		MotherPlanet* temp = (MotherPlanet*)mother.second;
		temp->negativeAns(s);
		busy = true;
	}
	if (Help::komenda == L"tak" && shipOnPlanet && !busy)
	{
		currentPlanet.second->shopingTime(s);
		busy = true;
	}
	if (Help::komenda == L"nie" && shipOnPlanet && !busy)
	{
		currentPlanet.second->negativeAns(s);
		busy = true;
	}
	if (Help::komenda == L"sprzedaj" /*&& !busy2*/)
	{
		int temp = (int)_wtof(Help::argument.c_str());
		if (temp == 0)
		{
			Help::komenda = L"tak";
		}
		else
		{
			currentPlanet.second->positiveAns(temp, s);
			Help::komenda = L"tak";
		}
		//busy2 = true;
	}
	if (Help::komenda == L"kup" && shipOnMother)
	{
		int temp = (int)_wtof(Help::argument.c_str());
		if (temp == 0)
		{
			Help::komenda = L"tak";
		}
		else
		{
			MotherPlanet* temptemp = (MotherPlanet*)currentPlanet.second;
			temptemp->positiveAns(s, temp);
			Help::komenda = L"tak";
		}
	}
	if (Help::komenda == L"leć")
	{
		
		if (Help::argument == L"lewo" || Help::argument == L"prawo" || Help::argument == L"gór" || Help::argument == L"dół")
		{	
			if(s.isStuckv2 == false)
			s.fly(dt, Help::argument);

		}
		else
		{
			s.flyTo(dt, *planets[Help::argument]);
		}
	}
	if (Help::komenda == L"płać")
	{
		if (Pirate::busy)
		{
			p1.positiveAnswer(s);
		}
		if (BorderMan::busy)
		{
			b.positiveAns(*currentPlanet.second,s);
		}
	}
	if (Help::komenda == L"nie")
	{
		if (Pirate::busy)
		{
			p1.negativeAnswer(s);
			s.isStuck = false;
		}
		if (BorderMan::busy  && shipOnPlanet)
		{
			b.negativeAns(*currentPlanet.second);
		}
	}
	if (Help::komenda == L"zeruj")
	{
		zeruj();
	}


	Help::flaga = false;
}

void MotherPlanet::odblokowanie() {
	for (auto planet : planets) {
		planet.second->SetBoolTrue();
		planet.second->visited = false;
	}
}

void zeruj()
{
	s.setMoney(0);
	s.SetStuff(0);
}