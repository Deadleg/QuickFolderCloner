#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QPoint>
#include <QMenu>
#include <QAction>

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
    resetList();

    setMasterLayout(masterDirectory);

    connect(ui->listBackup, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
}

void MainWindow::resetList()
{
    childDirectories = new QStringList();

    // Populate model
    model->setStringList(*childDirectories);
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

    // Check if the new dir is not already added, is not empty, and is not the same as the master directory.
    if (newBackupDir != masterDirectory && *newBackupDir != "" && !childDirectories->contains(*newBackupDir)) {
        // Add to list
        childDirectories->append(*newBackupDir);

        // Populate model
        model->setStringList(*childDirectories);
    } else {
        // TODO create dialog to print the error.
    }


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

    // Print file paths
    qDebug() << "src:" << srcFilePath;
    qDebug() << "tgt:" << tgtFilePath;

    if (srcFileInfo.isDir()) { // Is a directory
        qDebug() << "is dir:" << srcFileInfo.isDir();
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();

        // Creater new folder
        if (srcFilePath != masterDirectory && !targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;

        // Get list of files from the source folder
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

        // Call copyRecursively for each file
        foreach (const QString &fileName, fileNames) {
            qDebug() << fileName;
            QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else { // Is a file
        QFile *file = new QFile(tgtFilePath);

        // Clear the targer directory of the file, then copy
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

void MainWindow::ShowContextMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = ui->listBackup->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Delete");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        int row = ui->listBackup->currentIndex().row();
        qDebug() << "Remove row:" << row;
        model->removeRow(row);

        // Remove from list of directores. TODO: check if index is correct.
        childDirectories->removeAt(row);
    }
    else
    {
        qDebug() << "Do nothing";
    }
}
