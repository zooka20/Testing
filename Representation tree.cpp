#include <iostream>
#include <stack>
#include <string>
#include<bits/stdc++.h>
using namespace std;

// An expression tree node
struct n {
   char d;
   n *l;
   n *r;
};

int top = -1;
n *a[50];

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// Simply determine if character is one of the four standard operators.
bool isOperator(char character) {
    if (character == '+' || character == '-' || character == '*' || character == '/' ) {
        return true;
    }
    return false;
}


// If the character is not an operator or a parenthesis, then it is assumed to be an operand.
bool isOperand(char character) {
    if (!isOperator(character) && character != '(' && character != ')') {
        return true;
    }
    return false;
}


// Compare operator precedence of main operators.
// Return 0 if equal, -1 if op2 is less than op1, and 1 if op2 is greater than op1.
int compareOperators(char op1, char op2) {
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) { return -1; }
    else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) { return 1; }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//////////////##### Buliding stack manual #####//////////////////////

void push(n *tree) {
   top++;
   a[top] = tree;
}
n *pop() {
   top--;
   return (a[top + 1]);
}
////////////////////////////////////////////
void construct_expression_tree(char *suffix) {
   char s;
   n *newl, *p1, *p2;

   s = suffix[0];
   for (int i = 1; s != 0; i++) {

      if (isOperand(s)) {
         newl = new n;
         newl->d = s;
         newl->l = NULL;
         newl->r = NULL;
         push(newl);
      } else {
         p1 = pop();
         p2 = pop();
         newl = new n;
         newl->d = s;
         newl->l = p2;
         newl->r = p1;
         push(newl);
      }
      s = suffix[i];
   }
}
////////////////////////////////////
void preOrder(n *tree) {
   if (tree != NULL) {
      cout << tree->d;
      preOrder(tree->l);
      preOrder(tree->r);
   }
}
void inOrder(n *tree) {
   if (tree != NULL) {
      inOrder(tree->l);
      cout << tree->d;
      inOrder(tree->r);
   }
}
void postOrder(n *tree) {
   if (tree != NULL) {
      postOrder(tree->l);
      postOrder(tree->r);
      cout << tree->d;
   }
}
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void run(){
    stack<char> opStack;
    string postFixString = "";

    char input[100];

    // Collect input
    cout << " Enter The Expression : \n ";
    cin >> input;

    // Get a pointer to our character array.
    char *cPtr = input;

    // Loop through the array (one character at a time) until we reach the end of the string.
    while (*cPtr != '\0') {
        // If operand, simply add it to our postfix string.
        // If it is an operator, pop operators off our stack until it is empty, an open parenthesis or an operator with less than or equal precedence.
        if (isOperand(*cPtr)) { postFixString += *cPtr; }
        else if (isOperator(*cPtr)) {
            while (!opStack.empty() && opStack.top() != '(' && compareOperators(opStack.top(),*cPtr) <= 0) {
                postFixString += opStack.top();
                opStack.pop();
            }
            opStack.push(*cPtr);
        }
        // Simply push all open parenthesis onto our stack
        // When we reach a closing one, start popping off operators until we run into the opening parenthesis.
        else if (*cPtr == '(') { opStack.push(*cPtr); }
        else if (*cPtr == ')') {
            while (!opStack.empty()) {
                if (opStack.top() == '(') { opStack.pop(); break; }
                postFixString += opStack.top();
                opStack.pop();
            }
        }

        // Advance our pointer to next character in string.
        cPtr++;
    }

    // After the input expression has been ran through, if there is any remaining operators left on the stack
    // pop them off and put them onto the postfix string.
    while (!opStack.empty()) {
        postFixString += opStack.top();
        opStack.pop();
    }
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////

    char y[postFixString.size() + 1];
	strcpy(y, postFixString.c_str());

	/////////////////////////////////////
    construct_expression_tree(y);
    cout << "\n                                                 ###In-Order Traversal###  \n\n                                                         ";
    inOrder(a[0]);
    cout << "\n\n                                                 ###Pre-Order Traversal###  \n\n                                                         ";
    preOrder(a[0]);
    cout << "\n\n                                                 ###Post-Order Traversal###  \n\n                                                         ";
    postOrder(a[0]);




}



int main()
{
    // Empty character stack and blank postfix string.
    cout<<"\n\n                                             ##Expression Tree Project##\n\n                                      ## © 2019  Ahmed Ibrahim All Rights Reserved ##\n\n\n\n";
    run();
    int ch;
    cout<<"\n                                           #Do You Want To Try Another Expression ?? \n                                           1- YES      2-NO \n\n";
    cin>>ch;
    while(ch){
    switch (ch)
   {
       case 1: run();
               return 0;
                break;
       case 2: cout<<"\n                                           ######  Thanks For Using My Application ###### \n";
                return 0;
                break;

       default: cout<<"\n                                           ######Wrong Input######\n";
        cout<<"\n                                           #Do You Want To Try Another Expression ?? \n                                           1- YES      2-NO \n\n";
        cin>>ch;
                break;
   }
    }
   return 0;
}

