#ifndef SIMSTARTWINDOW_H
#define SIMSTARTWINDOW_H

#include <QDialog>
#include <QSpinBox>
#include <QCloseEvent>
#include <QMessageBox>
#include <QBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>

/**
 * @brief SimStartWindow provides a Dialog, asking the user to enter the amount of simulated photons
 *
 * 3 Default Numbers are provided by buttons
 */
class SimStartWindow : public QDialog{
    Q_OBJECT
public:
    explicit SimStartWindow(QWidget* parent = 0);
public slots:
    void closeEvent(QCloseEvent*);
    void closeOK();
signals:
    void simStart(int);
private:
    QSpinBox* input;
private slots:
    void setQuickTest();
    void setRecommended();
    void setMax();
};

#endif // SIMSTARTWINDOW_H
