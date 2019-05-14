#include "equationSolver.h"

double EquationSolver::operate(){
    map_variables();
    simplify_sign();
    return solve_equation(text_equation);
}

double EquationSolver::solve_equation(string &equation){
    format_equation(equation);
    double ans = solve(0, equation.size()-1, equation);
    return ans;
}

double EquationSolver::solve(int l, int r, string &equation){
    if(l == r){
        if(equation[l] == '?'){
            double num =numbers[l].top();
            numbers[l].pop();
            return num;
        }
        else{
            return variables[equation[l]];
        }
    }
    
    unordered_map<char, int> op_pos;
    for(int i = l; i<=r; i++){
        if(operators.find(equation[i]) != operators.end()){
            op_pos[equation[i]] = i;
        }
    }

    if(op_pos.find('+') != op_pos.end())
        return solve(l, op_pos['+']-1, equation) + solve(op_pos['+']+1, r, equation);
    if(op_pos.find('-') != op_pos.end())
        return solve(l, op_pos['-']-1, equation) - solve(op_pos['-']+1, r, equation);
    if(op_pos.find('*') != op_pos.end()) 
        return solve(l, op_pos['*']-1, equation) * solve(op_pos['*']+1, r, equation);
    if(op_pos.find('/') != op_pos.end())
        return solve(l, op_pos['/']-1, equation) / solve(op_pos['/']+1, r, equation);
    if(op_pos.find('^') != op_pos.end())
        return pow(solve(l, op_pos['^']-1, equation), solve(op_pos['^']+1, r, equation));

    return 0;
}

void EquationSolver::map_variables(){
    for(char x : text_equation){
        if(x < 'a' || x > 'z') continue;
        if(variables.find(x) != variables.end()) continue;
        cout<<"Please insert the value of variable "<<x<<": ";
        cin>>variables[x];
    }
}

void EquationSolver::simplify_sign(){
    string simplified_equation;
    for(int i = 0; i<text_equation.size(); i++){
        if(text_equation[i] != '+' && text_equation[i] != '-'){
            simplified_equation += text_equation[i];
            continue;
        }

        int negcnt = 0, j;
        for(j=i; j < text_equation.size() && (text_equation[j] == '+' || text_equation[j] == '-'); j++){
            if(text_equation[j] == '-') negcnt++;
        }

        if(negcnt%2 == 0) simplified_equation += '+';
        else simplified_equation += '-';
        i = j-1;
    }
    text_equation = simplified_equation;
}

void EquationSolver::format_equation(string &equation){
    string formated_equation;
    for(int i = 0; i<equation.size(); i++){
        if((equation[i] >= '0' && equation[i] <= '9') || equation[i] == '-' || equation[i] == '+') {
            map_number(i, equation, formated_equation);
        }
        else if(equation[i] == '('){
            solve_bracket(i, equation, formated_equation);
        }
        else{
            formated_equation += equation[i];
        }
    }
    equation = formated_equation;
}

void EquationSolver::map_number(int &i, string & equation, string &formated_equation){
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
    numbers[formated_equation.size()].push(number);

    formated_equation += '?';
    i += j-1;
}

void EquationSolver::solve_bracket(int &i, string &equation, string &formated_equation){
    i++;
    int bracket_count = 0, j = 0;
    while(bracket_count != 0 || equation[i+j] != ')'){
        if(equation[i+j] == '(') bracket_count++;
        if(equation[i+j] == ')') bracket_count--;
        j++;
    }

    string subequation = equation.substr(i, j);
    numbers[formated_equation.size()].push(solve_equation(subequation));
    formated_equation += '?';
    i += j;
}

