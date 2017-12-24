/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGraphicsView *graphicsView;
    QLineEdit *lifesLabel;
    QLineEdit *scoreLabel;
    QLineEdit *infoLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(600, 600);
        Widget->setAutoFillBackground(false);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(50, 70, 500, 500));
        lifesLabel = new QLineEdit(Widget);
        lifesLabel->setObjectName(QStringLiteral("lifesLabel"));
        lifesLabel->setGeometry(QRect(370, 10, 221, 41));
        QFont font;
        font.setFamily(QStringLiteral("Bauhaus 93"));
        font.setPointSize(26);
        lifesLabel->setFont(font);
        scoreLabel = new QLineEdit(Widget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setGeometry(QRect(10, 10, 341, 41));
        scoreLabel->setFont(font);
        infoLabel = new QLineEdit(Widget);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setGeometry(QRect(50, 570, 501, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Bauhaus 93"));
        font1.setPointSize(18);
        infoLabel->setFont(font1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
