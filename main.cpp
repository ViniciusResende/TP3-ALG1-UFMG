#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "loja.hpp"


void printMatrix(int** M, int rows, int columns) {
  // print columns identifiers
  printf("%9s"," ");
  for (int i = 0; i < columns; i++) printf("%8d ", i);
  printf("\n");

  for (int i = 0; i < rows; i++) {
    printf("%8d ", i);
    for(int j = 0; j < columns; j++) {
      printf("%8d ", M[i][j]);
    }
    printf("\n");
  }
}

int max(int a, int b) {
  return a > b ? a : b;
}

int ALG(std::vector<int> v, int i, int left, int right, int** M) {
  if(i == v.size())
    return 0;

  if(M[left][right] != -1) return M[left][right];

  if(!left && !right) {    
    M[left][right] = max(ALG(v, i+1, v[i], v[i], M) + 1, ALG(v, i+1, left, right, M));
    return M[left][right];
  }

  if(v[i] > left) {
    M[left][right] = max(ALG(v, i+1, v[i], right, M) + 1, ALG(v, i+1, left, right, M));
    return M[left][right]; 
  } else if(v[i] < right) {
    M[left][right] = max(ALG(v, i+1, left, v[i], M) + 1, ALG(v, i+1, left, right, M));
    return M[left][right]; 
  } else {
    M[left][right] = ALG(v, i+1, left, right, M);
    return M[left][right];
  }
}

int getMaxRollsDesc(std::vector<int> v, int n) {
  int** M = (int**) malloc((n+1) * sizeof(int*));
  for(int i = 0; i < n+1; i++) {
    M[i] = (int*) malloc((n+1) * sizeof(int));
    for(int j = 0; j < n+1; j++)
      M[i][j] = -1;
  }

  // printMatrix(M, n, n+1);

  int a = ALG(v, 0, 0, 0, M);

  // printMatrix(M, n, n+1);

  return a;
}

int main() {
  unsigned int testCasesAmount = 0;
  unsigned int numOfRolls = 0;
  unsigned int currentBeingReadRoll = 0;

  std::cin >> testCasesAmount;

  for(unsigned int i = 0; i < testCasesAmount; i++) {
    std::cin >> numOfRolls;
    std::vector<int> silkRolls(numOfRolls, 0);

    for(unsigned int j = 0; j < numOfRolls; j++) {
      std::cin >> currentBeingReadRoll;
      silkRolls[j] = currentBeingReadRoll;
    }

    std::cout << getMaxRollsDesc(silkRolls, numOfRolls) << std::endl;

    // std::cout << "vector " << i << " -> ";
    // for(int roll : silkRolls)
    //   std::cout << roll << " ";
    // std::cout << std::endl;
  }

  return(0);
}
