#include <iostream>
#include <vector>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

class Pancake
{
public:
    Pancake(double radius, double hight)
    : radius_(radius), hight_(hight)
    {
    }

    double valueAsBotton() const
    {
        return valueAsElement() + M_PI * radius_ * radius_;
    }

    double valueAsElement() const
    {
        return 2.0 * M_PI * radius_ * hight_;
    }

public:
    double radius_;
    double hight_;
};

void solveCase(size_t t)
{
    cout << "Case #" << t << ": ";

    size_t n,k;
    cin >> n >> k;

    vector<Pancake> pancakes;

    for (size_t i = 0; i < n; ++i)
    {
        double radius, hight;
        cin >> radius  >> hight;
        pancakes.push_back(Pancake(radius, hight));
    }

    auto elementSort = [] (const Pancake& lhs, const Pancake& rhs)
    {
        return lhs.valueAsElement() > rhs.valueAsElement();
    };

    sort(pancakes.begin(), pancakes.end(), elementSort);

    double bestResult = 0;
    for (size_t bottomIndex = 0; bottomIndex < n; ++bottomIndex)
    {
        double thisResult = pancakes[bottomIndex].valueAsBotton();
        const double towerMaxRadius = pancakes[bottomIndex].radius_;
        size_t numberOfUsedPancakes;
        size_t i;
        for (numberOfUsedPancakes = 0, i = 0; i < n; ++i)
        {
            if (bottomIndex == i) // can't consider bottom twice;
                continue;
            if (pancakes[i].radius_ > towerMaxRadius)
                continue;

            if (numberOfUsedPancakes == k - 1) // all slots used
                break;

            thisResult += pancakes[i].valueAsElement();
            ++numberOfUsedPancakes;
        }
        if (numberOfUsedPancakes == k - 1)
            bestResult = max(bestResult, thisResult);
    }

    cout << bestResult << '\n';
}

int main()
{
     ios_base::sync_with_stdio(false);
     cin.tie(nullptr);

     cout.precision(9);
     cout << fixed;

     size_t t;
     cin >> t;
     for (size_t i = 0; i < t; ++i)
     {
         solveCase(i+1);
     }
}
