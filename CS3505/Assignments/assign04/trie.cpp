/*
implementation of trie data structure for assign04.

By Reece Kalmar
02/07/2025
*/

#include "trie.h"
#include <cstddef>
#include <utility>

Trie::Trie() : isEnd(false), children{} {}

Trie::Trie(const Trie &other) : isEnd(other.isEnd) {
  for (size_t i = 0; i < 26; i++) {
    if (other.children[i]) {
      children[i] = new Trie(*other.children[i]);
    } else {
      children[i] = nullptr;
    }
  }
}

Trie::~Trie() {
  for (size_t i = 0; i < 26; i++) {
    delete children[i];
    children[i] = nullptr;
  }
}

Trie &Trie::operator=(Trie other) {
  std::swap(isEnd, other.isEnd);
  std::swap(children, other.children);
  return *this;
}

bool Trie::isValidChar(char chr) const {
  int index = chr - 'a';
  return (index >= 0 && index <= 'z' - 'a');
}

void Trie::addWord(const std::string &word, size_t pos) {
  if (pos == word.size()) {
    isEnd = true;
    return;
  }

  int index = word[pos] - 'a';
  if (!children[index]) {
    children[index] = new Trie();
  }
  children[index]->addWord(word, pos + 1);
}

void Trie::addWord(const std::string &word) {
  if (word.empty()) {
    return;
  }

  addWord(word, 0);
}
bool Trie::isWord(const std::string &word, size_t pos) const {
  if (pos == word.size()) {
    return isEnd;
  }

  if (!isValidChar(word[pos])) {
    return false; // Ensure invalid characters return false immediately
  }

  int index = word[pos] - 'a';
  if (children[index]) {
    return children[index]->isWord(word, pos + 1);
  }

  return false;
}

bool Trie::isWord(const std::string &word) const {
  if (word.empty())
    return false;

  return isWord(word, 0);
}

void Trie::allWords(const std::string &word,
                    std::vector<std::string> &words) const {
  if (isEnd) {
    words.push_back(word);
  }
  for (int i = 0; i < 26; i++) {
    if (children[i]) {
      children[i]->allWords(word + (char)('a' + i), words);
    }
  }
}

std::vector<std::string>
Trie::allWordsStartingWithPrefix(const std::string &prefix) const {
  const Trie *temp = this;
  std::vector<std::string> words;

  for (char chr : prefix) {
    if (!isValidChar(chr)) {
      return words; // Return empty vector if invalid character is found
    }

    int index = chr - 'a';
    if (!temp->children[index]) {
      return words;
    }
    temp = temp->children[index];
  }

  temp->allWords(prefix, words);
  return words;
}
