#include "stdafx.h"
#include "Help.h"
#include "BorderMan.h"
#include "Pirate.h"

Ship* Help::statek;
float * Help::dt;
map<wstring, Planet*> Help::planety;
wstring Help::komenda;
wstring Help::argument;
bool Help::flaga = false;

Help::Help()
{
}


Help::~Help()
{
}

std::vector<std::wstring> Help::tokenize(const std::wstring& source)
{
	std::wistringstream iss(source);
	std::vector<std::wstring> tokens;
	std::move(std::istream_iterator<std::wstring, wchar_t, std::char_traits<wchar_t>>(iss),
		std::istream_iterator<std::wstring, wchar_t, std::char_traits<wchar_t>>(),
		std::back_inserter(tokens));
	return tokens;
}



int Help::ssearch(wstring a, wstring b) //(gdzie, szukany)
{
	unsigned int present;
	for (auto i = 0; i < a.length(); i++)
	{
		for (auto j = i; j < a.length(); j++)
		{
			present = 0;
			for (auto k = 0; k < b.length() && (j + k)<a.length(); k++)
			{
				if (a[j + k] == b[k])
				{
					present++;
				}
				if (present == b.length())
				{
					return j;
				}
			}
		}
	}
	return 1000;
}

std::wstring Help::textAnalysis(std::wstring text)
{
	//slownik

	vector<wstring> bezargumentowe = {L"zeruj", L"wita", L"cześć", L"siem", L"hej", L"doberek", L"płać", L"sprzedaj", L"tak", L"nie", L"stop", L"kup" };
	vector<wstring> przeklenstwa = { L"kurw", L"jeb", L"pierd", L"chuj", L"dziwk"};
	vector<wstring> operatory = { L"leć" };
	vector<wstring> latanie = {  L"OrionV", L"prawo", L"lewo", L"gór", L"dół", L"Merkury", L"Uran", L"Jowisz", L"Neptun", L"matk" };
	vector<vector<wstring>*> wskazniki = { &latanie };

	
	vector<wstring> tokens = tokenize(text);

	//analiza

	//ugrzeczniacz
	int j = 0;
	int k = 0;
	while (j < tokens.size())
	{
		k = 0;
		while (k <przeklenstwa.size() && ssearch(tokens.at(j), przeklenstwa.at(k)) == 1000)
		{
			k++;
		}
		if (k == przeklenstwa.size()) //nie bylo operatora, nastepne slowo
		{
			j++;
		}
		else
		{
			return L"Nie! Grzeczniej prosze!";
		}
	}


	//wyszukiwanie bezargumentowych
	j = 0;
	k = 0;
	while (j < tokens.size())
	{
		k = 0;
		while (k < bezargumentowe.size() && ssearch(tokens.at(j), bezargumentowe.at(k)) == 1000)
		{
			k++;
		}
		if (k == bezargumentowe.size()) //nie bylo operatora, nastepne slowo
		{
			j++;
		}
		else if (ssearch(tokens.at(j), L"płać") != 1000)
		{
			if (Pirate::busy == true || BorderMan::busy == true)
			{
				komenda = L"płać";
				flaga = true;
				statek->isStuck = false;
				return L"Płacimy, Kapitanie!";
			}
			else
			{
				return L"Kapitanie, nie ma komu płacić!";
			}
		}
		else if (ssearch(tokens.at(j), L"stop") != 1000)
			 {
			
				komenda = L"stop";
				statek->movementCounter = 0;
				flaga = false;
				statek->isStuck = false;
				return L"Stop Kapitanie!";
			
			}
		else if (ssearch(tokens.at(j), L"tak") != 1000)
		{
			komenda = L"tak";
			flaga = true;
			return L"Przekazujemy komendę do kontroli naziemnej";
		}
		else if (ssearch(tokens.at(j), L"nie") != 1000)
		{
			komenda = L"nie";
			flaga = true;
			return L"Przekazujemy komendę do rozmówcy";
		}
		else if (ssearch(tokens.at(j), L"kup") != 1000)
		{
			if (statek->isOnPlanet)
			{
				komenda = L"kup";
				if (tokens.size() <= (j + 1))
				{
					return L"Musisz podać ilość jednostek towaru, którą chcesz kupić!";
				}
				else
				{
					if (tokens.at(j + 1) == L"towar")
					{
						argument = L"100";
					}
					else
					{
						argument = tokens.at(j + 1);
					}
					flaga = true;
					return L"Kupujemy " + argument + L" jednostek towaru!";
				}
			}
			else return L"Nie ma komu sprzedać!";
		}
		else if (ssearch(tokens.at(j), L"sprzedaj") != 1000)
		{
			if (statek->isOnPlanet)
			{
				komenda = L"sprzedaj";
				if (tokens.size() <= (j + 1))
				{
					return L"Musisz podać ilość jednostek towaru, którą chcesz sprzedać!";
				}
				else
				{
					if (tokens.at(j + 1) == L"towar")
					{
						argument = L"100";
					}
					else
					{
						argument = tokens.at(j + 1);
					}
					flaga = true;
					return L"Sprzedajemy " + argument + L" jednostek towaru!";
				}
			}
			else return L"Nie ma komu sprzedać!";
		}
		else
		{
			komenda = tokens.at(j);
			return tokens.at(j) + L" Kapitanie!";
		}
	}
	j = 0;
	k = 0;
	//wyszukiwanie operatorow
	while (j < tokens.size())
	{
		k = 0;
		while (k<operatory.size() && ssearch(tokens.at(j), operatory.at(k)) == 1000)
		{
			k++;
		}
		if (k == operatory.size()) //nie bylo operatora, nastepne slowo
		{
			j++;
		}
		else //byl operator, szukamy argumentu
		{
			for (auto i = j; i < tokens.size(); i++)//slowa po operatorze
			{
				for (auto l = 0; l < (*wskazniki.at(k)).size(); l++)
				{
					if (ssearch(tokens.at(i), (*wskazniki.at(k)).at(l)) != 1000)
					{
						//wywolanie funkcji operator z argumentem 
						komenda = operatory.at(k);//tokens.at(j);
						argument = (*wskazniki.at(k)).at(l);//tokens.at(i);
						flaga = true;

						//////
						statek->isStuckv2 = false;
						//////
						return L"Wykonuję komendę \"" + tokens.at(j) + L" " + tokens.at(i) + L"\"";
					}
				}

			}
		
			return L"Komenda \"" + tokens.at(j) + L"\" wymaga argumentu!";
			j++;
		}
	}
	return L"Komenda nieznana";
}

void Help::podaj_statek(Ship * st, float * time, map<wstring, Planet*> planets)
{
	statek = st;
	dt = time;
	planety = planets;
}
