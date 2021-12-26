#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

void printMatrix(vector<vector<string>> matrix) {
    for (long unsigned int i = 0; i < matrix.size(); i++) {
        for (long unsigned int j = 0; j < matrix[i].size(); j++) {
            //cout << j << " ";
            cout << matrix[0][0] << " ";
        }
        //cout << i << " ";
        cout << endl;
    }
}

vector<vector<string>> readfile(string filename) {
  string lines;
  
  string source = "./files/" + filename;
  vector<vector<string>> matrix;
  vector<string> v_lines;
  std::stringstream ss;
  cout << source << endl;
  ifstream file(source);
  long unsigned int cols = 0;
  long unsigned int rows = 0;
  while (getline(file, lines)) {
    //std::cout << lines.size() << endl;

 
    string s_aux(lines);
    v_lines.push_back(s_aux);
    cout << v_lines.size() << endl;

    cols++;    
  }
    rows = v_lines.size() / cols;
    matrix.resize(cols, vector<string>(rows));

    for (long unsigned int i = 0; i < matrix.size(); i++) {
        for (long unsigned int j = 0; j < matrix[i].size(); j++) {            
            matrix[i][j] = (v_lines[(i * rows) + j]);
        }
    }

    file.close();
    return matrix;
}

bool isRepeated(vector<string> v, string str) {
  for (int i = 0; i < v.size(); i++) {
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
vector<string> readFile(string filename) {

  string lines;
  string source = "./files/" + filename;
  vector<string> words;
  string word;
  string delimiter = " ";
  size_t pos = 0;
  
  ifstream file(source);
  while (file >> word) {
    word = removePunctuation(word);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (isRepeated(words, word) == false) {
      words.push_back(word);
    } else {
      cout << "REPETIDA: " << word << endl;
    }
    
  }
  file.close();
  return words;
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
  vector<string> v_words;
  for (long unsigned int i = 0; i < filenames.size(); i++) {
    //vector<vector<string>> matrix = readFile(filenames[i]);
    //cout << matrix[1][0];
    // printMatrix(matrix);
    cout << filenames[i];
    v_words = readFile(filenames[i]);
    
  }
  for (unsigned int i = 0; i < v_words.size(); i++) {
    cout << v_words[i] << endl;
    }
}