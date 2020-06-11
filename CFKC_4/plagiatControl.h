#pragma once
#include <QObject>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <clocale>
#include <algorithm>
#include <regex>
#include <codecvt>
#include <locale>
#include < Windows.h >
#include <QString>



class PlagiatControl : public QObject {
    Q_OBJECT

private:

    std::vector<std::set<std::wstring>> m_allFileSet;

    std::set<std::wstring> m_mergeSet;
    std::set<std::wstring> m_intersectionSet;

    std::vector <std::string>  m_filePathes;

    double  m_Dif;
    double  m_Same;
    double  m_NormalA;
    double  m_NormalB;
    
public:

    PlagiatControl()
    {}

    std::wstring s2ws(const std::string& str);

    void insertWordsFromFile(std::wifstream& fileStream, std::vector<std::set<std::wstring>>& _Set);
    void setIntersection();
    void setMerge();

    void setPath(QString & _firstPath);

    int getNumFilePath();

public slots:

    void clickResult();
    void clickReset();


signals:

    void DifChanged(const QString&);
    void SameChanged(const QString&);
    void NormalAChanged(const QString&);
    void NormalBChanged(const QString&);
    void changeFileNum(int);

};

