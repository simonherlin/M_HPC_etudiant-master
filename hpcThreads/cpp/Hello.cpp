#include <iostream>
#include <thread>

namespace Hello {

  // fonction qui affiche l'id du thread qui l'execute
  void noyauCalcul() {
    std::thread::id idThread = std::this_thread::get_id();
    std::cout << "Bonjour, je suis le thread " << idThread << std::endl;
  }

  void hello() {
    // affiche l'id du thread principal
    // noyauCalcul();

    // exécute le noyau de calcul en parallèle sur 2 threads
    
    // cree deux threads qui affiche leur id
    std::thread thread1(noyauCalcul);
    std::thread thread2(noyauCalcul);

    // attend la fin de l'execution des threads
    thread1.join();
    thread2.join(); 

  }

}  // namespace Hello

