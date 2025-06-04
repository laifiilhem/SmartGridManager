#ifndef GRAPHIQUE_MANAGER_H
#define GRAPHIQUE_MANAGER_H

#include <QtCharts>
#include <QChartView>
#include "SmartGridManager.h"

class GraphiqueManager
{
public:
    static QChart* creerGraphiqueProdCons(const SmartGridManager& manager);
    static QChart* creerGraphiqueBatteries(const SmartGridManager& manager);
};

#endif // GRAPHIQUE_MANAGER_H