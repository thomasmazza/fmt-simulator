#include "../include/cmpList.hpp"
#include "../include/cmpEditWindow.hpp"

#include "../../utils/include/utils.hpp"

CmpList_element::CmpList_element(int _number, QString _type, List* _list){
    //Übergebe Listen-Referenz
    componentList = _list;

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
    connect(elmButtonRemove, &QPushButton::clicked, this, &CmpList_element::deleteElm);
    elmButtonUp = new QPushButton();
    elmButtonUp->setFixedSize(23, 23);
    elmButtonUp->setIcon(QIcon::fromTheme("go-up"));
    connect(elmButtonUp, &QPushButton::clicked, this, &CmpList_element::moveUpElm);
    elmButtonDown = new QPushButton();
    elmButtonDown->setFixedSize(23, 23);
    elmButtonDown->setIcon(QIcon::fromTheme("go-down"));
    connect(elmButtonDown, &QPushButton::clicked, this, &CmpList_element::moveDownElm);

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

void CmpList_element::changeButtonActivity(bool _butUp, bool _butDown){
    elmButtonUp->setEnabled(_butUp);
    elmButtonDown->setEnabled(_butDown);
}

void CmpList_element::editElm(){
    if(elmType->text() == "Detector"){
        DetectorEditWindow* editWin = new DetectorEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2]);
        connect(editWin, &DetectorEditWindow::editDetector, this, &CmpList_element::applyEditDetector);
    }
    else if(elmType->text() == "Filter"){
        FilterEditWindow* editWin = new FilterEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<Filter &>(*componentList->elem(elmNumber->text().toInt() - 1)).getLowerLimit(),
            static_cast<Filter &>(*componentList->elem(elmNumber->text().toInt() - 1)).getUpperLimit());
        connect(editWin, &FilterEditWindow::editFilter, this, &CmpList_element::applyEditFilter);
    }
    else if(elmType->text() == "One Sided Lens"){
        LensOneSidedEditWindow* editWin = new LensOneSidedEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getN(),
            static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusH(),
            static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusW(),
            static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getD(),
            static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getPlaneIsFront());
        connect(editWin, &LensOneSidedEditWindow::editLensOneSided, this, &CmpList_element::applyEditLensOneSided);
    }
    else if(elmType->text() == "Two Sided Lens"){
        LensTwoSidedEditWindow* editWin = new LensTwoSidedEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getN(),
            static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusH(),
            static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusI(),
            static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusO(),
            static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).getD());
        connect(editWin, &LensTwoSidedEditWindow::editLensTwoSided, this, &CmpList_element::applyEditLensTwoSided);
    }
    else if(elmType->text() == "Circle Mirror"){
        MirrorCircleEditWindow* editWin = new MirrorCircleEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<MirrorCircle &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadius());
        connect(editWin, &MirrorCircleEditWindow::editMirrorCircle, this, &CmpList_element::applyEditMirrorCircle);
    }
    else if(elmType->text() == "Elliptical Mirror"){
        MirrorEllipticalEditWindow* editWin = new MirrorEllipticalEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<MirrorElliptical &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusH(),
            static_cast<MirrorElliptical &>(*componentList->elem(elmNumber->text().toInt() - 1)).getRadiusW());
        connect(editWin, &MirrorEllipticalEditWindow::editMirrorElliptical, this, &CmpList_element::applyEditMirrorElliptical);
    }
    else if(elmType->text() == "Rectangular Mirror"){
        MirrorRectangularEditWindow* editWin = new MirrorRectangularEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<MirrorRectangle &>(*componentList->elem(elmNumber->text().toInt() - 1)).getLengthH(),
            static_cast<MirrorRectangle &>(*componentList->elem(elmNumber->text().toInt() - 1)).getLengthW());
        connect(editWin, &MirrorRectangularEditWindow::editMirrorRectangular, this, &CmpList_element::applyEditMirrorRectangular);
    }
    else if(elmType->text() == "Square Mirror"){
        MirrorSquareEditWindow* editWin = new MirrorSquareEditWindow(this,
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getPosition()[2],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[0],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[1],
            componentList->elem(elmNumber->text().toInt() - 1)->getNormal()[2],
            static_cast<MirrorSquare &>(*componentList->elem(elmNumber->text().toInt() - 1)).getLength());
        connect(editWin, &MirrorSquareEditWindow::editMirrorSquare, this, &CmpList_element::applyEditMirrorSquare);
    }
}

//Übernehmen der Änderungen der einzelnen Komponententypen
void CmpList_element::applyEditDetector(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
}

void CmpList_element::applyEditFilter(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _lowerLim, double _upperLim){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<Filter &>(*componentList->elem(elmNumber->text().toInt() - 1)).setLowerLimit(_lowerLim);
    static_cast<Filter &>(*componentList->elem(elmNumber->text().toInt() - 1)).setUpperLimit(_upperLim);
}

void CmpList_element::applyEditLensOneSided(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _refIndex, double _radiusH, double _radiusW, double _thickness, bool _planeIsFront){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setN(_refIndex);
    static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusH(_radiusH);
    static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusW(_radiusW);
    static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setD(_thickness);
    static_cast<LensOneSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setPlaneIsFront(_planeIsFront);
}

void CmpList_element::applyEditLensTwoSided(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _refIndex, double _radiusH, double _radiusI, double _radiusO, double _thickness){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setN(_refIndex);
    static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusH(_radiusH);
    static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusI(_radiusI);
    static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusO(_radiusO);
    static_cast<LensTwoSided &>(*componentList->elem(elmNumber->text().toInt() - 1)).setD(_thickness);
}

void CmpList_element::applyEditMirrorCircle(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radius){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<MirrorCircle &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadius(_radius);
}

void CmpList_element::applyEditMirrorElliptical(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _radiusH, double _radiusW){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<MirrorElliptical &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusH(_radiusH);
    static_cast<MirrorElliptical &>(*componentList->elem(elmNumber->text().toInt() - 1)).setRadiusW(_radiusW);
}

void CmpList_element::applyEditMirrorRectangular(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _height, double _width){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<MirrorRectangle &>(*componentList->elem(elmNumber->text().toInt() - 1)).setLengthH(_height);
    static_cast<MirrorRectangle &>(*componentList->elem(elmNumber->text().toInt() - 1)).setLengthW(_width);
}

void CmpList_element::applyEditMirrorSquare(double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _length){
    //In Liste übernehmen
    componentList->elem(elmNumber->text().toInt() - 1)->setPosition(std::vector<double>(3) = {_xPos, _yPos, _zPos});
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    componentList->elem(elmNumber->text().toInt() - 1)->setNormal(_norm);
    static_cast<MirrorSquare &>(*componentList->elem(elmNumber->text().toInt() - 1)).setLength(_length);
}

void CmpList_element::deleteElm(){
    //Element löschen und Liste aktualisieren
    componentList->del(elmNumber->text().toInt());
    emit triggerRebuildList();
}

void CmpList_element::moveUpElm(){
    //TODO: Liste aktualisieren
    componentList->swap(elmNumber->text().toInt() - 1, elmNumber->text().toInt() - 2);
    emit triggerRebuildList();
}

void CmpList_element::moveDownElm(){
    //TODO: Liste aktualisieren
    componentList->swap(elmNumber->text().toInt() - 1, elmNumber->text().toInt());
    emit triggerRebuildList();
}

void CmpList_box::rebuildFromList(){
    auto del = layout->layout();
    utilsGUI::removeItems(del);

    int length = componentList->getLength();
    //Lade alle Components aus der Liste neu und stelle grafisch dar
    for(int i = 0; i < length; i++){
        ComponentType _type = componentList->elem(i)->getType();

        CmpList_element* element;
        switch(_type){
        case detector:
            element = new CmpList_element(i + 1, "Detector", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case filter:
            element = new CmpList_element(i + 1, "Filter", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case lensOneSided:
            element = new CmpList_element(i + 1, "One Sided Lens", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case lensTwoSided:
            element = new CmpList_element(i + 1, "Two Sided Lens", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case mirrorCircle:
            element = new CmpList_element(i + 1, "Circle Mirror", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case mirrorElliptical:
            element = new CmpList_element(i + 1, "Elliptical Mirror", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case mirrorRectangle:
            element = new CmpList_element(i + 1, "Rectangular Mirror", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        case mirrorSquare:
            element = new CmpList_element(i + 1, "Square Mirror", componentList);

            //Element einfügen
            layout->removeItem(bottomSpacer);
            layout->addWidget(element);
            layout->addItem(bottomSpacer);
            break;
        }
        //Deaktiviere Hoch/Runter-Buttons für erstes/letztes Element
        if(length == 1) element->changeButtonActivity(false, false);
        else{
            if(i == 0) element->changeButtonActivity(false, true);
            else if(i == length - 1) element->changeButtonActivity(true, false);
            else element->changeButtonActivity(true, true);
        }

        connect(element, &CmpList_element::triggerRebuildList, this, &CmpList_box::rebuildFromList);
    }
}

void CmpList_box::resetList(){
    componentList = new List();
}

List* CmpList_box::getComponentList(){
    return componentList;
}

void CmpList_box::addCmpButtonPressed(){
    CmpAddWindow* addWin = new CmpAddWindow(this);

    //Klick auf OK des addWin-Fensters mit Erstellung der neuen Komponente vernknüpfen
    connect(addWin, &CmpAddWindow::createNewCmp, this, &CmpList_box::addCmpToList);
}

void CmpList_box::addCmpToList(QString _type, double _xPos, double _yPos, double _zPos, double _xNorm, double _yNorm, double _zNorm, double _in1, double _in2, double _in3, double _in4, double _in5a, bool _in5b){
    layout->removeItem(bottomSpacer);
    //Ermittle Element-Nummer aus Listenplatz/Listenlänge
    int length = componentList->getLength();
    short elmNumber = length + 1;
    CmpList_element* element = new CmpList_element(elmNumber, _type, componentList);
    connect(element, &CmpList_element::triggerRebuildList, this, &CmpList_box::rebuildFromList);

    //Füge Element in die Liste ein
    std::vector<double> _pos(3); _pos[0] = _xPos; _pos[1] = _yPos; _pos[2] = _zPos;
    std::vector<double> _norm(3); _norm[0] = _xNorm; _norm[1] = _yNorm; _norm[2] = _zNorm;
    Utils::normalizeVector(_norm);
    //If-Verzweigung weil switch-cases nicht mit Strings kompatibel sind...
    if(_type == "Detector"){
        //TODO: Übergebene Werte beheben
        Detector* _new = new Detector(_pos, _norm, _norm, _norm, 3, 0.1);
        componentList->append<Detector>(*_new);
    }
    else if(_type == "Filter"){
        Filter* _new = new Filter(_pos, _norm, _in1, _in2);
        componentList->append<Filter>(*_new);
    }
    else if(_type == "One Sided Lens"){
        LensOneSided* _new = new LensOneSided(_pos, _norm, _in1, _in2, _in3, _in4, _in5b);
        componentList->append<LensOneSided>(*_new);
    }
    else if(_type == "Two Sided Lens"){
        LensTwoSided* _new = new LensTwoSided(_pos, _norm, _in1, _in2, _in3, _in4, _in5a);
        componentList->append<LensTwoSided>(*_new);
    }
    else if(_type == "Circle Mirror"){
        MirrorCircle* _new = new MirrorCircle(_pos, _norm, _in1);
        componentList->append<MirrorCircle>(*_new);
    }
    else if(_type == "Elliptical Mirror"){
        MirrorElliptical* _new = new MirrorElliptical(_pos, _norm, _in1, _in2);
        componentList->append<MirrorElliptical>(*_new);
    }
    else if(_type == "Rectangular Mirror"){
        MirrorRectangle* _new = new MirrorRectangle(_pos, _norm, _in1, _in2);
        componentList->append<MirrorRectangle>(*_new);
    }
    else if(_type == "Square Mirror"){
        MirrorSquare* _new = new MirrorSquare(_pos, _norm, _in1);
        componentList->append<MirrorSquare>(*_new);
    }

    rebuildFromList();
}

CmpList_box::CmpList_box(){
    layout = new QVBoxLayout(this);
    bottomSpacer = new QSpacerItem(100, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(bottomSpacer);
    setLayout(layout);

    componentList = new List();
}

CmpList_box::~CmpList_box(){
}
