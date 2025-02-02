#include "trie.h"

Trie::Trie() : children{}, isEnd(false) {}

Trie::Trie(const Trie &other) { *this = other; }

Trie::~Trie() {}

Trie &Trie::operator=(Trie other) {
  std::swap(children, other.children);
  std::swap(isEnd, other.isEnd);

  return *this;
}

bool Trie::isValidChar(char chr) {
  int index = chr - 'a';
  return (index >= 0 && index <= 'z' - 'a');
}

void Trie::addWord(std::string word) {
  if (!word.empty()) {
    int index = word.back() - 'a';
    if (!children[index]) {
      children[index] = new Trie();
    }
    word.pop_back();

    if (word.empty()) {
      children[index]->isEnd = true;
      return;
    }
    children[index]->addWord(word);
  }
}

bool Trie::isWord(std::string word) {
  if (!word.empty()) {
    int chr = word.back();
    int index = chr - 'a';
    if (isValidChar(chr)) {
      if (children[index]) {
        word.pop_back();
        if (word.empty()) {
          return children[index]->isEnd;
        }
        return children[index]->isWord(word);
      }
    }
  }

  return false;
}

void Trie::allWords(Trie temp, std::string word,
                    std::vector<std::string> &words) {
  if (temp.isEnd) {
    words.push_back(word);
  }
  for (int i = 0; i < 26; i++) {
    if (temp.children[i]) {
      std::string copy = word;
      copy.push_back('a' + i);
      allWords(*temp.children[i], copy, words);
    }
  }
}

std::vector<std::string> Trie::allWordsStartingWithPrefix(std::string prefix) {
  std::vector<std::string> words;
  Trie temp = *this;
  while (!prefix.empty() && isValidChar(prefix.back())) {
    int index = prefix.back() - 'a';

    if (!temp.children[index])
      return words;

    temp = *temp.children[index];
    prefix.pop_back();
  }

  allWords(temp, prefix, words);
  return words;
}
