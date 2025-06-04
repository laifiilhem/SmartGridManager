#ifndef SMART_GRID_MANAGER_H
#define SMART_GRID_MANAGER_H

#include "UniteElectrique.h"
#include <vector>
#include <memory>

class SmartGridManager {
private:
    std::vector<std::unique_ptr<UniteElectrique>> unites;

public:
    void ajouterUnite(std::unique_ptr<UniteElectrique> unite);
    void afficherUnites() const;
    void miseAJourConsoProd(const std::string& id, double prod, double conso);
    void simulerCoupure();
    double calculerSoldeTotal() const;
    
    const std::vector<std::unique_ptr<UniteElectrique>>& getUnites() const;
};

#endif