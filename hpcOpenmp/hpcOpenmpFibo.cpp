
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>

#include "omp.h"

// calcule le Nieme terme de la suite de "Fibonacci modulo 42"
// precondition : N >= 0
int FibonacciMod42(int N)
{
    int f_curr = 0;
    int f_prec = 1;
    for (int i=1; i<=N; i++)
    {
        int tmp = f_curr;
        f_curr = (f_curr + f_prec) % 42;
        f_prec = tmp;
    }
    return f_curr;
}

int main(int argc, char ** argv)
{
    // verifie les parametres de la ligne de commande
    if (argc != 3)
    {
        std::cout << "usage: " << argv[0] << " <nbData>" << std::endl;
        std::cout << "usage: " << argv[0] << " <nbThreads>" << std::endl;
        return -1;
    }

    // getting number of element
    int nbData = std::stoi(argv[1]);
    int nbThread = std::stoi(argv[2]);

    std::cout << "P | T(P) b | T(P) c | S(P) b | S(P) c |" << std::endl;
    std::cout << "--+--------+--------+--------+--------|" << std::endl;

    for (int i = 1; i <= nbThread; i++){
     
      // OLD PART
      // start chrono
      double startTimeOld = omp_get_wtime();

      // calcule le tableau de donnees
      std::vector<int> dataOld(nbData); 
    
      for (int i=0; i<nbData; i++)
      {
          dataOld[i] = FibonacciMod42(i);
      }

      // stop chrono
      double endTimeOld = omp_get_wtime();
      double totalTimeOld = endTimeOld - startTimeOld;

      // BLOCK PART 
      // start chrono
      double startTimeB = omp_get_wtime();

      // calcule le tableau de donnees
      std::vector<int> dataB(nbData); 
    
      #pragma omp parallel for num_threads(i) 
      for (int i=0; i<nbData; i++)
      {
          dataB[i] = FibonacciMod42(i);
      }

      // stop chrono
      double endTimeB = omp_get_wtime();
      double totalTimeB = endTimeB - startTimeB;


      // CYCL PART
      // start chrono
      double startTimeC = omp_get_wtime();

      // calcule le tableau de donnees
      std::vector<int> dataC(nbData);

      #pragma omp parallel for schedule(static, 1) num_threads(i)
      for (int i=0; i<nbData; i++)
      {
          dataC[i] = FibonacciMod42(i);
      }
 
      // stop chrono
      double endTimeC = omp_get_wtime();
      double totalTimeC = endTimeC - startTimeC;


      double speedUpB = totalTimeOld / totalTimeB;
      double speedUpC = totalTimeOld / totalTimeC;

      
      std::cout << std::fixed;
      std::cout << std::setprecision(4);
      std::cout << i << " | " << totalTimeB << " | " << totalTimeC << " | " << speedUpB << " | " << speedUpC << " | " << std::endl;

    }
      
    // Unused code
    
    // ecrit les donnees calculees dans un fichier
    //std::ofstream ofs("output.txt");
    //for (int x : data)
    //{
    //    ofs << x << ' ';
    //}

    return 0;
}

