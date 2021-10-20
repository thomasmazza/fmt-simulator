#include "../include/simStartWindow.hpp"

void SimStartWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::warning(this, "Warning", "If you close the window now, the Simulation will be cancelled.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void SimStartWindow::closeOK(){
    emit simStart(input->value());
    this->accept();
}

void SimStartWindow::setQuickTest(){
    //Setze Quick-Test Anzahl
    input->setValue(100000);
}

void SimStartWindow::setRecommended(){
    //Setze empfohlene Anzahl
    input->setValue(10000000);
}

void SimStartWindow::setMax(){
    //Setze maximale Anzahl
    input->setValue(std::numeric_limits<int>::max());
}

SimStartWindow::SimStartWindow(QWidget* parent):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Simulation Settings");
    this->setFixedSize(400, 120);

    //Layout-Element erstellen
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Layout für Form und Buttons erstellen
    QHBoxLayout* interactionHolder = new QHBoxLayout();
    interactionHolder->setSpacing(6);

    //Form-Layout für Projektname erstellen
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);
    QLabel* inputLabel = new QLabel("Number of simulated Photons");
    input = new QSpinBox();
    input->setRange(10000, std::numeric_limits<int>::max());
    input->setSingleStep(1000);
    inputHolder->addRow(inputLabel, input);

    //Buttons für vorgegebene Photonenzahlen erstellen
    QPushButton* quickTestButton = new QPushButton("Quick Testing");
    quickTestButton->setToolTip("Fast throughput for validation purposes");

    QPushButton* recommendedButton = new QPushButton("Recommended");
    recommendedButton->setIcon(QIcon::fromTheme("zoom-fit-best"));
    recommendedButton->setToolTip("Recommended number for a reasonable output");

    QPushButton* maxButton = new QPushButton("Maximum");
    maxButton->setIcon(QIcon::fromTheme("dialog-warning"));
    maxButton->setToolTip("Might lead to enormous calculation times!");

    interactionHolder->addWidget(quickTestButton);
    interactionHolder->addWidget(recommendedButton);
    interactionHolder->addWidget(maxButton);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Dem Layout hinzufügen
    layout->addItem(inputHolder);
    layout->addItem(interactionHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);
    this->show();

    connect(quickTestButton, SIGNAL(clicked()), this, SLOT(setQuickTest()));
    connect(recommendedButton, SIGNAL(clicked()), this, SLOT(setRecommended()));
    connect(maxButton, SIGNAL(clicked()), this, SLOT(setMax()));

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
