#ifndef UNITE_ELECTRIQUE_H
#define UNITE_ELECTRIQUE_H

#include <string>

class UniteElectrique {
protected:
    std::string id;
    double energieProduite;
    double energieConsommee;

public:
    UniteElectrique(const std::string& id, double prod, double conso);
    virtual ~UniteElectrique() = default;

    virtual double getSolde() const = 0;
    virtual void afficherInfo() const = 0;

    std::string getId() const;
    double getEnergieProduite() const;
    double getEnergieConsommee() const;

    void setEnergieProduite(double prod);
    void setEnergieConsommee(double conso);
};

#endif