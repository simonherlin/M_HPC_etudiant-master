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
  
  void calculerBloc(std::vector<int> &data, int begin, int end){
    for(unsigned i = begin; i < end; i++){
      data[i] = FibonacciMod42(i);
    }  
  }  

  std::vector<int> fiboBlocs(int nbData) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData); 
    // calculer sur deux threads, par bloc
    int dataSize = data.size();
    std::thread th1(Fibo::calculerBloc, std::ref(data), 0, dataSize/2);
    std::thread th2(Fibo::calculerBloc, std::ref(data), dataSize/2, dataSize);
    th1.join();
    th2.join();

    return data;
  }

  //////////////////////////////////////////////////////////////////////

  void calculCyclique(std::vector<int> &data, int begin, int step){
    for(unsigned i = begin; i < data.size(); i += step){
      data[i] = FibonacciMod42(i);
    }	
  }

  std::vector<int> fiboCyclique2(int nbData) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData); 
    // calculer sur deux threads, cycliquement
    std::thread th1(Fibo::calculCyclique, std::ref(data), 0, 2);
    std::thread th2(Fibo::calculCyclique, std::ref(data), 1, 2);

    th1.join();
    th2.join();

    return data;
  }

  //////////////////////////////////////////////////////////////////////

  std::vector<int> fiboCycliqueN(int nbData, int nbProc) {
    // cree le tableau de donnees a calculer
    std::vector<int> data(nbData);
    std::vector<std::thread> threads(nbProc);

    for(unsigned i = 0; i < threads.size(); i++){
	    threads[i] = std::thread(Fibo::calculCyclique, std::ref(data), i, nbProc);
    }
     
    for(unsigned i = 0; i < threads.size(); i++){
	    threads[i].join();
    } 
    return data;
  }

  //////////////////////////////////////////////////////////////////////

  void fiboCycliqueNFake(int nbData, int nbProc) {
    std::vector<int> data(nbData);
    std::vector<std::thread> threads(nbProc);

    for(unsigned i = 0; i < threads.size(); i++){
	    threads[i] = std::thread(Fibo::calculCyclique, std::ref(data), i, nbProc);
    }
     
    for(unsigned i = 0; i < threads.size(); i++){
	    threads[i].join();
    }
  }

} // namespace Fibo