#include "../include/fmt_mainwindow.hpp"
#include "../include/cmpList.hpp"
#include "../include/prjNewWindow.hpp"
#include "../include/saveStpAsWindow.hpp"
#include "../include/simStartWindow.hpp"

#include "../../logic/include/objectGenerator.hpp"
#include "../../logic/include/mainRoutine.hpp"

#include <QMessageBox>

#include <iostream>
#include <fstream>

/**
 * @brief Constructs a main window for the FMT-Simulator
 * @param parent Default parent window
 */
fmt_mainWindow::fmt_mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fmt_mainWindow)
{
    ui->setupUi(this);

    connect(ui->CmpAddButton, &QPushButton::clicked, this, &fmt_mainWindow::checkOnCmpAdd);
    connect(this, &fmt_mainWindow::triggerCmpAdd, ui->CmpListBox, &CmpList_box::addCmpButtonPressed);
}

/**
 * @brief Standard destructor. Deleting ui-form
 */
fmt_mainWindow::~fmt_mainWindow()
{
    delete ui;
}

/**
 * @brief Checks, if a Setup is loaded and therefore adding a component is allowed
 */
void fmt_mainWindow::checkOnCmpAdd(){
    //Prüfen, ob eine Setup-Datei geladen ist, falls nein, das adden unterbinden
    if(ui->StpFilePath->toPlainText() == "" || ui->StpFilePath->toPlainText() == "Auto detection failed") return;
    emit triggerCmpAdd();
}

/**
 * @brief Automatically detects, if a file with given name and type exists in project directory
 * @param _name Name of file without ending
 * @param _filetype Filetype ending
 * @return True, if File exists
 */
bool fmt_mainWindow::autoDetect(QString _name, QString _filetype){
    if(QFile::exists(ui->ProjPath->text() + "/" + _name + _filetype)){
        return true;
    }
    return false;
}

/**
 * @brief Disables all Widgets except ProgressBar
 * @param inStyle Reference to Style Settings of AutoInput Button, is set to Style before deactivation
 * @param stpStyle Reference to Style Settings of AutoSetup Button, is set to Style before deactivation
 */
void fmt_mainWindow::setMainWindowInactive(QString& inStyle, QString& stpStyle){
    for(auto* widget : this->findChildren<QPushButton*>()){
        widget->setEnabled(false);
    }
    for(auto* widget : this->findChildren<QLabel*>()){
        widget->setEnabled(false);
    }
    for(auto* widget : this->findChildren<QLineEdit*>()){
        widget->setEnabled(false);
    }
    for(auto* widget : this->findChildren<QTextBrowser*>()){
        widget->setEnabled(false);
    }
    ui->Priority1_Box->setEnabled(false);
    ui->Priority2_Box->setEnabled(false);
    ui->Priority3_Box->setEnabled(false);
    inStyle = ui->InFileAuto->styleSheet();
    stpStyle = ui->StpFileAuto->styleSheet();
    ui->InFileAuto->setStyleSheet("QPushButton {color: grey}");
    ui->StpFileAuto->setStyleSheet("QPushButton {color: grey}");
}

/**
 * @brief Enables all Widgets, counterpart to setMainWindowInactive
 * @param inStyle Style of AutoInput button, is reassigned to Button
 * @param stpStyle Style of AutoSetup button, is reassigned to Button
 */
void fmt_mainWindow::setMainWindowActive(QString& inStyle, QString& stpStyle){
    for(auto* widget : this->findChildren<QPushButton*>()){
        widget->setEnabled(true);
    }
    for(auto* widget : this->findChildren<QLabel*>()){
        widget->setEnabled(true);
    }
    for(auto* widget : this->findChildren<QLineEdit*>()){
        widget->setEnabled(true);
    }
    for(auto* widget : this->findChildren<QTextBrowser*>()){
        widget->setEnabled(true);
    }
    ui->Priority1_Box->setEnabled(true);
    ui->Priority2_Box->setEnabled(true);
    ui->Priority3_Box->setEnabled(true);
    ui->InFileAuto->setStyleSheet(inStyle);
    ui->StpFileAuto->setStyleSheet(stpStyle);
}

/**
 * @brief Opens an input file from file explorer, if allowed
 */
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

/**
 * @brief Opens a setup file from file explorer, if allowed
 */
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

    //Bestimme Namen
    QString prjDirectoryName = ui->ProjPath->text();
    int posSlash = prjDirectoryName.lastIndexOf(QChar('/')) + 1;
    QString prjName = prjDirectoryName;
    prjName.remove(0, posSlash);

    //Auto detect auf aus, falls nicht Standartdatei gewählt
    if(ui->StpFilePath->toPlainText() != prjName + ".xml") ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
    else ui->StpFileAuto->setStyleSheet("QPushButton {color: green}");

    //Setup aus Datei importieren und in Liste speichern, Liste dann aktualisieren
    ui->CmpListBox->resetList();

    //Prüfen, ob Datei leer ist
    std::ifstream file;
    file.open((ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
    if(file.peek() != std::ifstream::traits_type::eof()) Importer::importStp(*(ui->CmpListBox->getComponentList()), (ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
    ui->CmpListBox->rebuildFromList();
}

/**
 * @brief Triggers creation process of new project, creating a window for name selection
 */
void fmt_mainWindow::on_actionNew_Project_triggered()
{
    QString prjDirectoryName = QFileDialog::getExistingDirectory(this, "Select a directory", (QCoreApplication::applicationDirPath() + "/../fmt-simulator/setups"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //Abbrechen falls cancel gedrückt wurde
    if(prjDirectoryName == "") return;

    PrjNewWindow* projectNameWindow = new PrjNewWindow(this, prjDirectoryName);
    connect(projectNameWindow, &PrjNewWindow::setPrjName, this, &fmt_mainWindow::createNewProject);
}

/**
 * @brief Creates a new project with given _name, if its not already existing
 * @param _name Selected name of project
 * @param _path Path, where project has to be created
 *
 * Also creates a matching setup file, wich can be auto detected
 */
void fmt_mainWindow::createNewProject(QString _name, QString _path){
    QDir prjDir(_path + "/" + _name);
    if(!prjDir.exists()){
        prjDir.mkpath(".");
    }
    else{
        QMessageBox::critical(this, "Error", "Project " + _name + " cant be created, because there is already a project with this name at your selectet path.", QMessageBox::Ok);
        return;
    }

    //Erstelle neue .xml-Datei
    QString stpFileName = (_path + "/" + _name + "/" + _name + ".xml");
    QFile stpFile(stpFileName);
    stpFile.open(QIODevice::WriteOnly);
    stpFile.close();

    ui->ProjPath->setText(_path + "/" + _name);
    ui->InFilePath->setText("Please select an input file");
    ui->StpFilePath->setText(_name + ".xml");
    ui->StpFileAuto->setStyleSheet("QPushButton {color: green}");

    //Liste zurücksetzen
    ui->CmpListBox->resetList();
    ui->CmpListBox->rebuildFromList();
    ui->SimProgressBar->setValue(0);
}

/**
 * @brief Loads existing project from selection in a file explorer
 *
 * Also triggers auto detect for both input and setup files
 */
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

        //Setup aus Datei importieren und in Liste speichern, Liste dann aktualisieren
        ui->CmpListBox->resetList();

        //Prüfen, ob Datei leer ist
        std::ifstream file;
        file.open((ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        if(file.peek() != std::ifstream::traits_type::eof()) Importer::importStp(*(ui->CmpListBox->getComponentList()), (ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        ui->CmpListBox->rebuildFromList();
        ui->SimProgressBar->setValue(0);
    }
    else{
        ui->StpFilePath->setText("Auto detection failed");
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
    }
}

/**
 * @brief Performs auto detection on input file in current project directory
 */
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

/**
 * @brief Performs auto detection on setup file in current project directory
 */
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

        //Setup aus Datei importieren und in Liste speichern, Liste dann aktualisieren
        ui->CmpListBox->resetList();

        //Prüfen, ob Datei leer ist
        std::ifstream file;
        file.open((ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        if(file.peek() != std::ifstream::traits_type::eof()) Importer::importStp(*(ui->CmpListBox->getComponentList()), (ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        ui->CmpListBox->rebuildFromList();
    }
    else{
        if(ui->StpFilePath->toPlainText() == (prjName + ".xml")) ui->StpFilePath->setText("Auto detection failed");
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");
    }
}

/**
 * @brief Saves the current setup in loaded setup file
 *
 * Also creates a warning window, informing the user that the current file will be overwritten
 */
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
        //Export Setup aus der Liste
        Exporter::exportStp(*(ui->CmpListBox->getComponentList()), (ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        return;
    }
}

/**
 * @brief Triggers the saving as process
 *
 * Creates a Window for defining the perferred name of the setup
 */
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

/**
 * @brief Saves current setup into a setup file with given name
 * @param _name Chosen name
 *
 * Checks, if datatype is valid, if not, proposes possible name for saving, and provides the possibility
 * to redefine the name
 */
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
        ui->StpFilePath->setText(_name);
        ui->StpFileAuto->setStyleSheet("QPushButton {color: black}");

        //Export Setup aus der Liste
        Exporter::exportStp(*(ui->CmpListBox->getComponentList()), (ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        return;
    }
    else if(autoStpName == QMessageBox::No){
        //Neues Fenster erstellen, in dem der Name erneut festgelegt werden kann
        SaveStpAsWindow* saveName = new SaveStpAsWindow(this);

        connect(saveName, &SaveStpAsWindow::setStpName, this, &fmt_mainWindow::saveWithOtherName);
        return;
    }
}

/**
 * @brief Catches the closure of software, if a project is loaded
 * @param event Standard close event
 *
 * Gives the opportunity, to cancel the software exit or save the project and then exit
 */
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
        //Export Setup aus der Liste
        Exporter::exportStp(*(ui->CmpListBox->getComponentList()), (ui->ProjPath->text() + "/" + ui->StpFilePath->toPlainText()).toStdString());
        event->accept();
        return;
    }
    event->ignore();
}

/**
 * @brief Runs optimization with chosen priorities
 */
void fmt_mainWindow::on_RunOptimization_clicked()
{
    //Prüfen, ob Simulation ausgeführt wurde
    if(ui->SimProgressBar->value() == ui->SimProgressBar->maximum()){
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
        short prioBright = 0;
        short prioFocus = 0;
        short prioDoF = 0;

        short checkedCounter = 0;
        if(ui->Prio1_bright->isChecked()){prioBright = 100; checkedCounter++;}
        if(ui->Prio2_bright->isChecked() && ui->Priority2_Box->isChecked()){prioBright = 10; checkedCounter++;}
        if(ui->Prio3_bright->isChecked() && ui->Priority3_Box->isChecked()){prioBright = 1; checkedCounter++;}
        if(checkedCounter > 1){
            QMessageBox::critical(this, "Error", "Each Parameter requires a distinct Optimization Priority.", QMessageBox::Ok);
            return;
        }

        checkedCounter = 0;
        if(ui->Prio1_focus->isChecked()){prioFocus = 100; checkedCounter++;}
        if(ui->Prio2_focus->isChecked() && ui->Priority2_Box->isChecked()){prioFocus = 10; checkedCounter++;}
        if(ui->Prio3_focus->isChecked() && ui->Priority3_Box->isChecked()){prioFocus = 1; checkedCounter++;}
        if(checkedCounter > 1){
            QMessageBox::critical(this, "Error", "Each Parameter requires a distinct Optimization Priority.", QMessageBox::Ok);
            return;
        }

        checkedCounter = 0;
        if(ui->Prio1_DoF->isChecked()){prioDoF = 100; checkedCounter++;}
        if(ui->Prio2_DoF->isChecked() && ui->Priority2_Box->isChecked()){prioDoF = 10; checkedCounter++;}
        if(ui->Prio3_DoF->isChecked() && ui->Priority3_Box->isChecked()){prioDoF = 1; checkedCounter++;}
        if(checkedCounter > 1){
            QMessageBox::critical(this, "Error", "Each Parameter requires a distinct Optimization Priority.", QMessageBox::Ok);
            return;
        }

        //Oberfläche ausblenden
        QString inStyle; QString stpStyle;
        setMainWindowInactive(inStyle, stpStyle);

        List* _List = ui->CmpListBox->getComponentList();
        simulation::doStuff(prioBright, prioFocus, prioDoF, simObj, _List, photonList);

        //Oberfläche einblenden
        setMainWindowActive(inStyle, stpStyle);

        //Pixmap reloaden, und Liste aktualisieren
        resultImage = new QPixmap((ui->ProjPath->text() + "/" + ui->ExpFileTextfield->text()));
        ui->GraphicalResult->setPixmap(*resultImage);
        ui->CmpListBox->rebuildFromList();

        //Debug-Werte aus Detector auslesen
        Detector _detect = static_cast<Detector &>(*ui->CmpListBox->getComponentList()->elem(ui->CmpListBox->getComponentList()->getLength() - 1));
        int _brightness = _detect.getBrightness();
        ui->Brightness->setText(QString::number(_brightness));
        int _focus = _detect.getSharpness();
        ui->Focus->setText(QString::number(_focus));
        int _DoF = simulation::getDof(_List);
        ui->DepthOfField->setText(QString::number(_DoF));
        return;
    }
    QMessageBox::critical(this, "Error", "A simulation has to be completed before an optimization can be started.", QMessageBox::Ok);
}

/**
 * @brief Starts simulation process, if all inputs are valid
 *
 * The function checks, if a project is loaded, and if setup and input are correctly loaded.
 * Also checks if the last component is a detector, and if the output .bmp file is correctly
 * named, and proposes a default name if not.
 * Creates a window, wich asks the user to select the number of simulated photons, if all conditions
 * are fullfilled.
 */
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

    //Prüfen, ob letztes Element ein Detector ist, sonst abbrechen
    List* _tempList = ui->CmpListBox->getComponentList();
    if(_tempList->elem(_tempList->getLength() - 1)->getType() != detector){
        QMessageBox::critical(this, "Error", "The last Component has to be a Detector.", QMessageBox::Ok);
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

/**
 * @brief Runs simulation with given number of photons
 */
void fmt_mainWindow::startSimulation(int photonNumber){
    //Leere Photonen-Liste
    photonList = new std::vector<Photon>();

    //Importiere Objekt
    //Prüfen, ob Datei leer ist
    std::ifstream file;
    file.open((ui->ProjPath->text() + "/" + ui->InFilePath->toPlainText()).toStdString());
    if(file.peek() != std::ifstream::traits_type::eof()){
        Importer::importObject(simObj, (ui->ProjPath->text() + "/" + ui->InFilePath->toPlainText()).toStdString());
    }

    //Konfiguriere Progress Bar
    ui->SimProgressBar->setRange(0, photonNumber);
    ui->SimProgressBar->setValue(0);

    //Setze alle Widgets auf Inaktiv, bis auf Progress Bar
    QString inStyle; QString stpStyle;
    setMainWindowInactive(inStyle, stpStyle);

    //Starte Simulation mit Parametern
    List* _List = ui->CmpListBox->getComponentList();
    static_cast<Detector &>(*ui->CmpListBox->getComponentList()->elem(ui->CmpListBox->getComponentList()->getLength() - 1)).resetSensor();
    photonList = simulation::startTracing(simObj, photonNumber, _List, ui->SimProgressBar);

    //Lese generiertes Image, speichere und lade es ins Fenster
    Detector _detect = static_cast<Detector &>(*ui->CmpListBox->getComponentList()->elem(ui->CmpListBox->getComponentList()->getLength() - 1));
    Exporter::exportBMPImage(_detect, (ui->ProjPath->text() + "/" + ui->ExpFileTextfield->text()).toStdString());

    resultImage = new QPixmap((ui->ProjPath->text() + "/" + ui->ExpFileTextfield->text()));
    ui->GraphicalResult->setPixmap(*resultImage);

    //Debug-Werte aus Detector auslesen
    int _brightness = _detect.getBrightness();
    ui->Brightness->setText(QString::number(_brightness));
    int _focus = _detect.getSharpness();
    ui->Focus->setText(QString::number(_focus));
    int _DoF = simulation::getDof(_List);
    ui->DepthOfField->setText(QString::number(_DoF));

    //Setze alle Widgets auf Aktiv
    setMainWindowActive(inStyle, stpStyle);

    ui->SimProgressBar->setValue(photonNumber);

    ui->CmpListBox->rebuildFromList();
}

/**
 * @brief Creates a small "about" window with quick information
 */
void fmt_mainWindow::on_actionFMT_Simulator_triggered()
{
    QString boxContent = "Version 0.99\n\nDeveloped by\nLasse Alsmeyer / lasse.alsmeyer@rwth-aachen.de\nNiklas Damhorst / niklas.damhorst@rwth-aachen.de";
    boxContent.append("\nThomas Mazza / thomas.mazza@rwth-aachen.de\nNikolay Panov / nikolay.panov@rwth-aachen.de");
    boxContent.append("\n\nUnder supervision of\nDr. rer. medic. Dipl.-Inf. Felix Gremse,\nProf. Dr. rer. nat. Uwe Naumann\n\n31.10.2021");
    QMessageBox::about(this, "About FMT-Simulator", boxContent);
}

