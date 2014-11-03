#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionNew_Project_triggered();

    void on_actionQuit_triggered();

    void on_pushButtonBrowse_clicked();

    void on_pushButtonBackup_clicked();

    void ShowContextMenu(const QPoint& pos);

private:
    bool copyRecursively(QString &srcFileDirectory, QString &child);
    void setMasterLayout(const QString &dir);
    void enableWidgets(bool enable);
    void resetList();

    QStringListModel *backupModel;
    QFileSystemModel *filesModel;
    Ui::MainWindow *ui;
    QString masterDirectory;
    QString *newBackupDir;
    QStringList *childDirectories;
};

#endif // MAINWINDOW_H
