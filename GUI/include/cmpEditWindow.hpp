#ifndef CMPEDITWINDOW_HPP
#define CMPEDITWINDOW_HPP

#include <QDialog>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QValidator>
#include <QMessageBox>
#include <QCloseEvent>
#include <QComboBox>

#include "../../logic/include/setupList.hpp"
#include "../../components/include/detector.hpp"
#include "../../components/include/filter.hpp"
#include "../../components/include/lensOneSided.hpp"
#include "../../components/include/lensTwoSided.hpp"
#include "../../components/include/mirrorCircle.hpp"
#include "../../components/include/mirrorElliptical.hpp"
#include "../../components/include/mirrorRectangle.hpp"
#include "../../components/include/mirrorSquare.hpp"

class DetectorEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit DetectorEditWindow(QWidget*, double, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editDetector(double, double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* edgeLength;
    QLineEdit* pixelCount;

    List* componentList;
};

class FilterEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit FilterEditWindow(QWidget*, double, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editFilter(double, double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* lowerLim;
    QLineEdit* upperLim;

    List* componentList;
};

class LensOneSidedEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit LensOneSidedEditWindow(QWidget*, double, double, double, double, double, double, double, double, double, double, bool);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editLensOneSided(double, double, double, double, double, double, double, double, double, double, bool);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* refIndex;
    QLineEdit* radiusH;
    QLineEdit* radiusW;
    QLineEdit* thickness;
    QComboBox* planeIsFront;

    List* componentList;
};

class LensTwoSidedEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit LensTwoSidedEditWindow(QWidget*, double, double, double, double, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editLensTwoSided(double, double, double, double, double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* refIndex;
    QLineEdit* radiusH;
    QLineEdit* radiusI;
    QLineEdit* radiusO;
    QLineEdit* thickness;

    List* componentList;
};

class MirrorCircleEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorCircleEditWindow(QWidget*, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editMirrorCircle(double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* radius;

    List* componentList;
};

class MirrorEllipticalEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorEllipticalEditWindow(QWidget*, double, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editMirrorElliptical(double, double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* radiusH;
    QLineEdit* radiusW;

    List* componentList;
};

class MirrorRectangularEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorRectangularEditWindow(QWidget*, double, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editMirrorRectangular(double, double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* height;
    QLineEdit* width;

    List* componentList;
};

class MirrorSquareEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorSquareEditWindow(QWidget*, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editMirrorSquare(double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* length;

    List* componentList;
};

class ApertureEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit ApertureEditWindow(QWidget*, double, double, double, double, double, double, double);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editAperture(double, double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* radius;

    List* componentList;
};

#endif // CMPEDITWINDOW_HPP
