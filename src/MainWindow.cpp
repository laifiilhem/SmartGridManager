#include "MainWindow.h"
#include "../ui/ui_MainWindow.h"
#include "Maison.h"
#include "Hopital.h"
#include "EtablissementPublic.h"
#include "FichierManager.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDebug>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Configuration de la table
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID", "Type", "Production (kWh)", "Consommation (kWh)", 
                          "Région", "Autonomie (jours)", "Type Établissement"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->setColumnWidth(1, 150);

    // Connexion manuelle si nécessaire
    connect(ui->btnAfficherGraphique, &QPushButton::clicked, 
            this, &MainWindow::on_btnAfficherGraphique_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAfficherGraphique_clicked()
{
    if(manager.getUnites().empty()) {
        QMessageBox::information(this, "Information", "Aucune donnée à afficher");
        return;
    }

    // Calcul des données par région
    QMap<QString, QPair<double, double>> donnees; // <Région, <Consommation, Production>>
    
    for(const auto& unite : manager.getUnites()) {
        QString region;
        if(auto m = dynamic_cast<Maison*>(unite.get())) {
            region = QString::fromStdString(m->getRegion());
        } 
        else if(auto h = dynamic_cast<Hopital*>(unite.get())) {
            region = QString::fromStdString(h->getRegion());
        }
        
        if(!region.isEmpty()) {
            donnees[region].first += unite->getEnergieConsommee();
            donnees[region].second += unite->getEnergieProduite();
        }
    }

    // Création du graphique (version moderne)
    auto chart = new QChart();
    chart->setTitle("Bilan énergétique par région (kWh)");
    
    auto series = new QBarSeries();
    QStringList categories;
    
    for(auto it = donnees.begin(); it != donnees.end(); ++it) {
        QString region = it.key();
        double conso = it.value().first;
        double prod = it.value().second;
        
        auto setConso = new QBarSet(region + " (Conso)");
        *setConso << conso;
        setConso->setColor(QColor(231, 76, 60)); // Rouge
        
        auto setProd = new QBarSet(region + " (Prod)");
        *setProd << prod;
        setProd->setColor(QColor(46, 204, 113)); // Vert
        
        series->append(setConso);
        series->append(setProd);
        categories << region;
    }

    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Configuration des axes (méthode moderne)
    auto axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    auto axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Affichage
    auto chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    QDialog dialog(this);
    dialog.setWindowTitle("Statistiques énergétiques");
    QVBoxLayout layout(&dialog);
    layout.addWidget(chartView);
    dialog.resize(1000, 600);
    dialog.exec();
}

void MainWindow::on_btnAjouterMaison_clicked()
{
    QString id = ui->txtMaisonId->text();
    double prod = ui->spinMaisonProd->value();
    double conso = ui->spinMaisonConso->value();
    QString region = ui->txtMaisonRegion->text();
    
    if(id.isEmpty() || region.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }
    
    try {
        double batterie = conso / 24.0; // Calcul de la batterie
        manager.ajouterUnite(std::make_unique<Maison>(id.toStdString(), prod, conso, 
                                                   region.toStdString(), batterie));
        afficherMessage("Maison ajoutée avec succès");
        afficherUnitesDansTableau();
        
        ui->txtMaisonId->clear();
        ui->spinMaisonProd->setValue(0);
        ui->spinMaisonConso->setValue(0);
        ui->txtMaisonRegion->clear();
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Erreur: %1").arg(e.what()));
    }
}

void MainWindow::on_btnAjouterHopital_clicked()
{
    QString id = ui->txtHopitalId->text();
    double prod = ui->spinHopitalProd->value();
    double conso = ui->spinHopitalConso->value();
    QString region = ui->txtHopitalRegion->text();
    int autonomie = ui->spinHopitalAutonomie->value();
    
    if(id.isEmpty() || region.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }
    
    try {
        double batterie = conso / 24.0 * autonomie;
        manager.ajouterUnite(std::make_unique<Hopital>(id.toStdString(), prod, conso, 
                                                     region.toStdString(), batterie, autonomie));
        afficherMessage("Hôpital ajouté avec succès");
        afficherUnitesDansTableau();
        
        ui->txtHopitalId->clear();
        ui->spinHopitalProd->setValue(0);
        ui->spinHopitalConso->setValue(0);
        ui->txtHopitalRegion->clear();
        ui->spinHopitalAutonomie->setValue(0);
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Erreur: %1").arg(e.what()));
    }
}

void MainWindow::on_btnAjouterEtablissement_clicked()
{
    QString id = ui->txtEtablissementId->text();
    double prod = ui->spinEtablissementProd->value();
    double conso = ui->spinEtablissementConso->value();
    QString type = ui->comboEtablissementType->currentText();
    
    if(id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }
    
    try {
        manager.ajouterUnite(std::make_unique<EtablissementPublic>(
            id.toStdString(), prod, conso, type.toStdString()));
        afficherMessage("Établissement ajouté avec succès");
        afficherUnitesDansTableau();
        
        ui->txtEtablissementId->clear();
        ui->spinEtablissementProd->setValue(0);
        ui->spinEtablissementConso->setValue(0);
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Erreur: %1").arg(e.what()));
    }
}

void MainWindow::on_btnAfficherUnites_clicked()
{
    afficherUnitesDansTableau();
    afficherMessage("Liste des unités actualisée");
}

void MainWindow::on_btnSimulerCoupure_clicked()
{
    if(manager.getUnites().empty()) {
        QMessageBox::warning(this, "Erreur", "Aucune unité à simuler");
        return;
    }
    
    manager.simulerCoupure();
    double solde = manager.calculerSoldeTotal();
    
    if(solde >= 0) {
        afficherMessage(QString("Réseau stable - Excédent: %1 kWh").arg(solde));
    } else {
        QMessageBox::warning(this, "ALERTE", QString("Déficit énergétique: %1 kWh").arg(-solde));
    }
    
    afficherUnitesDansTableau();
}

void MainWindow::on_btnSauvegarder_clicked()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Sauvegarder", "", "Fichiers CSV (*.csv)");
    if(!fichier.isEmpty()) {
        try {
            FichierManager::sauvegarderDonnees(manager, fichier.toStdString());
            afficherMessage("Données sauvegardées en CSV avec succès");
        } catch(const std::exception& e) {
            QMessageBox::critical(this, "Erreur", QString("Erreur lors de la sauvegarde: %1").arg(e.what()));
        }
    }
}

void MainWindow::on_btnCharger_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Charger", "", "Fichiers CSV (*.csv)");
    if(!fichier.isEmpty()) {
        try {
            FichierManager::chargerDonnees(manager, fichier.toStdString());
            afficherMessage("Données chargées depuis CSV avec succès");
            afficherUnitesDansTableau();
        } catch(const std::exception& e) {
            QMessageBox::critical(this, "Erreur", QString("Erreur lors du chargement: %1").arg(e.what()));
        }
    }
}

void MainWindow::on_btnMettreAJour_clicked()
{
    QString id = ui->txtMajId->text();
    double prod = ui->spinMajProd->value();
    double conso = ui->spinMajConso->value();
    
    if(id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID");
        return;
    }
    
    try {
        manager.miseAJourConsoProd(id.toStdString(), prod, conso);
        afficherMessage("Mise à jour effectuée");
        afficherUnitesDansTableau();
        
        ui->txtMajId->clear();
        ui->spinMajProd->setValue(0);
        ui->spinMajConso->setValue(0);
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Erreur: %1").arg(e.what()));
    }
}

void MainWindow::afficherUnitesDansTableau()
{
    ui->tableWidget->setRowCount(0);
    
    for(const auto& unite : manager.getUnites()) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(unite->getId())));
        
        // Détermination du type
        if(dynamic_cast<Maison*>(unite.get())) {
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Maison"));
        } 
        else if(dynamic_cast<Hopital*>(unite.get())) {
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Hôpital"));
        } 
        else if(dynamic_cast<EtablissementPublic*>(unite.get())) {
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Établissement"));
        }
        
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(unite->getEnergieProduite())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(unite->getEnergieConsommee())));
        
        if(auto maison = dynamic_cast<Maison*>(unite.get())) {
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(maison->getRegion())));
        }
        else if(auto hopital = dynamic_cast<Hopital*>(unite.get())) {
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(hopital->getRegion())));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(hopital->getJoursAutonomie())));
        }
        else if(auto etablissement = dynamic_cast<EtablissementPublic*>(unite.get())) {
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(etablissement->getTypeEtablissement())));
        }
    }
}

void MainWindow::afficherMessage(const QString& message)
{
    ui->statusbar->showMessage(message, 5000); // Notez le 'statusbar' en minuscules
}







