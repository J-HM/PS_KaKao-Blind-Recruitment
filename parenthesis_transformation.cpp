#include <iostream>
#include <string>


using std::string;

bool isCorrect(string& str)
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

int getDividingIndex(string& str)
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

string getOppositeParentheses(const string& str)
{
  string output = "";
  for (auto& chr : str)
  {
    if (chr == '(')
      output += ')';
    else 
      output += '(';
  }
  return output;
}

string process(string u, string v)
{
  if (u == "") return "";
  int dividing_index = getDividingIndex(v);
  if (!isCorrect(u))
  {
    string output = "";
    output += "(";
    output += process(v.substr(0, dividing_index), v.substr(dividing_index));
    output += ")";
    output += getOppositeParentheses(u).substr(1, u.length() - 2);
    return output;
  }
  else
  {
    return u + process(v.substr(0, dividing_index), v.substr(dividing_index));
  }
}

int main()
{
  string input;
  std::cin >> input;
  int dividing_index = getDividingIndex(input);
  string output = process(input.substr(0, dividing_index), input.substr(dividing_index));;
  std::cout << output << std::endl;
  return 0;
}