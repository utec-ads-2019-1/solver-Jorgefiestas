#include "equationSolver.h"

double EquationSolver::operate(){
    map_variables();
    simplify_sign();
    format_equation();
    map_brackets();
    return solve(0, equation.size()-1);
}

double EquationSolver::solve(int l, int r){
    if(brackets.find(l) != brackets.end() && brackets[l] == r){
        return solve(l+1, r-1);
    }
    if(l == r){
        if(equation[l] == '?'){
            return numbers[l];
        }
        else{
            return variables[equation[l]];
        }
    }
    
    unordered_map<char, int> op_pos;
    for(int i = l; i<=r; i++){
        if(equation[i] == '('){
            i = brackets[i];
            continue;
        }
        if(operators.find(equation[i]) != operators.end()){
            op_pos[equation[i]] = i;
        }
    }

    if(op_pos.find('+') != op_pos.end()){
        return solve(l, op_pos['+']-1) + solve(op_pos['+']+1, r);
    }
    if(op_pos.find('-') != op_pos.end()){
        return solve(l, op_pos['-']-1) - solve(op_pos['-']+1, r);
    }
    if(op_pos.find('*') != op_pos.end()){
        return solve(l, op_pos['*']-1) * solve(op_pos['*']+1, r);
    }
    if(op_pos.find('/') != op_pos.end()){
        return solve(l, op_pos['/']-1) / solve(op_pos['/']+1, r);
    }
    if(op_pos.find('^') != op_pos.end()){
        return pow(solve(l, op_pos['^']-1), solve(op_pos['^']+1, r));
    }

    return 0;
}

void EquationSolver::map_variables(){
    for(char x : equation){
        if(x < 'a' || x > 'z') continue;
        if(variables.find(x) != variables.end()) continue;
        cout<<"Please insert the value of variable "<<x<<": ";
        cin>>variables[x];
    }
}

void EquationSolver::simplify_sign(){
    string simplified_equation;
    for(int i = 0; i<equation.size(); i++){
        if(equation[i] != '+' && equation[i] != '-'){
            simplified_equation += equation[i];
            continue;
        }

        int negcnt = 0, j;
        for(j=i; j < equation.size() && (equation[j] == '+' || equation[j] == '-'); j++){
            if(equation[j] == '-') negcnt++;
        }

        if(negcnt%2 == 0) simplified_equation += '+';
        else simplified_equation += '-';
        i = j-1;
    }
    equation = simplified_equation;
}

void EquationSolver::format_equation(){
    string formated_equation;
    for(int i = 0; i<equation.size(); i++){
        if((equation[i] >= '0' && equation[i] <= '9') || equation[i] == '-' || equation[i] == '+') {
            map_number(i, formated_equation);
        }
        else{
            formated_equation += equation[i];
        }
    }
    equation = formated_equation;
}

void EquationSolver::map_number(int &i, string &formated_equation){
    if(equation[i] == '+'){
        if(i-1 >= 0 && operators.find(equation[i-1]) == operators.end()){
            formated_equation += '+';
        }
        return;
    }

    int j = 0;
    if(equation[i] == '-'){
        if(i - 1 >= 0 && operators.find(equation[i-1]) == operators.end()){
            formated_equation += '-';
            return ;
        }
        j++;
    }

    while(i+j < equation.size() && ((equation[i+j] >= '0' && equation[i+j] <= '9') || equation[i+j] == '.')) j++;

    double number = stod(equation.substr(i, j));
    numbers[formated_equation.size()] = number;

    formated_equation += '?';
    i += j-1;
}

void EquationSolver::map_brackets(){
    stack<int> bracket_stack;
    for(int i = 0; i<equation.size(); i++){
        char x = equation[i];
        if(x == '('){
            bracket_stack.push(i);
        }
        else if(x == ')'){
            brackets[bracket_stack.top()] = i;
            bracket_stack.pop();
        }
    }
}


