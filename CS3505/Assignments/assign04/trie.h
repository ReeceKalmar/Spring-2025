#pragma once

#include <string>
#include <vector>
class Trie {
private:
  bool isEnd;

  Trie *children[26];

  bool isValidChar(char chr);

  void allWords(Trie temp, std::string word, std::vector<std::string> &words);

public:
  Trie();
  Trie(const Trie &other);
  ~Trie();
  Trie &operator=(Trie other);
  void addWord(std::string word);
  bool isWord(std::string word);
  std::vector<std::string> allWordsStartingWithPrefix(std::string prefix);
};
