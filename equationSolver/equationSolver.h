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
        string equation;
        unordered_map<int, int> numbers;
        unordered_map<char, double> variables;
        unordered_map<int, int> brackets;
        unordered_set<char> operators {'+', '-', '*', '/', '^'};

    public:
        EquationSolver(string equation){
            this->equation = equation;
        }

        static EquationSolver* buildFromEquation(string equation){
            return new EquationSolver(equation);
        }

        double operate();
        double solve(int l, int r);

        void map_variables();
        void format_equation();
        void map_number(int &, string &);
        void map_brackets();
        void simplify_sign();
};

#endif
