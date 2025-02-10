/*
Tests the trie data structure for assign04.

By Reece Kalmar
02/07/2025
*/

#include "trie.h"
#include <fstream>
#include <iostream>

/*
 * Loads words from a file and inserts them into the Trie.
 */
void loadWordsIntoTrie(const std::string &filename, Trie &trie) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << "\n";
    return;
  }

  std::string word;
  while (std::getline(file, word)) {
    trie.addWord(word);
  }

  file.close();
}

/*
 * Reads queries from a file, checks if they are in the Trie,
 * and prints the results to an output file.
 */
void processQueries(const std::string &filename, Trie &trie,
                    const std::string &outputFile) {
  std::ifstream file(filename);
  std::ofstream outFile(outputFile);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << "\n";
    return;
  }
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file: " << outputFile << "\n";
    return;
  }

  std::string query;
  while (std::getline(file, query)) {
    outFile << "Checking " << query << ":\n";
    if (trie.isWord(query)) {
      outFile << "Word found\n";
    } else {
      outFile << "Word not found\n";
    }

    std::vector<std::string> words = trie.allWordsStartingWithPrefix(query);
    for (const std::string &word : words) {
      outFile << word << " ";
    }
    outFile << "\n";
  }

  file.close();
  outFile.close();
}

/*
 * Tests the Rule-of-Three implementation for Trie.
 */
void testRuleOfThree(std::ofstream &outFile) {
  outFile << "\n--- Testing Rule-of-Three Methods ---\n";

  // Create a Trie and insert words
  Trie firstTrie;
  firstTrie.addWord("cat");
  firstTrie.addWord("car");
  firstTrie.addWord("dog");

  // Test copy constructor
  Trie secondTrie(firstTrie);
  outFile << "Second Trie created via copy constructor. Should contain 'cat', "
             "'car', and 'dog'.\n";

  // Test assignment operator
  Trie thirdTrie = secondTrie;
  outFile << "Third Trie assigned from Second Trie. Should also contain 'cat', "
             "'car', and 'dog'.\n";

  // Modify secondTrie and check it does not affect firstTrie
  secondTrie.addWord("bat");
  outFile << "Added 'bat' to secondTrie. Checking if firstTrie has it: "
          << (firstTrie.isWord("bat") ? "Yes" : "No") << "\n";

  // Modify thirdTrie and check it does not affect secondTrie
  thirdTrie.addWord("fish");
  outFile << "Added 'fish' to thirdTrie. Checking if secondTrie has it: "
          << (secondTrie.isWord("fish") ? "Yes" : "No") << "\n";

  outFile << "--- Rule-of-Three Test Completed ---\n";
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <wordlist file> <query file> <output file>\n";
    return 1;
  }

  Trie trie;

  loadWordsIntoTrie(argv[1], trie);
  processQueries(argv[2], trie, argv[3]);

  std::ofstream outFile(argv[3], std::ios::app);
  if (!outFile.is_open()) {
    std::cerr << "Error opening output file for Rule-of-Three tests.\n";
    return 1;
  }

  testRuleOfThree(outFile);

  outFile.close();

  return 0;
}
