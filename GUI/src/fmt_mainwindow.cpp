#include "../include/fmt_mainwindow.hpp"
#include "../include/cmpList.hpp"
#include "../include/prjNewWindow.hpp"
#include "../include/saveStpAsWindow.hpp"
#include "../include/simStartWindow.hpp"

#include <QMessageBox>

#include <iostream>

fmt_mainWindow::fmt_mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fmt_mainWindow)
{
    ui->setupUi(this);

    connect(ui->CmpAddButton, &QPushButton::clicked, this, &fmt_mainWindow::checkOnCmpAdd);
    connect(this, &fmt_mainWindow::triggerCmpAdd, ui->CmpListBox, &CmpList_box::addCmpButtonPressed);
}

fmt_mainWindow::~fmt_mainWindow()
{
    delete ui;
}

void fmt_mainWindow::checkOnCmpAdd(){
    //Prüfen, ob eine Setup-Datei geladen ist, falls nein, das adden unterbinden
    if(ui->StpFilePath->toPlainText() == "" || ui->StpFilePath->toPlainText() == "Auto detection failed") return;
    emit triggerCmpAdd();
}

bool fmt_mainWindow::autoDetect(QString _name, QString _filetype){
    if(QFile::exists(ui->ProjPath->text() + "/" + _name + _filetype)){
        return true;
    }
    return false;
}

void fmt_mainWindow::on_OpenInFile_clicked(){
    //Abbrechen, falls kein Projekt geladen ist
    if(ui->ProjPath->text() == "No project loaded"){
        QMessageBox::critical(this, "Error", "No project is currently loaded", QMessageBox::Ok);
        return;
    }

    //Öffne Dateibrowser und wähle gewünschte Datei
    QString inFileName = QFileDialog::getOpenFileName(this, "Select an input file", ui->ProjPath->text());

    //Abbrechen, falls keine Datei ausgewählt
    if(inFileName == "") return;

    //Datentyp bestimmen
    int posDot = inFileName.lastIndexOf(QChar('.'));
    QString datatype = inFileName;
    datatype.remove(0, posDot);

    if(datatype != ".ipt"){
        QMessageBox::critical(this, "Error", "The Input File has to be of '.ipt'-Type", QMessageBox::Ok);
        return;
    }

    //Prüfen, ob bereits Datei geladen wurde. Falls ja, vor überschreiben warnen
    if(!(ui->InFilePath->toPlainText() == "Auto detection failed" || ui->InFilePath->toPlainText() == "Please select an input file")){
        QMessageBox::StandardButton loadAgreement = QMessageBox::warning(this, "Warning", "Loading this File will overwrite all non-saved Changes.", QMessageBox::Ok|QMessageBox::Cancel);
        if(loadAgreement == QMessageBox::Cancel) return;
    }

    //Erstelle Pfad zu gewählter Datei
    QDir _projPath(ui->ProjPath->text());
    ui->InFilePath->setText(_projPath.relativeFilePath(inFileName));
    ui->InFileAuto->setStyleSheet("QPushButton {color: black}");
}

void fmt_mainWindow::on_OpenStpFile_clicked(){
    //Abbrechen, falls kein Projekt geladen ist
    if(ui->ProjPath->text() == "No project loaded"){
        QMessageBox::critical(this, "Error", "No project is currently loaded", QMessageBox::Ok);
        return;
    }

    //Öffne Dateibrowser und wähle gewünschte Datei
    QString stpFileName = QFileDialog::getOpenFileName(this, "Select a setup file", ui->ProjPath->text());

    //Abbrechen, falls keine Datei ausgewählt
    if(stpFileName == "") return;

    //Datentyp bestimmen
    int posDot = stpFileName.lastIndexOf(QChar('.'));
    QString datatype = stpFileName;
    datatype.remove(0, posDot);

    if(datatype != ".xml"){
        QMessageBox::critical(this, "Error", "The Input File has to be of '.xml'-Type", QMessageBox::Ok);
        return;
    }

    //Prüfen, ob bereits Datei geladen wurde. Falls ja, vor überschreiben warnen
    if(!(ui->StpFilePath->toPlainText() == "Auto detection failed")){
        QMessageBox::StandardButton loadAgreement = QMessageBox::warning(this, "Warning", "Loading this File will overwrite all non-saved Changes.", QMessageBox::Ok|QMessageBox::Cancel);
        if(loadAgreement == QMessageBox::Cancel) return;
    }

    //Erstelle Pfad zu gewählter Datei
    QDir _projPath(ui->ProjPath->text());
    ui->StpFilePath->setText(_projPath.relativeFilePath(stpFileName));
    ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");

    //TODO: Importiere Liste aus Setup, aktualisere List Box
}

void fmt_mainWindow::on_actionNew_Project_triggered()
{
    QString prjDirectoryName = QFileDialog::getExistingDirectory(this, "Select a directory", (QCoreApplication::applicationDirPath() + "/../fmt-simulator/setups"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //Abbrechen falls cancel gedrückt wurde
    if(prjDirectoryName == "") return;

    PrjNewWindow* projectNameWindow = new PrjNewWindow(this, prjDirectoryName);
    connect(projectNameWindow, &PrjNewWindow::setPrjName, this, &fmt_mainWindow::createNewProject);
}

void fmt_mainWindow::createNewProject(QString _name, QString _path){
    QDir prjDir(_path + "/" + _name);
    if(!prjDir.exists()){
        prjDir.mkpath(".");
    }
    else{
        QMessageBox::critical(this, "Error", "Project " + _name + " cant be created, because there is already a project with this name at your selectet path.", QMessageBox::Ok);
        return;
    }

    //Erstelle neue .stp-Datei
    QString stpFileName = (_path + "/" + _name + "/" + _name + ".xml");
    QFile stpFile(stpFileName);
    stpFile.open(QIODevice::WriteOnly);
    stpFile.close();

    ui->ProjPath->setText(_path + "/" + _name);
    ui->InFilePath->setText("Please select an input file");
    ui->StpFilePath->setText(_name + ".xml");
    ui->StpFileAuto->setStyleSheet("QPushButton {color: green}");
}

void fmt_mainWindow::on_actionLoad_Project_triggered()
{
    QString prjDirectoryName = QFileDialog::getExistingDirectory(this, "Select the project directory", (QCoreApplication::applicationDirPath() + "/../fmt-simulator/setups"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //Abfangen, falls Cancel-Button gedrückt wurde
    if(prjDirectoryName == "") return;

    //Bestimme Namen
    int posSlash = prjDirectoryName.lastIndexOf(QChar('/')) + 1;
    QString prjName = prjDirectoryName;
    prjName.remove(0, posSlash);

    ui->ProjPath->setText(prjDirectoryName);

    //Auto-Detect Input und Setup-Dateien
    if(autoDetect(prjName, ".ipt")){
        ui->InFilePath->setText(prjName + ".ipt");
        ui->InFileAuto->setStyleSheet("QPushButton {color: green}");
    }
    else{
        ui->InFilePath->setText("Auto detection failed");
        ui->InFileAuto->setStyleSheet("QPushButton {color: black}");
    }

    if(autoDetect(prjName, ".xml")){
        ui->StpFilePath->setText(prjName + ".xml");
        ui->StpFileAuto->setStyleSheet("QPushButton {color: green}");
    }
    else{
        ui->StpFilePath->setText("Auto detection failed");
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
    }
}


void fmt_mainWindow::on_InFileAuto_clicked()
{
    QString prjDirectoryName = ui->ProjPath->text();

    //Bestimme Namen
    int posSlash = prjDirectoryName.lastIndexOf(QChar('/')) + 1;
    QString prjName = prjDirectoryName;
    prjName.remove(0, posSlash);

    if(autoDetect(prjName, ".ipt")){
        //Prüfen, ob bereits Datei geladen wurde. Falls ja, vor überschreiben warnen
        if(!(ui->InFilePath->toPlainText() == "Auto detection failed" || ui->InFilePath->toPlainText() == "Please select an input file")){
            QMessageBox::StandardButton loadAgreement = QMessageBox::warning(this, "Warning", "Input File '" + prjName + ".ipt' was found.\nLoading this File will overwrite all non-saved Changes.", QMessageBox::Ok|QMessageBox::Cancel);
            if(loadAgreement == QMessageBox::Cancel) return;
        }
        ui->InFilePath->setText(prjName + ".ipt");
        ui->InFileAuto->setStyleSheet("QPushButton {color: green}");
    }
    else{
        if(ui->InFilePath->toPlainText() == (prjName + ".ipt")) ui->InFilePath->setText("Auto detection failed");
        ui->InFileAuto->setStyleSheet("QPushButton {color: black}");
    }
}


void fmt_mainWindow::on_StpFileAuto_clicked()
{
    QString prjDirectoryName = ui->ProjPath->text();

    //Bestimme Namen
    int posSlash = prjDirectoryName.lastIndexOf(QChar('/')) + 1;
    QString prjName = prjDirectoryName;
    prjName.remove(0, posSlash);

    if(autoDetect(prjName, ".xml")){
        //Prüfen, ob bereits Datei geladen wurde. Falls ja, vor überschreiben warnen
        if(!(ui->StpFilePath->toPlainText() == "Auto detection failed")){
            QMessageBox::StandardButton loadAgreement = QMessageBox::warning(this, "Warning", "Setup File '" + prjName + ".xml' was found.\nLoading this File will overwrite all non-saved Changes.", QMessageBox::Ok|QMessageBox::Cancel);
            if(loadAgreement == QMessageBox::Cancel) return;
        }
        ui->StpFilePath->setText(prjName + ".xml");
        ui->StpFileAuto->setStyleSheet("QPushButton {color: green}");

        //TODO: Setup aus Datei importieren und in Liste speichern, Liste dann aktualisieren
    }
    else{
        if(ui->StpFilePath->toPlainText() == (prjName + ".xml")) ui->StpFilePath->setText("Auto detection failed");
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
    }
}

void fmt_mainWindow::on_actionSave_Project_triggered()
{
    //Prüfen, ob ein Projekt geladen ist
    if(ui->ProjPath->text().toStdString() == "No project loaded"){
        QMessageBox::critical(this, "Error", "No project is currently loaded", QMessageBox::Ok);
        return;
    }

    //Benachrichtigen, dass vorherige Datei überschrieben wird
    QMessageBox::StandardButton saveAgreement = QMessageBox::warning(this, "Warning", "Setup File " + ui->StpFilePath->toPlainText() + " is about to be overwritten.\nAre you sure you want to continue?", QMessageBox::Yes|QMessageBox::No);
    if(saveAgreement == QMessageBox::Yes){
        //TODO: Export Setup aus der Liste
        return;
    }
}

void fmt_mainWindow::on_actionSave_Setup_as_triggered()
{
    //Prüfen, ob ein Projekt geladen ist
    if(ui->ProjPath->text().toStdString() == "No project loaded"){
        QMessageBox::critical(this, "Error", "No project is currently loaded", QMessageBox::Ok);
        return;
    }
    //Fenster erstellen, in dem Name festgelegt wird
    SaveStpAsWindow* saveName = new SaveStpAsWindow(this);

    connect(saveName, &SaveStpAsWindow::setStpName, this, &fmt_mainWindow::saveWithOtherName);
}

void fmt_mainWindow::saveWithOtherName(QString _name){
    //Bestimme Endung
    int posDot = _name.lastIndexOf(QChar('.'));
    QString datatype = _name;
    datatype.remove(0, posDot);

    //Speichern, wenn Endung .xml ist
    if(datatype.toStdString() == ".xml"){
        //TODO: Export Setup aus der Liste
        ui->StpFilePath->setText(_name);
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
        return;
    }

    //Nach Speichern mit automatischer .xml-Endung fragen
    QMessageBox::StandardButton autoStpName = QMessageBox::warning(this, "Warning", "Setup File has to be an '.xml'-File.\nDo you want to save it as '" + _name + ".xml' ?", QMessageBox::Yes|QMessageBox::No);
    if(autoStpName == QMessageBox::Yes){
        _name = _name + ".xml";
        //TODO: Export Setup aus der Liste
        ui->StpFilePath->setText(_name);
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
        return;
    }
    else if(autoStpName == QMessageBox::No){
        //Neues Fenster erstellen, in dem der Name erneut festgelegt werden kann
        SaveStpAsWindow* saveName = new SaveStpAsWindow(this);

        connect(saveName, &SaveStpAsWindow::setStpName, this, &fmt_mainWindow::saveWithOtherName);
        return;
    }
}

void fmt_mainWindow::closeEvent(QCloseEvent *event){
    //Programm einfach schliessen, falls kein Projekt geladen ist
    if(ui->ProjPath->text() == "No project loaded"){
        event->accept();
        return;
    }

    //Warnen, falls Projekt geöffnet ist und Speichern oder Abbrechen ermöglichen
    QMessageBox::StandardButton closeAgreement = QMessageBox::warning(this, "Warning", "The current Project might not be saved yet. Do you want to exit now?\nAll non-saved Changes will be lost.", QMessageBox::Yes|QMessageBox::No|QMessageBox::Save);
    if(closeAgreement == QMessageBox::Yes){
        event->accept();
        return;
    }
    else if(closeAgreement == QMessageBox::Save){
        //TODO: Export Setup aus der Liste
        event->accept();
        return;
    }
    event->ignore();
}

void fmt_mainWindow::on_RunOptimization_clicked()
{
    //TODO: Prüfen, ob Simulation ausgeführt wurde
    if(true){
        //Gültige Kombination der Auswahlen prüfen
        if(!(ui->Priority1_Box->isChecked() || ui->Priority2_Box->isChecked() || ui->Priority3_Box->isChecked())){
            QMessageBox::information(this, "Information", "No Optimization Priorities have been set. There are no Parameters to optimize to.", QMessageBox::Ok);
            return;
        }
        if((!ui->Priority1_Box->isChecked() && (ui->Priority2_Box->isChecked() || ui->Priority3_Box->isChecked())) ||
        (ui->Priority1_Box->isChecked() && !ui->Priority2_Box->isChecked() && ui->Priority3_Box->isChecked())){
            QMessageBox::critical(this, "Error", "Priorities have been set in a non chronological order.", QMessageBox::Ok);
            return;
        }
        //Abfangen, falls pro Parameter mehrere Prioritäten ausgewählt wurden
        int checkedCounter = 0;
        if(ui->Prio1_bright->isChecked()) checkedCounter++;
        if(ui->Prio2_bright->isChecked() && ui->Priority2_Box->isChecked()) checkedCounter++;
        if(ui->Prio3_bright->isChecked() && ui->Priority3_Box->isChecked()) checkedCounter++;
        if(checkedCounter > 1){
            QMessageBox::critical(this, "Error", "Each Parameter requires a distinct Optimization Priority.", QMessageBox::Ok);
            return;
        }

        checkedCounter = 0;
        if(ui->Prio1_focus->isChecked()) checkedCounter++;
        if(ui->Prio2_focus->isChecked() && ui->Priority2_Box->isChecked()) checkedCounter++;
        if(ui->Prio3_focus->isChecked() && ui->Priority3_Box->isChecked()) checkedCounter++;
        if(checkedCounter > 1){
            QMessageBox::critical(this, "Error", "Each Parameter requires a distinct Optimization Priority.", QMessageBox::Ok);
            return;
        }

        checkedCounter = 0;
        if(ui->Prio1_DoF->isChecked()) checkedCounter++;
        if(ui->Prio2_DoF->isChecked() && ui->Priority2_Box->isChecked()) checkedCounter++;
        if(ui->Prio3_DoF->isChecked() && ui->Priority3_Box->isChecked()) checkedCounter++;
        if(checkedCounter > 1){
            QMessageBox::critical(this, "Error", "Each Parameter requires a distinct Optimization Priority.", QMessageBox::Ok);
            return;
        }

        //TODO: Optimierung starten
    }
}


void fmt_mainWindow::on_SimStartSimulation_clicked()
{
    //Prüfen, ob ein Projekt geladen ist
    if(ui->ProjPath->text().toStdString() == "No project loaded"){
        QMessageBox::critical(this, "Error", "No project is currently loaded", QMessageBox::Ok);
        return;
    }

    //Prüfen, ob Setup und Input gültig und geladen sind
    if((ui->InFilePath->toPlainText() == "" || ui->InFilePath->toPlainText() == "Auto detection failed" || ui->InFilePath->toPlainText() == "Please select an input file") ||
    (ui->StpFilePath->toPlainText() == "" || ui->StpFilePath->toPlainText() == "Auto detection failed")){
        QMessageBox::critical(this, "Error", "Both Input and Setup Files have to be loaded before starting the Simulation.", QMessageBox::Ok);
        return;
    }

    //Prüfe Ausgabe-Dateiname auf gültige Endung .bmp
    QString filename = ui->ExpFileTextfield->text();
    if(filename.isEmpty()){
        //Bestimme Namen
        QString prjDirectoryName = ui->ProjPath->text();
        int posSlash = prjDirectoryName.lastIndexOf(QChar('/')) + 1;
        QString prjName = prjDirectoryName;
        prjName.remove(0, posSlash);

        //Schlage automatischen Export-Namen vor
        QMessageBox::StandardButton autoSaveAgreement = QMessageBox::warning(this, "Warning", "Export File Name was not declared.\nDo you want to export it as '" + prjName + ".bmp' ?", QMessageBox::Yes|QMessageBox::Cancel);
        if(autoSaveAgreement == QMessageBox::Cancel) return;
        filename = prjName + ".bmp";
        ui->ExpFileTextfield->setText(filename);
    }

    //Bestimme Endung
    int posDot = filename.lastIndexOf(QChar('.'));
    QString datatype = filename;
    datatype.remove(0, posDot);

    //Schlage automatische .bmp-Endung vor
    if(datatype != ".bmp"){
        QMessageBox::StandardButton autoTypeAgreement = QMessageBox::warning(this, "Warning", "The exported image File has to be of type '.bmp'.\nDo you want to export it as '" + filename + ".bmp' ?", QMessageBox::Yes|QMessageBox::Cancel);
        if(autoTypeAgreement == QMessageBox::Cancel) return;
        filename = filename + ".bmp";
        ui->ExpFileTextfield->setText(filename);
    }

    //Fenster zum Festlegen der Photonenzahl
    SimStartWindow* setWin = new SimStartWindow(this);
    connect(setWin, &SimStartWindow::simStart, this, &fmt_mainWindow::startSimulation);
}

void fmt_mainWindow::startSimulation(int photonNumber){
    //TODO: Starte Simulation mit Photonen-Anzahl
}
