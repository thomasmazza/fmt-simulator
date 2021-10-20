#ifndef PRJNEWWINDOW_HPP
#define PRJNEWWINDOW_HPP

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

class PrjNewWindow : public QDialog{
    Q_OBJECT
public:
    explicit PrjNewWindow(QWidget* parent = 0, QString _path = "/home");
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void setPrjName(QString, QString);
private:
    QLineEdit* input;
    QString path;
};

#endif // PRJNEWWINDOW_HPP
