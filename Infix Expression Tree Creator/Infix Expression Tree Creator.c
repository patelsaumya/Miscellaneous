#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arraySize 1000

typedef struct TreeNode {
  char character;
  struct TreeNode* parent;
  struct TreeNode* leftChild;
  struct TreeNode* rightChild;
} TreeNode;

typedef struct OperatorDetails {
  char symbol;
  int index;
  int precedence;
  int associativity;
  TreeNode* symbolRoot;
  char leftOperand[arraySize];
  char rightOperand[arraySize];
  char taskCompleted[arraySize];
} OperatorDetails;

typedef struct CharacterProcessed {
  char character;
  int isProcessed;
} CharacterProcessed;

char lookUpTable[5][3];

int checkValidityOfExpression(char*);
void printPostfixExpression(TreeNode*);
void printPrefixExpression(TreeNode*);
TreeNode* searchLeftOperand(OperatorDetails*, int, OperatorDetails*);
TreeNode* searchRightOperand(OperatorDetails*, int, OperatorDetails*);
void insertToTree(OperatorDetails*, int, OperatorDetails*);
void reverseString(char*);
void fillLeftOperand(OperatorDetails*, CharacterProcessed*);
void fillRightOperand(OperatorDetails*, CharacterProcessed*, int);
void fillTaskCompleted(OperatorDetails*);
void fillCp(CharacterProcessed*, char*);
int isBracket(char);
int numberOfBracketsBeforeOperators(int, char*);
void initialize(OperatorDetails*, int);
void updateIndex(OperatorDetails*, int, char*);
int isOperator(char);
int getPrecedence(char);
int getAsscociativity(char);
int numberOfOperators(char*);
void fillSymbol(OperatorDetails*, char*);
void fillIndex(OperatorDetails*, char*);
int numberOfBracketsForPrecedence(int, char*);
void fillPrecedenceAsPerBrackets(OperatorDetails*, int, char*);
void fillAssociativity(OperatorDetails*, int, char*);
void sort(OperatorDetails*, int);
void fillLookUpTable(void);
int maxDepth(TreeNode*);
void printTree(TreeNode*, int, int, FILE*);

TreeNode* head = NULL;

void main() {
  char infixExpressionOld[arraySize];
  int numOfOperators;
  int infixExpressionLengthOld;
  char infixExpressionNew[arraySize];
  int infixExpressionLengthNew;
  int depth;
  OperatorDetails* op;
  CharacterProcessed* cp;
  fillLookUpTable();
  printf("-> Valid variables are a-b, A-B, 0-9.\n-> Valid parenthesis are ().\n-> Operators: (+ : Add, - : Subtract, / : Divide, * : Multiply, ^ : Exponent)");
  printf("\n\n===============================\n\n");
  printf("Enter the infix expression: ");
  scanf("%[^\n]", infixExpressionOld);
  printf("\n===============================");
  infixExpressionLengthOld = strlen(infixExpressionOld);
  numOfOperators = numberOfOperators(infixExpressionOld);
  op = (OperatorDetails*)malloc((numOfOperators) * sizeof(OperatorDetails));

  int j = 0;
  for(int i = 0; i < infixExpressionLengthOld; ++i) {
    if(isBracket(infixExpressionOld[i]) == 1) {
      continue;
    }
    infixExpressionNew[j] = infixExpressionOld[i];
    ++j;
  }
  infixExpressionNew[j] = '\0';
  infixExpressionLengthNew = strlen(infixExpressionNew);
  if(!checkValidityOfExpression(infixExpressionNew)) {
      printf("\n\nInvalid Expression!");
      free(op);
      return;
  }
  if(infixExpressionLengthNew == 1) {
    if(!isOperator(infixExpressionNew[0])) {
      TreeNode* tn = (TreeNode*)malloc(sizeof(TreeNode));
      tn->character = infixExpressionNew[0];
      tn->rightChild = NULL;
      tn->leftChild = NULL;
      tn->parent = NULL;
      head = tn;
      printf("\n\nPostfix expression: ");
      printPostfixExpression(head);
      printf("\n\n");
      printf("Prefix expression: ");
      printPrefixExpression(head);
      depth = maxDepth(head);
      printf("\n\nDepth of the expression tree: %d\n\n", depth);
      printf("===============================\n\n");
      printf("Infix Expression Tree: \n\n");
      printf("%c(B: %d)\n", infixExpressionNew[0], depth);
      printf("\n\nEach node is of the format: character(Left / Base / Right: Level)");
      free(tn);
    } else {
      printf("\n\nInvalid Expression!");
    }
    free(op);
    return;
  }
  initialize(op, numOfOperators);

  fillSymbol(op, infixExpressionOld);

  fillIndex(op, infixExpressionOld);

  fillPrecedenceAsPerBrackets(op, numOfOperators, infixExpressionOld);

  fillAssociativity(op, numOfOperators, infixExpressionOld);

  updateIndex(op, numOfOperators, infixExpressionOld);
  printf("\n\n");
  sort(op, numOfOperators);
  cp = (CharacterProcessed*)malloc(infixExpressionLengthNew * sizeof(CharacterProcessed));
  fillCp(cp, infixExpressionNew);

  for(int i = 0; i < numOfOperators; ++i) {
    fillLeftOperand(&op[i], cp);
    fillRightOperand(&op[i], cp, infixExpressionLengthNew);
    fillTaskCompleted(&op[i]);
  }

  for(int i = 0; i < numOfOperators; ++i) {
    insertToTree(&op[i], i, op);
  }
  printf("Postfix expression: ");
  printPostfixExpression(head);
  printf("\n\n");
  printf("Prefix expression: ");
  printPrefixExpression(head);


  depth = maxDepth(head);
  printf("\n\nDepth of the expression tree: %d\n\n", depth);
  char fileName[100];
  printf("===============================\n\n");
  printf("File in which you want to print Infix-Expression-Tree(.txt): ");
  scanf("%s", fileName);
  FILE* fp = fopen(fileName, "w");
  printTree(head, depth, -1, fp);
  fclose(fp);
  printf("\nInfix-Expression-Tree drawn successfully in the file!");
  printf("\n\nEach node is of the format: character(Left / Base / Right: Level)");
  free(op);
  free(cp);

}

int checkValidityOfExpression(char* infixExpressionNew) {
  int infixExpressionLengthNew = strlen(infixExpressionNew);
  for(int i = 0; i + 1 < infixExpressionLengthNew; ++i) {
    if(infixExpressionNew[i] == ' ') {
      return 0;
    }
    if((!isOperator(infixExpressionNew[i])) && (!isOperator(infixExpressionNew[i+1]))) {
      return 0;
    }
    if((isOperator(infixExpressionNew[i])) && (isOperator(infixExpressionNew[i+1]))) {
      return 0;
    }
  }
  if((isOperator(infixExpressionNew[0])) || (isOperator(infixExpressionNew[infixExpressionLengthNew-1]))) {
    return 0;
  }
  if(infixExpressionNew[0] == ' ') {
    return 0;
  }
  return 1;
}

void printTree(TreeNode* tn, int depth, int isLeft, FILE* fp) {
  if(tn == NULL) {
    return;
  }
  if(tn->leftChild != NULL) {
    printTree(tn->leftChild, depth - 1, 1, fp);
  }
  for(int i = 0; i < depth - 1; ++i) {
    fprintf(fp, "\t\t\t");
  }
  if(isLeft == -1) {
    fprintf(fp, "%c(B: %d)\n", tn->character, depth);
  } else if (isLeft == 1) {
    fprintf(fp, "%c(L: %d)\n", tn->character, depth);
  } else {
    fprintf(fp, "%c(R: %d)\n", tn->character, depth);
  }
  if(tn->rightChild != NULL) {
    printTree(tn->rightChild, depth - 1, 0, fp);
  }
}

int maxDepth(TreeNode* head) {
  int depth = 0;
  if(head == NULL) {
    return depth;
  }
  depth = 1;
  int leftDepth = maxDepth(head->leftChild);
  int rightDepth = maxDepth(head->rightChild);
  if(leftDepth > rightDepth) {
    depth = 1 + leftDepth;
  } else {
    depth = 1 + rightDepth;
  }
  return depth;
}

void printPostfixExpression(TreeNode* tn) {
  if(tn->leftChild != NULL) {
    printPostfixExpression(tn->leftChild);
  }

  if(tn->rightChild != NULL) {
    printPostfixExpression(tn->rightChild);
  }

  printf("%c",tn->character);
}

void printPrefixExpression(TreeNode* tn) {
  printf("%c",tn->character);

  if(tn->leftChild != NULL) {
    printPrefixExpression(tn->leftChild);
  }

  if(tn->rightChild != NULL) {
    printPrefixExpression(tn->rightChild);
  }
}

TreeNode* searchLeftOperand(OperatorDetails* op, int index, OperatorDetails* opAry) {
  for(int i = index - 1; i >= 0; --i) {
    if(strcmp(op->leftOperand, opAry[i].taskCompleted) == 0) {
      return opAry[i].symbolRoot;
    }
  }
  return NULL;
}

TreeNode* searchRightOperand(OperatorDetails* op, int index, OperatorDetails* opAry) {
  for(int i = index - 1; i >= 0; --i) {
    if(strcmp(op->rightOperand, opAry[i].taskCompleted) == 0) {
      return opAry[i].symbolRoot;
    }
  }
  return NULL;
}

void insertToTree(OperatorDetails* op, int index, OperatorDetails* opAry) {
  TreeNode* left = searchLeftOperand(op, index, opAry);
  if(left == NULL) {
    left = (TreeNode*)malloc(sizeof(TreeNode));
    left->character = op->leftOperand[0];
    left->leftChild = NULL;
    left->rightChild = NULL;
  }
  TreeNode* right = searchRightOperand(op, index, opAry);
  if(right == NULL) {
    right = (TreeNode*)malloc(sizeof(TreeNode));
    right->character = op->rightOperand[0];
    right->rightChild = NULL;
    right->leftChild = NULL;
  }
  TreeNode* parentNew = (TreeNode*)malloc(sizeof(TreeNode));
  op->symbolRoot = parentNew;
  parentNew->character = op->symbol;
  head = parentNew;
  parentNew->leftChild = left;
  parentNew->parent = NULL;
  left->parent = parentNew;
  parentNew->rightChild = right;
  right->parent = parentNew;
  return;
}

void reverseString(char* str) {
  int len = strlen(str);
  char tmp;
  for(int i = 0; i < len/2; ++i) {
    tmp = str[i];
    str[i] = str[len-i-1];
    str[len-i-1] = tmp;
  }
  return;
}

void fillLeftOperand(OperatorDetails* op, CharacterProcessed* cp) {
  int index = op->index;
  int j = 0;
  cp[index].isProcessed = 1;
  for(int i = index - 1; i >= 0; --i) {
    if(cp[i].isProcessed == 0) {
      if(isOperator(cp[i].character) == 0) {
        op->leftOperand[j] = cp[i].character;
        ++j;
        cp[i].isProcessed = 1;
      }
      break;
    }
    if(cp[i].isProcessed == 1) {
      op->leftOperand[j] = cp[i].character;
      ++j;
    }
  }
  op->leftOperand[j] = '\0';
  reverseString(op->leftOperand);
  return;
}

void fillRightOperand(OperatorDetails* op, CharacterProcessed* cp, int infixExpressionLengthNew) {
  int index = op->index;
  int j = 0;
  cp[index].isProcessed = 1;
  for(int i = index + 1; i < infixExpressionLengthNew; ++i) {
    if(cp[i].isProcessed == 0) {
      if(isOperator(cp[i].character) == 0) {
        op->rightOperand[j] = cp[i].character;
        ++j;
        cp[i].isProcessed = 1;
      }
      break;
    }
    if(cp[i].isProcessed == 1) {
      op->rightOperand[j] = cp[i].character;
      ++j;
    }
  }
  op->rightOperand[j] = '\0';
  return;
}

void fillTaskCompleted(OperatorDetails* op) {
  char sym[3];
  sym[0] = op->symbol;
  sym[1] = '\0';
  op->taskCompleted[0] = '\0';
  strcat(op->taskCompleted, op->leftOperand);
  strcat(op->taskCompleted, sym);
  strcat(op->taskCompleted, op->rightOperand);
  return;
}

void fillCp(CharacterProcessed* cp, char* infixExpressionNew) {
  int infixExpressionLengthNew = strlen(infixExpressionNew);
  for(int i = 0; i < infixExpressionLengthNew; ++i) {
    cp[i].character = infixExpressionNew[i];
    cp[i].isProcessed = 0;
  }
  return;
}

int isBracket(char ch) {
  if((ch == '(') || (ch == ')')) {
    return 1;
  }
  return 0;
}

int numberOfBracketsBeforeOperators(int index, char* infixExpressionOld) {
  int infixExpressionLengthOld = strlen(infixExpressionOld);
  int brackets = 0;
  for(int i = 0; i < index; ++i) {
    if(isBracket(infixExpressionOld[i]) == 1) {
      ++brackets;
    }
  }
  return brackets;
}

void initialize(OperatorDetails* op, int numOfOperators) {
  for(int i = 0; i < numOfOperators; ++i) {
    op[i].leftOperand[0] = '\0';
    op[i].rightOperand[0] = '\0';
    op[i].taskCompleted[0] = '\0';
  }
  return;
}

void updateIndex(OperatorDetails* op, int numOfOperators, char* infixExpressionOld) {
  for(int i = 0; i < numOfOperators; ++i) {
    op[i].index -= numberOfBracketsBeforeOperators(op[i].index, infixExpressionOld);
  }
  return;
}

int isOperator(char ch) {
  if((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*') || (ch == '^')) {
    return 1;
  }
  return 0;
}

int getPrecedence(char ch) {
  for(int i = 0; i < 5; ++i) {
    if(lookUpTable[i][0] == ch) {
      int precedence = ((int)lookUpTable[i][1]) - 48;
      return precedence;
    }
  }
  return -1;
}

int getAsscociativity(char ch) {
  for(int i = 0; i < 5; ++i) {
    if(lookUpTable[i][0] == ch) {
      int associativity = ((int)lookUpTable[i][2]) - 48;
      return associativity;
    }
  }
  return -1;
}

int numberOfOperators(char* infixExpressionOld) {
  int infixExpressionLengthOld = strlen(infixExpressionOld);
  int numOfOperators = 0;
  for(int i = 0; i < infixExpressionLengthOld; ++i) {
    if(isOperator(infixExpressionOld[i]) == 1) {
      ++numOfOperators;
    }
  }
  return numOfOperators;
}

void fillSymbol(OperatorDetails* op, char* infixExpressionOld) {
  int infixExpressionLengthOld = strlen(infixExpressionOld);
  for(int i = 0, j = 0; i < infixExpressionLengthOld; ++i) {
    if(isOperator(infixExpressionOld[i]) == 1) {
      op[j].symbol = infixExpressionOld[i];
      ++j;
    }
  }
  return;
}

void fillIndex(OperatorDetails* op, char* infixExpressionOld) {
  int infixExpressionLengthOld = strlen(infixExpressionOld);
  for(int i = 0, j= 0; i < infixExpressionLengthOld; ++i) {
    if(isOperator(infixExpressionOld[i]) == 1) {
      op[j].index = i;
      ++j;
    }
  }
  return;
}

int numberOfBracketsForPrecedence(int index, char* infixExpressionOld) {
  int brackets = 0;
  for(int i = 0; i < index; ++i) {
    if(infixExpressionOld[i] == '(') {
      ++brackets;
    }
    if(infixExpressionOld[i] == ')') {
      --brackets;
    }
  }
  return brackets;
}

void fillPrecedenceAsPerBrackets(OperatorDetails* op, int numberOfOperators, char* infixExpressionOld) {
  for(int i = 0; i < numberOfOperators; ++i) {
    int brackets = numberOfBracketsForPrecedence(op[i].index, infixExpressionOld);
    int precedenceFromLookUpTable = getPrecedence(infixExpressionOld[op[i].index]);
    op[i].precedence = brackets*10 + precedenceFromLookUpTable;
  }
  return;
}

void fillAssociativity(OperatorDetails* op, int numberOfOperators, char* infixExpressionOld) {
  for(int i = 0; i < numberOfOperators; ++i) {
    char symbol = infixExpressionOld[op[i].index];
    op[i].associativity = getAsscociativity(symbol);
  }
  return;
}

void sort(OperatorDetails* op, int numOfOperators) {
  for(int j = 0; j < numOfOperators-1; ++j) {
    for(int i = 0; i+1 < numOfOperators; ++i) {
      OperatorDetails tmp;
      if(op[i].precedence < op[i+1].precedence) {
        tmp.symbol = op[i].symbol;
        tmp.index = op[i].index;
        tmp.precedence = op[i].precedence;
        tmp.associativity = op[i].associativity;

        op[i].symbol = op[i+1].symbol;
        op[i].index = op[i+1].index;
        op[i].precedence = op[i+1].precedence;
        op[i].associativity = op[i+1].associativity;

        op[i+1].symbol = tmp.symbol;
        op[i+1].index = tmp.index;
        op[i+1].precedence = tmp.precedence;
        op[i+1].associativity = tmp.associativity;
      }
      if(op[i].precedence == op[i+1].precedence) {
        if((op[i].associativity == 0) && (op[i+1].associativity == 0) && (op[i].index < op[i+1].index)) {
          tmp.symbol = op[i].symbol;
          tmp.index = op[i].index;
          tmp.precedence = op[i].precedence;
          tmp.associativity = op[i].associativity;

          op[i].symbol = op[i+1].symbol;
          op[i].index = op[i+1].index;
          op[i].precedence = op[i+1].precedence;
          op[i].associativity = op[i+1].associativity;

          op[i+1].symbol = tmp.symbol;
          op[i+1].index = tmp.index;
          op[i+1].precedence = tmp.precedence;
          op[i+1].associativity = tmp.associativity;
        }
      }
    }
  }
  return;
}

void fillLookUpTable(void) {
  lookUpTable[0][0] = '^';
  lookUpTable[0][1] = '3';
  lookUpTable[0][2] = '0';

  lookUpTable[1][0] = '/';
  lookUpTable[1][1] = '2';
  lookUpTable[1][2] = '1';

  lookUpTable[2][0] = '*';
  lookUpTable[2][1] = '2';
  lookUpTable[2][2] = '1';

  lookUpTable[3][0] = '+';
  lookUpTable[3][1] = '1';
  lookUpTable[3][2] = '1';

  lookUpTable[4][0] = '-';
  lookUpTable[4][1] = '1';
  lookUpTable[4][2] = '1';
  return;
}