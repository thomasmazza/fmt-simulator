#include "../include/cmpList.hpp"
#include "../include/cmpEditWindow.hpp"

CmpList_element::CmpList_element(int _number, QString _type){
    //TODO: Process list reference transfer
    //Lege Style der Box fest
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(1);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(4);

    //erstellen der buttons und textfelder
    elmNumber = new QLabel(QString::number(_number));
    elmNumber->setFixedWidth(50);
    QFont elmNumberFont = elmNumber->font();
    elmNumberFont.setBold(true);
    elmNumberFont.setPointSize(16);
    elmNumber->setFont(elmNumberFont);
    elmNumber->setAlignment(Qt::AlignCenter);

    elmType = new QLabel(_type);
    elmButtonEdit = new QPushButton();
    elmButtonEdit->setFixedSize(23, 23);
    elmButtonEdit->setIcon(QIcon::fromTheme("document-properties"));
    connect(elmButtonEdit, &QPushButton::clicked, this, &CmpList_element::editElm);

    //Trennlinie erstellen
    QFrame* elmSepLine = new QFrame();
    elmSepLine->setFrameShape(QFrame::VLine);
    elmSepLine->setFrameShadow(QFrame::Sunken);

    //Button-Leiste am Rand erstellen
    QVBoxLayout* elmButtonBox = new QVBoxLayout();
    elmButtonBox->setContentsMargins(0, 5, 6, 5);
    elmButtonBox->setSpacing(3);

    elmButtonRemove = new QPushButton();
    elmButtonRemove->setFixedSize(23, 23);
    elmButtonRemove->setIcon(QIcon::fromTheme("list-remove"));
    elmButtonUp = new QPushButton();
    elmButtonUp->setFixedSize(23, 23);
    elmButtonUp->setIcon(QIcon::fromTheme("go-up"));
    elmButtonDown = new QPushButton();
    elmButtonDown->setFixedSize(23, 23);
    elmButtonDown->setIcon(QIcon::fromTheme("go-down"));

    elmButtonBox->addWidget(elmButtonRemove);
    elmButtonBox->addWidget(elmButtonUp);
    elmButtonBox->addWidget(elmButtonDown);

    //Linken Block anlegen
    QHBoxLayout* elmBoxLeft = new QHBoxLayout();
    elmBoxLeft->setContentsMargins(8, 6, 0, 6);
    elmBoxLeft->setSpacing(3);
    elmBoxLeft->addWidget(elmNumber);
    elmBoxLeft->addWidget(elmType);
    elmBoxLeft->addWidget(elmButtonEdit);


    //Dem Layout hinzufügen
    layout->addItem(elmBoxLeft);
    layout->addWidget(elmSepLine);
    layout->addItem(elmButtonBox);

    this->setLayout(layout);
}

CmpList_element::~CmpList_element(){
}

void CmpList_element::editElm(){
    if(elmType->text() == "Detector"){
        DetectorEditWindow* editWin = new DetectorEditWindow(this);
        connect(editWin, &DetectorEditWindow::editDetector, this, &CmpList_element::applyEditDetector);
    }
    else if(elmType->text() == "Filter"){
        FilterEditWindow* editWin = new FilterEditWindow(this);
        connect(editWin, &FilterEditWindow::editFilter, this, &CmpList_element::applyEditFilter);
    }
    else if(elmType->text() == "One Sided Lens"){
        LensOneSidedEditWindow* editWin = new LensOneSidedEditWindow(this);
        connect(editWin, &LensOneSidedEditWindow::editLensOneSided, this, &CmpList_element::applyEditLensOneSided);
    }
    else if(elmType->text() == "Two Sided Lens"){
        LensTwoSidedEditWindow* editWin = new LensTwoSidedEditWindow(this);
        connect(editWin, &LensTwoSidedEditWindow::editLensTwoSided, this, &CmpList_element::applyEditLensTwoSided);
    }
    else if(elmType->text() == "Circle Mirror"){
        MirrorCircleEditWindow* editWin = new MirrorCircleEditWindow(this);
        connect(editWin, &MirrorCircleEditWindow::editMirrorCircle, this, &CmpList_element::applyEditMirrorCircle);
    }
    else if(elmType->text() == "Elliptical Mirror"){
        MirrorEllipticalEditWindow* editWin = new MirrorEllipticalEditWindow(this);
        connect(editWin, &MirrorEllipticalEditWindow::editMirrorElliptical, this, &CmpList_element::applyEditMirrorElliptical);
    }
    else if(elmType->text() == "Rectangular Mirror"){
        MirrorRectangularEditWindow* editWin = new MirrorRectangularEditWindow(this);
        connect(editWin, &MirrorRectangularEditWindow::editMirrorRectangular, this, &CmpList_element::applyEditMirrorRectangular);
    }
    else if(elmType->text() == "Square Mirror"){
        MirrorSquareEditWindow* editWin = new MirrorSquareEditWindow(this);
        connect(editWin, &MirrorSquareEditWindow::editMirrorSquare, this, &CmpList_element::applyEditMirrorSquare);
    }
}

//Übernehmen der Änderungen der einzelnen Komponententypen
void CmpList_element::applyEditDetector(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditFilter(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _lowerLim, double _upperLim){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditLensOneSided(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _refIndex, double _radiusH, double _radiusW, double _thickness, bool _planeIsFront){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditLensTwoSided(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _refIndex, double _radiusH, double _radiusI, double _radiusO, double _thickness){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditMirrorCircle(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radius){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditMirrorElliptical(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radiusH, double _radiusW){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditMirrorRectangular(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _height, double _width){
    //TODO: In Liste übernehmen
}

void CmpList_element::applyEditMirrorSquare(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _length){
    //TODO: In Liste übernehmen
}

void CmpList_element::deleteElm(){
    //TODO: Liste aktualisieren
}

void CmpList_element::moveUpElm(){
    //TODO: Liste aktualisieren
}

void CmpList_element::moveDownElm(){
    //TODO: Liste aktualisieren
}

void CmpList_box::addCmpButtonPressed(){
    CmpAddWindow* addWin = new CmpAddWindow(this);

    //Klick auf OK des addWin-Fensters mit Erstellung der neuen Komponente vernknüpfen
    connect(addWin, &CmpAddWindow::createNewCmp, this, &CmpList_box::addCmpToList);
}

void CmpList_box::addCmpToList(QString _type, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _in1, double _in2, double _in3, double _in4, double _in5a, bool _in5b){
    layout->removeItem(bottomSpacer);
    //TODO: Ermittle Element-Nummer aus Listenplatz/Listenlänge
    CmpList_element* element = new CmpList_element(1, _type); //TODO: Add List reference transfer

    //TODO: Füge Element in Liste ein

    layout->addWidget(element);
    layout->addItem(bottomSpacer);
}

CmpList_box::CmpList_box(){
    layout = new QVBoxLayout(this);
    bottomSpacer = new QSpacerItem(100, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(bottomSpacer);
    setLayout(layout);
}

CmpList_box::~CmpList_box(){
}
