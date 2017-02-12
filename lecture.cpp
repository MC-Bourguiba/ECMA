
#include <ilcplex/ilocplex.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <set>

ILOSTLBEGIN
using namespace std;
IloEnv env;
typedef IloArray<IloIntArray> DataMatrix;
DataMatrix A; //le pattern = le sous graphe
DataMatrix B; //la target = le grand graphe
struct Edge {
    IloInt i;
    IloInt j;
};
typedef IloArray<Edge> Edges;
Edges setOfEdgeA(env);
Edges setOfEdgeB(env);

int nA;
int nB; //IloInt nB;
int eA;
int eB;

void getData(const IloEnv env, char nom_fichier_A[], char nom_fichier_B[]) {
	//lit les matrices A et B depuis les fichiers
	int deg;
	int j;
	ifstream fichier(nom_fichier_A); 
	if(fichier) {
		//lire le n
		fichier >> nA;
		// lire A
		A = DataMatrix(env, nA);
		for(int i=0; i < nA; i++){
			A[i]=IloIntArray(env);
			for(int j = 0; j < nA; j++){
				A[i].add(0);
			}
		}
		for(int i=0; i < nA; i++){
			fichier >> deg;
			for(int d=0; d < deg; d++){
				fichier >> j;
				A[i][j] = 1;
			}
		}
		fichier.close(); 
	}
    
	ifstream fichierB(nom_fichier_B); 
	if(fichierB) {
		//lire le n
		fichierB >> nB;
		// lire B
		B = DataMatrix(env, nB);
		for(int i=0; i < nB; i++){
			B[i]=IloIntArray(env);
			for(int j = 0; j < nB; j++){
				B[i].add(0);
			}
		}
		for(int i=0; i < nB; i++){
			fichierB >> deg;
			for(int d=0; d < deg; d++){
				fichierB >> j;
				B[i][j] = 1;
			}
		}
		fichierB.close();
	}
   
	cout << "Lecture terminee" << endl;
	//Affichage pour OPL
    
	int degA[nA];
	//int degmaxA[40];
	int degB[nB];
	//int degmaxB[200];
	cout << "A = {" << endl;
	for(int i=0; i < nA; i++){
		degA[i] = 0;
		for(int j = 0; j < nA; j++){
			if(A[i][j] == 1){
				cout << "<" << i+1 <<"," << j+1 <<">,";
				degA[i] =degA[i]+1;
                Edge a ;
                a.i = IloInt(i+1);
                a.j = IloInt(j+1);
                setOfEdgeA.add(a);
                eA+=1;
                
			}
		}
	}
    
	cout << "};" << endl;
    
	cout << "B={" << endl;
    
	for(int i=0; i < nB; i++){
		degB[i] = 0;
		for(int j = 0; j < nB; j++){
			if(B[i][j] == 1){
				cout << "<" << i+1 <<"," << j+1 <<">,";
				degB[i] =degB[i] +1;
                Edge b ;
                b.i = i+1;
                b.j=j+1;
                setOfEdgeB.add(b);
                eB+=1;
                
			}
		}
		//cout << endl;
	}
	cout << "};" << endl;
	cout << "degA = [" << endl;
	for(int i=0; i <nA; i++){
		cout << degA[i] << ", ";
	}
	cout << "];" << endl;
	cout << "degB = [" << endl;
	for(int i=0; i < nB; i++){
		cout << degB[i] << ", ";
	}
	cout << "];" << endl;
    
    
}

static void setData (IloModel model, IloNumVarArray x, IloRangeArray con, IloInt na,IloInt nb, DataMatrix A, DataMatrix B)
{
    IloEnv env = model.getEnv();
}
int
main (void) {
   
   try {
      IloModel model(env);

      IloNumVarArray var(env);
      IloRangeArray con(env);
      DataMatrix edge = DataMatrix(env,2);
       

	  char spattern[] = "pattern"; //"A.02/pattern";
	  char starget[] = "target"; //"A.02/target";
	  char liste[] = "0123456789";
	  
      getData(env, spattern, starget);
      cout << "Test de l'heuristique sur " << spattern << endl;
	  
	  
	  //setdata(model, var, p, E, con);
	 /* IloRangeArray cuts(env);
	  IloExprArray lhs(env);
	  IloNumArray rhs(env);
	  makeCuts(var,lhs,rhs,n);*/

   //   IloCplex cplex(model);
	  ///*cplex.setParam(IloCplex::CutsFactor, 1.0); 
	  //cplex.setParam(IloCplex::EachCutLim, 0); 
	  //cplex.setParam(IloCplex::PreInd, 0);*/
   //   cplex.solve();

   //   env.out() << "Solution status = " << cplex.getStatus() << endl;
   //   env.out() << "Solution value  = " << cplex.getObjValue() << endl;

   //   IloNumArray vals(env);
   //   cplex.getValues(vals, var);
   //   env.out() << "Values        = " << vals << endl;
   //   cplex.getSlacks(vals, con);
   //   env.out() << "Slacks        = " << vals << endl;

   //   cplex.exportModel("pl.lp");
   }
   catch (IloException& e) {
      cerr << "Concert exception caught: " << e << endl;
   }
   catch (...) {
      cerr << "Unknown exception caught" << endl;
   }
    for (int k=0; k < eA; k++){
        cout << "Aretes de la matrice A" << endl;
        cout << setOfEdgeA[k].i << endl;
        cout << setOfEdgeA[k].j << endl;
    }
   env.end();
   return 0;

}  
