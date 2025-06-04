#include "GraphiqueManager.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QValueAxis>

QChart* GraphiqueManager::creerGraphiqueProdCons(const SmartGridManager& manager)
{
    auto chart = new QChart();
    chart->setTitle("Production et Consommation");
    
    // [...] Implémentation des séries de données
    
    return chart;
}