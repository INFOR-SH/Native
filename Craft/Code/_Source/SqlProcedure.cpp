#include "../SqlProcedure.h"

using namespace SyteLine::Craft;
using namespace SyteLine::Craft::Code;

wstring TSqlProcedure::MakeFullName(WSTRING& sRawName, WSTRING& sRawOwner)
{
    wstring sName;
    wstring sOwner;
    wstring sFullName;

    if(L'@' == sRawName[0] || L'[' == sRawName[0])
    {
        sName = sRawName;
    }
    else
    {
        sName.append(L"[");
        sName.append(sRawName);
        sName.append(L"]");
    }

    if(S_BLANK == sRawOwner)
    {
        sOwner = L"[dbo]";
    }
    else if(L'[' == sRawName[0])
    {
        sOwner = sRawName;
    }
    else
    {
        sOwner.append(L"[");
        sOwner.append(sRawName);
        sOwner.append(L"]");
    }

    if(L'@' == sRawName[0])
    {
        sFullName = sName;
    }
    else
    {
        sFullName = sOwner + L"." + sName;
    }

    return move(sFullName);
}

TSqlProcedure::TSqlProcedure()
    :m_sOwner(L"dbo")
{
}

TSqlProcedure::TSqlProcedure(const TSqlProcedure& that)
    :CSqlField(that)
    ,m_sOwner(that.m_sOwner)
    ,m_sName(that.m_sName)
    ,m_sReturnVariableName(that.m_sReturnVariableName)
    ,m_tArguments(that.m_tArguments)
{
}

TSqlProcedure::TSqlProcedure(const TSqlProcedure&& that)
{
    *this = move(that);
}

TSqlProcedure::~TSqlProcedure()
{
}

void TSqlProcedure::Owner(WSTRING& value)
{
    if(L'[' == value[0])
    {
        m_sOwner = value.substr(1);

        if(L']' == m_sOwner[m_sOwner.length()-1])
        {
            m_sOwner = m_sOwner.substr(0, m_sOwner.length()-1);
        }
    }
    else
    {
        m_sOwner = value;
    }
}

wstring TSqlProcedure::Owner()
{
    return m_sOwner;
}

void TSqlProcedure::Name(WSTRING& value)
{
    if(L'[' == value[0])
    {
        m_sName = value.substr(1);

        if(L']' == m_sName[m_sName.length()-1])
        {
            m_sName = m_sName.substr(0, m_sName.length()-1);
        }
    }
    else
    {
        m_sName = value;
    }
}

wstring TSqlProcedure::Name() const
{
    return m_sName;
}

void TSqlProcedure::ReturnVariableName(WSTRING& value)
{
    m_sReturnVariableName = value;
}

wstring TSqlProcedure::ReturnVariableName() const
{
   return m_sReturnVariableName;
}

void TSqlProcedure::AppendArgument(const CSqlArgument& oArgument)
{
    wstring sKey = UString::ToLower(oArgument.RightValue());

    m_tArguments.Append(sKey, oArgument);
}

TQueried<CSqlArgument> TSqlProcedure::QueryArgument(WSTRING& sName) const
{
    wstring sKey = UString::ToLower(sName);

    return m_tArguments.Query(sKey);
}

void TSqlProcedure::Clear()
{
    CSqlField::Clear();
    m_sOwner = L"dbo";
    m_sName = S_BLANK;
    m_sReturnVariableName = S_BLANK;
    m_tArguments.Clear();
}

wstring TSqlProcedure::ToFullName() const
{
    wstring sFullName;

    if(m_sName.length() > 0 && m_sOwner.length() > 0)
    {
        if(m_sName[0] != L'@')
        {
            sFullName.append(L"[");
            sFullName.append(m_sOwner);
            sFullName.append(L"].[");
            sFullName.append(m_sName);
            sFullName.append(L"]");
        }
        else
        {
            sFullName = m_sName; 
        }
    }

    return move(sFullName);
}

TCollection<wstring, CSqlArgument>& TSqlProcedure::QuoteArguments()
 {
     return m_tArguments;
 }

 const TSqlProcedure& TSqlProcedure::operator=(const TSqlProcedure& rvalue)
{
    CSqlField::operator=(rvalue);

    m_sOwner = rvalue.m_sOwner;
    m_sName = rvalue.m_sName;
    m_sReturnVariableName = rvalue.m_sReturnVariableName;
    m_tArguments = rvalue.m_tArguments;

    return *this;
}