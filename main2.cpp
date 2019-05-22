#include <iostream>
#include "equationSolver/equationSolver.h"

int main(){
    string eq;
    while(cin>>eq){
        if(eq=="exit") break;
        EquationSolver* es = EquationSolver::buildFromEquation(eq);
        cout<<es->operate()<<endl;
    }
    return 0;
}
