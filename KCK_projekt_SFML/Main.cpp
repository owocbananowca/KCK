﻿#pragma once

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
Ship s; Pirate p1; BorderMan b;
map<wstring, Planet*> planets;
float dt;
pair<wstring, Planet*> currentPlanet;
bool shipOnPlanet = false;
bool busy = true;

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
		if (!shipOnPlanet)
		{
			for (auto planet : planets)
			{
				if (planet.second->onPlanet(s) && planet.first != L"OrionV")
				{
					planet.second->welcome(s, b);
					currentPlanet = planet;
					shipOnPlanet = true;
				}
			}
		}
		if (currentPlanet.second->onPlanet(s) == false)
		{
			shipOnPlanet = false;
			busy = false;
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


		p1.attack(s.getX(), s.getY(), s);
		money.display(s.getMoney());
		stuff.display(s.GetStuff());
		s.setTexture2();

		for (const auto& planet : planets)
		{
			planet.second->display();
		}
			
		s.display();
		
		Window::display();	

	}
	return 0;
}


void wykonaj_komende()
{
	
		if (Help::komenda == L"tak" && shipOnPlanet && !busy)
		{
			currentPlanet.second->shopingTime(s);
			busy = true;
		}
		if (Help::komenda == L"sprzedaj" && !busy)
		{
			int temp = (int)_wtof(Help::argument.c_str());
			currentPlanet.second->positiveAns(temp, s);
			busy = true;
		}
	
	if (Help::komenda == L"leć")
	{
		
		if (Help::argument == L"lewo" || Help::argument == L"prawo" || Help::argument == L"góra" || Help::argument == L"dół")
		{	
			if (s.isStuckv2 == false )
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
			cout << "pirat";
			p1.positiveAnswer(s);
		}
		if (BorderMan::busy)
		{
			for (const auto& a : planets)
			{
				if (a.second->onPlanet(s))
				{
					cout << "granicznik";
					b.positiveAns(*a.second,s);
				}
			}
		}

	}


	Help::flaga = false;
}

void MotherPlanet::odblokowanie() {
	for (auto planet : planets) {
		planet.second->SetBoolTrue();
		planet.second->visited = false;
	}
}