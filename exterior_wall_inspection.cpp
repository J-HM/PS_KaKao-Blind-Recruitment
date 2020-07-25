#include <iostream>
#include <vector>

using namespace std;


int getMinimumDistance(int size, int first_index, int second_index)
{
  int big_index, small_index;
  if (first_index > second_index)
  {
    big_index = first_index;
    small_index = second_index;
  }
  else
  {
    big_index = second_index;
    small_index = first_index;
  }
  int distance = big_index - small_index;
  if (distance < size / 2)
    return distance;
  else
    return size - distance;
}


int solution(int n, vector<int> weak, vector<int> dist) {
  
  for (int i = 0; i < weak.size(); i++)
    for (int j = i + 1; j < weak.size(); j++)
      cout << i << " and " << j << " distance : " << getMinimumDistance(n, weak[i], weak[j]) << endl;
  int result = 0;

  return result;
}

int main()
{
  int n;
  vector<int> weak;
  vector<int> dist;
  n = 12;
  weak = {1, 5, 6, 10};
  dist = {1, 2, 3, 4};	

  auto result = solution(n, weak, dist);
  cout << result << endl;
  return 0;
}