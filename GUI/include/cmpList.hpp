#ifndef CMPLIST_H
#define CMPLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

#include "cmpAddWindow.hpp"

#include "../../logic/include/setupList.hpp"
#include "../../logic/include/exporter.hpp"
#include "../../logic/include/importer.hpp"
#include "../../components/include/detector.hpp"
#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorElliptical.hpp"
#include "../../components/include/mirrorRectangle.hpp"
#include "../../components/include/mirrorSquare.hpp"
#include "../../components/include/aperture.hpp"

/**
 * @brief Small representation widget for components in the list
 */
class CmpList_element : public QFrame{
    Q_OBJECT
public:
    CmpList_element(int, QString, List*);
    ~CmpList_element();
    void changeButtonActivity(bool, bool);
signals:
    void triggerRebuildList();
public slots:
    void editElm();
    void deleteElm();
    void moveUpElm();
    void moveDownElm();

    void applyEditDetector(double, double, double, double, double, double, double, double);
    void applyEditFilter(double, double, double, double, double, double, double, double);
    void applyEditLensOneSided(double, double, double, double, double, double, double, double, double, double, bool);
    void applyEditLensTwoSided(double, double, double, double, double, double, double, double, double, double, double);
    void applyEditMirrorCircle(double, double, double, double, double, double, double);
    void applyEditMirrorElliptical(double, double, double, double, double, double, double, double);
    void applyEditMirrorRectangular(double, double, double, double, double, double, double, double);
    void applyEditMirrorSquare(double, double, double, double, double, double, double);
    void applyEditAperture(double, double, double, double, double, double, double);
private:
    QLabel* elmNumber;
    QLabel* elmType;
    QPushButton* elmButtonEdit;
    QPushButton* elmButtonRemove;
    QPushButton* elmButtonUp;
    QPushButton* elmButtonDown;

    List* componentList;
};

class CmpList_box : public QWidget{
    Q_OBJECT
public:
    CmpList_box();
    ~CmpList_box();
    List* getComponentList();
    void rebuildFromList();
    void resetList();
public slots:
    void addCmpButtonPressed();
    void addCmpToList(QString, double, double, double, double, double, double, double, double, double, double, double, bool);
private:
    QVBoxLayout* layout;
    QSpacerItem* bottomSpacer;

    List* componentList;
};

#endif // CMPLIST_H
