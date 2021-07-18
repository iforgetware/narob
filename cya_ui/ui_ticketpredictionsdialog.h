/********************************************************************************
** Form generated from reading UI file 'ticketpredictionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKETPREDICTIONSDIALOG_H
#define UI_TICKETPREDICTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>

QT_BEGIN_NAMESPACE

class Ui_TicketPredictionsDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QFrame *frame;
    QGridLayout *gridLayout_2;

    void setupUi(QDialog *TicketPredictionsDialog)
    {
        if (TicketPredictionsDialog->objectName().isEmpty())
            TicketPredictionsDialog->setObjectName(QString::fromUtf8("TicketPredictionsDialog"));
        TicketPredictionsDialog->resize(1540, 515);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TicketPredictionsDialog->sizePolicy().hasHeightForWidth());
        TicketPredictionsDialog->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(TicketPredictionsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(TicketPredictionsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        frame = new QFrame(TicketPredictionsDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));

        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(TicketPredictionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TicketPredictionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TicketPredictionsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TicketPredictionsDialog);
    } // setupUi

    void retranslateUi(QDialog *TicketPredictionsDialog)
    {
        TicketPredictionsDialog->setWindowTitle(QApplication::translate("TicketPredictionsDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicketPredictionsDialog: public Ui_TicketPredictionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKETPREDICTIONSDIALOG_H
