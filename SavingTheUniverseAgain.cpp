#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdint>

using namespace std;

class Sequence
{
public:
	Sequence(string& s)
	{
		shots_.reserve(s.size());
		shots_.push_back(0u);
		for (char c : s)
		{
			if (c == 'S')
			{
				shots_.back()++;
			}
			else
			{
				shots_.push_back(0u);
			}
		}
		clearEnd();
	}
	
	int reduceToDamage(uint_fast64_t targetDamage)
	{
		uint_fast64_t currentDamage = calculateCurrentDamage();
		int numberOfSteps = 0;
		while (currentDamage > targetDamage && shots_.size() > 1)
		{
			const uint_fast64_t highestSlot = shots_.size() - 1u;
			const uint_fast64_t secondHighestSlot = highestSlot - 1u;
			const uint_fast64_t dmgReduction =
				calculateDmgForSlot(secondHighestSlot);
			shots_[highestSlot]--;
			shots_[secondHighestSlot]++;
			clearEnd();
			
			numberOfSteps++;
			currentDamage -= dmgReduction;
		}
		
		if (currentDamage <= targetDamage)
			return numberOfSteps;
		return -1;
	}

private:
	uint_fast64_t calculateCurrentDamage() const
	{
		uint_fast64_t damage = 0u;
		for (uint_fast64_t slot = 0u; slot < shots_.size(); ++slot)
		{
			damage += calculateDmgForSlot(slot) * shots_[slot];
		}
		return damage;
	}
	
	uint_fast64_t calculateDmgForSlot(uint_fast64_t slot) const
	{
		return pow(2.0, static_cast<double>(slot));
	}
	
	void clearEnd()
	{
		while (shots_.back() == 0u)
		{
			shots_.pop_back();
		}
	}
	
private:
	vector<uint_fast64_t> shots_;
};

int main()
{
	cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
	uint_fast64_t t;
	cin >> t;
	for (uint_fast64_t tNumber = 1u; tNumber < t + 1; ++tNumber)
	{
		uint_fast64_t targetDmg;
		cin >> targetDmg;
		string s;
		cin >> s;
		Sequence shotSequence(s);
		const int solution = shotSequence.reduceToDamage(targetDmg);
		cout << "Case #" << tNumber << ": ";
		if (solution == -1)
			cout << "IMPOSSIBLE";
		else
			cout << solution;
		cout << '\n';
	}
	return 0;
}
