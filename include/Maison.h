#ifndef MAISON_H
#define MAISON_H

#include "UniteElectrique.h"
#include <string>

class Maison : public UniteElectrique {
private:
    std::string region;
    double batterieCapacite;

public:
    Maison(const std::string& id, double prod, double conso, 
           const std::string& region, double batterie);
    
    double getSolde() const override;
    void afficherInfo() const override;
    
    double consommationMoyenne() const;
    void utiliserBatterie(double quantite);
    
    std::string getRegion() const;
    double getBatterieCapacite() const;
};

#endif