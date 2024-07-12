#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <algorithm>
#include <iostream>

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QFileDialog>

class MainWindow : public QWidget {
private:
    Q_OBJECT

    QPushButton *sourceButton;
    QPushButton *targetButton;
    QPushButton *saveButton;
    QCheckBox *saveSameDirectory;
    QGridLayout *gridLayout;
    QVBoxLayout *vLayout;
    QLineEdit *sourceLocation;
    QLineEdit *targetLocation;
    QLineEdit *name;
    QLabel *source;
    QLabel *target;
    QLabel *newName;
    QPixmap *pixmap;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SaveInSameDirectory(int);
    void EnterSourcePath();
    void EnterTargetPath();
    void UpdateTargetPath();
};

#endif // MAINWINDOW_H
