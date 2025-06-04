# SmartGridManager

**Application de gestion énergétique intelligente** développée en C++ avec Qt pour visualiser, analyser et optimiser la distribution d’électricité entre diverses unités (maisons, hôpitaux, établissements publics).

---

## Fonctionnalités Principales

### Gestion des Unités Électriques  
- Ajout/suppression de trois types d'unités :  
  - Maisons (ID, production, consommation, région)  
  - Hôpitaux (ID, production, consommation, région, autonomie en jours)  
  - Établissements Publics (écoles, mairies, bibliothèques)  
- Mise à jour dynamique des données (production/consommation).

### Visualisation des Données  
- Tableau synthétique listant toutes les unités avec leurs caractéristiques.  
- Graphiques interactifs :  
  - Comparaison production vs consommation par région (diagrammes en barres).  
  - Visualisation des déséquilibres énergétiques.

### Simulation de Coupures  
- Analyse en temps réel du réseau.  
- Détection des déficits énergétiques avec alertes spécifiques pour les hôpitaux (unités critiques).

### Persistance des Données  
- Sauvegarde et chargement des données au format CSV.  
- Export optionnel des graphiques en images.

---

## Technologies Utilisées

- **Langage :** C++17  
- **Framework :** Qt 5 (Widgets, Charts, UI Designer)  
- **Outils :**  
  - CMake (compilation)  
  - Qt Creator (développement)  
  - QtCharts (visualisation)

---

## Architecture du Projet

SmartGridManager/

├── CMakeLists.txt # Configuration CMake

├── data/ # Fichiers CSV d'exemple

├── include/ # Headers (.h)

│ ├── UniteElectrique.h # Classe de base

│ ├── Maison.h # Spécialisation "Maison"

│ ├── Hopital.h # Spécialisation "Hôpital"

│ └── ...

├── src/ # Implémentations (.cpp)

├── ui/ # Fichiers d'interface (.ui)

└── resources/ # Assets (styles, images)


---

## Installation et Compilation

```bash
git clone https://github.com/tonpseudo/SmartGridManager.git
cd SmartGridManager
mkdir build && cd build
cmake ..
make
./SmartGridManager

Contribution
Les contributions sont les bienvenues !
Merci de créer une branche dédiée, de faire des commits clairs et de soumettre une Pull Request.

Contact
Pour toute question ou remarque, contactez-moi :

Email : ilhem.lafi@etudiant-enit.utm.tn

LinkedIn :linkedin.com/in/ilhem-laifi-9682702b2
