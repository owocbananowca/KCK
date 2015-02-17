#include "stdafx.h"
#include "Generator.h"



//koñcowy_projekt

int Generator::generate(int from, int to)
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	default_random_engine generator(seed);
	uniform_int_distribution<unsigned> distribution(from, to);

	auto chance = distribution(generator);

	return chance;
}

Generator::Generator()
{
}


Generator::~Generator()
{
}
