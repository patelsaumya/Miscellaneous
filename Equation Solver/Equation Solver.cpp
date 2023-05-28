#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cmath>

using namespace std;

int compareDoubles(double a, double b) {
  if(abs(a-b) < 1E-9) {
    return 1;
  } else {
    return 0;
  }
}

typedef struct ComplexNumber {
  public:
    double realPart;
    double imaginaryPart;
} ComplexNumber;

class LinearEquation {
  public:

    double xNumLHS;
    double yNumLHS;
    double cNumLHS;
    double xDenLHS;
    double yDenLHS;
    double cDenLHS;
    double cRHS;

    LinearEquation(void) {
    }

    ~LinearEquation() {
    }

    int checkValidity(void) {
      if((this->yDenLHS == 0) && (this->xDenLHS == 0) && (this->cDenLHS == 0)) {
        return 0;
      }
      if((this->xNumLHS == 0) && (this->xDenLHS == 0)) {
        if((this->yNumLHS == 0) && (this->yDenLHS == 0)) {
          if(compareDoubles(this->cRHS, this->cNumLHS / this->cDenLHS)) {
            return 2;
          } else {
            return 0;
          }
        }
        else if((this->yNumLHS != 0) && (this->yDenLHS != 0)) {
          if((this->cNumLHS == 0) && (this->cDenLHS == 0)) {
            if(compareDoubles(this->cRHS, this->yNumLHS / this->yDenLHS)) {
              return 2;
            } else {
              return 0;
            }
          }
          else if((this->cNumLHS != 0) && (this->cDenLHS != 0)) {
            if(compareDoubles(this->yNumLHS / this->yDenLHS, this->cNumLHS / this->cDenLHS)) {
              if(compareDoubles(this->cRHS, this->cNumLHS / this->cDenLHS) && compareDoubles(this->cRHS, this->yNumLHS / this->yDenLHS)) {
                return 2;
              } else {
                return 0;
              }
            } else {
              return 1;
            }
          }
        }
        return 1;
      }
      else if((this->xNumLHS != 0) && (this->xDenLHS != 0)) {
        if((this->yNumLHS == 0) && (this->yDenLHS == 0)) {
          if((this->cNumLHS == 0) && (this->cDenLHS == 0)) {
            if(compareDoubles(this->cRHS, this->xNumLHS / this->xDenLHS)) {
              return 2;
            } else {
              return 0;
            }
          }
          else if((this->cNumLHS != 0) && (this->cDenLHS != 0)) {
            if(compareDoubles(this->xNumLHS / this->xDenLHS, this->cNumLHS / this->cDenLHS)) {
              if(compareDoubles(this->cRHS, this->cNumLHS / this->cDenLHS) && compareDoubles(this->cRHS, this->xNumLHS / this->xDenLHS)) {
                return 2;
              } else {
                return 0;
              }
            } else {
              return 1;
            }
          }
        }
        else if((this->yNumLHS != 0) && (this->yDenLHS != 0)) {
          if((this->cNumLHS == 0) && (this->cDenLHS == 0)) {
            if(compareDoubles(this->xNumLHS / this->xDenLHS, this->yNumLHS / this->yDenLHS)) {
              if(compareDoubles(this->cRHS, this->yNumLHS / this->yDenLHS) && compareDoubles(this->cRHS, this->xNumLHS / this->xDenLHS)) {
                return 2;
              } else {
                return 0;
              }
            } else {
              return 1;
            }
          }
          else if((this->cNumLHS != 0) && (this->cDenLHS != 0)) {
            if(compareDoubles(this->xNumLHS / this->xDenLHS, this->cNumLHS / this->cDenLHS) && compareDoubles(this->yNumLHS / this->yDenLHS, this->xNumLHS / this->xDenLHS)) {
              if(compareDoubles(this->cRHS, this->cNumLHS / this->cDenLHS) &&
                 compareDoubles(this->cRHS, this->xNumLHS / this->xDenLHS) &&
                 compareDoubles(this->cRHS, this->yNumLHS / this->yDenLHS)) {
                  return 2;
              } else {
                return 0;
              }
            } else {
              return 1;
            }
          }
        }
      return 1;
    }
    return 1;
  }

    void printLinearEquation(void) {
      cout << this->xNumLHS - this->cRHS * this->xDenLHS << "x + " << this->yNumLHS - this->cRHS * this->yDenLHS <<
      "y = " << this->cDenLHS * this->cRHS - this->cNumLHS << "\n";
      return;
    }
};

class EquationOfOrder2 {
  public:
    double xCoeff;
    double yCoeff;
    double constRHS;

    EquationOfOrder2(void) {
    }

    ~EquationOfOrder2() {
    }

    int checkValidity(void) {
      if(compareDoubles(this->constRHS, 0)) {
        return 1;
      } else {
        if(compareDoubles(this->xCoeff, 0) || compareDoubles(this->yCoeff, 0)) {
          return 0;
        }
      }
      return 1;
    }

    void printEquationOfOrder2(void) {
      cout << "(" << this->xCoeff << "x) * (" << this->yCoeff << "y) = " << this->constRHS << "\n";
      return;
    }
};

class SpecialCaseForEquations {
  public:
    static int SC1(LinearEquation* e1, LinearEquation* e2) {
      if(compareDoubles(e1->xNumLHS - e1->cRHS * e1->xDenLHS, 0) && compareDoubles(e2->xNumLHS - e2->cRHS * e2->xDenLHS, 0)) {
        if(compareDoubles(e1->yNumLHS - e1->cRHS * e1->yDenLHS, 0) && compareDoubles(e2->yNumLHS - e2->cRHS * e2->yDenLHS, 0)) {
          if(compareDoubles(e1->cRHS * e1->cDenLHS - e1->cNumLHS, 0) && compareDoubles(e2->cRHS * e2->cDenLHS - e2->cNumLHS, 0)) {
            cout << "Infinite number of solutions\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " << e1->cDenLHS <<
            "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" <<
            "The solution should satisfy both the equations\n";
            return 1;
          }
          else {
            cout << "No solution\n";
            return 1;
          }
        }
        else if((compareDoubles(e1->yNumLHS - e1->cRHS * e1->yDenLHS, 0) == 0) && (compareDoubles(e2->yNumLHS - e2->cRHS * e2->yDenLHS, 0) == 0)) {
          if(compareDoubles(e1->cRHS * e1->cDenLHS - e1->cNumLHS, 0) && compareDoubles(e2->cRHS * e2->cDenLHS - e2->cNumLHS, 0)) {
            cout << "y = 0\n" << "x has infinite possible values\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " << e1->cDenLHS <<
            "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" << "The solution should satisfy both the equations\n";
            return 1;
          }
          else if(compareDoubles(((e1->cRHS * e1->cDenLHS - e1->cNumLHS)/(e1->yNumLHS - e1->cRHS * e1->yDenLHS)),
                  ((e2->cRHS * e2->cDenLHS - e2->cNumLHS)/(e2->yNumLHS - e2->cRHS * e2->yDenLHS)))) {
            cout << "y = " << (e1->cRHS * e1->cDenLHS - e1->cNumLHS)/(e1->yNumLHS - e1->cRHS * e1->yDenLHS) <<
            "\nx has infinite possible values\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " << e1->cDenLHS <<
            "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" << "The solution should satisfy both the equations\n";
            return 1;
          }
          else {
            cout << "No solution\n";
            return 1;
          }
        }
      }
      else if((compareDoubles(e1->xNumLHS - e1->cRHS * e1->xDenLHS, 0) == 0) && (compareDoubles(e2->xNumLHS - e2->cRHS * e2->xDenLHS, 0) == 0)) {
        if(compareDoubles(e1->yNumLHS - e1->cRHS * e1->yDenLHS, 0) && compareDoubles(e2->yNumLHS - e2->cRHS * e2->yDenLHS, 0)) {
          if(compareDoubles(e1->cRHS * e1->cDenLHS - e1->cNumLHS, 0) && compareDoubles(e2->cRHS * e2->cDenLHS - e2->cNumLHS, 0)) {
            cout << "x = 0\n" << "y has infinite possible values\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " << e1->cDenLHS <<
            "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" << "The solution should satisfy both the equations\n";
            return 1;
          }
          else if(compareDoubles(((e1->cRHS * e1->cDenLHS - e1->cNumLHS)/(e1->xNumLHS - e1->cRHS * e1->xDenLHS)),
                  ((e2->cRHS * e2->cDenLHS - e2->cNumLHS)/(e2->xNumLHS - e2->cRHS * e2->xDenLHS)))) {
            cout << "x = " << (e2->cRHS * e2->cDenLHS - e2->cNumLHS)/(e2->xNumLHS - e2->cRHS * e2->xDenLHS) <<
            "\ny has infinite possible values\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " << e1->cDenLHS <<
            "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" << "The solution should satisfy both the equations\n";
            return 1;
          }
          else {
            cout << "No solution\n";
            return 1;
          }
        }
      }

      return 0;
    }

    static int SC2(LinearEquation* e1, LinearEquation* e2, double n1, double n2, double den) {
      if(compareDoubles(den, 0)) {
        if(compareDoubles(n1, 0) && compareDoubles(n2, 0)) {
        cout << "Infinte number of solutions\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " <<
        e1->cDenLHS << "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" << "The solution should satisfy both the equations\n";

        } else {
        cout << "No solution\n";
        }
        return 1;
      }
      return 0;
    }

    static int SC3(EquationOfOrder2* e1, LinearEquation* e2) {
      if(compareDoubles(e1->constRHS, 0)) {
        if(compareDoubles(e1->xCoeff, 0) || compareDoubles(e1->yCoeff, 0)) {
          cout << "Infinite number of solutions\n" << "Except where\n" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\nThe solution should satisfy both the equations\n";
        } else {
          int i = 0;
          int j = 0;
          if(compareDoubles(e2->yNumLHS - e2->cRHS * e2->yDenLHS, 0) == 0) {
            double x = 0;
            double y = (e2->cRHS * e2->cDenLHS - e2->cNumLHS) / (e2->yNumLHS - e2->cRHS * e2->yDenLHS);
            if(compareDoubles(e2->yDenLHS * y + e2->cDenLHS, 0)) {
              i = 1;
            } else {
              cout << "x1 = 0\ny1 = " << y << "\n\n";
            }
          }
          if(compareDoubles(e2->xNumLHS - e2->cRHS * e2->xDenLHS, 0) == 0) {
            double y = 0;
            double x = (e2->cRHS * e2->cDenLHS - e2->cNumLHS) / (e2->xNumLHS - e2->cRHS * e2->xDenLHS);
            if(compareDoubles(e2->xDenLHS * x + e2->cDenLHS, 0)) {
              j = 1;
            } else {
              if(i == 0) {
                cout << "y2 = 0\nx2 = " << x << "\n";
              } else {
                cout << "y = 0\nx = " << x << "\n";
              }
            }
          }
          if((i == 1) && (j == 1)) {
            cout <<"No solution\n";
          }
        }
        return 1;
      } else {
        if(compareDoubles(e1->xCoeff, 0) || compareDoubles(e1->yCoeff, 0)) {
          cout << "No solution\n";
          return 1;
        }
        if(compareDoubles((e2->yNumLHS - e2->cRHS * e2->yDenLHS), 0)) {
          if(compareDoubles(e2->xNumLHS - e2->cRHS * e2->xDenLHS, 0) == 0) {
            double x = (e2->cRHS * e2->cDenLHS - e2->cNumLHS) / (e2->xNumLHS - e2->cRHS * e2->xDenLHS);
            double y = (e1->constRHS) / ((e1->xCoeff) * (e1->yCoeff) * x);
            if(compareDoubles(e2->xDenLHS * x + e2->yDenLHS * y + e2->cRHS, 0)) {
              cout << "No solution\n";
            } else {
              cout << "x = " << x << "\ny = " << y << "\n";
            }
          } else if(compareDoubles(e2->cRHS * e2->cDenLHS - e2->cNumLHS, 0) == 0) {
            cout << "No solution\n";
          } else {
            cout << "Infinite number of solutions\n" << "Except where\n" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS
            << "\nbecome zero.\nThe solution should satisfy both the equations\n";
          }
          return 1;
        }
        return 0;
      }
    }
};

void solveTheEquationOfOrder2AndLinearEquation(EquationOfOrder2* e1, LinearEquation* e2) {
  if(SpecialCaseForEquations :: SC3(e1, e2)) {
    return;
  }
  double discriminantPart1 = pow((e1->xCoeff)*(e1->yCoeff)*(e2->cNumLHS - e2->cRHS * e2->cDenLHS), 2);
  double discriminantPart2 = 4 * e1->xCoeff * e1->yCoeff * e1->constRHS * (e2->yNumLHS - e2->cRHS * e2->yDenLHS) * (e2->xNumLHS - e2->cRHS * e2->xDenLHS);
  double discriminant = discriminantPart1 - discriminantPart2;
  double yDenominator = 2 * (e1->xCoeff) * (e1->yCoeff) * (e2->yNumLHS - e2->cRHS * e2->yDenLHS);
  int i = 0;
  int j = 0;
  ComplexNumber* y1 = (ComplexNumber*)malloc(sizeof(ComplexNumber));
  ComplexNumber* y2 = (ComplexNumber*)malloc(sizeof(ComplexNumber));
  ComplexNumber* x1 = (ComplexNumber*)malloc(sizeof(ComplexNumber));
  ComplexNumber* x2 = (ComplexNumber*)malloc(sizeof(ComplexNumber));
  if(compareDoubles((e2->cRHS * e2->cDenLHS - e2->cNumLHS), 0)) {
    y1->realPart = 0;
    y2->realPart = 0;
  } else {
    y1->realPart = (e1->xCoeff) * (e1->yCoeff) * (e2->cRHS * e2->cDenLHS - e2->cNumLHS) / yDenominator;
    y2->realPart = (e1->xCoeff) * (e1->yCoeff) * (e2->cRHS * e2->cDenLHS - e2->cNumLHS) / yDenominator;
  }
  if(compareDoubles(discriminant, 0) == 0) {
    if(discriminant < (double)0) {
      discriminant = (-1) * discriminant;
      double squareRootOfDiscriminant = sqrt(discriminant);
      y1->imaginaryPart = squareRootOfDiscriminant / yDenominator;
      y2->imaginaryPart = (-1) * squareRootOfDiscriminant / yDenominator;
    } else if(discriminant > (double(0))) {
      double squareRootOfDiscriminant = sqrt(discriminant);
      y1->realPart = y1->realPart + (squareRootOfDiscriminant / yDenominator);
      y2->realPart = y2->realPart - (squareRootOfDiscriminant / yDenominator);
      y1->imaginaryPart = (double)0;
      y2->imaginaryPart = (double)0;
    }
    if(compareDoubles(y1->realPart, 0) && compareDoubles(y1->imaginaryPart, 0)) {
      i = 1;
      free(x1);
      free(y1);
    } else {
      double x1Denominator = (e1->xCoeff) * (e1->yCoeff) * (pow(y1->realPart, 2) + pow(y1->imaginaryPart, 2));
      x1->realPart = (e1->constRHS * (y1->realPart)) / x1Denominator;
      x1->imaginaryPart = ((-1) * e1->constRHS * (y1->imaginaryPart)) / x1Denominator;
      if((compareDoubles((e2->xDenLHS * x1->realPart + e2->yDenLHS * y1->realPart + e2->cDenLHS), 0) == 0)
        || (compareDoubles((e2->xDenLHS * x1->imaginaryPart + e2->yDenLHS * y1->imaginaryPart), 0)) == 0) {
        cout << "x1 = " << x1->realPart << " + " << x1->imaginaryPart << " i\n";
        cout << "y1 = " << y1->realPart << " + " << y1->imaginaryPart << " i\n\n";
      } else {
        i = 2;
      }
      free(x1);
      free(y1);
    }
    if(compareDoubles(y2->realPart, 0) && compareDoubles(y2->imaginaryPart, 0)) {
      j = 1;
      free(x2);
      free(y2);
    } else {
      double x2Denominator = (e1->xCoeff) * (e1->yCoeff) * (pow(y2->realPart, 2) + pow(y2->imaginaryPart, 2));
      x2->realPart = (e1->constRHS * (y2->realPart)) / x2Denominator;
      x2->imaginaryPart = ((-1) * e1->constRHS * (y2->imaginaryPart)) / x2Denominator;
      if((compareDoubles((e2->xDenLHS * x2->realPart + e2->yDenLHS * y2->realPart + e2->cDenLHS), 0) == 0)
        || (compareDoubles((e2->xDenLHS * x2->imaginaryPart + e2->yDenLHS * y2->imaginaryPart), 0)) == 0) {
        if(i == 1) {
          cout << "x1 = " << x2->realPart << " + " << x2->imaginaryPart << " i\n";
          cout << "y1 = " << y2->realPart << " + " << y2->imaginaryPart << " i\n";
        } else {
          cout << "x2 = " << x2->realPart << " + " << x2->imaginaryPart << " i\n";
          cout << "y2 = " << y2->realPart << " + " << y2->imaginaryPart << " i\n";
        }
      } else {
        j = 2;
      }
      free(x2);
      free(y2);
    }
    if((i == 0) || (j == 0)) {

    } else {
      cout << "No solution\n";
    }
  } else {
    free(x2);
    free(y2);
    if(compareDoubles(y1->realPart, 0) == 0) {
      x1->realPart = (e1->constRHS * y1->realPart) / ((e1->xCoeff) * (e1->yCoeff) * pow(y1->realPart, 2));
      if(compareDoubles(e2->xDenLHS * x1->realPart + e2->yDenLHS * y1->realPart + e2->cDenLHS, 0) == 0) {
        cout << "x1,x2 = " << x1->realPart << "\ny1,y2 = " << y1->realPart << "\n";
      } else {
        cout <<"No solution\n";
      }
      free(x1);
      free(y1);
    } else {
      free(x1);
      free(y1);
      x1->realPart = y1->realPart;
      if(compareDoubles(e2->xDenLHS * x1->realPart + e2->yDenLHS * y1->realPart + e2->cDenLHS, 0) == 0) {
        cout << "x1,x2 = " << x1->realPart << "\ny1y2 = " << y1->realPart << "\n";
      } else {
        cout << "No solution\n";
      }
    }
  }
  return;
}

void solveTheLinearEquations(LinearEquation* e1, LinearEquation* e2) {
  if(SpecialCaseForEquations :: SC1(e1, e2)) {
    return;
  }

  double n1, n2, den, x, y;
  n1 = ((e1->yNumLHS - e1->cRHS * e1->yDenLHS) * (e2->cRHS * e2->cDenLHS - e2->cNumLHS) -
        (e2->yNumLHS - e2->cRHS * e2->yDenLHS) * (e1->cRHS * e1->cDenLHS - e1->cNumLHS));
  n2 = ((e2->xNumLHS - e2->cRHS * e2->xDenLHS) * (e1->cRHS * e1->cDenLHS - e1->cNumLHS) -
        (e2->cRHS * e2->cDenLHS - e2->cNumLHS) * (e1->xNumLHS - e1->cRHS * e1->xDenLHS));
  den = ((e1->yNumLHS - e1->cRHS * e1->yDenLHS) * (e2->xNumLHS - e2->cRHS * e2->xDenLHS) -
        (e1->xNumLHS - e1->cRHS * e1->xDenLHS) * (e2->yNumLHS - e2->cRHS * e2->yDenLHS));
  if(SpecialCaseForEquations :: SC2(e1, e2, n1, n2, den)) {
    return;
  }
  x = n1 / den;
  y = n2 / den;
  if(compareDoubles((e1->xDenLHS) * x + (e1->yDenLHS) * y + e1->cDenLHS, 0)) {
    cout << "No solution\n";
    return;
  }
  if(compareDoubles((e2->xDenLHS) * x + (e2->yDenLHS) * y + e2->cDenLHS, 0)) {
    cout << "No solution\n";
    return;
  }
  cout << "x = " << x << "\n";
  cout << "y = " << y << "\n";
  return;
}

int main(void) {
  int choice;
  do {
    cout << "\n\n..........EQUATION SOLVER (2 Variables, 2 Equations)..........\n\n";
    cout << "Flavor of the System of Equations:- (Eg: 2x + 3y = 2 and 1 / ( 4x - y ) = 8 combinely are '+/' Flavor)\n\n";
    cout << "0 : Exit\n";
    cout << "1 : ++ , +- , -- , +/ , -/ , //\n";
    cout << "2 : *+ , *- , */\n\n";
    cout << "Which 2 equations do you want to solve?\n\n";
    cout << "Enter your choice: ";
    scanf("%d", &choice);
    switch(choice) {

      case 0: {
        cout << "\n--------------------------- ENDED ---------------------------";
        break;
      }

      case 1: {
        cout << "\n------------------------------------------------------\n";
        int i = 1;
        LinearEquation* e1 = new LinearEquation();
        LinearEquation* e2 = new LinearEquation();

        while(i <= 2) {
          cout << "\n(ax+by+c)/(Ax+By+C) = d\n\n";
          cout << "Linear Equation " << i << " :\n\n";

          cout << "\t\tCoefficient of x in numerator (a) : ";
          if(i == 1) {
            scanf("%lf", &(e1->xNumLHS));
          } else {
            scanf("%lf", &(e2->xNumLHS));
          }

          cout << "\t\tCoefficient of y in numerator (b) : ";
          if(i == 1) {
            scanf("%lf", &(e1->yNumLHS));
          } else {
            scanf("%lf", &(e2->yNumLHS));
          }

          cout << "\t\tConstant in numerator (c) : ";
          if(i == 1) {
            scanf("%lf", &(e1->cNumLHS));
          } else {
            scanf("%lf", &(e2->cNumLHS));
          }

          cout << "\t\tCoefficient of x in denominator (A) : ";
          if(i == 1) {
            scanf("%lf", &(e1->xDenLHS));
          } else {
            scanf("%lf", &(e2->xDenLHS));
          }

          cout << "\t\tCoefficient of y in denominator (B) : ";
          if(i == 1) {
            scanf("%lf", &(e1->yDenLHS));
          } else {
            scanf("%lf", &(e2->yDenLHS));
          }

          cout << "\t\tConstant in denominator (C) : ";
          if(i == 1) {
            scanf("%lf", &(e1->cDenLHS));
          } else {
            scanf("%lf", &(e2->cDenLHS));
          }

          cout << "\t\tConstant in RHS (d) : ";
          if(i == 1) {
            scanf("%lf", &(e1->cRHS));
          } else {
            scanf("%lf", &(e2->cRHS));
          }
          cout << "\n";

          ++i;
        }

        if(e1->checkValidity() && e2->checkValidity()) {
          if((e1->checkValidity() == 2) || (e2->checkValidity() == 2)) {
            if(e1->checkValidity() == 2) {
              cout << "0x + 0y = 0\n";
            } else {
              e1->printLinearEquation();
            }

            if(e2->checkValidity() == 2) {
              cout << "0x + 0y = 0\n";
            } else {
              e2->printLinearEquation();
            }
            cout << "_______________\n\n";
            cout << "Infinte number of solutions\n" << "Except where\n" << e1->xDenLHS << "x + " << e1->yDenLHS << "y + " <<
            e1->cDenLHS << "\tOR\t" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS << "\nbecome zero.\n" << "The solution should satisfy both the equations\n";
          } else {
            e1->printLinearEquation();
            e2->printLinearEquation();
            cout << "_______________\n\n";
            solveTheLinearEquations(e1, e2);
          }
        } else {
          cout << "Linear Equation/s invalid !\n";
        }
        delete e2;
        delete e1;
        cout << "\n\n======================================================";
        break;
      }

      case 2: {
        cout << "\n------------------------------------------------------\n";
        EquationOfOrder2* e1 = new EquationOfOrder2();
        LinearEquation* e2 = new LinearEquation();


        cout << "\n(ax) * (by) = c\n\n";
        cout << "Multiplication Equation :\n\n";
        cout << "\t\tCoefficient of x in LHS (a) : ";
        scanf("%lf", &(e1->xCoeff));
        cout << "\t\tCoefficient of y in LHS (b) : ";
        scanf("%lf", &(e1->yCoeff));
        cout << "\t\tConstant in RHS (c) : ";
        scanf("%lf", &(e1->constRHS));
        cout << "\n";


        cout << "\n(ax+by+c)/(Ax+By+C) = d\n\n";
        cout << "Linear Equation :\n\n";
        cout << "\t\tCoefficient of x in numerator (a) : ";
        scanf("%lf", &(e2->xNumLHS));
        cout << "\t\tCoefficient of y in numerator (b) : ";
        scanf("%lf", &(e2->yNumLHS));
        cout << "\t\tConstant in numerator (c) : ";
        scanf("%lf", &(e2->cNumLHS));
        cout << "\t\tCoefficient of x in denominator (A) : ";
        scanf("%lf", &(e2->xDenLHS));
        cout << "\t\tCoefficient of y in denominator (B) : ";
        scanf("%lf", &(e2->yDenLHS));
        cout << "\t\tConstant in denominator (C) : ";
        scanf("%lf", &(e2->cDenLHS));
        cout << "\t\tConstant in RHS (d) : ";
        scanf("%lf", &(e2->cRHS));
        cout << "\n";


        if(e1->checkValidity() && e2->checkValidity()) {
          if(e2->checkValidity() == 2) {
            e1->printEquationOfOrder2();
            cout << "0x + 0y = 0\n";
            cout << "_______________\n\n";
            cout << "Infinite number of solutions\n" << "Except where\n" << e2->xDenLHS << "x + " << e2->yDenLHS << "y + " << e2->cDenLHS
            << "\nbecome zero.\nThe solution should satisfy both the equations\n";
          } else {
            e1->printEquationOfOrder2();
            e2->printLinearEquation();
            cout << "_______________\n\n";
            solveTheEquationOfOrder2AndLinearEquation(e1, e2);
          }
        } else {
          cout << "Invalid Equation/s !\n";
        }
        delete e2;
        delete e1;
        cout << "\n\n======================================================";
        break;
      }

      default: {
        cout << "\n------------------------------------------------------\n";
        cout << "\nIncorrect choice!\n";
        cout << "\n======================================================";
        break;
      }
    }
  } while(choice != 0);
  return 0;
}