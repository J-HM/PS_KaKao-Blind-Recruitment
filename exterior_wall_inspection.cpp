#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int size;
vector<int> weaks;
vector<int> dists;


int getWeaksDistance(int first_index, int second_index)
{
  if (second_index > first_index)
    return weaks[second_index] - weaks[first_index];
  else if (second_index == first_index)
    return 0;
  else
    return size + weaks[second_index] - weaks[first_index];
}

// int inspection(int weak_index, int dist_index, int remaining_weaks_count)
// {
//   if (remaining_weaks_count == 0) 
//     return 1;
//   int insepction_size = dists.at(dist_index);
//   int next_weak_index = weak_index + 1;
//   while(next_weak_index < weaks.size() + weak_index)
//   {
//     next_weak_index++;
//     int distance = getWeaksDistance(weak_index, next_weak_index);
//     if (distance < insepction_size)
//       break;
//   }
//   return 1 + inspection(next_weak_index, dist_index, remaining_weaks_count - 1);
// }

int inspection()
{
  
  for (int i = 0; i < weaks.size(); i++)
  {
  
    for (int j = i; j < weaks.size() + i; j++)
    {

    }

  }
}

int solution(int input_size, vector<int> input_weaks, vector<int> input_dists)
{
  size = input_size;
  weaks = input_weaks;
  dists = input_dists;

  sort(dists.begin(), dists.end(), greater<int>()); // Reverse dists
  
  int inspection_count = inspection(0, 0, weaks.size());
  return inspection_count;
}

int main()
{
  int size;
  vector<int> weaks;
  vector<int> dists;
  size = 12;
  weaks = {1, 5, 6, 10};
  dists = {1, 2, 3, 4};	

  auto result = solution(size, weaks, dists);
  cout << result << endl;
  return 0;
}