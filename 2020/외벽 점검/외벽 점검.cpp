#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int size;
vector<int> weaks;
vector<int> dists;

vector<vector<int>> getNewWeaks()
{
  vector<vector<int>> new_weakss;
  for (int i = 0; i < weaks.size(); i++)
  {
    vector<int> new_weaks;
    for (int j = i; j < weaks.size() + i; j++)
    {
      if (j < weaks.size())
        new_weaks.push_back(weaks[j]);
      else
        new_weaks.push_back(weaks[j - weaks.size()] + size);
    }
    new_weakss.push_back(new_weaks);
  }
  return new_weakss;
}

bool inspect(vector<int>& new_dists, vector<vector<int>>& new_weakss)
{
  do
  {
    for (auto new_weaks : new_weakss)
    {
      int new_weaks_index = 0;
      int new_dists_index = 0;
      int new_weaks_size = new_weaks.size();
      int new_dists_size = new_dists.size();
      while(new_weaks_index < new_weaks_size && new_dists_index < new_dists_size)
      {
        int current_value = new_weaks[new_weaks_index] + new_dists[new_dists_index];
        new_dists_index++;
        while (new_weaks_index < new_weaks_size)
        {
          if (new_weaks[new_weaks_index] > current_value)
            break;
          else
            new_weaks_index++;
        }
        if (new_weaks_index == new_weaks_size) 
          return true;
      }
    }
  }
  while (prev_permutation(new_dists.begin(), new_dists.end()));
  return false;
}

int solution(int input_size, vector<int> input_weaks, vector<int> input_dists)
{
  size = input_size;
  weaks = input_weaks;
  dists = input_dists;
  sort(dists.begin(), dists.end(), greater<int>()); // Reverse dists
  auto new_weakss = getNewWeaks();
  for (int i = 1; i < dists.size() + 1; i++)
  {
    vector<int> new_dist(dists.begin(), dists.begin() + i);
    if (inspect(new_dist, new_weakss))
      return i;
  }
  return -1;
}

int main()
{
  int size;
  vector<int> weaks;
  vector<int> dists;
  size = 1;
  weaks = {0};
  dists = {1};	

  auto result = solution(size, weaks, dists);
  cout << result << endl;
  return 0;
}