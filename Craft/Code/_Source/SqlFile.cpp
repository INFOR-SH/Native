#include "../SqlFile.h"
#include "../SqlVariable.h"
#include "../SqlArgument.h"

using namespace SyteLine::Craft;
using namespace SyteLine::Craft::Code;

CSqlFile::CSqlFile()
{
}

CSqlFile::CSqlFile(const CSqlFile& that)
    :m_oDeclaration(that.m_oDeclaration)
    ,m_tProcedures(that.m_tProcedures)
{
}

CSqlFile::CSqlFile(const CSqlFile&& that)
{
    *this = move(that);
}

CSqlFile::~CSqlFile()
{
}

void CSqlFile::Declaration(const CSqlDeclaration& value)
{
    m_oDeclaration = value;
}

CSqlDeclaration CSqlFile::Declaration() const
{
    return m_oDeclaration;
}

void CSqlFile::Procedures(const TCollection<wstring, TSqlProcedure>& value)
{
    m_tProcedures = value;
}

TCollection<wstring, TSqlProcedure> CSqlFile::Procedures() const
{
    return m_tProcedures;
}

void CSqlFile::AppendProcedure(const TSqlProcedure& oProcedure)
{
    wstring sKey = UString::ToLower(oProcedure.ToFullName());

    m_tProcedures.Append(sKey, oProcedure);
}

TQueried<CSqlVariable> CSqlFile::QueryParameter(WSTRING& sName) const
{
    wstring sKey = UString::ToLower(sName);

    return m_oDeclaration.QueryParameter(sKey);
}

TQueried<TSqlProcedure> CSqlFile::QueryProcedure(WSTRING& sName) const
{
    wstring sKey = UString::ToLower(sName);

    return m_tProcedures.Query(TSqlProcedure::MakeFullName(sKey));
}

CSqlDeclaration& CSqlFile::QuoteDeclaration()
{
    return m_oDeclaration;
}

TCollection<wstring, TSqlProcedure>& CSqlFile::QuoteProcedures()
{
    return m_tProcedures;
}

const CSqlFile& CSqlFile::operator=(const CSqlFile& rvalue)
{
    m_oDeclaration = rvalue.m_oDeclaration;
    m_tProcedures = rvalue.m_tProcedures;

    return *this;
}