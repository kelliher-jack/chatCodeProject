/********************************************************************************
** Form generated from reading UI file 'htm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTM_H
#define UI_HTM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_htmClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *htmClass)
    {
        if (htmClass->objectName().isEmpty())
            htmClass->setObjectName(QStringLiteral("htmClass"));
        htmClass->resize(600, 400);
        menuBar = new QMenuBar(htmClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        htmClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(htmClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        htmClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(htmClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        htmClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(htmClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        htmClass->setStatusBar(statusBar);

        retranslateUi(htmClass);

        QMetaObject::connectSlotsByName(htmClass);
    } // setupUi

    void retranslateUi(QMainWindow *htmClass)
    {
        htmClass->setWindowTitle(QApplication::translate("htmClass", "htm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class htmClass: public Ui_htmClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTM_H
