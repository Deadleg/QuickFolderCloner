#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

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

    enableWidgets(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Project_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open File"), "F:/google drive/code", QFileDialog::ShowDirsOnly);
    masterDirectory = dir;

    enableWidgets(true);

    setMasterLayout(masterDirectory);
}

void MainWindow::setMasterLayout(const QString &dir)
{
    ui->labelMasterDir->setText(dir);
}

void MainWindow::enableWidgets(bool enable)
{
    ui->listFiles->setEnabled(enable);
    ui->listBackup->setEnabled(enable);
    ui->pushButtonBackup->setEnabled(enable);
    ui->pushButtonBrowse->setEnabled(enable);
    ui->textEditBackupDir->setEnabled(enable);
}

void MainWindow::on_actionQuit_triggered()
{

}

void MainWindow::on_pushButtonBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open File"), "F:/google drive/code", QFileDialog::ShowDirsOnly);
    newBackupDir = &dir;

    // Add to list
    childDirectories->append(*newBackupDir);

    // Populate model
    model->setStringList(*childDirectories);
}

void MainWindow::on_pushButtonBackup_clicked()
{
    for (int i = 0; i < childDirectories->length(); i++) {
        QString dir = childDirectories->at(i);
        //QString srcDir = *masterDirectory;
        //qDebug() << "master" << *masterDirectory;
        copyRecursively(masterDirectory, dir);
    }
}

bool MainWindow::copyRecursively(QString &srcFilePath, QString &tgtFilePath){

    QFileInfo srcFileInfo(srcFilePath);

    qDebug() << "src:" << srcFilePath;
    qDebug() << "tgt:" << tgtFilePath;

    if (srcFileInfo.isDir()) {
        qDebug() << "is dir:" << srcFileInfo.isDir();
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        //qDebug() << !targetDir.mkdir(QFileInfo(tgtFilePath).fileName());
        if (srcFilePath != masterDirectory && !targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

        foreach (const QString &fileName, fileNames) {
            qDebug() << fileName;
            QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
            //qDebug() << "recur" << !copyRecursively(newSrcFilePath, newTgtFilePath);
            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else {
        QFile *file = new QFile(tgtFilePath);
        if (!file->exists() || file->remove()) {
            qDebug() << srcFilePath << "clean!";
            if (!QFile::copy(srcFilePath, tgtFilePath)) {
                qDebug() << srcFilePath << "not clean!";
                return false;
            }
        }
    }
    return true;
}
