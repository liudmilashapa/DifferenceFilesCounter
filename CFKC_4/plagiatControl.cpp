
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


    void PlagiatControl::setIntersection()
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

    void PlagiatControl::setMerge()
    {
        std::set<std::wstring>tempSet;
        for (int i = 0; i < m_filePathes.size() ; i++)
        {
            tempSet = m_allFileSet[i];
            m_mergeSet.merge(tempSet);
        }

    }
    void PlagiatControl::setPath(QString  & _firstPath)
    {
        if (std::find(m_filePathes.begin(), m_filePathes.end(), _firstPath.toStdString()) == m_filePathes.end())
        {
            m_filePathes.push_back(_firstPath.toStdString());
        }
    }

    int PlagiatControl::getNumFilePath()
    {
        return m_filePathes.size();
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
        m_mergeSet.clear();
        m_intersectionSet.clear();

        for (int i = 0; i < m_filePathes.size(); i++)
        {
            std::wifstream fileStream(m_filePathes[i]);
            insertWordsFromFile(fileStream, m_allFileSet);
        }
        setIntersection();
        setMerge();
       
        m_Same = (float)((float)m_intersectionSet.size() / (float)m_mergeSet.size());
        m_Dif = (float)((float)(m_mergeSet.size()- m_intersectionSet.size()) / (float)m_mergeSet.size());

        {

            emit DifChanged(QString::number(m_Dif, 'f', 3));
            emit SameChanged(QString::number(m_Same, 'f', 3));

        }
    }




