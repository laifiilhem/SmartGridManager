#ifndef ETABLISSEMENT_PUBLIC_H
#define ETABLISSEMENT_PUBLIC_H

#include "UniteElectrique.h"
#include <string>

class EtablissementPublic : public UniteElectrique {
private:
    std::string typeEtablissement;

public:
    EtablissementPublic(const std::string& id, double prod, double conso, 
                        const std::string& type);
    
    double getSolde() const override;
    void afficherInfo() const override;
    
    std::string getTypeEtablissement() const;
};

#endif