#include <iostream>
#include <string>


using std::string;


bool isCorrect(string str)
{
  int parenthesis_num = 0;
  for (int i = 0; i < str.length(); i++)
  {
    if (str.at(i) == '(')
      parenthesis_num++;
    else 
      parenthesis_num--;
    if (parenthesis_num < 0) return false;
  }
  if (parenthesis_num == 0)
    return true;
  else
    return false;
}

int getDividingIndex(string str)
{
  int left = 0, right = 0;
  for (int i = 0; i < str.length(); i++)
  {
    if (str.at(i) == '(')
      left++;
    else 
      right++;
    if (left == right)
      return ++i;
  }
  return str.length();
}

string process(string u, string v)
{
  // @test
  if (isCorrect(u)) std::cout <<  "U : " << u << " correct" << std::endl; 
  else std::cout <<  "U : " << u << " Incorrect" << std::endl; 
  std::cout << "V : " << v << std::endl << std::endl;
  // @test

  if (v == "") return u;
  if (!isCorrect(u))
  {
    
  }
  int dividing_index = getDividingIndex(v);
  return u + process(v.substr(0, dividing_index), v.substr(dividing_index));
}

int main()
{
  string input;
  std::cin >> input;
  string solution;
  int dividing_index = getDividingIndex(input);
  solution = process(input.substr(0, dividing_index), input.substr(dividing_index));
  std::cout << solution << std::endl;
  return 0;
}