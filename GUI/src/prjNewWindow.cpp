#include "../include/prjNewWindow.hpp"

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void PrjNewWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no new project will be created.", QMessageBox::Yes|QMessageBox::No);
    if(exitMessage == QMessageBox::Yes) event->accept();
    else event->ignore();
}

/**
 * @brief Checks, if a name is entered, and if so, triggers its transfer to the parent window
 */
void PrjNewWindow::closeOK(){
    if(input->text().isEmpty()){
        QMessageBox::critical(this, "Error", "Please enter a Project Name.", QMessageBox::Ok);
        return;
    }
    emit setPrjName(input->text(), path);
    this->accept();
}

/**
 * @brief Creates a new window for entering a project name, containing the input text field and OK/Cancel-Buttons
 * @param parent Parent window, wich is affected by modality
 * @param _path Previously selected path to project
 */
PrjNewWindow::PrjNewWindow(QWidget* parent, QString _path):QDialog(parent){
    path = _path;

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Create new project");
    this->setFixedSize(400, 80);

    //Layout-Element erstellen
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Form-Layout für Projektname erstellen
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);
    QLabel* inputLabel = new QLabel("Project Name");
    input = new QLineEdit();
    inputHolder->addRow(inputLabel, input);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Dem Layout hinzufügen
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);
    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
