#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulationparameters.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_inputTotalEdit_returnPressed();

    void on_inputObjectEdit_returnPressed();

    void on_inputPerEdit_returnPressed();

    void on_inputCellEdit_returnPressed();

    void on_oscIndexEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    SimParams *parameters;
};

#endif // MAINWINDOW_H
