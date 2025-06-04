#include "FichierManager.h"
#include "Maison.h"
#include "Hopital.h"
#include "EtablissementPublic.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void FichierManager::sauvegarderDonnees(const SmartGridManager& manager, const std::string& fichier) {
    std::ofstream out(fichier);
    
    for (const auto& unite : manager.getUnites()) {
        out << unite->getId() << ","
            << unite->getEnergieProduite() << ","
            << unite->getEnergieConsommee() << ",";
        
        if (auto maison = dynamic_cast<Maison*>(unite.get())) {
            out << "maison," << maison->getRegion() << "," << maison->getBatterieCapacite();
            
            if (auto hopital = dynamic_cast<Hopital*>(unite.get())) {
                out << "," << hopital->getJoursAutonomie();
            }
        } else if (auto etablissement = dynamic_cast<EtablissementPublic*>(unite.get())) {
            out << "etablissement," << etablissement->getTypeEtablissement();
        }
        
        out << "\n";
    }
}

void FichierManager::chargerDonnees(SmartGridManager& manager, const std::string& fichier) {
    std::ifstream in(fichier);
    std::string ligne;
    
    while (std::getline(in, ligne)) {
        std::stringstream ss(ligne);
        std::vector<std::string> tokens;
        std::string token;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() < 4) continue;
        
        std::string id = tokens[0];
        double prod = std::stod(tokens[1]);
        double conso = std::stod(tokens[2]);
        std::string type = tokens[3];
        
        if (type == "maison") {
            if (tokens.size() >= 6) {
                manager.ajouterUnite(std::make_unique<Hopital>(
                    id, prod, conso, tokens[4], std::stod(tokens[5]), std::stoi(tokens[6])));
            } else {
                manager.ajouterUnite(std::make_unique<Maison>(
                    id, prod, conso, tokens[4], std::stod(tokens[5])));
            }
        } else if (type == "etablissement") {
            manager.ajouterUnite(std::make_unique<EtablissementPublic>(
                id, prod, conso, tokens[4]));
        }
    }
}