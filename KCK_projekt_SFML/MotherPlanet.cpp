#pragma once
#include "stdafx.h"
#include "Planet.h"
#include "MotherPlanet.h"
#include "Console.h"
#include "Generator.h"

MotherPlanet::MotherPlanet(float x, float y, float numer)
{
	SetPrice(50);
	generatorIlosci();

	interactive = false;
	visited = true;	//ważne
	setTexture(numer);
	setPosition(x, y);
	isMotherPlanet = true;

}


MotherPlanet::~MotherPlanet()
{
}

void MotherPlanet::powitanieDom() {
	Console::putTextLine(L"Domowa Obsluga Naziemna >> Witaj w domu, dobrze Cię widzieć. Chcesz odkupić trochę świeżego towaru?");
	MotherPlanet::odblokowanie();
	//Odblokowanie wszystkich planet przy wizycie
}

void MotherPlanet::kupowanie(Ship& s) {
	s.isOnPlanet = true;
	if (s.GetStuff() == 0) {
		wstring temp2;
		wstring temp = to_wstring(GetPrice());
		wstring temp3 = to_wstring(ilosc);
		temp2 = L"Domowa Obsluga Naziemna >> Możemy Ci sprzedać " + temp3 + L" towaru po " + temp + L".";

		Console::putTextLine(temp2);
		Console::putTextLine(L"Domowa Obsluga Naziemna >> Czy chcesz kupić towar?");
	}
	else {
		Console::putTextLine(L"Domowa Obsluga Naziemna >> Jeszcze nie sprzedałeś poprzedniego towaru, wróć jak się go pozbędziesz.");
	}
}

void MotherPlanet::negativeAns(Ship& s) {
	Console::putTextLine(L"Domowa Obsluga Naziemna >> Nie to nie, żegnam.");
	s.isStuck = false;
}

void MotherPlanet::positiveAns(Ship& s,int i) {
	s.isStuck = false;
	if (s.getMoney() >= i * GetPrice() && s.GetStuff() == 0) {
		if (i == 0)
		{
			Console::putTextLine(L"Domowa Obsluga Naziemna >> Nie wiemy ile chcesz kupić!");
			s.isStuck = false;
		}
		else
		{
			s.setMoney(s.getMoney() - i * GetPrice());
			s.SetStuff(s.GetStuff() + i);
			ilosc = ilosc - i;
			Console::putTextLine(L"Domowa Obsluga Naziemna >> Zakupiłeś towar.");
			
			s.movementCounter = 0;
		}
	}
	else if (s.getMoney() <= i * GetPrice())
	{
		Console::putTextLine(L"Domowa Obsługa Naziemna >> Nie stać Cię!");
		Console::putTextLine(L"Domowa Obsługa Naziemna >> Spróbuj kupić mniejszą ilość!");
		s.isStuck = false;
	}
	else if (s.GetStuff() != 0)
	{
		Console::putTextLine(L"Domowa Obsługa Naziemna >> Posiadasz towar, sprzedaj go zanim do nas wrócisz5!");
		s.isStuck = false;
		s.isStuckv2 = false;
		s.movementCounter = 0;
	}
}

void MotherPlanet::generatorIlosci() {

ilosc = Generator::generate(15,80);
}