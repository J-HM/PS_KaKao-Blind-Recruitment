#include <iostream>
#include <vector>


using namespace std;

int getRealQueryCount(string& str)
{
  int real_query_count = 0;
  for (auto chr : str) 
    if (chr != '?') 
      real_query_count++;
  return real_query_count;
}

int getRealQueryFrontIndex(string& str)
{
  int real_query_front_index = 0;
  for (auto chr : str)
  {
    if (chr != '?')
      return real_query_front_index;
    real_query_front_index++;
  }
  return real_query_front_index;
}

vector<int> solution(vector<string> words, vector<string> queries) {
  vector<int> results;
  for (auto query : queries)
  {
    int match_count = 0;
    int real_query_count = getRealQueryCount(query);
    int real_query_front_index = getRealQueryFrontIndex(query);
    string real_query = query.substr(real_query_front_index, real_query_count);
    for (auto word : words)
    {
      if (query.length() == word.length()) 
      {
        if (real_query_count == 0)
          match_count++;
        else if (word.substr(real_query_front_index, real_query_count) == real_query)
          match_count++;
      }
    }
    results.push_back(match_count);
  }
  return results;
}

int main()
{
  vector<string> words;
  vector<string> queries;

  words = {"frodo", "front", "frost", "frozen", "frame", "kakao"};
  queries = {"???", "?????", "??????", "frost", "pro?"};

  auto results = solution(words, queries);

  for (auto result : results)
    cout << result << ", ";
  cout << endl;
}