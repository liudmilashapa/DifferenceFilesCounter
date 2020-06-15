
#include "plagiatControl.h"

    std::wstring PlagiatControl::s2ws(const std::string& str)
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }

    void PlagiatControl::insertWordsFromFile(std::wifstream & fileStream, std::vector<std::set<std::wstring>>& _Set)
    {
        std::set <std::wstring> tempSet;
        std::locale::global(std::locale("ru_RU.UTF-8"));
        fileStream.imbue(std::locale());
        while (!fileStream.eof())
        {
            std::wstring currentLine;
            std::getline(fileStream, currentLine);
            std::wregex word_regex(s2ws("(\\w+)"));
            auto words_begin =
                std::wsregex_iterator(currentLine.begin(), currentLine.end(), word_regex);
            auto words_end = std::wsregex_iterator();
            for (std::wsregex_iterator i = words_begin; i != words_end; ++i) {
                std::wsmatch match = *i;
                std::wstring match_str = match.str();
                tempSet.insert(match_str);
            }    
        }
        _Set.push_back(tempSet);
        fileStream.close();
    }


    void PlagiatControl::setCommonIntersection()
    {
        if (m_allFileSet.size() == 1)
        {
            m_intersectionSet = m_allFileSet[0];
        }
        for (int i = 0; i < m_filePathes.size()-1; i++)
        {
           std::set_intersection(m_allFileSet[i].begin(), m_allFileSet[i].end(), m_allFileSet[i+1].begin(), m_allFileSet[i+1].end(), std::inserter(m_intersectionSet, m_intersectionSet.begin()));
        }
     
    }

    void PlagiatControl::setCommonMerge()
    {
       /* std::set<std::wstring>tempSet;*/
        for (int i = 0; i < m_filePathes.size()-1 ; i++)
        {
            m_mergeSet.merge(getMerge(m_allFileSet[i], m_allFileSet[i+1]));
            //tempSet = m_allFileSet[i];
            //m_mergeSet.merge(tempSet);
        }
    }

    std::set<std::wstring>  PlagiatControl::getIntersection(std::set<std::wstring> & _firstFile, std::set<std::wstring> & _secondFile)
    {
        std::set<std::wstring> resultSet ;
        std::set_intersection(_firstFile.begin(), _firstFile.end(), _secondFile.begin(), _secondFile.end(), std::inserter(resultSet, resultSet.begin()));
        return resultSet;
    }

    void PlagiatControl::setSeparateDiff()
    { 
        std::vector <double> tempVector;
        for (int i = 0; i < m_allFileSet.size(); i++)
        {
           
            for (int j = 0; j < m_allFileSet.size(); j++)
            {      
                tempVector.push_back(getDifference(  getMerge(m_allFileSet[i], m_allFileSet[j]),getIntersection(m_allFileSet[i], m_allFileSet[j])));
            }
            m_differences.push_back(tempVector);
            tempVector.clear();
        }
    }

    double PlagiatControl::getDifference(std::set<std::wstring>& _mergeSet, std::set<std::wstring>& _intersectionSet)
    {
          return (float)((float)(_mergeSet.size() - _intersectionSet.size()) / (float)_mergeSet.size());
    }

    double PlagiatControl::getSimilarity(std::set<std::wstring>& _mergeSet, std::set<std::wstring>& _intersectionSet)
    {
        return (float)((float)_intersectionSet.size() / (float)_mergeSet.size());
    }

    double PlagiatControl::getDifference()
    {
        return m_Dif;
    }

    double PlagiatControl::getSimilarity()
    {
        return m_Same;
    }

    std::set<std::wstring> PlagiatControl::getMerge(std::set<std::wstring>& _firstFile, std::set<std::wstring>& _secondFile)
    {
        std::set<std::wstring> resultSet=_secondFile;
        std::set<std::wstring> tempSet=_firstFile;
        resultSet.merge(tempSet);
        return resultSet;
    }

    void PlagiatControl::setPath(QString  & _firstPath)
    {
        if (std::find(m_filePathes.begin(), m_filePathes.end(), _firstPath.toStdString()) == m_filePathes.end())
        {
            m_filePathes.push_back(_firstPath.toStdString());
        }
    }

    QString PlagiatControl::getAllPathesQString()
    {
        QString temp;
        for (int i = 0; i < m_filePathes.size(); i++)
        {
            temp.append(QString::number(i + 1));
            temp.append(". ");

            temp.append(QString::fromStdString(m_filePathes.at(i)));
            if (i != m_filePathes.size() - 1)
            {
                temp.append("\n");
            }
        }
        return temp;
    }

    int PlagiatControl::getNumFilePath()
    {
        return m_filePathes.size();
    }

    QVector<std::vector<double>>& PlagiatControl::getSeparateDiff()
    {
        return m_differences;
    }

    void PlagiatControl::clickReset()
    {
        m_allFileSet.clear();
        m_filePathes.clear();
        m_mergeSet.clear();
        m_intersectionSet.clear();
        m_Dif = 0;
        m_Same = 0;
        emit changeFileNum(m_filePathes.size());
        emit DifChanged(QString::number(0, 'f', 3));
        emit SameChanged(QString::number(0, 'f', 3));
    }


    void PlagiatControl::clickResult()
    {
        m_Dif = 0;
        m_Same = 0;
        m_NormalA = 0;
        m_NormalB = 0;
        m_allFileSet.clear();
        m_differences.clear();
        m_mergeSet.clear();
        m_intersectionSet.clear();

        for (int i = 0; i < m_filePathes.size(); i++)
        {
            std::wifstream fileStream(m_filePathes[i]);
            insertWordsFromFile(fileStream, m_allFileSet);
        }
        setCommonIntersection();
        setCommonMerge();
        m_Dif = getDifference(m_mergeSet, m_intersectionSet);
        m_Same = getSimilarity(m_mergeSet, m_intersectionSet);   
        setSeparateDiff();
    }




