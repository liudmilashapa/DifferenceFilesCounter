#include "CFKC_4.h"

CFKC_4::CFKC_4(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_widget = new  QWidget();
    setCentralWidget(m_widget);
    createMainBox();
    m_plagiatControl = new PlagiatControl();
}

void CFKC_4::createLableBox(QBoxLayout& _mainBoxLayout)
{
    m_lableBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom); 
    _mainBoxLayout.addLayout(m_lableBoxLayout);

    m_differenceBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_similarityBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
   

    m_lableBoxLayout->addLayout(m_similarityBoxLayout);
    m_lableBoxLayout->addLayout(m_differenceBoxLayout);


    m_constDif = new QLabel("Difference");
    m_constSame = new QLabel("Similarity");
    m_DifLable = new QLabel();
    m_SameLable = new QLabel();

    QFont font1 = m_DifLable->font();
    QFont font2 = m_DifLable->font();
    font1.setPointSize(14);
    font2.setPointSize(10);
    m_DifLable->setFont(font1);
    m_constDif->setFont(font2);

    m_SameLable->setFont(font1);
    m_constSame->setFont(font2);

    m_differenceBoxLayout->addWidget(m_constDif);
    m_differenceBoxLayout->addWidget(m_DifLable);

    m_similarityBoxLayout->addWidget(m_constSame);
    m_similarityBoxLayout->addWidget(m_SameLable);

}

void CFKC_4::createButtonBox(QBoxLayout & _mainBoxLayout)
{
    m_buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    _mainBoxLayout.addLayout(m_buttonBoxLayout);

    m_resultButtton = new QPushButton(("Get Result"));
    m_resetButtton = new QPushButton(("Reset"));

    m_buttonBoxLayout->addWidget(m_resultButtton);
    m_buttonBoxLayout->addWidget(m_resetButtton);

}

void CFKC_4::createResultBox(QBoxLayout & _mainBoxLayout)
{
    m_resultBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    _mainBoxLayout.addLayout(m_resultBoxLayout);
    createLableBox(*m_resultBoxLayout);
    createButtonBox(*m_resultBoxLayout);
    m_resultBoxLayout->setMargin(50);
}

void CFKC_4::createPathInputBox(QBoxLayout & _mainBoxLayout)
{
    m_fileInputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    _mainBoxLayout.addLayout(m_fileInputBoxLayout);

    m_firstfileInputBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_numFileAddedBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_fileInputBoxLayout->addLayout(m_firstfileInputBoxLayout);
    m_fileInputBoxLayout->addLayout(m_numFileAddedBoxLayout);


    m_firstPathLineEdit = new QLineEdit();
    m_browseFirstFileButtton = new QPushButton("File path");
    m_firstfileInputBoxLayout->addWidget(m_firstPathLineEdit);
    m_firstfileInputBoxLayout->addWidget(m_browseFirstFileButtton);


    m_constNumFileAdded = new QLabel("File selected: ");
    m_numFileAdded = new QLabel();
    m_numFileAddedBoxLayout->addWidget(m_constNumFileAdded);
    m_numFileAddedBoxLayout->addWidget(m_numFileAdded);
    QFont font = m_constNumFileAdded->font();
    font.setPointSize(8);
    m_constNumFileAdded->setFont(font);
    m_numFileAdded->setFont(font);
}

void CFKC_4::createMainBox()
{
    m_mainBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    m_widget->setLayout(m_mainBoxLayout);
    createPathInputBox(*m_mainBoxLayout);
    createResultBox(*m_mainBoxLayout);

}

void CFKC_4::clickBrowseFileButtton()
{
    m_QFileDialogTester = new QFileDialogTester();
    QString temp = m_QFileDialogTester->openFile();
    m_plagiatControl->setPath(temp);
    m_firstPathLineEdit->setText(temp);
    m_numFileAdded->setNum(m_plagiatControl->getNumFilePath());
}

