#include "EtablissementPublic.h"

EtablissementPublic::EtablissementPublic(const std::string& id, double prod, double conso, 
                                         const std::string& type)
    : UniteElectrique(id, prod, conso), typeEtablissement(type) {}

double EtablissementPublic::getSolde() const {
    return energieProduite - energieConsommee;
}

void EtablissementPublic::afficherInfo() const {
    // Implémentation simplifiée pour Qt
}

std::string EtablissementPublic::getTypeEtablissement() const { 
    return typeEtablissement; 
}