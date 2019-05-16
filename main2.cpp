#include <bits/stdc++.h>
#include "equationSolver/equationSolver.h"
using namespace std;

int main(){
    string equation;
    cin>>equation;
    EquationSolver es(equation);
    cout<<es.operate()<<endl;
    return 0;
}
