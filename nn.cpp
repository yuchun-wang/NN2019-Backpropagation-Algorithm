#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int main() {

  int n = 2, q = 2, p = 1, k = 1, I = 1, round = 1;
  int desire[5] = {};
  double error[5] = {};
  double x[5][3] = {};
  double S_x[3] = {};
  double z[3] = {};
  double S_z[3] = {};
  double y[3] = {};
  double S_y[3] = {};
  double deltas_j[3] = {};
  double deltas_h[3] = {};
  double weight_i_h[3][3][3] = {}; //i=0,...n h=1,...q
  double weight_h_j[3][3][3] = {}; //h=0,...q j=1...p
  double difweight_i_h[3][3][3] = {};
  double difweight_h_j[3][3][3] = {};
  double learningrate = 0.5, a = 0.5, t = 0.001, e = 0;

  //Given
  fstream inFile;
  inFile.open("test.txt");

  if(!inFile.is_open()){
    cout << "no file.";
    exit(1);
  }
  else{
    for (int I = 1; I < 5; I++) {
      for (int i = 1; i < 3; i++)
        inFile >> x[I][i];
      inFile >> desire[I];
    }
    inFile.close();
  }

  //Initialize
  srand( time(NULL) );
  for(int i = 0; i <= n; i++){
    for(int h = 0; h <= q; h++){
      weight_i_h[k][i][h] = (double) rand() / RAND_MAX;
      difweight_i_h[0][i][h] = 0;
    }
  }

  for(int h = 0; h <= q; h++){
    for(int j = 0; j <= p; j++){
      weight_h_j[k][h][j] = (double) rand() / RAND_MAX;
      difweight_h_j[0][h][j] = 0;
    }
  }

  //Iterate
  do{
    I = 1, e = 0;
    cout << "[Interation " << round << "]\n";

    do{
      k = 1;

      for(int i = 1; i <= n; i++){
        S_x[i] = 0;
        z[i] = 0;
        S_z[i] = 0;
        y[i] = 0;
        S_y[i] = 0;
      }

      for(int i = 1; i <= n; i++)
        S_x[i] = x[I][i];
      S_x[0] = 1;

      for(int h = 1; h <= q; h++){
        for(int i = 0; i <= n; i++)
          z[h] = z[h] + (weight_i_h[k][i][h] * S_x[i]);
        S_z[h] = 1 / (1 + exp(-z[h]));
      }
      S_z[0] = 1;

      for(int j = 1; j <= p; j++){
        for(int h = 0; h <= q; h++)
          y[j] = y[j] + (weight_h_j[k][h][j] * S_z[h]);
        S_y[j] = 1 / (1 + exp(-y[j]));
      }

      for(int j = 1; j <= p; j++)
        deltas_j[j] = (desire[I] - S_y[j]) * (S_y[j] * (1 - S_y[j]));

      for (int h = 0; h <= q; h++) {
        for(int j = 1; j <= p; j++)
          difweight_h_j[k][h][j] = learningrate * deltas_j[j] * S_z[h] + (a * difweight_h_j[k-1][h][j]);
      }

      for(int h = 1; h <= q; h++){
        for(int j = 1; j <= p; j++)
          deltas_h[h] = deltas_h[h] + (deltas_j[j] * weight_h_j[k][h][j]);
        deltas_h[h] = deltas_h[h] * ((S_z[h]) * (1 - S_z[h]));
      }

      for (int i = 0; i <= n; i++) {
        for(int h = 1; h <= q; h++)
          difweight_i_h[k][i][h] = learningrate * deltas_h[h] * S_x[i] + (a * difweight_i_h[k-1][i][h]);
      }

      for(int h = 0; h <= q; h++){
        for(int j = 1; j <= p; j++){
          weight_h_j[k+1][h][j] = weight_h_j[k][h][j] + difweight_h_j[k][h][j] + (a * difweight_h_j[k-1][h][j]);
          weight_h_j[k][h][j] = weight_h_j[k+1][h][j];
          difweight_h_j[k-1][h][j] = difweight_h_j[k][h][j];
        }
      }

      for(int i = 0; i <= n; i++){
        for(int h = 1; h <= q; h++){
          weight_i_h[k+1][i][h] = weight_i_h[k][i][h] + difweight_i_h[k][i][h] + (a * difweight_i_h[k-1][i][h]);
          weight_i_h[k][i][h] = weight_i_h[k+1][i][h];
          difweight_i_h[k-1][i][h] = difweight_i_h[k][i][h];
        }
      }

      for(int j = 1; j <= p; j++)
        error[I] = ((desire[I] - S_y[j]) * (desire[I] - S_y[j])) * 0.5;
      e = e + error[I];

      cout << "\nX1: " << x[I][1] << "   X2: " << x[I][2]<< "   desired: " << desire[I] << " \nS_y: " << S_y[1] <<"\n";
      cout << "error: " << error[I] <<"\n\n";

      I++;

    } while (I < 5);

    e = e / 4;
    cout << "avg e:" << e <<"\n\n\n\n\n";
    round++;

  } while(e > t);
}
