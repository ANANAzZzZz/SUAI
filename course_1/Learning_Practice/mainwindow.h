#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Create_clicked();

    void on_AutomaticInputButton_clicked();

    void on_sortButton_clicked();

    void on_clearButton_clicked();

    void on_info_triggered();

    void fillMatrixZeroes(int i, int j);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
