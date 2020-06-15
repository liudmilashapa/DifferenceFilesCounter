#include "CFKC_4.h"
#include <QtWidgets>
#include <qstring.h>
#include <QWidget>
#include "plagiatControl.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CFKC_4* window = new CFKC_4();
    window->setWindowTitle("Find similarities and differences in text object");
    window->setAutoFillBackground(false);
    QWidget * newW =  new QWidget(window);
  //  newW->resize(minimumSizeHint());
  newW->resize(150,200);


    QObject::connect(window->m_resultButtton, SIGNAL(clicked()),
        window, SLOT(clickResultButtton())
    );
    QObject::connect(window->m_resetButtton, SIGNAL(clicked()),
        window, SLOT(clickResetButtton())
    );
    QObject::connect(window->m_browseFirstFileButtton, SIGNAL(clicked()),
        window, SLOT(clickBrowseFileButtton())
    );

    QObject::connect(window->m_plagiatControl, SIGNAL(changeFileNum(int)),
        window->m_numFileAdded, SLOT(setNum(int))
    ); 
    QObject::connect(window->m_plagiatControl, SIGNAL(DifChanged(const QString &)),
        window->m_DifLable, SLOT(setText(const QString &))
    );
    QObject::connect(window->m_plagiatControl, SIGNAL(SameChanged(const QString &)),
        window->m_SameLable, SLOT(setText(const QString &))
    );
  /*  QObject::connect(window->m_resultButtton, SIGNAL(clicked()),
        &plagiatControl, SLOT(clickResult1())
    );*/

    //QObject::connect(window->m_resultButtton, SIGNAL(clicked()),
    //    window, SLOT(clickResult())
    //);
    //QObject::connect(window->m_browseSecondFileButtton, SIGNAL(clicked()),
    //    window, SLOT(clickBrowseSecondFileButtton())
    //);


    //QObject::connect(window->m_plagiatControl, SIGNAL(NormalAChanged(const QString&)),
    //    window->m_NormalA, SLOT(setText(const QString &))
    //);
    //QObject::connect(window->m_plagiatControl, SIGNAL(NormalBChanged(const QString&)),
    //    window->m_NormalB, SLOT(setText(const QString &))
    //);

    //QObject::connect(/* */, SIGNAL(plagiatChanged(int)),
    //    window->m_plagiat, SLOT(setNum(int))
    //);


    window->show();
    newW->show();
    return app.exec();
}

