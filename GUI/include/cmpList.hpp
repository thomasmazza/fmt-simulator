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

class CmpList_element : public QFrame{
    Q_OBJECT
public:
    CmpList_element(int, QString);
    ~CmpList_element();
public slots:
    void editElm();
    void deleteElm();
    void moveUpElm();
    void moveDownElm();

    void applyEditDetector(double, double, double, double, double, double);
    void applyEditFilter(double, double, double, double, double, double, double, double);
    void applyEditLensOneSided(double, double, double, double, double, double, double, double, double, double, bool);
    void applyEditLensTwoSided(double, double, double, double, double, double, double, double, double, double, double);
    void applyEditMirrorCircle(double, double, double, double, double, double, double);
    void applyEditMirrorElliptical(double, double, double, double, double, double, double, double);
    void applyEditMirrorRectangular(double, double, double, double, double, double, double, double);
    void applyEditMirrorSquare(double, double, double, double, double, double, double);
private:
    QLabel* elmNumber;
    QLabel* elmType;
    QPushButton* elmButtonEdit;
    QPushButton* elmButtonRemove;
    QPushButton* elmButtonUp;
    QPushButton* elmButtonDown;
};

class CmpList_box : public QWidget{
    Q_OBJECT
public:
    CmpList_box();
    ~CmpList_box();
public slots:
    void addCmpButtonPressed();
    void addCmpToList(QString, double, double, double, double, double, double, double, double, double, double, double, bool);
private:
    QVBoxLayout* layout;
    QSpacerItem* bottomSpacer;
};

#endif // CMPLIST_H
