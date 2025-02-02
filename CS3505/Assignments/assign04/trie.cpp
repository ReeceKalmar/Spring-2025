#include "trie.h"
#include <cstddef>

Trie::Trie() : children{}, isEnd(false) {}

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
  }
}

Trie &Trie::operator=(Trie other) {
  std::swap(children, other.children);
  std::swap(isEnd, other.isEnd);

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

  if (isValidChar(word[pos])) {
    int index = word[pos] - 'a';
    if (children[index]) {
      return children[index]->isWord(word, pos + 1);
    }
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
    int index = chr - 'a';
    if (!isValidChar(chr) || !temp->children[index]) {
      return words;
    }
    temp = temp->children[index];
  }

  temp->allWords(prefix, words);
  return words;
}
