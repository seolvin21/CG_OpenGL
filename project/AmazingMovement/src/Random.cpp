#include "Random.h"
using namespace std;

CRandom::CRandom() : gen{rd()}
{
}

CRandom::~CRandom()
{

}

int CRandom::get(size_t start, size_t end)
{
	uniform_int_distribution<size_t> dist(start, end);

	return dist(this->gen);
}

int CRandom::get(int start, int end)
{
	uniform_int_distribution<int> dist(start, end);

	return dist(this->gen);
}

float CRandom::get(float start, float end)
{
	std::normal_distribution<float> dist(start, end);

	return dist(this->gen);
}
