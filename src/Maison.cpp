#include "Maison.h"

Maison::Maison(const std::string& id, double prod, double conso, 
               const std::string& region, double batterie)
    : UniteElectrique(id, prod, conso), region(region), batterieCapacite(batterie) {}

double Maison::getSolde() const {
    return energieProduite - energieConsommee;
}

void Maison::afficherInfo() const {
    // Implémentation simplifiée pour Qt (sera affiché dans le tableau)
}

double Maison::consommationMoyenne() const {
    return energieConsommee / 24.0;
}

void Maison::utiliserBatterie(double quantite) {
    batterieCapacite = std::max(0.0, batterieCapacite - quantite);
}

std::string Maison::getRegion() const { return region; }
double Maison::getBatterieCapacite() const { return batterieCapacite; }