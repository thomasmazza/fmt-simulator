#include "../include/cmpEditWindow.hpp"

//---------------
//Detector Window
//---------------

void DetectorEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void DetectorEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        emit editDetector(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

DetectorEditWindow::DetectorEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Detector");
    this->setFixedSize(400, 110);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//Filter Window
//---------------

void FilterEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void FilterEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !lowerLim->text().isEmpty() &&
            !upperLim->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(lowerLim->text().contains(',')){
            QMessageBox::critical(this, "Error", (lowerLim->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _lowerLim = lowerLim->text().toDouble();

        if(upperLim->text().contains(',')){
            QMessageBox::critical(this, "Error", (upperLim->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _upperLim = upperLim->text().toDouble();

        emit editFilter(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _lowerLim, _upperLim);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

FilterEditWindow::FilterEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _lowerLim, double _upperLim):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Filter");
    this->setFixedSize(400, 180);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* lowerLimLabel = new QLabel("Lower Limit");
    lowerLim = new QLineEdit();
    lowerLim->setValidator(inValidate);
    lowerLim->setText(QString::number(_lowerLim));
    inputHolder->addRow(lowerLimLabel, lowerLim);

    QLabel* upperLimLabel = new QLabel("Upper Limit");
    upperLim = new QLineEdit();
    upperLim->setValidator(inValidate);
    upperLim->setText(QString::number(_upperLim));
    inputHolder->addRow(upperLimLabel, upperLim);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//One Sided Lens Window
//---------------

void LensOneSidedEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void LensOneSidedEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !refIndex->text().isEmpty() &&
            !radiusH->text().isEmpty() &&
            !radiusW->text().isEmpty() &&
            !thickness->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(refIndex->text().contains(',')){
            QMessageBox::critical(this, "Error", (refIndex->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _refIndex = refIndex->text().toDouble();

        if(radiusH->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusH->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusH = radiusH->text().toDouble();

        if(radiusW->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusW->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusW = radiusW->text().toDouble();

        if(thickness->text().contains(',')){
            QMessageBox::critical(this, "Error", (thickness->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _thickness = thickness->text().toDouble();

        bool _planeIsFront = false;
        if(planeIsFront->currentText() == "Front") _planeIsFront = true;

        emit editLensOneSided(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _refIndex, _radiusH, _radiusW, _thickness, _planeIsFront);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

LensOneSidedEditWindow::LensOneSidedEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _refIndex, double _radiusH, double _radiusW, double _thickness, bool _planeIsFront):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit One Sided Lens");
    this->setFixedSize(400, 270);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* refIndexLabel = new QLabel("Refractive Index");
    refIndex = new QLineEdit();
    refIndex->setValidator(inValidate);
    refIndex->setText(QString::number(_refIndex));
    inputHolder->addRow(refIndexLabel, refIndex);

    QLabel* radiusHLabel = new QLabel("Radius of Lens");
    radiusH = new QLineEdit();
    radiusH->setValidator(inValidate);
    radiusH->setText(QString::number(_radiusH));
    inputHolder->addRow(radiusHLabel, radiusH);

    QLabel* radiusWLabel = new QLabel("Radius of Curvature");
    radiusW = new QLineEdit();
    radiusW->setValidator(inValidate);
    radiusW->setText(QString::number(_radiusW));
    inputHolder->addRow(radiusWLabel, radiusW);

    QLabel* thicknessLabel = new QLabel("Thickness");
    thickness = new QLineEdit();
    thickness->setValidator(inValidate);
    thickness->setText(QString::number(_thickness));
    inputHolder->addRow(thicknessLabel, thickness);

    QLabel* planeIsFrontLabel = new QLabel("Position of plane Surface");
    planeIsFront = new QComboBox();
    planeIsFront->addItem("Front");
    planeIsFront->addItem("Back");
    if(!_planeIsFront) planeIsFront->setCurrentIndex(1);
    inputHolder->addRow(planeIsFrontLabel, planeIsFront);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//Two Sided Lens Window
//---------------

void LensTwoSidedEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void LensTwoSidedEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !refIndex->text().isEmpty() &&
            !radiusH->text().isEmpty() &&
            !radiusI->text().isEmpty() &&
            !radiusO->text().isEmpty() &&
            !thickness->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(refIndex->text().contains(',')){
            QMessageBox::critical(this, "Error", (refIndex->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _refIndex = refIndex->text().toDouble();

        if(radiusH->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusH->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusH = radiusH->text().toDouble();

        if(radiusI->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusI->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusI = radiusI->text().toDouble();

        if(radiusO->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusO->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusO = radiusO->text().toDouble();

        if(thickness->text().contains(',')){
            QMessageBox::critical(this, "Error", (thickness->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _thickness = thickness->text().toDouble();

        emit editLensTwoSided(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _refIndex, _radiusH, _radiusI, _radiusO, _thickness);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

LensTwoSidedEditWindow::LensTwoSidedEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _refIndex, double _radiusH, double _radiusI, double _radiusO, double _thickness):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Two Sided Lens");
    this->setFixedSize(400, 270);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* refIndexLabel = new QLabel("Refractive Index");
    refIndex = new QLineEdit();
    refIndex->setValidator(inValidate);
    refIndex->setText(QString::number(_refIndex));
    inputHolder->addRow(refIndexLabel, refIndex);

    QLabel* radiusHLabel = new QLabel("Radius of Lens");
    radiusH = new QLineEdit();
    radiusH->setValidator(inValidate);
    radiusH->setText(QString::number(_radiusH));
    inputHolder->addRow(radiusHLabel, radiusH);

    QLabel* radiusILabel = new QLabel("Radius of Inner Curvature");
    radiusI = new QLineEdit();
    radiusI->setValidator(inValidate);
    radiusI->setText(QString::number(_radiusI));
    inputHolder->addRow(radiusILabel, radiusI);

    QLabel* radiusOLabel = new QLabel("Radius of Outer Curvature");
    radiusO = new QLineEdit();
    radiusO->setValidator(inValidate);
    radiusO->setText(QString::number(_radiusO));
    inputHolder->addRow(radiusOLabel, radiusO);

    QLabel* thicknessLabel = new QLabel("Thickness");
    thickness = new QLineEdit();
    thickness->setValidator(inValidate);
    thickness->setText(QString::number(_thickness));
    inputHolder->addRow(thicknessLabel, thickness);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//Circle Mirror Window
//---------------

void MirrorCircleEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void MirrorCircleEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !radius->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(radius->text().contains(',')){
            QMessageBox::critical(this, "Error", (radius->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radius = radius->text().toDouble();

        emit editMirrorCircle(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _radius);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

MirrorCircleEditWindow::MirrorCircleEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radius):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Circle Mirror");
    this->setFixedSize(400, 140);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* radiusLabel = new QLabel("Radius");
    radius = new QLineEdit();
    radius->setValidator(inValidate);
    radius->setText(QString::number(_radius));
    inputHolder->addRow(radiusLabel, radius);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//Elliptical Mirror Window
//---------------

void MirrorEllipticalEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void MirrorEllipticalEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !radiusH->text().isEmpty() &&
            !radiusW->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(radiusH->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusH->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusH = radiusH->text().toDouble();

        if(radiusW->text().contains(',')){
            QMessageBox::critical(this, "Error", (radiusW->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _radiusW = radiusW->text().toDouble();

        emit editMirrorElliptical(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _radiusH, _radiusW);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

MirrorEllipticalEditWindow::MirrorEllipticalEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radiusH, double _radiusW):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Elliptical Mirror");
    this->setFixedSize(400, 170);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* radiusHLabel = new QLabel("Height Radius");
    radiusH = new QLineEdit();
    radiusH->setValidator(inValidate);
    radiusH->setText(QString::number(_radiusH));
    inputHolder->addRow(radiusHLabel, radiusH);

    QLabel* radiusWLabel = new QLabel("Width Radius");
    radiusW = new QLineEdit();
    radiusW->setValidator(inValidate);
    radiusW->setText(QString::number(_radiusW));
    inputHolder->addRow(radiusWLabel, radiusW);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//Rectangular Mirror Window
//---------------

void MirrorRectangularEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void MirrorRectangularEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !height->text().isEmpty() &&
            !width->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(height->text().contains(',')){
            QMessageBox::critical(this, "Error", (height->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _height = height->text().toDouble();

        if(width->text().contains(',')){
            QMessageBox::critical(this, "Error", (width->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _width = width->text().toDouble();

        emit editMirrorRectangular(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _height, _width);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

MirrorRectangularEditWindow::MirrorRectangularEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _lengthH, double _lengthW):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Rectangular Mirror");
    this->setFixedSize(400, 170);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* heightLabel = new QLabel("Height");
    height = new QLineEdit();
    height->setValidator(inValidate);
    height->setText(QString::number(_lengthH));
    inputHolder->addRow(heightLabel, height);

    QLabel* widthLabel = new QLabel("Width");
    width = new QLineEdit();
    width->setValidator(inValidate);
    width->setText(QString::number(_lengthW));
    inputHolder->addRow(widthLabel, width);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

//---------------
//Square Mirror Window
//---------------

void MirrorSquareEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

void MirrorSquareEditWindow::closeOK(){
    if(!xPos->text().isEmpty() &&
            !yPos->text().isEmpty() &&
            !zPos->text().isEmpty() &&
            !xNorm->text().isEmpty() &&
            !yNorm->text().isEmpty() &&
            !zNorm->text().isEmpty() &&
            !length->text().isEmpty()){
        //Eingaben auf double prüfen und konvertieren
        if(xPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (xPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xPos = xPos->text().toDouble();

        if(yPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (yPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yPos = yPos->text().toDouble();

        if(zPos->text().contains(',')){
            QMessageBox::critical(this, "Error", (zPos->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zPos = zPos->text().toDouble();

        if(xNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (xNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _xNorm = xNorm->text().toDouble();

        if(yNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (yNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _yNorm = yNorm->text().toDouble();

        if(zNorm->text().contains(',')){
            QMessageBox::critical(this, "Error", (zNorm->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _zNorm = zNorm->text().toDouble();

        if(length->text().contains(',')){
            QMessageBox::critical(this, "Error", (length->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _length = length->text().toDouble();

        emit editMirrorSquare(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _length);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

MirrorSquareEditWindow::MirrorSquareEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _length):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Square Mirror");
    this->setFixedSize(400, 140);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(12);

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    //Double-Validator erstellen
    QDoubleValidator* inValidate = new QDoubleValidator();
    inValidate->setNotation(QDoubleValidator::ScientificNotation);

    //Position-Eingabefelder
    QLabel* posLabel = new QLabel("Position");
    QHBoxLayout* posBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xPos = new QLineEdit();
    xPos->setValidator(inValidate);
    xPos->setPlaceholderText("X");
    xPos->setText(QString::number(_xPos));
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    yPos->setText(QString::number(_yPos));
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
    zPos->setText(QString::number(_zPos));
    posBox->addWidget(xPos);
    posBox->addWidget(yPos);
    posBox->addWidget(zPos);

    //Richtungs-Eingabefelder
    QLabel* normLabel = new QLabel("Direction");
    QHBoxLayout* normBox = new QHBoxLayout();
    posBox->setContentsMargins(0, 0, 0, 0);
    posBox->setSpacing(5);
    xNorm = new QLineEdit();
    xNorm->setValidator(inValidate);
    xNorm->setPlaceholderText("X");
    xNorm->setText(QString::number(_xNorm));
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    yNorm->setText(QString::number(_yNorm));
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    zNorm->setText(QString::number(_zNorm));
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    inputHolder->addRow(posLabel, posBox);
    inputHolder->addRow(normLabel, normBox);

    //Restliche Parameter
    QLabel* lengthLabel = new QLabel("Edge Length");
    length = new QLineEdit();
    length->setValidator(inValidate);
    length->setText(QString::number(_length));
    inputHolder->addRow(lengthLabel, length);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addItem(inputHolder);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    this->show();

    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
