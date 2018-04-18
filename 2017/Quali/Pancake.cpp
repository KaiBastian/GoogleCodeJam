#include <iostream>
#include <vector>

using namespace std;

void solveCase(size_t t)
{
     size_t k;
     std::vector<bool> row;
     char c;
     while (true)
     {
         cin.get(c);
         if (c == '+')
             row.push_back(true);
         else if (c == '-')
             row.push_back(false);
         else if (c == '\n')
             continue;
         else
         {
             cin.unget();
             break;
         }
     }
     cin >> k;

     size_t flipps = 0;
     size_t rowLength = row.size();
     size_t currentP = 0;
     for (; currentP + k <= rowLength; ++currentP)
     {
         if (row[currentP] == false)
         {
             ++flipps;
             for (size_t i = 0; i < k; ++i)
             {
                 row[currentP + i] = !row[currentP + i];
             }
         }
     }

     cout << "Case #" << t << ": ";
     bool possible = true;
     for (size_t i = currentP; i < rowLength; ++i)
     {
         if (!row[i])
             possible = false;
     }

     if (!possible)
     {
         cout << "IMPOSSIBLE\n";
     }
     else
     {
         cout << flipps << '\n';
     }

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
