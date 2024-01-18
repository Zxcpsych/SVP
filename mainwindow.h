// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QTextStream>
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <iostream>

namespace Ui {
class MainWindow;
}

// Добавляем объявление функций из пространства имен BMR
namespace BMR {
double calculateBMR_MifflinSanJeor(int weight, int height, int age, char gender);
double calculateBMR_HarrisBenedict(int weight, int height, int age, char gender);
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int age = 0;
    int weight = 0;
    int height = 0;
    char gender = ' ';
    QString resultFormula = "";
    int resultCount = 0;

private slots:
    double calculateBMR();
    void updateAge(const QString &text);
    void updateWeight(const QString &text);
    void updateHeight(const QString &text);
    void updateGender(int index);
    void updateFormula(int index);
    void on_bmr_clicked();
    void on_Save_clicked();
    void on_resultLabel_linkActivated(const QString &link);
    QString getFormulaChoice() const;
};

#endif // MAINWINDOW_H
