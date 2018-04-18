#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

void makeNonDecreasing(vector<int>& number)
{
     if (number.size() == 1)
         return;

     auto current = prev(number.end());
     const auto begin = number.begin();
     const auto end = number.end();
     while (current != begin)
     {
         auto pre = prev(current);
         const bool preTooLarge = *pre > *current;
         if (preTooLarge)
         {
             --(*pre);
             for (auto it = current; it != end; ++it)
             {
                 *it = 9;
             }
         }
         current = pre;
     }
}

void print(size_t t, vector<int>& number)
{
     cout << "Case #" << t << ": ";
     for (auto i : number)
     {
         if (i == 0)
             continue;

         cout << i;
     }
     cout << '\n';
}

void solveCase(size_t t)
{
     vector<int> number;
     string line;
     getline(cin, line);
     stringstream ss(line);
     char c;
     while(ss >> c)
         number.push_back(static_cast<int>(c - '0'));

     makeNonDecreasing(number);
     print(t, number);
}

int main()
{
     ios_base::sync_with_stdio(false);
     cin.tie(nullptr);

     string line;
     getline(cin, line);
     stringstream ss(line);
     size_t t;
     ss >> t;
     for (size_t i = 0; i < t; ++i)
     {
         solveCase(i+1);
     }
}
