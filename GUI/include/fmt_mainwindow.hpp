#ifndef FMT_MAINWINDOW_HPP
#define FMT_MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>

#include "ui_fmt_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class fmt_mainWindow; }
QT_END_NAMESPACE

class fmt_mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    fmt_mainWindow(QWidget *parent = nullptr);
    ~fmt_mainWindow();
signals:
    void triggerCmpAdd();

private slots:
    void closeEvent(QCloseEvent*);

    void checkOnCmpAdd();

    void on_OpenInFile_clicked();

    void on_OpenStpFile_clicked();

    void on_actionNew_Project_triggered();

    void createNewProject(QString, QString);

    void on_actionLoad_Project_triggered();

    void on_InFileAuto_clicked();

    void on_StpFileAuto_clicked();

    void on_actionSave_Setup_as_triggered();

    void on_actionSave_Project_triggered();

    void saveWithOtherName(QString);

    void on_RunOptimization_clicked();

    void on_SimStartSimulation_clicked();

    void startSimulation(int);

    void on_actionFMT_Simulator_triggered();

private:
    bool autoDetect(QString, QString);
    Ui::fmt_mainWindow *ui;

    Config::object simObj;
    std::vector<Photon>* photonList;
    QPixmap* resultImage;
};
#endif // FMT_MAINWINDOW_HPP
