#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int isValid(int, int, int[] = NULL, int[][2] = NULL);
int isReflexive(int, int, int[] = NULL, int[][2] = NULL);
int isIdentity(int, int, int[] = NULL, int[][2] = NULL);
int isIrreflexive(int, int, int[] = NULL, int[][2] = NULL);
int isSymmetric(int, int, int[] = NULL, int[][2] = NULL);
int isAntisymmetric(int, int, int[] = NULL, int[][2] = NULL);
int isAsymmetric(int, int, int[] = NULL, int[][2] = NULL);
int isTransitive(int, int, int[] = NULL, int[][2] = NULL);
int isEquivalence(int, int, int[] = NULL, int[][2] = NULL);

int main(void) {
  int numS, numR;
  cout << "Number of elements in set S: ";
  cin >> numS;
  if(numS == 0) {
    system("cls");
    cout << "S = {}\n";
    numR = 0;
    cout << "R : S -> S\n";
    cout << "R = {}\n\n\n";
    if(isValid(numR, numS)) {
      if(isIdentity(numR, numS)) {
        cout << "R is IDENTITY relation!\n";
      } else {
        cout << "R is NOT IDENTITY relation!\n";
      }

      if(isReflexive(numR, numS)) {
        cout << "R is REFLEXIVE relation!\n";
      } else {
        cout << "R is NOT REFLEXIVE relation!\n";
      }

      if(isIrreflexive(numR, numS)) {
        cout << "R is IRREFLEXIVE relation!\n";
      } else {
        cout << "R is NOT IRREFLEXIVE relation!\n";
      }

      if(isSymmetric(numR, numS)) {
        cout << "R is SYMMETRIC relation!\n";
      } else {
        cout << "R is NOT SYMMETRIC relation!\n";
      }

      if(isAntisymmetric(numR, numS)) {
        cout << "R is ANTISYMMETRIC relation!\n";
      } else {
        cout << "R is NOT ANTISYMMETRIC relation!\n";
      }

      if(isAsymmetric(numR, numS)) {
        cout << "R is ASYMMETRIC relation!\n";
      } else {
        cout << "R is NOT ASYMMETRIC relation!\n";
      }
      if(isTransitive(numR, numS)) {
        cout << "R is TRANSITIVE relation!\n";
      } else {
        cout << "R is NOT TRANSITIVE relation!\n";
      }
      if(isEquivalence(numR, numS)) {
        cout << "R is EQUIVALENCE relation!\n";
      } else {
        cout << "R is NOT EQUIVALENCE relation!\n";
      }
    } else {
      cout << "\nInvalid Input" << "\n";
      return 1;
    }
  } else {
    int aryS[numS];
    for(int i = 0; i < numS; ++i) {
      if(i == 0) {
        cout << "S = {";
      }
      cin >> aryS[i];
      if(i != numS - 1) {
        cout << ",";
      } else {
        cout << "}";
      }
    }
    cout << "Number of pairs in relation R: ";
    cin >> numR;
    if(numR == 0) {
      system("cls");
      for(int i = 0; i < numS; ++i) {
        if(i == 0) {
          cout << "S = {";
        }
        cout << aryS[i];
        if(i != numS - 1) {
          cout << ",";
        } else {
          cout << "}";
        }
      }
      cout << "\nR : S -> S\n";
      cout << "R = {}\n\n\n";
      if(isValid(numR, numS)) {
        if(isIdentity(numR, numS, aryS)) {
          cout << "R is IDENTITY relation!\n";
        } else {
          cout << "R is NOT IDENTITY relation!\n";
        }

        if(isReflexive(numR, numS, aryS)) {
          cout << "R is REFLEXIVE relation!\n";
        } else {
          cout << "R is NOT REFLEXIVE relation!\n";
        }

        if(isIrreflexive(numR, numS, aryS)) {
          cout << "R is IRREFLEXIVE relation!\n";
        } else {
          cout << "R is NOT IRREFLEXIVE relation!\n";
        }

        if(isSymmetric(numR, numS, aryS)) {
          cout << "R is SYMMETRIC relation!\n";
        } else {
          cout << "R is NOT SYMMETRIC relation!\n";
        }

        if(isAntisymmetric(numR, numS, aryS)) {
          cout << "R is ANTISYMMETRIC relation!\n";
        } else {
          cout << "R is NOT ANTISYMMETRIC relation!\n";
        }

        if(isAsymmetric(numR, numS, aryS)) {
          cout << "R is ASYMMETRIC relation!\n";
        } else {
          cout << "R is NOT ASYMMETRIC relation!\n";
        }
        if(isTransitive(numR, numS, aryS)) {
          cout << "R is TRANSITIVE relation!\n";
        } else {
          cout << "R is NOT TRANSITIVE relation!\n";
        }
        if(isEquivalence(numR, numS, aryS)) {
          cout << "R is EQUIVALENCE relation!\n";
        } else {
          cout << "R is NOT EQUIVALENCE relation!\n";
        }
      } else {
        cout << "\nInvalid Input" << "\n";
        return 1;
      }
    }
    if(numR != 0) {
      int aryR[numR][2];
      cout << "\nR : S -> S\n";
      for(int i = 0; i < numR; ++i) {
        if(i == 0) {
          cout << "R = {(";
        } else {
          cout << "(";
        }
        for(int j = 0; j < 2; ++j) {
          cin >> aryR[i][j];
          if(j == 0) {
            cout << ",";
          }
        }
        if(i == numR-1) {
          cout << ")}";
        } else {
          cout << "), ";
        }
      }
      system("cls");
      for(int i = 0; i < numS; ++i) {
        if(i == 0) {
          cout << "S = {";
        }
        cout << aryS[i];
        if(i != numS - 1) {
          cout << ",";
        } else {
          cout << "}";
        }
      }
      cout << "\nR : S -> S\n";
      for(int i = 0; i < numR; ++i) {
        if(i == 0) {
          cout << "R = {(";
        } else {
          cout << "(";
        }
        for(int j = 0; j < 2; ++j) {
          cout << aryR[i][j];
          if(j == 0) {
            cout << ",";
          }
        }
        if(i == numR-1) {
          cout << ")}\n\n\n";
        } else {
          cout << "), ";
        }
      }
      if(isValid(numR, numS, aryS, aryR)) {
        if(isIdentity(numR, numS, aryS, aryR)) {
          cout << "R is IDENTITY relation!\n";
        } else {
          cout << "R is NOT IDENTITY relation!\n";
        }
        
        if(isReflexive(numR, numS, aryS, aryR)) {
          cout << "R is REFLEXIVE relation!\n";
        } else {
          cout << "R is NOT REFLEXIVE relation!\n";
        }

        if(isIrreflexive(numR, numS, aryS, aryR)) {
          cout << "R is IRREFLEXIVE relation!\n";
        } else {
          cout << "R is NOT IRREFLEXIVE relation!\n";
        }

        if(isSymmetric(numR, numS, aryS, aryR)) {
          cout << "R is SYMMETRIC relation!\n";
        } else {
          cout << "R is NOT SYMMETRIC relation!\n";
        }

        if(isAntisymmetric(numR, numS, aryS, aryR)) {
          cout << "R is ANTISYMMETRIC relation!\n";
        } else {
          cout << "R is NOT ANTISYMMETRIC relation!\n";
        }

        if(isAsymmetric(numR, numS, aryS, aryR)) {
          cout << "R is ASYMMETRIC relation!\n";
        } else {
          cout << "R is NOT ASYMMETRIC relation!\n";
        }
        if(isTransitive(numR, numS, aryS, aryR)) {
          cout << "R is TRANSITIVE relation!\n";
        } else {
          cout << "R is NOT TRANSITIVE relation!\n";
        }
        if(isEquivalence(numR, numS, aryS, aryR)) {
          cout << "R is EQUIVALENCE relation!\n";
        } else {
          cout << "R is NOT EQUIVALENCE relation!\n";
        }
      } else {
        cout << "\nInvalid Input" << "\n";
        return 1;
      }
    }
  }
  return 0;
}

int isValid(int numR, int numS, int aryS[], int aryR[][2]) {
  if(numS == 0) {
    if(numR == 0) {
      return 1;
    }
    return 0;
  } else if(numR == 0) {
    return 1;
  }
  int l = 0;
  for(int i = 0; i < numR; ++i) {
    for(int j = 0; j < 2; ++j) {
      l = 0;
      for(int k = 0; k < numS; ++k) {
        if(aryR[i][j] == aryS[k]) {
          l = 1;
          break;
        }
      }
      if(l == 0) {
        cout << aryR[i][j] << " is not in set S\n";
        break;
      }
    }
    if(l == 0) {
      break;
    }
  }
  return l;
}

int isReflexive(int numR, int numS, int aryS[], int aryR[][2]) {
  int k = 0;
  for(int i = 0; i < numS; ++i) {
    k = 0;
    for(int j = 0; j < numR; ++j) {
      if((aryR[j][0] == aryR[j][1]) && (aryR[j][0] == aryS[i])) {
        k = 1;
        break;
      }
    }
    if(k == 0) {
      cout << "(" << aryS[i] << ", " << aryS[i] << ") is NOT PRESENT that's why, ";
      break;
    }
  }
  if((numR == 0) && (numS == 0)) {
    return 1;
  }
  return k;
}

int isIdentity(int numR, int numS, int aryS[], int aryR[][2]) {
  if(isReflexive(numR, numS, aryS, aryR)) {
    for(int j = 0; j < numR; ++j) {
      if(aryR[j][0] != aryR[j][1]) {
        cout << "(" << aryR[j][0] << ", " << aryR[j][1] << ") is PRESENT that's why, ";
        return 0;
      }
    }
    return 1;
  } else {
    return 0;
  }
}

int isIrreflexive(int numR, int numS, int aryS[], int aryR[][2]) {
  for(int j = 0; j < numR; ++j) {
    if(aryR[j][0] == aryR[j][1]) {
      cout << "(" << aryR[j][0] << ", " << aryR[j][1] << ") is PRESENT that's why, ";
      return 0;
    }
  }
  return 1;
}

int isSymmetric(int numR, int numS, int aryS[], int aryR[][2]) {
  int k = 0;
  for(int i = 0; i < numR; ++i) {
    k = 0;
    for(int j = 0; j < numR; ++j) {
      if((aryR[j][0] == aryR[i][1]) && (aryR[j][1] == aryR[i][0])) {
        k = 1;
        break;
      }
    }
    if(k == 0) {
      cout << "(" << aryR[i][1] << ", " << aryR[i][0] << ") is NOT PRESENT that's why, ";
      break;
    }
  }
  if(numR == 0) {
    return 1;
  }
  return k;
}

int isAntisymmetric(int numR, int numS, int aryS[], int aryR[][2]) {
  int k = 0;
  for(int i = 0; i < numR; ++i) {
    for(int j = 0; j < numR; ++j) {
      if((aryR[j][1] == aryR[i][0]) && (aryR[j][0] == aryR[i][1])) {
        if(aryR[j][1] == aryR[j][0]) {
          k = 1;
        } else {
          cout << "(" << aryR[j][0] << ", " << aryR[j][1] << ") is PRESENT that's why, ";
          k = 0;
        }
        break;
      }
      k = 1;
    }
    if(k == 0) {
      break;
    }
  }
  if(numR == 0) {
    return 1;
  }
  return k;
}

int isAsymmetric(int numR, int numS, int aryS[], int aryR[][2]) {
  int k = 0;
  for(int i = 0; i < numR; ++i) {
    for(int j = 0; j < numR; ++j) {
      if((aryR[j][0] == aryR[i][1]) && (aryR[j][1] == aryR[i][0])) {
        cout << "(" << aryR[j][0] << ", " << aryR[j][1] << ") is PRESENT that's why, ";
        k = 0;
        break;
      }
      k = 1;
    }
    if(k == 0) {
      break;
    }
  }
  if(numR == 0) {
    return 1;
  }
  return k;
}

int isTransitive(int numR, int numS, int aryS[], int aryR[][2]) {
  int l = 0;
  for(int i = 0; i < numR; ++i) {
    for(int j = 0; j < numR; ++j) {
      if(aryR[i][1] == aryR[j][0]) {
        int m = aryR[j][1];
        int n = aryR[i][0];
        for(int k = 0; k < numR; ++k) {
          if((aryR[k][0] == n) && (aryR[k][1] == m)) {
            l = 1;
            break;
          }
          l = 0;
          if((k == numR - 1) && (l == 0)) {
            cout << "(" << n << ", " << m << ") is NOT PRESENT that's why, ";
          }
        }
        if(l == 0) {
          break;
        }
      } else {
        l = 1;
      }
    }
    if(l == 0) {
      break;
    }
  }
  if(numR == 0) {
    return 1;
  }
  return l;
}

int isEquivalence(int numR, int numS, int aryS[], int aryR[][2]) {
  if(isReflexive(numR, numS, aryS, aryR) && isSymmetric(numR, numS, aryS, aryR) && isTransitive(numR, numS, aryS, aryR)) {
    return 1;
  }
  return 0;
}