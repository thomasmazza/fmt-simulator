#ifndef CMPADDWINDOW_HPP
#define CMPADDWINDOW_HPP

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QCloseEvent>
#include <QMessageBox>
#include <QValidator>

class CmpAddWindow : public QDialog{
    Q_OBJECT
public:
    explicit CmpAddWindow(QWidget* parent = 0);
    static void removeItems(QLayout*);
public slots:
    void typeChanged(QString);
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void createNewCmp(QString, double, double, double, double, double, double, double, double, double, double, double, bool);
private:
    void changeCmpType(QString);
    QVBoxLayout* layout;
    QComboBox* cmpSelection;

    QLineEdit* xPos;
    QLineEdit* yPos;
    QLineEdit* zPos;
    QLineEdit* xNorm;
    QLineEdit* yNorm;
    QLineEdit* zNorm;
    QLineEdit* input1;
    QLineEdit* input2;
    QLineEdit* input3;
    QLineEdit* input4;
    QLineEdit* input5a;
    QComboBox* input5b;
};

#endif // CMPADDWINDOW_HPP
