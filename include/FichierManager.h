#ifndef FICHIER_MANAGER_H
#define FICHIER_MANAGER_H

#include "SmartGridManager.h"
#include <string>

class FichierManager {
public:
    static void sauvegarderDonnees(const SmartGridManager& manager, const std::string& fichier);
    static void chargerDonnees(SmartGridManager& manager, const std::string& fichier);
};

#endif