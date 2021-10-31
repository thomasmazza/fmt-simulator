#include "../include/cmpEditWindow.hpp"

//---------------
//Detector Window
//---------------

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void DetectorEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

        if(edgeLength->text().contains(',')){
            QMessageBox::critical(this, "Error", (edgeLength->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _edgeLength = edgeLength->text().toDouble();

        if(pixelCount->text().contains(',')){
            QMessageBox::critical(this, "Error", (pixelCount->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
            return;
        }
        double _pixelCount = pixelCount->text().toDouble();


        emit editDetector(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _edgeLength, _pixelCount);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Detector
 * @param _yPos Y-Position of Detector
 * @param _zPos Z-Position of Detector
 * @param _xNorm X-Normal of Detector
 * @param _yNorm Y-Normal of Detector
 * @param _zNorm Z-Normal of Detector
 * @param _edgeLength Edge Length of Detector
 * @param _pixelCount Pixel Count on Edge of Detector
 */
DetectorEditWindow::DetectorEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _edgeLength, double _pixelCount):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Detector");
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
    QLabel* edgeLengthLabel = new QLabel("Edge Length");
    edgeLength = new QLineEdit();
    edgeLength->setValidator(inValidate);
    edgeLength->setText(QString::number(_edgeLength));
    inputHolder->addRow(edgeLengthLabel, edgeLength);

    QLabel* pixelCountLabel = new QLabel("Pixel Count");
    pixelCount = new QLineEdit();
    pixelCount->setValidator(inValidate);
    pixelCount->setText(QString::number(_pixelCount));
    inputHolder->addRow(pixelCountLabel, pixelCount);

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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void FilterEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Filter
 * @param _yPos Y-Position of Filter
 * @param _zPos Z-Position of Filter
 * @param _xNorm X-Normal of Filter
 * @param _yNorm Y-Normal of Filter
 * @param _zNorm Z-Normal of Filter
 * @param _lowerLim Lower pass limit of Filter
 * @param _upperLim Upper pass limit of Filter
 */
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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void LensOneSidedEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of One Sided Lens
 * @param _yPos Y-Position of One Sided Lens
 * @param _zPos Z-Position of One Sided Lens
 * @param _xNorm X-Normal of One Sided Lens
 * @param _yNorm Y-Normal of One Sided Lens
 * @param _zNorm Z-Normal of One Sided Lens
 * @param _refIndex Refractive Index of One Sided Lens
 * @param _radiusH Radius of One Sided Lens
 * @param _radiusW Radis of curvature of One Sided Lens
 * @param _thickness Tickness of One Sided Lens
 * @param _planeIsFront True, if plane surface of One Sided Lens is its Front
 */
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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void LensTwoSidedEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Two Sided Lens
 * @param _yPos Y-Position of Two Sided Lens
 * @param _zPos Z-Position of Two Sided Lens
 * @param _xNorm X-Normal of Two Sided Lens
 * @param _yNorm Y-Normal of Two Sided Lens
 * @param _zNorm Z-Normal of Two Sided Lens
 * @param _refIndex Refractive Index of Two Sided Lens
 * @param _radiusH Radius of Two Sided Lens
 * @param _radiusI Radius of front side curvature of Two Sided Lens
 * @param _radiusO Radius of back side curvature of Two Sided Lens
 * @param _thickness Thickness of Two Sided Lens
 */
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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void MirrorCircleEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Circle Mirror
 * @param _yPos Y-Position of Circle Mirror
 * @param _zPos Z-Position of Circle Mirror
 * @param _xNorm X-Normal of Circle Mirror
 * @param _yNorm Y-Normal of Circle Mirror
 * @param _zNorm Z-Normal of Circle Mirror
 * @param _radius Radius of Circle Mirror
 */
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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void MirrorEllipticalEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Elliptical Mirror
 * @param _yPos Y-Position of Elliptical Mirror
 * @param _zPos Z-Position of Elliptical Mirror
 * @param _xNorm X-Normal of Elliptical Mirror
 * @param _yNorm Y-Normal of Elliptical Mirror
 * @param _zNorm Z-Normal of Elliptical Mirror
 * @param _radiusH Radius in height of Elliptical Mirror
 * @param _radiusW Radius in width of Elliptical Mirror
 */
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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void MirrorRectangularEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Rectangle Mirror
 * @param _yPos Y-Position of Rectangle Mirror
 * @param _zPos Z-Position of Rectangle Mirror
 * @param _xNorm X-Normal of Rectangle Mirror
 * @param _yNorm Y-Normal of Rectangle Mirror
 * @param _zNorm Z-Normal of Rectangle Mirror
 * @param _lengthH Height of Rectangle Mirror
 * @param _lengthW Width of Rectangle Mirror
 */
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

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void MirrorSquareEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
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

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Square Mirror
 * @param _yPos Y-Position of Square Mirror
 * @param _zPos Z-Position of Square Mirror
 * @param _xNorm X-Normal of Square Mirror
 * @param _yNorm Y-Normal of Square Mirror
 * @param _zNorm Z-Normal of Square Mirror
 * @param _length Edge length of Square Mirror
 */
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

//---------------
//Aperture Window
//---------------

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default Close event
 */
void ApertureEditWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer and checking for valid inputs
 */
void ApertureEditWindow::closeOK(){
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

        emit editAperture(_xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _radius);
        this->accept();
        return;
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

/**
 * @brief Creating a new edit window and inserting the current parameter values
 * @param parent Sets parent window, affected by modality
 * @param _xPos X-Position of Aperture
 * @param _yPos Y-Position of Aperture
 * @param _zPos Z-Position of Aperture
 * @param _xNorm X-Normal of Aperture
 * @param _yNorm Y-Normal of Aperture
 * @param _zNorm Z-Normal of Aperture
 * @param _radius Radius of Aperture
 */
ApertureEditWindow::ApertureEditWindow(QWidget* parent, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radius):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Edit Aperture");
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
    radius = new QLineEdit();
    radius->setValidator(inValidate);
    radius->setText(QString::number(_radius));
    inputHolder->addRow(lengthLabel, radius);

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
