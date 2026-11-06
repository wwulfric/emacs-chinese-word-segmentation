// tested compilers:
// general  g++:        g++ -Icppjieba/deps/limonp/include -Icppjieba/include -O3 -o cnws cnws.cpp
// debian   g++-12:     [-std=c++17]
// debian   clang++-14: -std=c++17
// cygwin   g++-11:     [-std=c++17]
// cygwin   clang++-8:  -std=c++17
// termux   clang++-15: [-std=c++11 | -std=c++14]

#include <algorithm>
#include <iostream>
#include <csignal>

#include "cppjieba/Jieba.hpp"

using namespace std;

int main(int argc, char** argv) {
  signal(SIGINT, exit);

  if (argc < 6) {
    fprintf(stderr, "Usage:\n\
  %s <DICT_PATH> <HMM_PATH> <USER_DICT_PATH> <IDF_PATH> <STOP_WORD_PATH>\n", argv[0]);
    exit (EXIT_FAILURE);
  }

  const char* const DICT_PATH       = argv[1];
  const char* const HMM_PATH        = argv[2];
  const char* const USER_DICT_PATH  = argv[3];
  const char* const IDF_PATH        = argv[4];
  const char* const STOP_WORD_PATH  = argv[5];

  cppjieba::Jieba jieba(
		  DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH
		  );
  vector<string> words;
  string s;

  cout << "Chinese word segmentation" << endl;
  cout << "=========================" << endl;

  while (getline (cin, s)) {
    if (!s.empty() && s.back() == '\r') s.erase(s.size() - 1);
    if (s == "EOF") {
      break;
    } else {
      jieba.Cut(s, words, true);
      cout << words << ": ";
      for (unsigned int i = 0; i < words.size(); i++) {
        cout << count_if(words[i].begin(), words[i].end(),
                         [](unsigned char byte) { return (byte & 0xc0) != 0x80; }) << " ";
      }
      cout << endl;
    }
  }
  return EXIT_SUCCESS;
}
