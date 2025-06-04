#include "UniteElectrique.h"

UniteElectrique::UniteElectrique(const std::string& id, double prod, double conso)
    : id(id), energieProduite(prod), energieConsommee(conso) {}

std::string UniteElectrique::getId() const { return id; }
double UniteElectrique::getEnergieProduite() const { return energieProduite; }
double UniteElectrique::getEnergieConsommee() const { return energieConsommee; }

void UniteElectrique::setEnergieProduite(double prod) { energieProduite = prod; }
void UniteElectrique::setEnergieConsommee(double conso) { energieConsommee = conso; }