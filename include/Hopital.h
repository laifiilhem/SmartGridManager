#ifndef HOPITAL_H
#define HOPITAL_H

#include "Maison.h"

class Hopital : public Maison {
private:
    int joursAutonomieGroupe;

public:
    Hopital(const std::string& id, double prod, double conso, 
            const std::string& region, double batterie, int autonomie);
    
    void afficherInfo() const override;
    void simulerCoupure(int heures);
    
    int getJoursAutonomie() const;
};

#endif