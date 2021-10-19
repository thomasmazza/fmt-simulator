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

class DetectorEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit DetectorEditWindow(QWidget* parent = 0);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void editDetector(double, double, double, double, double, double);
private:
    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
};

class FilterEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit FilterEditWindow(QWidget* parent = 0);
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
};

class LensOneSidedEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit LensOneSidedEditWindow(QWidget* parent = 0);
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
};

class LensTwoSidedEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit LensTwoSidedEditWindow(QWidget* parent = 0);
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
};

class MirrorCircleEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorCircleEditWindow(QWidget* parent = 0);
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
};

class MirrorEllipticalEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorEllipticalEditWindow(QWidget* parent = 0);
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
};

class MirrorRectangularEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorRectangularEditWindow(QWidget* parent = 0);
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
};

class MirrorSquareEditWindow : public QDialog{
    Q_OBJECT
public:
    explicit MirrorSquareEditWindow(QWidget* parent = 0);
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
};

#endif // CMPEDITWINDOW_HPP
