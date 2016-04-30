/*
  Tanner Gower

  This program enumerates all simple graphs with n vertices. It saves these
  graphs as a text file in the form of an adjacency matrix.

  When this program enumerates all possible combinations of 0s and 1s, it only
  focuses on the entries above the diagonal.

    So when these combinations are generated, this is the matrix generated:

              0 1 1 1                     0 1 0 1
              1 0 1 1   =   111111        1 0 0 1   =   101010
              1 1 0 1                     0 0 0 0
              1 1 1 0                     1 1 0 0
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void PrintMatrices(const string bin, const int len, const int &n, int &count)
{
  if (len == 0) {
    char mat[n][n];

    // Set diagonal to 0 because we are only interested in simple graphs
    for (int i = 0; i < n; i++)
      mat[i][i] = '0';

    // Fill matrix symmetrically because it's a simple graph
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        mat[i][j] = bin[k];
        mat[j][i] = bin[k];
        k++;
      }
    }

    count++;

    stringstream ss;
    ss << "n" << n << "g" << count << ".txt";

    ofstream fout(ss.str().c_str());

    // print matrix
    fout << n << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        fout << mat[i][j] << " ";
      }
      fout << endl;
    }
    return;
  }

  PrintMatrices(bin + "0", len - 1, n, count);
  PrintMatrices(bin + "1", len - 1, n, count);
}

int main ()
{
  int n,
      c = 0,
      sum = 0;

  string bin = ""; // Binary string of 0s and 1s

  cout << "n = ";
  cin >> n;

  for (int i = 1; i < n; i++)
    sum += i; // Size of each combination

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  PrintMatrices(bin, sum, n, c);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>( t2 - t1 ).count();

  double milli = duration / 1000.0;

  cout << "Finished in " << milli << " ms" << endl
       << "Number of simple graphs: " << c << endl;


  return 0;
}
