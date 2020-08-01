#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

vector<string> divideInputByIndex(const string& input, int index)
{
  vector<string> pieces;
  for (int i = 0; i < input.length(); i += index)
    pieces.push_back(input.substr(i , index));
  std::cout << "Index " << index << " : "; // @test
  for (int i = 0; i < pieces.size(); i++)  // @test
    std::cout << pieces.at(i) << " ";      // @test
  return pieces;
}

int getCompressedCapacity(const string& input, int index)
{
  vector<string> pieces = divideInputByIndex(input, index);
  int compressed_capacity = 0;
  int i, j;
  for (i = 0; i < pieces.size(); i += j)
  {
    compressed_capacity += pieces.at(i).length();
    for (j = 1; i + j < pieces.size(); j++)
    {
      if (pieces.at(i) != pieces.at(i + j))
        break;
    }
    if (j != 1)
      compressed_capacity += std::to_string(j).length();
  }
  std::cout << " Capacity : " << compressed_capacity; // @test
  std::cout << std::endl;                             // @test
  return compressed_capacity;
}

int main()
{
  string input;
  std::cin >> input;
  int output = input.length();
  for (int i = 1; i <= input.length()/2; i++)
  {
    int result = getCompressedCapacity(input, i);
    if (output > result)
      output = result;
  }
  std::cout << output << std::endl;
  return 0;
}