#ifndef MOTEUR_HPP
#define MOTEUR_HPP
#include <string>
#include <map>
enum fait{};
enum critere{complexite_premisses, plus_premisses, recence_regle, recence_deduit};

class Moteur{
  
private:
    std::map<std::string, bool*> BF;
public:
  Moteur();
  bool inference_inflammation();
  bool inference_infection(bool *fatigue, bool *inflammation);
  
  void run_critere(critere c);
  void run_paquets();
};


#endif
