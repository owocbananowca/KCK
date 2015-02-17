#pragma once
class MotherPlanet : public Planet
{
public:
	MotherPlanet(float x, float y, float numer);
	~MotherPlanet();

	int ilosc;
	//bool kupowanie = false;
	
	
	void powitanieDom();

	void kupowanie(Ship& s);

	void positiveAns(Ship& s,int i);
	void negativeAns(Ship& s);

	void odblokowanie();

	void generatorIlosci();
};

/*
int cena; <- Planet

*/