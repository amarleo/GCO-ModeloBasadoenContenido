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
#include <stdlib.h>

using namespace std;

// Método que comprueba si un vector contiene el string indicado por argumento. 
bool isRepeated(vector<string> v, string str) {
  for (unsigned int i = 0; i < v.size(); i++) {
    if (v[i] == str) return true;
  }
  return false;
}

// Dados un string, comprueba si hay signos de puntuacion y los elimina.
string removePunctuation(string str) {
  for(int i = 0, len = str.size(); i < len; i++) {
    if (ispunct(str[i])) {
      str.erase(i--, 1);
      len = str.size();
    }
  }
  return str;
}

// Dada una matriz, devuelve el mayor tamaño de sus filas. 
unsigned int maxCols(vector<vector<string>> v) {
  unsigned int max = 0;
  for (unsigned int i = 0; i < v.size(); i++) {
    if (v[i].size() > max) {
      max = v[i].size();
    }
  }
  return max;
}

// Método que copia una matriz en otra.
vector<vector<string>> copyMatrix(vector<vector<string>> v1, vector<vector<string>> v2) {
  for (unsigned int i = 0; i < v1.size(); i++) {
    for (unsigned int j = 0; j < v1[i].size(); j++) {
      v2[i][j] = v1[i][j];
    }
  }
  return v2;
}

// Método que lee los ficheros situados en /files
void readFile(string filename, vector<string> &norepeated_words, vector<string> &original_words) {

  string lines;
  string source = "./files/" + filename;
  string word;
  
  ifstream file(source);
  if (!file) {
    cerr << "\nERROR: file name '" << filename << "' does not exist or is not readable." << endl;
    exit(1);
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

// Método que devuelve un vector con el número de repeticiones por cada palabra de un fichero
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

// Método que calcula el IDF
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

// Método que imprime la tabla resultado
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

// Método que crea y rellena los ficheros CSV
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
    cout << "CSV file '" << filenames[i] << ".csv' created\n";
    fout.close();
  }
}

// Método que calcula la longitud del vector
vector<double> vectorLength(vector<vector<double>> idf) {
  vector<double> idf_length;
  double result = 0;
  for (unsigned int i = 0; i < idf.size(); i++) {
    result = 0;
    for (unsigned int j = 0; j < idf[i].size(); j++) {
      result = result + (pow(idf[i][j], 2));
    }
    result = sqrt(result);
    idf_length.push_back(result);
  }
  return idf_length;
}

// Método que normaliza el Vector
vector<vector<double>> normalizeVector(vector<vector<double>> idf, vector<double> idf_length) {
  vector<vector<double>> normalizedMatrix;
  normalizedMatrix.resize(idf.size(), vector<double>(idf[0].size()));
  for (unsigned int i = 0; i < idf.size(); i++) {
    for (unsigned int j = 0; j < idf[i].size(); j++) {
      normalizedMatrix[i][j] = (idf[i][j] / idf_length[i]);
    }
  }
  return normalizedMatrix;
}

// Método que reliza la similitud coseno de entre todos los ficheros.
void cosineValues(vector<vector<double>> normalizedMatrix, unsigned int size, vector<vector<string>> files_words) {
  unsigned int aux = 1;
  double result = 0;
  vector<double> cosine_values;
  for (unsigned int i = 0; i < size; i++) {
    aux = i+1;
    while (aux < size) {
        result = 0;
        for (unsigned int j = 0; j < normalizedMatrix[0].size(); j++) {
          for (unsigned int k = 0; k < normalizedMatrix[0].size(); k++) {
            if ((files_words[i][j] == (files_words[aux][k]) && (files_words[i][j].empty() == false))) {
              result = result + (normalizedMatrix[i][j] * normalizedMatrix[aux][k]);
            }
          }
        }
      cout << "cos(A" << i << ", A" << aux << ") = " << setprecision(5) << result << endl;
      cosine_values.push_back(result);
      aux++;
    }
  }
}

// Metodo ayuda
void help() {
  cout << "\nContent-based Filtering\nThis app filters files data and find out the similarity between all introduced txt files. Then, it prints the results on terminal and/or on a csv file\n"
      << "\nTo compile: 'make' or 'g++ -g src/main -o app_name'"
      << "\nusage: app_name [options] input1 input2 (...)"
      << "\n\t-f, --file: One or more file inputs could be placed before this option."
      << "Important: Only the files between this option and another will be redeabled."
      << "\n\t-c, --csv: This option puts the output of the app into an .csv file at the csv directory."
      << "\n\t-h, --help: Prints help table." << endl;
}

// Programa principal
int main(int argc, char** argv){

  int counter = 0;
  bool csv = false, flag = false;
  vector<string> filenames, norepeated_words, original_words;
  vector<unsigned int> word_frequencies;
  vector<vector<string>> files_words, aux;
  vector<vector<unsigned int>> files_frequency;
  vector<vector<double>> idf, normalized_matrix;
  vector<double> vector_length;
  
  for (int i = 0; i < argc; i++) {
    string aux = argv[i];
    int iterator = i;
    if ((aux == "-f") || (aux == "--file")) {
      flag = true; 
      iterator += 1;
      while (counter < argc - i - 1) {
        string str(argv[iterator]);
        if (str[0] == '-') break;
        filenames.push_back(str);
        counter++;
        iterator++;
      }
      if (filenames.size() == 0) {
        cout << "ERROR: There are no files specified by arguments. Check --help command";
        help();
        return -1;
      }
    }
    else if ((aux == "-c") || (aux == "--csv")) {
      csv = true;
      flag = false;
    }
    else if ((aux == "-h") || (aux == "--help")) {
      help();
      flag = false;
      return 0;
    }
    else {
      if (aux[0] == '-') {
        cout << "\nERROR: Command " << aux << " does not exist. Please, enter valid command." << endl;
        help();
        return -1;
      }
      else if ((flag == false) && (aux != "./sist_recomendacion")) {
        cout << "ERROR: Wrong file order, please follow the instructions below" << endl;
        help();
        return -1;
      }
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

  vector_length = vectorLength(idf);
  normalized_matrix = normalizeVector(idf, vector_length);
  cosineValues(normalized_matrix, filenames.size(),files_words);


  if (csv == true) {
    csvMode(files_words, files_frequency, idf, filenames);
  }
}