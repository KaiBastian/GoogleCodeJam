#include <iostream>

using namespace std;


// log k
void solveCase(size_t t)
{
     cout << "Case #" << t << ": ";
     size_t n,k;
     cin >> n >> k;
     if (k >= n)
     {
         cout << "0 0\n";
         return;
     }

     size_t base = n;
     size_t remainingK = k;
     size_t numberOfBase = 1;
     size_t numberOfOdd = base % 2 == 1 ? 1 : 0;
     while (true)
     {
         if (remainingK <= numberOfBase)
             break;

         remainingK = remainingK - numberOfBase;

         // How many odd numbers?
         const size_t numberOfEven = numberOfBase - numberOfOdd;
         switch (base % 4)
         {
             case 0:
                 numberOfOdd = numberOfEven;
                 break;
             case 1:
                 numberOfOdd = numberOfEven;
                 break;
             case 2:
                 numberOfOdd = numberOfEven + 2 * numberOfOdd;
                 break;
             case 3:
                 numberOfOdd = 2 * numberOfOdd + numberOfEven;
                 break;
         }

         base = (base - 1) / 2;
         numberOfBase = numberOfBase * 2;
     }

     size_t biggestGap;
     if (base % 2 == 1) // Even is bigger
     {
         const size_t numberOfEven = numberOfBase - numberOfOdd;
         if (remainingK <= numberOfEven)
             biggestGap = base + 1;
         else
             biggestGap = base;
     }
     else // Odd is bigger
     {
         if (remainingK <= numberOfOdd)
             biggestGap = base + 1;
         else
             biggestGap = base;
     }

     const size_t additionalSpaceInGap = biggestGap - 1;
     size_t min, max;
     min = additionalSpaceInGap / 2;
     max = additionalSpaceInGap / 2;

     const bool isOdd = additionalSpaceInGap % 2 == 1;
     if (isOdd)
         ++max;

     cout << max << ' ' << min << '\n';
}

int main()
{
     ios_base::sync_with_stdio(false);
     cin.tie(nullptr);

     size_t t;
     cin >> t;
     for (size_t i = 0; i < t; ++i)
     {
         solveCase(i+1);
     }
}
