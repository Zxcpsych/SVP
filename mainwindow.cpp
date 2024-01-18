// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bmr_calculator.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    age(0), weight(0), height(0), gender(' '),
    resultFormula(""), resultCount(0)
{
    ui->setupUi(this);
    connect(ui->age, &QLineEdit::textChanged, this, &MainWindow::updateAge);
    connect(ui->weight, &QLineEdit::textChanged, this, &MainWindow::updateWeight);
    connect(ui->height, &QLineEdit::textChanged, this, &MainWindow::updateHeight);
    connect(ui->gender, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::updateGender);
    connect(ui->bmr, &QPushButton::clicked, this, &MainWindow::on_bmr_clicked);
    connect(ui->resultLabel, &QLabel::linkActivated, this, &MainWindow::on_resultLabel_linkActivated);
    connect(ui->Save, &QPushButton::clicked, this, &MainWindow::on_Save_clicked);
    connect(ui->formulaChoice, QOverload<int>::of(&QComboBox::activated), this, [this](int index) {
        Q_UNUSED(index);
        calculateBMR();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::calculateBMR()
{
    if (weight <= 0 || height <= 0 || age <= 0) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите корректные значения для веса, роста и возраста.");
        return -1.0;
    }
    double bmr = 0.0;

    QString currentFormulaChoice = getFormulaChoice();

    if (currentFormulaChoice == "J")
    {
        bmr = BMR::calculateBMR_MifflinSanJeor(weight, height, age, gender);
    }
    else if (currentFormulaChoice == "H")
    {
        bmr = BMR::calculateBMR_HarrisBenedict(weight, height, age, gender);
    }
    else
    {
        // Обработка ошибки
        QMessageBox::critical(this, "Ошибка", "Выбрана неверная формула");
        return -1.0;  // Возвращаем -1.0 в случае ошибки
    }

    QString formulaName;
    if (currentFormulaChoice == "J")
    {
        formulaName = "Мифлин-Сан Джон";
    }
    else if (currentFormulaChoice == "H")
    {
        formulaName = "Гарис Бенедикт";
    }

    QString resultMessage = "Базовое количество калорий, затрачиваемых организмом на обмен веществ ("
                            + formulaName + "): " + QString::number(bmr) + " кал/сутки";

    ui->resultLabel->setText(resultMessage);

    // Добавим новые данные для сохранения
    resultFormula = formulaName;
    resultCount++;

    return bmr;  // Возвращаем результат вычислений
}

QString MainWindow::getFormulaChoice() const
{
    return ui->formulaChoice->currentText();
}

void MainWindow::updateAge(const QString &text)
{
    age = text.toInt();
    bool ok;
    int newAge = text.toInt(&ok);

    if (!ok || newAge <= 0) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите корректное значение для возраста.");
        return;
    }


}

void MainWindow::updateWeight(const QString &text)
{
    weight = text.toInt();
    bool ok;
    int newWeight = text.toInt(&ok);

    if (!ok || newWeight <= 0) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите корректное значение для веса.");
        return;
    }
}

void MainWindow::updateHeight(const QString &text)
{
    height = text.toInt();
    bool ok;
    int newHeight = text.toInt(&ok);

    if (!ok || newHeight <= 0) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите корректное значение для роста.");
        return;
    }
}

void MainWindow::on_bmr_clicked()
{
    calculateBMR();
}

void MainWindow::on_resultLabel_linkActivated(const QString &link)
{
    Q_UNUSED(link);
    // Ваш код обработки события
}

void MainWindow::updateGender(int index)
{
    gender = ui->gender->currentText().toLatin1().at(0);
}

void MainWindow::on_Save_clicked()
{
    qDebug() << "on_Save_clicked() start";
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить данные", "", "Текстовые файлы (*.txt);;Все файлы (*)");

    if (fileName.isEmpty()) {
        return; // Если пользователь не выбрал файл, прекратить выполнение функции
    }

    // Сохраняем текущее значение formulaChoice перед вызовом calculateBMR
    QString currentFormulaChoice = getFormulaChoice();

    // Вызываем calculateBMR и сохраняем результат в переменную
    double bmrResult = calculateBMR();

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        out << "Вес: " << weight << " кг\n";
        out << "Рост: " << height << " см\n";
        out << "Возраст: " << age << " лет\n";
        out << "Пол: " << gender << "\n";
        out << "Выбранная формула: " << currentFormulaChoice << "\n";  // Используем сохраненное значение
        out << "Автор формулы: " << resultFormula << "\n";
        if (bmrResult != -1.0) {
            out << "Результат вычислений по формуле: " << bmrResult << " кал/сутки\n";
        }

        file.close();
        QMessageBox::information(this, "Сохранение", "Данные успешно сохранены в файл: " + fileName);
    } else {
        qDebug() << "Ошибка открытия файла для записи: " << file.errorString();
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть/создать файл для записи: " + file.errorString());
    }
    qDebug() << "on_Save_clicked() end";
}

void MainWindow::updateFormula(int index)
{
    Q_UNUSED(index);
    calculateBMR();
}
