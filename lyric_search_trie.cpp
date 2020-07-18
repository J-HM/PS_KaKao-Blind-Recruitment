#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Trie
{
public:
  Trie()
  {
    for (auto& child : childs)
      child = nullptr;
  }

  ~Trie()
  {
    for (auto& child : childs)
      if (child != nullptr)
        delete child;
  }

  void insert(const string& string_value)
  {
    if (string_value.front() == 0)
      return;
    int index = string_value.front() - 'a';
    if (childs[index] == nullptr)
      childs[index] = new Trie;
    childs[index]->insert(string_value.substr(1));
  }

  Trie* find(const string& string_value)
  {
		if(string_value.front() == 0)
			return this;
		int index = string_value.front() - 'a';
		if(childs[index] == nullptr)
			return NULL;
		return childs[index]->find(string_value.substr(1));
  }

  void print(const Trie* node)
  {

  }

private:
  Trie* childs[26];
};

vector<int> solution(vector<string> words, vector<string> queries)
{
  vector<int> results;
  Trie *root = new Trie;

  for (auto word : words)
    root->insert(word);

  if (root->find("frodo"))
    cout << "true" << endl;
  else
    cout << "false" << endl;
  delete root;
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