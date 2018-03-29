#include "BOT.cpp"

bool testAreSorted()
{
	bool results[3];
	bool expectedResults[3] = { true,true,false };
	BOT<double> t({ 0.1, 0.2, 0.3, 0.33, 0.33 });
	results[0] = t.areSorted();
	t.add(0.33);
	results[1] = t.areSorted();
	t.add(0.329);
	results[2] = t.areSorted();
	for (int i = 0; i < 3; i++)
		if (results[i] != expectedResults[i])
			return false;
	return true;	
}
bool testInversions()
{
	BOT<int> t({ 1,1,1,2,1,1,1,3,2,-1 });
	int expectedInversions = 13;
	return expectedInversions == t.getInversions();
}

int main()
{
	std::cout << testAreSorted() << "\n";
	std::cout << testInversions();
	std::cin.get();
	return 0;
}