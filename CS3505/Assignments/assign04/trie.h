#pragma once

/*
Represents a trie data structure for assignment 4.

By Reece Kalmar
02/07/2025
*/

#include <string>
#include <vector>

/*
 * Trie class represents a prefix tree (Trie) used for storing and searching
 * words efficiently.
 */
class Trie {
private:
  bool isEnd; // Indicates whether this node marks the end of a valid word.
  Trie *children[26]; // Array of pointers to child nodes for each letter 'a' to
                      // 'z'.

  /*
   * Checks whether a given character is a lowercase letter between 'a' and 'z'.
   * Returns true if valid, false otherwise.
   */
  bool isValidChar(char chr) const;

  /*
   * Recursively retrieves all words stored in the Trie that start from the
   * current node. The found words are stored in the given vector.
   */
  void allWords(const std::string &word, std::vector<std::string> &words) const;

  /*
   * Recursively adds a word to the Trie.
   * The function processes one character at a time until the full word is
   * inserted.
   */
  void addWord(const std::string &word, size_t pos);

  /*
   * Recursively checks whether a given word exists in the Trie.
   * Returns true if the word is found, false otherwise.
   */
  bool isWord(const std::string &word, size_t pos) const;

public:
  /*
   * Constructs an empty Trie node.
   */
  Trie();

  /*
   * Copy constructor that creates a deep copy of another Trie.
   */
  Trie(const Trie &other);

  /*
   * Destructor that deallocates all dynamically allocated child nodes.
   */
  ~Trie();

  /*
   * Assignment operator that assigns one Trie to another, ensuring deep copy.
   */
  Trie &operator=(Trie other);

  /*
   * Inserts a word into the Trie.
   * If the word already exists, the Trie remains unchanged.
   */
  void addWord(const std::string &word);

  /*
   * Checks whether a given word exists in the Trie.
   * Returns true if the word is found, false otherwise.
   */
  bool isWord(const std::string &word) const;

  /*
   * Retrieves all words stored in the Trie that start with the given prefix.
   * If the prefix itself is a word, it is included in the result.
   * Returns a vector containing the matching words.
   */
  std::vector<std::string>
  allWordsStartingWithPrefix(const std::string &prefix) const;
};

