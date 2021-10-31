#include "../include/saveStpAsWindow.hpp"

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void SaveStpAsWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, the Setup will not be saved.", QMessageBox::Yes|QMessageBox::No);
    if(exitMessage == QMessageBox::Yes) event->accept();
    else event->ignore();
}

/**
 * @brief Checks, if a name is entered, and if so, triggers its transfer to the parent window
 */
void SaveStpAsWindow::closeOK(){
    if(input->text().isEmpty()){
        QMessageBox::critical(this, "Error", "Please enter a new Setup File Name.", QMessageBox::Ok);
        return;
    }
    emit setStpName(input->text());
    this->accept();
}

/**
 * @brief Creates a window for entering a setup name, providing a text field and OK/Cancel-Buttons
 * @param parent Parent window affected by modality
 */
SaveStpAsWindow::SaveStpAsWindow(QWidget* parent):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Save Setup File with other Name");
    this->setFixedSize(400, 80);

    //Layout-Element erstellen
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Form-Layout für Projektname erstellen
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);
    QLabel* inputLabel = new QLabel("Setup File Name");
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
