#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <algorithm>

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QProgressDialog>

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
    QProcess proc;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SaveInSameDirectory(int);
    void EnterSourcePath();
    void EnterTargetPath();
    void UpdateTargetPath();
    void SaveFile();
    void finished();
};

#endif // MAINWINDOW_H
