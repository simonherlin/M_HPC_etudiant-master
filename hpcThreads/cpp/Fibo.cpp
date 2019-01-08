#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

namespace Fibo {

  // calcule le Nieme terme de la suite de "Fibonacci modulo 42"
  // precondition : N >= 0
  int FibonacciMod42(int N) {
    int f_curr = 0;
    int f_prec = 1;
    for (int i=1; i<=N; i++) {
      int tmp = f_curr;
      f_curr = (f_curr + f_prec) % 42;
      f_prec = tmp;
    }
    return f_curr;
  }

  //////////////////////////////////////////////////////////////////////

  // fonction pour repartir les calculs
  void calculerTout(std::vector<int> &data) {
    // effectue tous les calculs
    for (unsigned i=0; i<data.size(); i++) {
      data[i] = FibonacciMod42(i);
    }
  };

  std::vector<int> fiboSequentiel(int nbData) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData); 
    // calcule les donnees sequentiellement
    calculerTout(data);
    return data;
  }

  //////////////////////////////////////////////////////////////////////

  std::vector<int> fiboBlocs(int nbData) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData); 
    // calculer sur deux threads, par bloc
    // TODO
    return data;
  }

  //////////////////////////////////////////////////////////////////////

  std::vector<int> fiboCyclique2(int nbData) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData); 
    // calculer sur deux threads, cycliquement
    // TODO
    return data;
  }

  //////////////////////////////////////////////////////////////////////

  std::vector<int> fiboCycliqueN(int nbData, int nbProc) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData); 
    // calculer sur N threads, cycliquement
    // TODO
    return data;
  }

  //////////////////////////////////////////////////////////////////////

  void fiboCycliqueNFake(int nbData, int nbProc) {
    // calculer sur N threads, cycliquement, en ignorant le résultat
    // TODO
    
  }

}  // namespace Fibo

