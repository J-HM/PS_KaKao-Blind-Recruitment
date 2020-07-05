#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using std::vector;
using std::string;
using std::multimap;

vector<string> getPiecesVector(const vector<char>& input_chars, int index)
{
  vector<string> pieces;
  int i = 0;
  while (i + index < input_chars.size())
  {
    pieces.push_back(string(input_chars.begin() + i, input_chars.begin() + i + index));
    i += index;
  }
  pieces.push_back(string(input_chars.begin() + i, input_chars.end()));
  return pieces;
}

multimap<string, int> getCountMapVector(const vector<string>& pieces)
{
  multimap<string, int> count_map;
  for (int j = 0; j < pieces.size();)
  {
    int k = 0;
    while (j + k < pieces.size())
    {
      if (pieces.at(j) != pieces.at(j + k))
        break;
      k++;
    }
    count_map.insert({pieces.at(j), k});
    j = j + k;
  }
  return count_map;
}

string compressString(const vector<char>& input_chars, int index)
{
  vector<string> pieces = getPiecesVector(input_chars, index);
  multimap<string, int> count_map = getCountMapVector(pieces);
  vector<string> compressed_strings;
  string compressed_string;
  for(const auto& element : count_map)
  {
    if (element.second != 1)
      compressed_string += std::to_string(element.second);
    compressed_string += element.first;
  }
  compressed_strings.push_back(compressed_string);
  string minimal_compressed_string(input_chars.begin(), input_chars.end());
  for (auto compressed_string : compressed_strings)
  {
    if (minimal_compressed_string.size() > compressed_string.size())
      minimal_compressed_string = compressed_string;
  }
  return minimal_compressed_string;
}

int main()
{
  string input_string;
  std::cin >> input_string;
  vector<char> input_chars(input_string.begin(), input_string.end());
  vector<string> output_strings;
  for (int i = 1; i <= input_chars.size()/2; i++)
    output_strings.push_back(compressString(input_chars, i));
  string minimal_string = input_string;
  for (auto output_string : output_strings)
    if (minimal_string.size() > output_string.size())
      minimal_string = output_string;
  std::cout << minimal_string.size() << std::endl;
  return 0;
}