#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_Project_triggered();

    void on_actionQuit_triggered();

    void on_pushButtonBrowse_clicked();

    void on_pushButtonBackup_clicked();

private:
    bool copyRecursively(QString &srcFileDirectory, QString &child);
    void setMasterLayout(const QString &dir);

    QStringListModel *model;
    Ui::MainWindow *ui;
    QString masterDirectory;
    QString *newBackupDir;
    QStringList *childDirectories;
};

#endif // MAINWINDOW_H
