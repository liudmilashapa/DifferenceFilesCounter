#pragma once
#include "plagiatControl.h"

#include <QtWidgets>

#include <qfiledialog.h>
#include <QFileDialog>
#include "ui_CFKC_4.h"

class QFileDialogTester : public QWidget
{
public:
    QString openFile()
    {
        QString filename = QFileDialog::getOpenFileName(
            this,
            "Open Document",
            QDir::currentPath(),
            "Text files (*.txt)");
        return filename;
    }
  
};


class CFKC_4 : public QMainWindow
{
    Q_OBJECT

public:
    CFKC_4(QWidget *parent = Q_NULLPTR);
	QWidget* m_widget;

	QLabel* m_DifLable;
	QLabel* m_constDif;
    QLabel* m_SameLable;
    QLabel* m_constSame;
    QLabel* m_NormalA;
    QLabel* m_constNormalA;
    QLabel* m_NormalB;
    QLabel* m_constNormalB;
    QLabel* m_constNumFileAdded;
    QLabel* m_numFileAdded;
    QFont qfontPrimary;
    QFont qfontSecondary;
    QLabel* m_descriptionCommonDiff;
    QLabel* m_descriptionSeparateDiff;

    QLabel* m_firstPathLineEdit;

	QPushButton* m_resultButtton;
    QPushButton* m_resetButtton;
    QPushButton* m_browseFirstFileButtton;

    QFileDialogTester* m_QFileDialogTester;

	QBoxLayout* m_mainBoxLayout;
	QBoxLayout* m_fileInputBoxLayout;
    QBoxLayout* m_firstfileInputBoxLayout;
    QBoxLayout* m_numFileAddedBoxLayout;
	QBoxLayout* m_resultBoxLayout;
    QBoxLayout* m_differenceBoxLayout;	
    QBoxLayout* m_similarityBoxLayout;
    QBoxLayout* m_buttonBoxLayout;
    QBoxLayout* m_lableBoxLayout;
    QBoxLayout* m_tableBoxLayout;

    QTableWidget* m_table = nullptr;

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/


	void createMainBox();

    QBoxLayout* createResultBox();
    QBoxLayout* createPathInputBox();
    QBoxLayout* createLableBox();
    QBoxLayout* createButtonBox();

    void addDisplatInfoTable();
    void displayTable();

    PlagiatControl * m_plagiatControl;

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

public slots:

    void clickBrowseFileButtton();
    void clickResultButtton();
    void clickResetButtton();

private:

    Ui::CFKC_4Class ui;

};
