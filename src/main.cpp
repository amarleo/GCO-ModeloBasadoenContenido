#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <iomanip>

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

unsigned int maxCols(vector<vector<string>> v) {
  unsigned int max = 0;
  for (unsigned int i = 0; i < v.size(); i++) {
    if (v[i].size() > max) {
      max = v[i].size();
    }
  }
  return max;
}

vector<vector<string>> copyMatrix(vector<vector<string>> v1, vector<vector<string>> v2) {
  for (unsigned int i = 0; i < v1.size(); i++) {
    for (unsigned int j = 0; j < v1[i].size(); j++) {
      v2[i][j] = v1[i][j];
    }
  }
  return v2;
}

int fileError() {
  return -1;
}

void readFile(string filename, vector<string> &norepeated_words, vector<string> &original_words) {

  string lines;
  string source = "./files/" + filename;
  string word;
  
  ifstream file(source);
  if (!file) {
    cerr << "ERROR: el nombre del fichero " << filename << " es erróneo o no se ha podido abrir.";
  }
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
  for (long unsigned int i = 0; i < norepeated_words.size(); i++) {
    for (long unsigned int j = 0; j < original_words.size(); j++) {
      if (norepeated_words[i] == original_words[j]) {
        counter++;
      }
    }
    word_frequencies.push_back(counter);
    counter = 0;
  }
  return word_frequencies;
}

vector<vector<double>> IDF(vector<vector<string>> files_words) {
  string word;
  unsigned int counter = 0;
  vector<vector<double>> v_idf;
  v_idf.resize(files_words.size(), vector<double>(maxCols(files_words)));
  for (unsigned int i = 0; i < files_words.size(); i++) {    
    for (unsigned int j = 0; j < files_words[i].size(); j++) {
      word = files_words[i][j];
      counter = 0;
      for (unsigned int k = 0; k < v_idf.size(); k++) {
        auto finder = find(files_words[k].begin(), files_words[k].end(), word);
        if (files_words[k].end() != finder) {
          counter += 1;
        }
      }
      v_idf[i][j] = counter;
    }
  }

  for(unsigned int i = 0; i < v_idf.size(); i++) {
    for(long unsigned int j = 0; j < v_idf[i].size(); j++) {
      if (files_words[i][j].empty() == false)  {
        float result = static_cast<float>(v_idf.size()) / v_idf[i][j];
        v_idf[i][j] = log10(result);
      }
    }
    cout << "\n";
  }
  return v_idf;
}

void printMatrixTable(vector<vector<string>> files_words, vector<vector<unsigned int>> files_frequency,
                      vector<vector<double>> idf) {

  for(unsigned int i = 0; i < files_words.size(); i++) {
    cout << "\t- - - File number " << i+1 << " - - -\nIndex\tTerm\t\tTF\t\tIDF\t\tTF-IDF\n";
    for(long unsigned int j = 0; j < files_words[i].size(); j++) {
      if (files_words[i][j].empty() == false)  {
        cout << j << ".\t";
        if (files_words[i][j].size() > 7) {
          cout << files_words[i][j] << "\t" << files_frequency[i][j] << "\t\t";
        } else {
          cout << files_words[i][j] << "\t\t" << files_frequency[i][j] << "\t\t"; 
        }
        cout << setprecision(5) << idf[i][j] << "\t\t" << files_frequency[i][j] * idf[i][j] << "\n";
      }
    }
  cout << "\n";
  }
  
}

void csvMode(vector<vector<string>> files_words, vector<vector<unsigned int>> files_frequency,
            vector<vector<double>> idf, vector<string> filenames) {
  fstream fout; 
  string file;
  
    for(unsigned int i = 0; i < files_words.size(); i++) {
      fout.open("./csv/" + filenames[i] + ".csv", ios::out);
      if(fout) {
      fout << "Index,Term,Tf,IDF,TF_IDF\n";
      for(long unsigned int j = 0; j < files_words[i].size(); j++) {
          if (files_words[i][j].empty() == false)  {
            fout << j << "," << files_words[i][j] << "," << files_frequency[i][j] << "," 
                << setprecision(5) << idf[i][j] << "," << setprecision(5) <<  files_frequency[i][j] * idf[i][j] << "\n";
          }
        }
      }
      cout << "CSV file " << filenames[i] << ".csv created\n";
      fout.close();
    }
  
  
}

int main(int argc, char** argv){

  int counter = 0;
  bool csv = false;
  vector<string> filenames, norepeated_words, original_words;
  vector<unsigned int> word_frequencies;
  vector<vector<string>> files_words, aux;
  vector<vector<unsigned int>> files_frequency;
  vector<vector<double>> idf;
  
  for (int i = 0; i < argc; i++) {
    string aux = argv[i];
    int iterator = i;
    if ((aux == "-f") || (aux == "--file")) {
      iterator += 1;
      while (counter < argc - i - 1) {
        string str(argv[iterator]);
        if (str[0] == '-') break;
        filenames.push_back(str);
        counter++;
        iterator++;
      } 
    }
    if ((aux == "-c") || (aux == "--csv")) {
      csv = true;
    }
    // RECONFIGURAR MENÚ
    if ((aux == "-h") || (aux == "--help")) {
      cout << "AYUDA";
    }
  }

  for (long unsigned int i = 0; i < filenames.size(); i++) {
    readFile(filenames[i], norepeated_words, original_words);
    word_frequencies = wordFrequency(norepeated_words, original_words);
    aux.push_back(norepeated_words);
    files_frequency.push_back(word_frequencies);
    norepeated_words.clear();
    word_frequencies.clear();
    original_words.clear();
  }
  files_words.resize(aux.size(), vector<string>(maxCols(aux)));
  files_words = copyMatrix(aux, files_words); 
  idf = IDF (files_words);
  printMatrixTable(files_words, files_frequency, idf);

  if (csv == true) {
    csvMode(files_words, files_frequency, idf, filenames);
  }
}