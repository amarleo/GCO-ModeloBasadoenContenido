#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

void printMatrix(vector<vector<string>> matrix) {
    for (long unsigned int i = 0; i < matrix.size(); i++) {
        for (long unsigned int j = 0; j < matrix[i].size(); j++) {
            //cout << j << " ";
            cout << matrix[i][j] << " ";
        }
        //cout << i << " ";
        cout << endl;
    }
}

vector<vector<string>> readFile(string filename) {
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
        for (unsigned int i = 0; i < lines.size(); i++) {
            
            if (lines[i] != ' ') {
                string s_aux(1, lines[i]);

                v_lines.push_back(s_aux);

            }
            
        }   
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

int main(int argc, char** argv){

  int counter = 0;
  vector<string> filenames;
  cout << "argc = " << argc << " argv = " << argv[2];
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
}