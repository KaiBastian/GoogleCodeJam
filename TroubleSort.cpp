#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdint>
#include <algorithm>

using namespace std;


int solveFast(vector<unsigned>& a, vector<unsigned>& b)
{
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	
	for (unsigned i = 0; i < a.size(); ++i)
	{
		const unsigned bIndex = i;
		if (bIndex < b.size())
		{
			if (b[bIndex] < a[i])
				return 2 * i;
		}
		const unsigned aIndex = i + 1;
		if (aIndex < a.size() && i < b.size())
		{
			if (a[aIndex] < b[i])
				return 2 * i + 1;
		}
	}
	
	return -1;
}

int main()
{
	cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
	uint_fast64_t t;
	cin >> t;
	for (uint_fast64_t tNumber = 1u; tNumber < t + 1; ++tNumber)
	{
		unsigned numElements;
		cin >> numElements;
		vector<unsigned> a;
		vector<unsigned> b;
		a.reserve(numElements / 2 + 1);
		b.reserve(numElements / 2);
		for (unsigned i = 0; i < numElements; ++i)
		{
			unsigned elem;
			cin >> elem;
			if (i % 2 == 0)
				a.push_back(elem);
			else
				b.push_back(elem);
		}
		
		const int solution = solveFast(a, b);
		cout << "Case #" << tNumber << ": ";
		if (solution == -1)
		{
			cout << "OK";
		}
		else
		{
			cout << solution;
		}
		cout << '\n';
	}
	return 0;
}
