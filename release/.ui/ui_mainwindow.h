/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Project;
    QAction *actionQuit;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *masterDirLayout;
    QLabel *labelMasterDir;
    QTreeView *treeViewMasterFolder;
    QWidget *layoutWidget1;
    QVBoxLayout *childDirLayout;
    QLabel *labelBackups;
    QListView *listBackup;
    QPushButton *pushButtonBackup;
    QPushButton *pushButtonBrowse;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(580, 418);
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName(QStringLiteral("actionNew_Project"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 261, 213));
        masterDirLayout = new QVBoxLayout(layoutWidget);
        masterDirLayout->setSpacing(6);
        masterDirLayout->setContentsMargins(11, 11, 11, 11);
        masterDirLayout->setObjectName(QStringLiteral("masterDirLayout"));
        masterDirLayout->setContentsMargins(0, 0, 0, 0);
        labelMasterDir = new QLabel(layoutWidget);
        labelMasterDir->setObjectName(QStringLiteral("labelMasterDir"));

        masterDirLayout->addWidget(labelMasterDir);

        treeViewMasterFolder = new QTreeView(layoutWidget);
        treeViewMasterFolder->setObjectName(QStringLiteral("treeViewMasterFolder"));

        masterDirLayout->addWidget(treeViewMasterFolder);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(310, 10, 261, 213));
        childDirLayout = new QVBoxLayout(layoutWidget1);
        childDirLayout->setSpacing(6);
        childDirLayout->setContentsMargins(11, 11, 11, 11);
        childDirLayout->setObjectName(QStringLiteral("childDirLayout"));
        childDirLayout->setContentsMargins(0, 0, 0, 0);
        labelBackups = new QLabel(layoutWidget1);
        labelBackups->setObjectName(QStringLiteral("labelBackups"));

        childDirLayout->addWidget(labelBackups);

        listBackup = new QListView(layoutWidget1);
        listBackup->setObjectName(QStringLiteral("listBackup"));
        listBackup->setContextMenuPolicy(Qt::CustomContextMenu);

        childDirLayout->addWidget(listBackup);

        pushButtonBackup = new QPushButton(centralWidget);
        pushButtonBackup->setObjectName(QStringLiteral("pushButtonBackup"));
        pushButtonBackup->setGeometry(QRect(160, 280, 261, 61));
        pushButtonBrowse = new QPushButton(centralWidget);
        pushButtonBrowse->setObjectName(QStringLiteral("pushButtonBrowse"));
        pushButtonBrowse->setGeometry(QRect(310, 240, 259, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 580, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew_Project->setText(QApplication::translate("MainWindow", "New Project", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        labelMasterDir->setText(QApplication::translate("MainWindow", "Master:", 0));
        labelBackups->setText(QApplication::translate("MainWindow", "Backups", 0));
        pushButtonBackup->setText(QApplication::translate("MainWindow", "Backup!", 0));
        pushButtonBrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
