#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include "loja.hpp"

int counterGlobal = 0;

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

void printVector(std::vector<int> v, int n) {
  for(int i = 0; i < n; i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;
}


std::vector<int> invertVec(std::vector<int> v, int n) {
  std::vector<int> invertedVec(n, 0);

  for(int i = 0; i < n; i++)
    invertedVec[i] = v[n-i-1];

  return invertedVec;
}

int lisBinarySearch(int* m, int key, int n) {
  int consideredStart = 0;
  int consideredEnd = n - 1;
  int half = 0;

  while(consideredStart - consideredEnd > 1) {
    half = (consideredStart + consideredEnd)/2;
    if(m[half] > key)
      consideredEnd = half - 1;
    else if (m[half] < key)
      consideredStart = half;
  } 

  return consideredStart;
}

// std::vector<int> LIS(std::vector<int> v, int n) {
//   int* m = (int*) malloc(n * sizeof(int));
//   m[0] = -(std::numeric_limits<int>::max());
//   for(int i = 1; i < n; i++)
//     m[i] = std::numeric_limits<int>::max();

//   std::vector<int> lis(n, 0);
//   int resp = 0;
//   for(int i = 1; i < n; i++) {
//     int j = lisSearch(m, v[i], n);
//     lis[i] = j+1;
//     m[j+1] = min(m[j+1], v[i]);
//     resp = max(resp, lis[i]);
//   }

//   return lis;
// }

std::vector<int> LIS(std::vector<int> v, int n) {
  std::vector<int> lis(n, 1);
  lis[0] = 1;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < i; j++){
      if(v[i] > v[j]) {
        lis[i] = max(lis[i], lis[j] + 1);
      }
    }
  }

  return lis;
}

// int ldsBinarySearch(int* m, int key, int n) {
//   int consideredStart = 0;
//   int consideredEnd = n - 1;
//   int half = 0;

//   while(consideredStart - consideredEnd > 1) {
//     half = (consideredStart + consideredEnd)/2;
//     if(m[half] > key)
//       consideredEnd = half;
//     else if (m[half] < key)
//       consideredStart = half - 1;
//   } 

//   return consideredStart;
// }

// std::vector<int> LDS(std::vector<int> v, int n) {
//   int* m = (int*) malloc(n * sizeof(int));
//   m[0] = -(std::numeric_limits<int>::max());
//   for(int i = 1; i < n; i++)
//     m[i] = std::numeric_limits<int>::max();

//   std::vector<int> lds(n, 0);
//   int resp = 0;
//   for(int i = 1; i < n; i++) {
//     int j = ldsSearch(m, v[i], n);
//     lds[i] = j+1;
//     m[j+1] = max(m[j+1], v[i]);
//     resp = max(resp, lds[i]);
//   }

//   return lds;
// }

std::vector<int> LDS(std::vector<int> v, int n) {
  std::vector<int> lds(n, 1);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < i; j++){
      if(v[j] > v[i]) {
        lds[i] = max(lds[i], lds[j] + 1);
      }
    }
  }

  return lds;
}

int getMaxRollsDesc(std::vector<int> v, int n) {
  std::vector<int> lds = LDS(invertVec(v, n), n);
  std::vector<int> lis = LIS(invertVec(v, n), n);
  int maxSummed = 0;
  
  for(int i = 0; i < n; i++) {
    maxSummed = max(maxSummed, lds[i] + lis[i]);
  }

  return maxSummed - 1;
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
    // std::cout << "chamadas -> " << counterGlobal << std::endl;
    // std::cout << "n -> " << numOfRolls << std::endl;
    counterGlobal = 0;

    // std::cout << "vector " << i << " -> ";
    // for(int roll : silkRolls)
    //   std::cout << roll << " ";
    // std::cout << std::endl;
  }

  return(0);
}
