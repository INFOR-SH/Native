#include "../Path.h"
#include "../String.h"

using namespace SyteLine::Craft;

CPath::CPath()
{
}

CPath::CPath(WSTRING& sPath, wchar_t cDivision)
    :m_sPath(sPath)
    ,m_cDivision(cDivision)
{
}

CPath::CPath(WSTRING& sDirectory, WSTRING& sFileName, wchar_t cDivision)
    :m_sPath(sDirectory)
    ,m_cDivision(cDivision)
{
    if(sDirectory[sDirectory.length()-1] != m_cDivision)
    {
        wchar_t wcsDivision[2] = {0};

        wcsDivision[0] = m_cDivision;
        m_sPath.append(wcsDivision);
    }

    m_sPath.append(sFileName);
}

CPath::CPath(const CPath& that)
    :m_sPath(that.m_sPath)
{
}

CPath::CPath(const CPath&& that)
{
    *this = move(that);
}

CPath::~CPath()
{
}

wstring CPath::Path() const
{
    return m_sPath;
}

wstring CPath::FileName() const
{
    auto aString = UString::Split(m_sPath, m_cDivision);

    return aString[aString.size()-1];
}

wstring CPath::Directory() const
{
    wstring sDirectory;

    if(m_cDivision == m_sPath[m_sPath.length()-1])
    {
        return m_sPath;
    }
    else
    {
        auto aString = UString::Split(m_sPath, m_cDivision);

        for(int i = 0; i <aString.size() - 1; i++)
        {
            wchar_t wcsDivision[2] = {0};

            wcsDivision[0] = m_cDivision;
            sDirectory.append(aString[i]);
            sDirectory.append(wcsDivision);
        }

        return move(sDirectory);
    }
}

const CPath& CPath::operator=(const CPath& rvalue)
{
    m_sPath = rvalue.m_sPath;

    return *this;
}