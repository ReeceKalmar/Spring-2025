#pragma once

#include <string>
#include <vector>
class Trie {
private:
  bool isEnd;

  Trie *children[26];

  bool isValidChar(char chr) const;

  void allWords(const std::string &word, std::vector<std::string> &words) const;

  void addWord(const std::string &word, size_t pos);

  bool isWord(const std::string &word, size_t pos) const;

public:
  Trie();
  Trie(const Trie &other);
  ~Trie();
  Trie &operator=(Trie other);
  void addWord(const std::string &word);
  bool isWord(const std::string &word) const;
  std::vector<std::string>
  allWordsStartingWithPrefix(const std::string &prefix) const;
};
