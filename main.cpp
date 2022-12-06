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

  if(!left && !right) {
    return max(ALG(v, i+1, v[i], v[i], M) + 1, ALG(v, i+1, left, right, M));
    // M[i][left] = max(ALG(v, i+1, v[i], v[i], M) + 1, ALG(v, i+1, left, right, M));
    // M[i][right] = M[i][left];
    // return M[i][left];
  }

  if(v[i] > left) {
    // std::cout << "1 -> [" << i << ", " << left << "]" << std::endl;
    // if(M[i][left] != -1 && left != -1) return M[i][left];

    // M[i][left] = max(ALG(v, i-1, v[i], _right, M) + 1, ALG(v, i-1, left, right, M));

    // return M[i][left];

    if(M[i][left] != -1) return M[i][left];

    M[i][left] = max(ALG(v, i+1, v[i], right, M) + 1, ALG(v, i+1, left, right, M));
    return M[i][left]; 
  } else if(v[i] < right) {
    // std::cout << "2 -> [" << i << ", " << right << "]" << std::endl;
    // if(M[i][right] != -1 && right != -1) return M[i][right];

    // M[i][right] = max(ALG(v, i-1, _left, v[i], M) + 1, ALG(v, i-1, left, right, M));

    // return M[i][right];
    // if(M[i][right] != -1) return M[i][right];

    return max(ALG(v, i+1, left, v[i], M) + 1, ALG(v, i+1, left, right, M));

    // M[i][right] = max(ALG(v, i+1, left, v[i], M) + 1, ALG(v, i+1, left, right, M));
    // return M[i][right]; 
  } else {
    // std::cout << "3 -> [" << i << ", " << right << "]" << std::endl;
    // std::cout << "4 -> [" << i << ", " << left << "]" << std::endl;

    // M[i][left] = ALG(v, i-1, _right, _left, M);
    // M[i][right] = M[i][left];

    // return M[i][left];
    // if(M[i][left] != -1 || M[i][right] != -1) {
    //   if(M[i][left] >= M[i][right]) return M[i][left];
    //   if(M[i][right] >= M[i][left]) return M[i][right];
    // }

    return ALG(v, i+1, left, right, M);
    // M[i][left] = ALG(v, i+1, left, right, M);
    // M[i][right] = M[i][left];
    // return M[i][left];
  }
}

int getMaxRollsDesc(std::vector<int> v, int n) {
  int** M = (int**) malloc(n * sizeof(int*));
  for(int i = 0; i < n; i++) {
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
    std::cout << std::endl;

    // std::cout << "vector " << i << " -> ";
    // for(int roll : silkRolls)
    //   std::cout << roll << " ";
    // std::cout << std::endl;
  }

  return(0);
}
