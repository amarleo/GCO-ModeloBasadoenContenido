#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

bool isRepeated(vector<string> v, string str) {
  for (unsigned int i = 0; i < v.size(); i++) {
    if (v[i] == str) return true;
  }
  return false;
}

string removePunctuation(string str) {
  for(int i = 0, len = str.size(); i < len; i++) {
    if (ispunct(str[i])) {
      str.erase(i--, 1);
      len = str.size();
    }
  }
  return str;
}

void readFile(string filename, vector<string> &norepeated_words, vector<string> &original_words) {

  string lines;
  string source = "./files/" + filename;
  string word;
  
  ifstream file(source);
  while (file >> word) {
    word = removePunctuation(word);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (isRepeated(norepeated_words, word) == false) {
      norepeated_words.push_back(word);
    }
    original_words.push_back(word);
  }
  file.close();
}

vector<unsigned int> wordFrequency(vector<string> norepeated_words, vector<string> original_words) {
  vector<unsigned int> word_frequencies;
  unsigned int counter = 0;
  for (int i = 0; i < norepeated_words.size(); i++) {
    for (int j = 0; j < original_words.size(); j++) {
      if (norepeated_words[i] == original_words[j]) {
        counter++;
      }
    }
    word_frequencies.push_back(counter);
    counter = 0;
  }
  return word_frequencies;
}

int main(int argc, char** argv){

  int counter = 0;
  vector<string> filenames;
  //cout << "argc = " << argc << " argv = " << argv[2];
  for (int i = 0; i < argc; i++) {
    string aux = argv[i];
    int iterator = i;
    if ((aux == "-f") || (aux == "--file")) {
      iterator += 1;
      while (counter < argc - i - 1) {
        string str(argv[iterator]);
        filenames.push_back(str);
        counter++;
        iterator++;
      } 
    }
  }
  vector<string> norepeated_words, original_words;
  vector<unsigned int> word_frequencies;
  for (long unsigned int i = 0; i < filenames.size(); i++) {
    cout << filenames[i];
    readFile(filenames[i], norepeated_words, original_words);
    word_frequencies = wordFrequency(norepeated_words, original_words);
    for (unsigned int j = 0; j < word_frequencies.size(); j++) {
    cout << norepeated_words[j] << " " << word_frequencies[j] << endl;
    }
    
  }
  
}