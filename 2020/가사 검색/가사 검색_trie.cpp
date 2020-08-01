#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 26; 

struct TrieNode
{
  TrieNode* childs[ALPHABET_SIZE];
  int child_count;
  bool is_end;

  TrieNode() : is_end(false), child_count(0)
  {
    for (auto& child : childs)
      child = nullptr;
  }

  ~TrieNode()
  {
    for (auto& child : childs)
      if (child != nullptr)
        delete child;
  }

  static void insert(TrieNode* trie_node, const string& string_value)
  {
    for (auto character : string_value)
    {
      int index = character - 'a';
      if (trie_node->childs[index] == nullptr) 
        trie_node->childs[index] = new TrieNode(); 
      trie_node->child_count++;
      trie_node = trie_node->childs[index];
    }
    trie_node->is_end = true;
  }

  static int getMatchingCount(TrieNode* trie_node, const string& string_value)
  {
    int matching_count = 0;
    for (auto character : string_value)
    {
      if (trie_node == nullptr)
        return 0;
      if (character == '?')
        return trie_node->child_count;
      int index = character - 'a';
      trie_node = trie_node->childs[index];
    }
    return 1;
  }
};

vector<int> solution(vector<string> words, vector<string> queries)
{
  vector<int> results;
  vector<TrieNode *> positive_roots(10000, nullptr); 
  vector<TrieNode *> negative_roots(10000, nullptr); 
  for (auto& word : words)
  {
    int word_length = word.length();
    if (positive_roots[word_length] == nullptr)
      positive_roots[word_length] = new TrieNode;
    TrieNode::insert(positive_roots[word_length], word);
  }
  for (auto& word : words)
  {
    reverse(word.begin(), word.end());
    int word_length = word.length();
    if (negative_roots[word_length] == nullptr)
      negative_roots[word_length] = new TrieNode;
    TrieNode::insert(negative_roots[word_length], word);
  }
  for (auto& query : queries)
  {
    if (query.front() != '?')
    {
      int matching_count = TrieNode::getMatchingCount(positive_roots[query.length()], query);
      results.push_back(matching_count);
    }
    else
    {  
      reverse(query.begin(), query.end());
      int matching_count = TrieNode::getMatchingCount(negative_roots[query.length()], query);
      results.push_back(matching_count);
    }
  }
  for (auto root : positive_roots) delete root;
  for (auto root : negative_roots) delete root;
  return results;
}

int main()
{
  vector<string> words;
  vector<string> queries;
  
  words = {"frodo", "front", "frost", "frozen", "frame", "kakao"};
  queries = {"fro??"};

  auto results = solution(words, queries);

  for (auto result : results)
    cout << result << ", ";
  cout << endl;
}