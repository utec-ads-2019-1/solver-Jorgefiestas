#ifndef SOLVER_H
#define SOLVER_H

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <iostream>

using namespace std; 

class EquationSolver{
    private:
        string text_equation;
        unordered_map<int, stack<double>> numbers;
        unordered_map<char, double> variables;
        unordered_set<char> operators {'+', '-', '*', '/', '^'};
    public:
        EquationSolver(string equation){
            text_equation = equation;
        }

        static EquationSolver* buildFromEquation(string equation){
            return new EquationSolver(equation);
        }

        double operate();
        double solve_equation(string &);
        double solve(int l, int r, string &);

        void map_variables();
        void format_equation(string &);
        void map_number(int &, string &, string &);
        void solve_bracket(int &, string &, string &);
        void simplify_sign();
};

#endif
