#include "SmartGridManager.h"
#include "Maison.h"
#include "Hopital.h"
#include "EtablissementPublic.h"

void SmartGridManager::ajouterUnite(std::unique_ptr<UniteElectrique> unite) {
    unites.push_back(std::move(unite));
}

void SmartGridManager::afficherUnites() const {
    // Implémentation vide car l'affichage est géré par Qt
}

void SmartGridManager::miseAJourConsoProd(const std::string& id, double prod, double conso) {
    for (const auto& unite : unites) {
        if (unite->getId() == id) {
            unite->setEnergieProduite(prod);
            unite->setEnergieConsommee(conso);
            return;
        }
    }
}

void SmartGridManager::simulerCoupure() {
    for (const auto& unite : unites) {
        if (auto hopital = dynamic_cast<Hopital*>(unite.get())) {
            hopital->simulerCoupure(1); // Simuler 1 heure de coupure
        } else if (auto maison = dynamic_cast<Maison*>(unite.get())) {
            maison->utiliserBatterie(maison->consommationMoyenne());
        }
    }
}

double SmartGridManager::calculerSoldeTotal() const {
    double total = 0;
    for (const auto& unite : unites) {
        total += unite->getSolde();
    }
    return total;
}

const std::vector<std::unique_ptr<UniteElectrique>>& SmartGridManager::getUnites() const {
    return unites;
}