#include <iostream>
#include <string>

using namespace std;

struct CNode {
    char data;
    CNode* next;
};

struct DNode {
    double data;
    DNode* next;
};

struct CStack {
    CNode* top;
};

struct DStack {
    DNode* top;
};

// ------------------ implement double stack ------------------
void Initialize(DStack &S) {
    S.top = NULL;
}
     
bool IsEmpty(DStack S) {
    return S.top == NULL;
}

void Push(DStack &S, double key) {
    DNode* p = new DNode;
    p->data = key;
    p->next = S.top;
    S.top = p;
}

void Pop(DStack &S) {
    if (S.top == NULL)
        return;
    DNode* p = S.top;
    S.top = S.top->next;
    delete p;
}

double Peek(DStack &S) {
    return S.top->data;
}

// ------------------ implement char stack ------------------
void Initialize(CStack &S) {
    S.top = NULL;
}
     
bool IsEmpty(CStack S) {
    return S.top == NULL;
}

void Push(CStack &S, char key) {
    CNode* p = new CNode;
    p->data = key;
    p->next = S.top;
    S.top = p;
}

void Pop(CStack &S) {
    if (S.top == NULL)
        return;
    CNode* p = S.top;
    S.top = S.top->next;
    delete p;
}

char Peek(CStack &S) {
    return S.top->data;
}
// -----------------------------------------------------------

int Priority(char token) {
    if (token == '*' || token == '/') 
        return 2;
    if (token == '+' || token == '-')
        return 1;
    return 0;
}

string Standardization(string &infix) { //remove space insert 0 (-x) -> (0 - x)
    string result = "";
    for (int i = 0; i < infix.size(); ++i) {
        if (infix[i] == ' ')
            continue;
        if (Priority(infix[i]) == 1) {
            if (i == 0 || (Priority(result.back()) == 1 || result.back() == '('))
                result += '0';
        }
        result += infix[i];
    }
    return result;
}

string InfixToRPN(string &infix) {
    string RPN = "";
    CStack S;
    Initialize(S);
    for (int i = 0; i < infix.size(); ++i) {
        if (isdigit(infix[i])) { // operand
            while (i < infix.size() && isdigit(infix[i]))
                RPN += infix[i++];
            RPN += " ";
        } 
        if (infix[i] == '(') {
            Push(S, infix[i]);
        }
        if (infix[i] == ')') { 
            while (Peek(S) != '(') {
                RPN += Peek(S);
                RPN += " ";
                Pop(S);
            }
            Pop(S); // remove (
        } 
        if (infix[i] == '*' || infix[i] == '+' || infix[i] == '-' || infix[i] == '/') { //operator
            while (!IsEmpty(S) && Priority(infix[i]) <= Priority(Peek(S))) { 
                RPN += Peek(S);
                RPN += " ";
                Pop(S);
            }
            Push(S, infix[i]);
        }
    }
    while (!IsEmpty(S)) RPN += Peek(S), RPN += " ", Pop(S);
    return RPN;
}

void Process(DStack &S, char token) {
    double y = Peek(S); Po p(S);
    double x = Peek(S); Pop(S);
    if (token == '+') Push(S, x + y);
    if (token == '-') Push(S, x - y);
    if (token == '*') Push(S, x * y);
    if (token == '/') Push(S, x / y);
}

double Calculate(string &RPN) {
    DStack S;
    Initialize(S);
    for (int i = 0; i < RPN.size(); ++i) {
        if (isdigit(RPN[i])) {
            double num = 0;
            while (i < RPN.size() && isdigit(RPN[i]))
                num = num * 10 + RPN[i++] - '0';
            Push(S, num);
        } else if (RPN[i] != ' ') {
            Process(S, RPN[i]);
        }
    }
    double result = Peek(S); Pop(S);
    return result;
}   

int main() {
    string infix = "2-(-5)";
    //cin >> infix;
    infix = Standardization(infix);
    cout << infix << endl;
    string RPN = InfixToRPN(infix);
    cout << RPN << endl;
    cout << Calculate(RPN);
    return 0;
}