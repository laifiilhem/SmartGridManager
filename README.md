# SmartGridManager

**Smart energy management application** developed in C++ with Qt to visualize, analyze, and optimize electricity distribution among various units (homes, hospitals, public institutions).

---

## 🔌 Main Features

### Energy Unit Management  
- Add/remove three types of units:  
  - Houses (ID, production, consumption, region)  
  - Hospitals (ID, production, consumption, region, autonomy in days)  
  - Public Institutions (schools, city halls, libraries)  
- Real-time update of data (production/consumption).

### Data Visualization  
- Summary table listing all units and their characteristics.  
- Interactive charts:  
  - Production vs. consumption comparison by region (bar charts).  
  - Visualization of energy imbalances.

### Power Outage Simulation  
- Real-time grid analysis.  
- Detection of energy deficits with special alerts for hospitals (critical units).

### Data Persistence  
- Save and load data in CSV format.  
- Optional export of graphs as images.

---

## 🛠️ Technologies Used

- **Language:** C++17  
- **Framework:** Qt 5 (Widgets, Charts, UI Designer)  
- **Tools:**  
  - CMake (build system)  
  - Qt Creator (development)  
  - QtCharts (visualization)

---

## 📁 Project Structure



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

## ⚙️ Installation & Build Instructions

### 🔧 Requirements
- Qt 5.x (with QtWidgets and QtCharts)
- CMake ≥ 3.15
- g++ / MinGW or MSVC
- *(Optional)* Qt Creator to simplify development

### 🖥️ Build Commands

```bash
git clone https://github.com/laifiilhem/SmartGridManager.git
cd SmartGridManager
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
./SmartGrid.exe

```


## Contribution
Contributions are welcome!
Please :

Create a dedicated branch (e.g., feature/your-feature-name)

Make clear and concise commits

Submit a Pull Request



## Contact
For any questions or suggestions, feel free to reach out: :

 Email : ilhem.lafi@etudiant-enit.utm.tn

 LinkedIn : linkedin.com/in/ilhem-laifi-9682702b2

