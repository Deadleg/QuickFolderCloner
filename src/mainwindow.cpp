#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QSettings>
#include <QtWidgets>
#include <Exception>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize file QTreeView
    filesModel = new QFileSystemModel(this);

    ui->treeViewMasterFolder->setModel(filesModel);

    QSettings appSettings("wk", "ThesisBackup");

    childDirectories = new QStringList();

    if (appSettings.contains("dirs")) {
        qDebug() << "contains dirs";
        masterDirectory = appSettings.value("master").toString();
        qDebug() << "crash";
        *childDirectories = appSettings.value("children").toStringList();

        enableWidgets(true);
        setMasterLayout(masterDirectory);

        // Set files treeView
        filesModel->setRootPath(masterDirectory);
        ui->treeViewMasterFolder->setRootIndex(filesModel->index(masterDirectory));
    } else {
        masterDirectory = "";
        childDirectories = new QStringList();

        enableWidgets(false);

    }

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));


    // Populate model
    backupModel = new QStringListModel(*childDirectories);
    backupModel->setStringList(*childDirectories);

    // Add to list
    ui->listBackup->setModel(backupModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Project_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open File"), "C:/", QFileDialog::ShowDirsOnly);
    masterDirectory = dir;

    qDebug() << dir;

    enableWidgets(true);
    resetList();

    setMasterLayout(masterDirectory);

    connect(ui->listBackup, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

    // Set files treeView
    filesModel->setRootPath(masterDirectory);
    ui->treeViewMasterFolder->setRootIndex(filesModel->index(masterDirectory));
}

void MainWindow::resetList()
{
    childDirectories = new QStringList();

    // Populate model
    backupModel->setStringList(*childDirectories);
}

void MainWindow::setMasterLayout(const QString &dir)
{
    ui->labelMasterDir->setText(dir);
}

void MainWindow::enableWidgets(bool enable)
{
    ui->treeViewMasterFolder->setEnabled(enable);
    ui->listBackup->setEnabled(enable);
    ui->pushButtonBackup->setEnabled(enable);
    ui->pushButtonBrowse->setEnabled(enable);
}

void MainWindow::on_actionQuit_triggered()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (masterDirectory.size() != 0 && childDirectories->size() != 0) {
        QSettings appSettings("wk", "ThesisBackup");
        appSettings.setValue("dirs", 1);
        appSettings.setValue("master", masterDirectory);
        appSettings.setValue("children", *childDirectories);
    }
    event->accept();
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
        backupModel->setStringList(*childDirectories);

    } else {
        // TODO create dialog to print the error.
    }


}

void MainWindow::on_pushButtonBackup_clicked()
{
    // Disable backup button while performing backup.
    ui->pushButtonBackup->setEnabled(false);
    for (int i = 0; i < childDirectories->length(); i++) {
        QString dir = childDirectories->at(i);
        copyRecursively(masterDirectory, dir);
        ui->statusBar->showMessage("Backup to " + childDirectories->at(i) + " completed");
    }

    // Enable backup button when finished.
    ui->pushButtonBackup->setEnabled(true);
}

bool MainWindow::copyRecursively(QString &srcFilePath, QString &tgtFilePath){

    QFileInfo srcFileInfo(srcFilePath);

    // Print file paths
    qDebug() << "src:" << srcFilePath;
    qDebug() << "tgt:" << tgtFilePath;

    if (srcFileInfo.isDir()) { // Is a directory
        ui->statusBar->showMessage("Entering " + srcFilePath);

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

        ui->statusBar->showMessage("Copying " + srcFilePath + " to " + tgtFilePath);
        // Clear the targer directory of the file, then copy
        if (!file->exists() || file->remove()) {
            qDebug() << srcFilePath << "clean!";

            ui->statusBar->showMessage("Deleted " + tgtFilePath);
            if (!QFile::copy(srcFilePath, tgtFilePath)) {
                qDebug() << srcFilePath << "not clean!";

                ui->statusBar->showMessage("Deletion failed for " + tgtFilePath);

                // Error occured copying file.
                QMessageBox msgBox;
                const QString err =  "An error occured copying " + srcFilePath + " to " + tgtFilePath;
                msgBox.critical(this,"Error!", err);
                msgBox.exec();

                return false;
            } else {
                ui->statusBar->showMessage("Successfully copied to " + tgtFilePath);
            }
        } else {
            ui->statusBar->showMessage("Unable to delete " + tgtFilePath);
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
        backupModel->removeRow(row);

        // Remove from list of directores. TODO: check if index is correct.
        childDirectories->removeAt(row);
    }
    else
    {
        qDebug() << "Do nothing";
    }
}


