#ifndef MOTEUR_HPP
#define MOTEUR_HPP
#include <string>

enum douleur{pulse, brule};
enum critere{complexite_premisses, plus_premisses, recence_regle, recence_deduit};

class Moteur{
  
private:
//   float * temperature;
//   bool fatigue;
//   bool * visite_afrique_asie;
//   char sexe;
//   unsigned int age;
//   bool oedeme;
//   bool chaleur;
//   douleur d;
//   int douleur_intensite;
//   bool rougeur;
//   bool alteration_fonctionnelle;
//   //--------------
//   bool infection;
  
public:
  Moteur();
  bool inflammation();
  bool infection(bool fatigue, float temperature,bool inflammation);
  
  void run(critere c);
};


#endif