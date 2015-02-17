#include "stdafx.h"
#include "Human.h"
#include "Ship.h"
#include "Pirate.h"
#include "Console.h"
#include "Generator.h"


unsigned int Pirate::chance;
bool Pirate::busy = false;


void Pirate::attack(int x, int y, Ship &s)
{

	if (((x % 70 == 0 || y % 70 == 0) && chance <= 10) && s.isStuck == false && s.wasAttacked == false)
	{
		
		s.isStuck = true; // <-- Bez tego dzia³a konsola :(
		s.setPosition(x, y);
		wstring text, temp2;
		temp2 = to_wstring(Pirate::GetPrice());
		Pirate::busy = true;
		text = L"Piraci >> Zapłać " + temp2 + L" albo spadaj!";
		Console::putTextLine(text);
		s.wasAttacked = true;
	}

}

Pirate::Pirate()
{

	chance = Generator::generate();

	SetPrice(220);
}


Pirate::~Pirate()
{
}

/*void Pirate::action(Ship& statek){
	//cout << "Zaplac " << Pirate::GetPrice() << " albo spadaj!\n";
	wstring text, temp2;
	temp2 = to_wstring(Pirate::GetPrice());
	text = L"Zaplac " + temp2 + L" albo spadaj!";
	Console::putTextLine(text);
	int  temp = 1;
	cin >> temp;
	if ((temp == 1) && (Pirate::GetPrice() < statek.getMoney())) {
	cout << "Dobra, lec\n";
	statek.setMoney(statek.getMoney() - Pirate::GetPrice());
	statek.isStuck = false;
	}
	else {
	cout << "Nie pokazuj sie tu wiecej,  frajerze!\n";
	statek.SetStuff(0);
	statek.isStuck = false;
	}
	}
	
}*/
void Pirate::negativeAnswer(Ship& statek) {
	Console::putTextLine(L"Piraci >> Nie pokazuj sie tu wiecej, frajerze!");
	statek.SetStuff(0);
	statek.isStuck = false;
	Pirate::busy = false;
}

void Pirate::positiveAnswer(Ship& statek) {
	if (Pirate::GetPrice() < statek.getMoney()) {
		Console::putTextLine(L"Piraci >> Dobra, leć");
		Pirate::busy = false;
		statek.setMoney(statek.getMoney() - Pirate::GetPrice());
		statek.isStuck = false;
	}
	else {
		negativeAnswer(statek);
	}
}
