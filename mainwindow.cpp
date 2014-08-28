#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    childDirectories = new QStringList();

    // Populate model
    model = new QStringListModel(*childDirectories);
    model->setStringList(*childDirectories);

    // Add to list
    ui->listBackup->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Project_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open File"), "C://", QFileDialog::ShowDirsOnly);
    masterDirectory = &dir;
    qDebug() << "Master: " << *masterDirectory;

    setMasterLayout(*masterDirectory);
}

void MainWindow::setMasterLayout(const QString &dir)
{
    ui->labelMasterDir->setText(dir);
}

void MainWindow::on_actionQuit_triggered()
{

}

void MainWindow::on_pushButtonBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open File"), "C://", QFileDialog::ShowDirsOnly);
    newBackupDir = &dir;

    // Add to list
    childDirectories->append(*newBackupDir);

    // Populate model
    model->setStringList(*childDirectories);

    // Add to list
    //ui->listBackup->setModel(model);
}
