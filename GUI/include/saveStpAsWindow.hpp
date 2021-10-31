#ifndef SAVESTPASWINDOW_HPP
#define SAVESTPASWINDOW_HPP

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QCloseEvent>
#include <QMessageBox>

/**
 * @brief SaveStpAsWindow asks the user to enter a name for the setup file
 */
class SaveStpAsWindow : public QDialog{
    Q_OBJECT
public:
    explicit SaveStpAsWindow(QWidget* parent = 0);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void setStpName(QString);
private:
    QLineEdit* input;
    QString path;
};

#endif // SAVESTPASWINDOW_HPP
