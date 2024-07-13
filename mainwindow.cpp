#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    source = new QLabel("Путь к файлу");
    target = new QLabel("Новый путь");
    newName = new QLabel("Новое имя");
    sourceButton = new QPushButton("Выбрать файл");
    targetButton = new QPushButton("Куда сохранить");
    saveButton = new QPushButton("Сохранить");
    saveSameDirectory = new QCheckBox("Сохранить в той же директории");
    sourceLocation = new QLineEdit;
    targetLocation = new QLineEdit;
    name = new QLineEdit;
    gridLayout = new QGridLayout;
    vLayout = new QVBoxLayout;
    QPixmap pixmap(":/new.png");
    sourceButton->setIcon(pixmap);
    sourceButton->setIconSize(pixmap.size());

    this->resize(720, 480);

    sourceLocation->setEnabled(false);

    vLayout->addWidget(sourceButton, 0, Qt::AlignHCenter);
    gridLayout->addWidget(source, 0, 0);
    gridLayout->addWidget(sourceLocation, 0, 1);
    gridLayout->addWidget(newName, 1, 0);
    gridLayout->addWidget(name, 1, 1);
    gridLayout->addWidget(target, 2, 0);
    gridLayout->addWidget(targetLocation, 2, 1);
    gridLayout->addWidget(targetButton, 2, 2);

    vLayout->addLayout(gridLayout);
    vLayout->addWidget(saveSameDirectory, 0, Qt::AlignHCenter);
    vLayout->addWidget(saveButton, 0, Qt::AlignHCenter);

    connect(saveSameDirectory, SIGNAL(stateChanged(int)), this, SLOT(SaveInSameDirectory(int)));
    connect(sourceButton, SIGNAL(clicked(bool)), this, SLOT(EnterSourcePath()));
    connect(targetButton, SIGNAL(clicked(bool)), this, SLOT(EnterTargetPath()));
    connect(name, SIGNAL(textChanged(const QString&)), this, SLOT(UpdateTargetPath()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(SaveFile()));
    connect(&proc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));

    setLayout(vLayout);
}


MainWindow::~MainWindow() {
    delete sourceButton;
    delete targetButton;
    delete saveButton;
    delete saveSameDirectory;
    delete gridLayout;
    delete vLayout;
    delete sourceLocation;
    delete targetLocation;
    delete name;
    delete source;
    delete target;
    delete newName;
}


void MainWindow::SaveInSameDirectory(int b) {
    targetLocation->setEnabled(!b);
    if (b) {
        UpdateTargetPath();
        targetButton->setEnabled(false);
    } else {
        targetLocation->clear();
        targetButton->setEnabled(true);
    }
}


void MainWindow::EnterSourcePath() {
    QString str = QFileDialog::getOpenFileName(nullptr, "Выбрать файл...", "", "*.mp4");
    sourceLocation->setText(str);
    UpdateTargetPath();
}


void MainWindow::EnterTargetPath() {
    targetLocation->setText(
                QFileDialog::getExistingDirectory(nullptr, "Выбрать каталог...", "") + "/");
}


void MainWindow::UpdateTargetPath() {
    if (!targetLocation->isEnabled()) {
        size_t pos = sourceLocation->text().toStdString().find_last_of("/");
        targetLocation->setText(
                    QString::fromStdString(
                        sourceLocation->text().toStdString().substr(0, pos + 1)));
    }
}


void MainWindow::SaveFile() {
    QString sourcePath = sourceLocation->text();
    QString targetPath = targetLocation->text() + name->text();

    if (sourceLocation->text().isEmpty() ||
        name->text().isEmpty() ||
        targetLocation->text().isEmpty()) {
        QMessageBox::critical(this, "", "Указаны неверные данные");
        return;
    }

    proc.setWorkingDirectory(QDir::currentPath()/* + "/debug"*/);
    proc.start("v2s_p.exe", QStringList({"-s", sourcePath, "-n",
                                         targetPath +
                                         (name->text().contains(".mp3") ? "" : ".mp3")}));
}


void MainWindow::finished() {
    QProcess::ExitStatus exitStatus = proc.exitStatus();

    if (exitStatus == QProcess::NormalExit) {
        QMessageBox::information(this, "", "Операция успешно выполнена");
    } else {
        QMessageBox::information(this, "", "Операция завершилась неудачно");
    }
}
