#include "Set.h"
#include <string>
#include <iostream>

#include <stack>
using namespace std;

//Removes space from infixes
string infixWithoutSpace(string infix) {
    string retStr;
    for (int i = 0; i < infix.size(); i++) {
        if (!(infix[i] == ' ')) {
            retStr += infix[i];
        }
    }
    
    return retStr;
}

//Checks to see if infix is valid
bool isInfixValid(string infix) {
    const string expressions = "&|!";
    char currChar;
    char nextChar;
    
    //Need to check that the number of ( is equal to the number of )
    int num_LeftParenths = 0;
    int num_RightParenths = 0;
    
    //Need to check that the number of operators is not more than the number of characters
    //The number of operators has to 1 less than the number of chars
    //i.e. (a|b), (a|b)|a
    
    int num_Operators = 0;
    int num_Chars = 0;
    
    //The number of ! must not be more than the number of characters
    //Assuming that each character gets a !, num_ex can't be > than num_Chars
    int num_ex = 0;
    
    //Iterate through the infix
    for (int i = 0; i < infix.size(); i++) {
        //Records the currect character being checked in the infix
        currChar = infix[i];
        
        //If curr is a letter but not a lowercase, return false
        if (isalpha(currChar) && !(islower(currChar))) {
            //cerr << "not a lower case letter" << endl;
            return false;
        }
        
        //Recording numbers:
        if (isalpha(currChar)) {
            //cerr << "found letter, adding one to numChar" << endl;
            num_Chars++;
        }
        
        else if (currChar == '(') {
            //cerr << "found (, adding one to num(" << endl;
            num_LeftParenths++;
        }
        
        else if (currChar == ')') {
            //cerr << "found ), adding one to num)" << endl;
            num_RightParenths++;
        }
        
        else if (!isalpha(currChar)) {
            if (expressions.find(currChar) == string::npos) {
                //cerr << "couldnt find " << currChar << endl;
                return false;
            }
            
            if (currChar == '!') {
                num_ex++;
            }
            
            else {
                num_Operators++;
            }
        }
    }
    
    //Checking the numbers
    if (num_RightParenths != num_LeftParenths) {
        //cerr << "num( != num): " << num_LeftParenths << "vs. " << num_RightParenths << endl;
        return false;
    }
    
    if (num_Chars != num_Operators+1) {
        //cerr << "numChar != numOperators+1 " << num_Chars << "vs. " << num_Operators << endl;
        return false;
    }
    
    if (num_ex > num_Chars) {
        return false;
    }
    
    //Now checking the order of characters vs operator
    for (int i = 0; i < infix.size()-1; i++) {
        currChar = infix[i];
        nextChar = infix[i+1];
        
        //cerr << "curr " << currChar << endl;
        //cerr << "next " << nextChar << endl;
        
        //Two characters can't be right next to each other
        if (isalpha(currChar)) {
            if (isalpha(nextChar)) {
                return false;
            }
        }

        else if ( (currChar == '&') || (currChar == '|') ) {
             //Operator can't start the infix
            if (i-1 < 0) {
                return false;
            }
            //cerr << expressions.find(currChar) << endl;
            
            char prevChar = infix[i-1];
            
            //The one before an operator must be a character or a close parenthese
            if ( (!isalpha(prevChar)) && (prevChar != ')') ) {
                return false;
            }
            
            //The one after an operator must be a character, new open parenthese, or !
            if ( (!(isalpha(nextChar))) && (nextChar != '(') && (nextChar != '!') ) {
                return false;
            }
        }
        
        else if (currChar == '!') {
            //The one after a ! must be a char, new open parentheses, or another !
            if ( (!(isalpha(nextChar))) && (nextChar != '(') && (nextChar != '!')) {
                return false;
            }
        }
        
        else if (currChar == '(') {
            //The one after a new open parenthese must be a char, another open parenthese or a !
            if ( (!(isalpha(nextChar))) && (nextChar != '(') && (nextChar != '!')) {
                return false;
            }
            
            //Note: there's no need to check for ) because all the cases have been covered by the above already
        }
    }
    
    return true;
}


//Return the precedence of the input operator
//Following convention, ! has higher precedence than &, which has higher precedence than |
int numPrece(char exp) {
    if (exp == '!') {
        return 3;
    }
    
    if (exp == '&') {
        return 2;
    }
    
    if (exp == '|') {
        return 1;
    }
    
    else {
        return 0;
    }
}

//Convert the infix to postfix and return the postfix
//Algorithm is given by the textbook
//My algorithm used is provided by my TA Angelina Poole
string infixToPostfix(string infix, string postfix) {
    string retStr;
    const string expressions = "|&!";
    stack<char> tempStack;
    
    //Start at the left-most token
    for (int i = 0; i < infix.size(); i++) {
        //cerr << "running!" << endl;
        //cerr << "infix: " << infix[i] << endl;
        
        //If it's a char, append it to the end of postfix string
        if (isalpha(infix[i])) {
            retStr += infix[i];
        }
        
        //If its a (, push it onto the stack
        else if (infix[i] == '(') {
            tempStack.push(infix[i]);
        }
        
        //If it's a ), pop operators off the stack and append onto postfix string until a matching ( is popped
        else if (infix[i] == ')') {
            while (tempStack.top() != '(') {
                retStr += tempStack.top();
                tempStack.pop();
            }
    
            tempStack.pop();
        }
        
        //If it's an operator
        else if (expressions.find(infix[i]) != string::npos) {
            
            //And the stack is empty
            if (tempStack.empty()) {
                //Push operator on the stack
                tempStack.push(infix[i]);
            }
            
            //If stack is not empty
            else {
                //Pop all operators with greater or equal precendence off the stack and append onto the postfix string
                while ( (!(tempStack.empty())) && (tempStack.top() != '(')) {
                    if ((numPrece(tempStack.top()) >= numPrece(infix[i]))) {
                        retStr += tempStack.top();
                        tempStack.pop();
                    }
                    
                    else {
                        break;
                    }
                }
                //Stop when you reach an operator with lower precendence
                //Push the new operator onto the stack
                tempStack.push(infix[i]);
            }
        }
    }
    
    //When all infix tokens are gone, pop each operator and append it to the postfix string
    while (!tempStack.empty()) {
        retStr += tempStack.top();
        tempStack.pop();
    }
    
    //Return the postfix
    return retStr;
}


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    //cerr << "starting" << endl;
    
    //Remove all spaces from infix
    infix = infixWithoutSpace(infix);
    
    //cerr << infix << endl;
    
    // If infix is a syntactically valid infix boolean expression whose
    //   only operands are single lower case letters (whether or not they
    //   appear in the values sets), then postfix is set to the postfix
    //   form of the expression.  If not, postfix might or might not be
    //   changed, result is unchanged, and the function returns 1.
    if (!isInfixValid(infix)) {
        //cerr << "Not valid infix" << endl;
        return 1;
    }
    
    postfix = infixToPostfix(infix, postfix);
    //cerr << postfix << endl;
    
    //   If infix is a syntactically valid infix boolean expression whose
    //   only operands are single lower case letters:
    //
    //      If every operand letter in the expression appears in either
    //      trueValues or falseValues but not both, then result is set to the
    //      result of evaluating the expression (using for each letter in the
    //      expression the value true if that letter appears in trueValues or
    //      false if that letter appears in false values) and the function
    //      returns 0.
    //
    //      Otherwise, result is unchanged and the value the function returns
    //      depends on these two conditions:
    //        at least one letter in the expression is in neither the
    //            trueValues nor the falseValues sets; and
    //        at least one letter in the expression is in both the
    //            trueValues and the falseValues set.
    //      If only the first condition holds, the function returns 2; if
    //      only the second holds, the function returns 3.  If both hold
    //      the function returns either 2 or 3 (and the function is not
    //      required to return the same one if called another time with the
    //      same arguments).
    
    stack<bool> operandStack;
    
    for (int i = 0; i < postfix.size(); i++) {
        if (isalpha(postfix[i])) {
            if ( (!trueValues.contains(postfix[i])) && (!falseValues.contains(postfix[i])) ) {
                return 2;
            }
            
            else if ( trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]) ) {
                return 3;
            }
            
            else {
                //Push the truth values of the postfix into the stack
                if (trueValues.contains(postfix[i])) {
                    operandStack.push(true);
                }
                
                else {
                    operandStack.push(false);
                }
            }
        }
        
        else {
            //when evaluating:
            //If you encouter a !, the ! affects the truth value of the boolean immediately at the top of the stack
            if (postfix[i] == '!') {
                bool tempBool = operandStack.top();
                operandStack.pop();
                //Evaluate the truth value accoridngly and push the changed value onto the stack again
                tempBool = !tempBool;
                operandStack.push(tempBool);
            }
            
            else {
                //Otherwise, each operator evaluates the top two booleans of the stack
                bool Bool1 = operandStack.top();
                operandStack.pop();
                bool Bool2 = operandStack.top();
                operandStack.pop();
                
                //Evaluate the top two values accordingly to the operator
                if (postfix[i] == '|') {
                    bool resultBool = (Bool1 || Bool2);
                    operandStack.push(resultBool);
                }
                
                else {
                    bool resultBool = (Bool1 && Bool2);
                    operandStack.push(resultBool);
                }
            }
        }
    }
    
    //The last boolean left in the stack is the truth value of the entire expression
    //Store it in result
    result = operandStack.top();
    
    //Everything was evaluated so return 0
    return 0;
}


int main() {
    
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    
    
    
        assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
               &&  pf == "ff!tn&&|"  &&  !answer);
     
    
        assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
        trues.insert('x');
        assert(evaluate("((x))", trues, falses, pf, answer) == 3);
        falses.erase('x');
    
        assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
        trues.erase('w');
        assert(evaluate("w| f", trues, falses, pf, answer) == 2);
        falses.insert('w');
        assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    
    
    /*
    string trueChars  = "aclu";
    string falseChars = "nsx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    
     assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n) ", trues, falses, pf, answer) == 0  &&
            answer);
    
    
    */
    cout << "Passed" << endl;
}
