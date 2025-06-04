#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "SmartGridManager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAfficherGraphique_clicked();  // Assurez-vous que ce nom correspond exactement au nom dans le .ui
    void on_btnAjouterMaison_clicked();
    void on_btnAjouterHopital_clicked();
    void on_btnAjouterEtablissement_clicked();
    void on_btnAfficherUnites_clicked();
    void on_btnSimulerCoupure_clicked();
    void on_btnSauvegarder_clicked();
    void on_btnCharger_clicked();
    void on_btnMettreAJour_clicked();

private:
    Ui::MainWindow *ui;
    SmartGridManager manager;
    
    void afficherUnitesDansTableau();
    void afficherMessage(const QString& message);
    void afficherGraphiqueConsommation();
};

#endif // MAINWINDOW_H