#include "Hopital.h"

Hopital::Hopital(const std::string& id, double prod, double conso, 
                 const std::string& region, double batterie, int autonomie)
    : Maison(id, prod, conso, region, batterie), joursAutonomieGroupe(autonomie) {}

void Hopital::afficherInfo() const {
    // Implémentation simplifiée pour Qt
}

void Hopital::simulerCoupure(int heures) {
    double consoTotale = consommationMoyenne() * heures;
    utiliserBatterie(std::min(consoTotale, getBatterieCapacite()));
}

int Hopital::getJoursAutonomie() const { return joursAutonomieGroupe; }