#include "../include/cmpAddWindow.hpp"

/**
 * @brief Changes input form of the Window corresponding to the given Type
 * @param _type Currently selected Type, which is selected in the Drop Down Menu.
 *
 * This function is called, if the user changes the Component Type in the Drop Down Menu.
 *
 * According to the given Type, the Window is adjusted. All Layout-Elements are taken out
 * of the Form Layout, and will be re-created right away, to match the Form of the selected
 * Type in the Drop Down Menu.
 */
void CmpAddWindow::changeCmpType(QString _type){
    auto del = layout->takeAt(1)->layout();
    utilsGUI::removeItems(del);

    QFormLayout* _inputHolder = new QFormLayout();
    _inputHolder->setSpacing(6);

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
    yPos = new QLineEdit();
    yPos->setValidator(inValidate);
    yPos->setPlaceholderText("Y");
    zPos = new QLineEdit();
    zPos->setValidator(inValidate);
    zPos->setPlaceholderText("Z");
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
    yNorm = new QLineEdit();
    yNorm->setValidator(inValidate);
    yNorm->setPlaceholderText("Y");
    zNorm = new QLineEdit();
    zNorm->setValidator(inValidate);
    zNorm->setPlaceholderText("Z");
    normBox->addWidget(xNorm);
    normBox->addWidget(yNorm);
    normBox->addWidget(zNorm);

    //Einfügen der Zeilen
    _inputHolder->addRow(posLabel, posBox);
    _inputHolder->addRow(normLabel, normBox);

    //Auf If-Verzweigung zurückgreifen, da switch cases nicht mit QString funktionieren.....
    if(_type == "Detector"){
        QLabel* lowerLimLabel = new QLabel("Edge Length");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(lowerLimLabel, input1);

        QLabel* upperLimLabel = new QLabel("Pixel Count");
        input2 = new QLineEdit();
        input2->setValidator(inValidate);
        _inputHolder->addRow(upperLimLabel, input2);
    }
    else if(_type == "Filter"){
        QLabel* lowerLimLabel = new QLabel("Lower Limit");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(lowerLimLabel, input1);

        QLabel* upperLimLabel = new QLabel("Upper Limit");
        input2 = new QLineEdit();
        input2->setValidator(inValidate);
        _inputHolder->addRow(upperLimLabel, input2);
    }
    else if(_type == "One Sided Lens"){
        QLabel* refIndexLabel = new QLabel("Refractive Index");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(refIndexLabel, input1);

        QLabel* radiusHLabel = new QLabel("Radius of Lens");
        input2 = new QLineEdit();
        input2->setValidator(inValidate);
        _inputHolder->addRow(radiusHLabel, input2);

        QLabel* radiusWLabel = new QLabel("Radius of Curvature");
        input3 = new QLineEdit();
        input3->setValidator(inValidate);
        _inputHolder->addRow(radiusWLabel, input3);

        QLabel* thicknessLabel = new QLabel("Thickness");
        input4 = new QLineEdit();
        input4->setValidator(inValidate);
        _inputHolder->addRow(thicknessLabel, input4);

        QLabel* planeIsFrontLabel = new QLabel("Position of plane Surface");
        input5b = new QComboBox();
        input5b->addItem("Front");
        input5b->addItem("Back");
        _inputHolder->addRow(planeIsFrontLabel, input5b);
    }
    else if(_type == "Two Sided Lens"){
        QLabel* refIndexLabel = new QLabel("Refractive Index");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(refIndexLabel, input1);

        QLabel* radiusHLabel = new QLabel("Radius of Lens");
        input2 = new QLineEdit();
        input2->setValidator(inValidate);
        _inputHolder->addRow(radiusHLabel, input2);

        QLabel* radiusILabel = new QLabel("Radius of Inner Curvature");
        input3 = new QLineEdit();
        input3->setValidator(inValidate);
        _inputHolder->addRow(radiusILabel, input3);

        QLabel* radiusOLabel = new QLabel("Radius of Outer Curvature");
        input4 = new QLineEdit();
        input4->setValidator(inValidate);
        _inputHolder->addRow(radiusOLabel, input4);

        QLabel* thicknessLabel = new QLabel("Thickness");
        input5a = new QLineEdit();
        input5a->setValidator(inValidate);
        _inputHolder->addRow(thicknessLabel, input5a);
    }
    else if(_type == "Circle Mirror"){
        QLabel* radiusLabel = new QLabel("Radius");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(radiusLabel, input1);
    }
    else if(_type == "Elliptical Mirror"){
        QLabel* radiusHLabel = new QLabel("Height Radius");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(radiusHLabel, input1);

        QLabel* radiusWLabel = new QLabel("Width Radius");
        input2 = new QLineEdit();
        input2->setValidator(inValidate);
        _inputHolder->addRow(radiusWLabel, input2);
    }
    else if(_type == "Rectangular Mirror"){
        QLabel* lengthHLabel = new QLabel("Height");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(lengthHLabel, input1);

        QLabel* lengthWLabel = new QLabel("Width");
        input2 = new QLineEdit();
        input2->setValidator(inValidate);
        _inputHolder->addRow(lengthWLabel, input2);
    }
    else if(_type == "Square Mirror"){
        QLabel* lengthLabel = new QLabel("Edge Length");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(lengthLabel, input1);
    }
    else if(_type == "Aperture"){
        QLabel* radiusLabel = new QLabel("Radius");
        input1 = new QLineEdit();
        input1->setValidator(inValidate);
        _inputHolder->addRow(radiusLabel, input1);
    }

    layout->insertLayout(1, _inputHolder);
    layout->update();
}

/**
 * @brief Triggers the Restructure of the Input Form according to the given type
 * @param _type Currently selected Component Type in Drop Down Menu
 */
void CmpAddWindow::typeChanged(QString _type){
    changeCmpType(_type);
}

/**
 * @brief Adds a warning dialog, if the user tries to close the window
 * @param event Default close event
 */
void CmpAddWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton exitMessage = QMessageBox::critical(this, "Warning", "If you close the window now, no changes will be made.", QMessageBox::Ok|QMessageBox::Cancel);
    if(exitMessage == QMessageBox::Ok) event->accept();
    else event->ignore();
}

/**
 * @brief Closes the window, triggering the data transfer
 */
void CmpAddWindow::closeOK(){
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


        //Wieder if-Verzweigung weil QString nicht im Switch-Case unterstützt wird
        QString type = cmpSelection->currentText();
        if(type == "Detector"){
            if(!input1->text().isEmpty() && !input2->text().isEmpty()){
                //Restliche inputs konvertieren und prüfen
                if(input1->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input1->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in1 = input1->text().toDouble();

                if(input2->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input2->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in2 = input2->text().toDouble();

                emit createNewCmp(type, _xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _in1, _in2, 0, 0, 0, false);
                this->accept();
                return;
            }
        }
        else if(type == "Filter" || type == "Elliptical Mirror" || type == "Rectangular Mirror"){
            if(!input1->text().isEmpty() && !input2->text().isEmpty()){
                //Restliche inputs konvertieren und prüfen
                if(input1->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input1->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in1 = input1->text().toDouble();

                if(input2->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input2->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in2 = input2->text().toDouble();

                emit createNewCmp(type, _xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _in1, _in2, 0, 0, 0, false);
                this->accept();
                return;
            }
        }
        else if(type == "One Sided Lens"){
            if(!input1->text().isEmpty() && !input2->text().isEmpty() && !input3->text().isEmpty()){
                //Restliche inputs konvertieren und prüfen
                if(input1->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input1->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in1 = input1->text().toDouble();

                if(input2->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input2->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in2 = input2->text().toDouble();

                if(input3->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input3->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in3 = input3->text().toDouble();

                if(input4->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input4->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in4 = input4->text().toDouble();

                bool _in5b = false;
                if(input5b->currentText() == "Front") _in5b = true;

                emit createNewCmp(type, _xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _in1, _in2, _in3, _in4, 0, _in5b);
                this->accept();
                return;
            }
        }
        else if(type == "Two Sided Lens"){
            if(!input1->text().isEmpty() && !input2->text().isEmpty() && !input3->text().isEmpty() && !input5a->text().isEmpty()){
                //Restliche inputs konvertieren und prüfen
                if(input1->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input1->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in1 = input1->text().toDouble();

                if(input2->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input2->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in2 = input2->text().toDouble();

                if(input3->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input3->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in3 = input3->text().toDouble();

                if(input4->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input4->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in4 = input4->text().toDouble();

                if(input5a->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input5a->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in5a = input5a->text().toDouble();

                emit createNewCmp(type, _xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _in1, _in2, _in3, _in4, _in5a, false);
                this->accept();
                return;
            }
        }
        else if(type == "Circle Mirror" || type == "Square Mirror" || type == "Aperture"){
            if(!input1->text().isEmpty()){
                //Restliche inputs konvertieren und prüfen
                if(input1->text().contains(',')){
                    QMessageBox::critical(this, "Error", (input1->text() + " is no valid number\nPlease use '.' instead of ','"), QMessageBox::Ok);
                    return;
                }
                double _in1 = input1->text().toDouble();

                emit createNewCmp(type, _xPos, _yPos, _zPos, _xNorm, _yNorm, _zNorm, _in1, 0, 0, 0, 0, false);
                this->accept();
                return;
            }
        }
    }
    QMessageBox::critical(this, "Error", "Empty input fields are not allowed.", QMessageBox::Ok);
}

/**
 * @brief Creates a new Window
 * @param parent Pointer to parental Window, wich is disabled due to modality, while CmpAddWindow is active
 */
CmpAddWindow::CmpAddWindow(QWidget* parent):QDialog(parent){
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Add new component");
    this->setFixedSize(400, 300);

    layout = new QVBoxLayout();
    layout->setSpacing(12);

    cmpSelection = new QComboBox();
    cmpSelection->addItem("Aperture");
    cmpSelection->addItem("Detector");
    cmpSelection->addItem("Filter");
    cmpSelection->addItem("One Sided Lens");
    cmpSelection->addItem("Two Sided Lens");
    cmpSelection->addItem("Circle Mirror");
    cmpSelection->addItem("Elliptical Mirror");
    cmpSelection->addItem("Rectangular Mirror");
    cmpSelection->addItem("Square Mirror");

    //Erstelle form layout für Eingabefelder
    QFormLayout* inputHolder = new QFormLayout();
    inputHolder->setSpacing(6);

    QSpacerItem* vSpacer = new QSpacerItem(100, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

    //Erstelle layout für Ok/Cancel Button
    QHBoxLayout* buttonHolder = new QHBoxLayout();
    buttonHolder->setSpacing(6);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonHolder->addWidget(okButton);
    buttonHolder->addWidget(cancelButton);

    //Füge zu Fensterlayout die Elemente hinzu
    layout->addWidget(cmpSelection);
    layout->addItem(inputHolder);
    layout->addItem(vSpacer);
    layout->addItem(buttonHolder);

    this->setLayout(layout);

    changeCmpType("Aperture");

    this->show();

    connect(cmpSelection, SIGNAL(currentTextChanged(QString)), this, SLOT(typeChanged(QString)));
    connect(okButton, SIGNAL(clicked()), this, SLOT(closeOK()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
