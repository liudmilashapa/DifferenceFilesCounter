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
    QVector<std::vector<double>> m_differences;
    
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
    
    void setCommonIntersection();
    void setCommonMerge();
    
    std::set<std::wstring>  getIntersection(std::set<std::wstring>& _firstFile, std::set<std::wstring>& _secondFile);
    std::set<std::wstring>  getMerge(std::set<std::wstring>& _firstFile, std::set<std::wstring>& _secondFile);

    void setSeparateDiff();

    double getDifference(std::set<std::wstring>& _mergeSet, std::set<std::wstring>& _intersectionSet);
    double getSimilarity(std::set<std::wstring>& _mergeSet, std::set<std::wstring>& _intersectionSet);

    double getDifference();
    double getSimilarity();


    void setPath(QString & _firstPath);

    int getNumFilePath();
    QString getAllPathesQString();

    QVector<std::vector<double>>& getSeparateDiff();

    void clickResult();
    void clickReset();

public slots:



signals:

    void DifChanged(const QString&);
    void SameChanged(const QString&);
    void NormalAChanged(const QString&);
    void NormalBChanged(const QString&);
    void changeFileNum(int);

};

