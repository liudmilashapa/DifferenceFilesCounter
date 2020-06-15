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

QBoxLayout* CFKC_4::createLableBox()
{
    m_lableBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom); 
    
    m_differenceBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_similarityBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
   
     m_lableBoxLayout->addLayout(m_differenceBoxLayout);
     m_lableBoxLayout->addLayout(m_similarityBoxLayout);


    /*m_descriptionCommonDiff = new QLabel("Agrigate difference and similarity");
    m_lableBoxLayout->addWidget(m_descriptionCommonDiff);*/

    m_constDif = new QLabel("Difference");
    m_constSame = new QLabel("Similarity");
    m_DifLable = new QLabel();
    m_SameLable = new QLabel();

    m_DifLable->setFont(qfontPrimary);
    m_constDif->setFont(qfontPrimary);

    m_SameLable->setFont(qfontPrimary);
    m_constSame->setFont(qfontPrimary);

    m_differenceBoxLayout->addWidget(m_constDif);
    m_differenceBoxLayout->addWidget(m_DifLable);

    m_similarityBoxLayout->addWidget(m_constSame);
    m_similarityBoxLayout->addWidget(m_SameLable);

    return m_lableBoxLayout;
}

QBoxLayout* CFKC_4::createButtonBox()
{
    m_buttonBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    m_resultButtton = new QPushButton(("Get Result"));
    m_resetButtton = new QPushButton(("Reset"));

    //m_resultButtton->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    //m_resetButtton->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    m_buttonBoxLayout->addWidget(m_resultButtton);
    m_buttonBoxLayout->addWidget(m_resetButtton);

    return m_buttonBoxLayout;
}

QBoxLayout* CFKC_4::createResultBox()
{
    m_resultBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
 //   m_resultBoxLayout->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
  //  m_resultBoxLayout->setSpacing(QLayout::SetFixedSize);
    m_resultBoxLayout->addLayout(createLableBox());
    m_resultBoxLayout->addLayout(createButtonBox());
    m_resultBoxLayout->setMargin(50);

    return m_resultBoxLayout;
}

QBoxLayout * CFKC_4::createPathInputBox()
{
    m_fileInputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    
    m_firstfileInputBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_numFileAddedBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_fileInputBoxLayout->addLayout(m_firstfileInputBoxLayout);
    m_fileInputBoxLayout->addLayout(m_numFileAddedBoxLayout);


    m_firstPathLineEdit = new QLabel();
    m_browseFirstFileButtton = new QPushButton("File path");

   // m_firstPathLineEdit->setSizePolicy(QSizePolicy::horizontalPolicy, QSizePolicy::verticalPolicy);
   // m_firstPathLineEdit->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    m_firstfileInputBoxLayout->addWidget(m_firstPathLineEdit);
    m_firstfileInputBoxLayout->addWidget(m_browseFirstFileButtton);


    m_constNumFileAdded = new QLabel("File selected: ");
    m_numFileAdded = new QLabel();
    m_numFileAddedBoxLayout->addWidget(m_constNumFileAdded);
    m_numFileAddedBoxLayout->addWidget(m_numFileAdded);
  
    m_constNumFileAdded->setFont(qfontSecondary);
    m_numFileAdded->setFont(qfontSecondary);

    return m_fileInputBoxLayout;
}

void CFKC_4::createMainBox()
{
    qfontPrimary.setPointSize(14);
    qfontSecondary.setPointSize(10);

    m_mainBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    m_widget->setLayout(m_mainBoxLayout);

    m_mainBoxLayout->addLayout(createPathInputBox());

    m_descriptionCommonDiff = new QLabel("Aggregate difference and similarity");
    m_mainBoxLayout->addWidget(m_descriptionCommonDiff);
    m_descriptionCommonDiff->setFont(qfontSecondary);

    m_mainBoxLayout->addLayout(createResultBox());

    m_descriptionSeparateDiff = new QLabel("Separate difference / similarity");
    m_mainBoxLayout->addWidget(m_descriptionSeparateDiff);
    m_descriptionSeparateDiff->setFont(qfontSecondary);

    m_tableBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
   /* m_tableBoxLayout->addWidget(m_descriptionSeparateDiff);*/
    m_mainBoxLayout->addLayout(m_tableBoxLayout);
    
    




}


void CFKC_4::displayTable()
{
    if (!m_table)
    {
        m_table = new QTableWidget;

    }
    m_table->setRowCount(0);
    m_table->setMaximumHeight(500);
    m_table->setMinimumHeight(100);
    m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_tableBoxLayout->addWidget(m_table);

    int maxsize = m_plagiatControl->getNumFilePath();
    int rowSize = m_plagiatControl->getNumFilePath();
    
    m_table->setRowCount(rowSize);
    m_table->setColumnCount(maxsize);
    m_table->setMinimumWidth(10 * maxsize);
    m_table->horizontalHeader()->setDefaultSectionSize(40);

    QColor color1;
    color1 = QColor(174, 214, 241);
   
    for (int i = 0; i < m_plagiatControl->getNumFilePath(); i++)
    {
        m_table->setColumnWidth(i, 100);
        for (int j = 0; j < m_plagiatControl->getNumFilePath(); j++)
        {
                double temp = m_plagiatControl->getSeparateDiff()[i][j];
                m_table->setItem(i, j, new QTableWidgetItem(QString::number(temp, 'f', 3)+"/"+ QString::number((1.0-temp), 'f', 3)));
        }
    }
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
void CFKC_4::clickBrowseFileButtton()
{
    m_QFileDialogTester = new QFileDialogTester();
    QString temp = m_QFileDialogTester->openFile();
    m_plagiatControl->setPath(temp); 
    m_firstPathLineEdit->setText(m_plagiatControl->getAllPathesQString());
    m_firstPathLineEdit->setWordWrap(true);
    m_numFileAdded->setNum(m_plagiatControl->getNumFilePath());
}

void CFKC_4::clickResultButtton()
{
    m_plagiatControl->clickResult();
    m_DifLable->setText(QString::number(m_plagiatControl->getDifference(), 'f', 3) );
    m_SameLable->setText(QString::number(m_plagiatControl->getSimilarity(), 'f', 3));
    displayTable();
   // resize(sizeHint());
}

void CFKC_4::clickResetButtton()
{
    if (m_table)
    {
        m_table->clear();
    }
    m_plagiatControl = new PlagiatControl();
    m_numFileAdded->clear();
    m_SameLable->clear();
    m_DifLable->clear();
    m_firstPathLineEdit->clear();
}