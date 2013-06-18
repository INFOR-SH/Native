#include "../MssqlCapturer.h"

using namespace SyteLine::Craft;
using namespace SyteLine::Craft::Code;

CMssqlCapturer::CMssqlCapturer()
{
}

CMssqlCapturer::CMssqlCapturer(const CMssqlCapturer& that)
    :CCapturer(that)
    ,m_oSqlFile(that.m_oSqlFile)
{
}

CMssqlCapturer::~CMssqlCapturer()
{
}

void CMssqlCapturer::CaptureDeclaration(const CSqlDeclaration& oDeclaration)
{
    m_oSqlFile.Declaration(oDeclaration);
}

void CMssqlCapturer::CaptureVariable(const CSqlVariable& oVariable)
{
}

void CMssqlCapturer::CaptureProcedure(const TSqlProcedure& oProcedure)
{
    m_oSqlFile.AppendProcedure(oProcedure);
}

TQueried<CSqlVariable> CMssqlCapturer::QueryParameter(WSTRING& sName) const
{
    return m_oSqlFile.QueryParameter(sName);
}

TQueried<TSqlProcedure> CMssqlCapturer::QueryProcedure(WSTRING& sName) const
{
    return m_oSqlFile.QueryProcedure(sName);
}

const CSqlFile& CMssqlCapturer::QuoteSqlFile() const
{
    return m_oSqlFile;
}

const CMssqlCapturer& CMssqlCapturer::operator=(const CMssqlCapturer& rvalue)
{
    CCapturer::operator=(rvalue);
    
    m_oSqlFile = rvalue.m_oSqlFile;

    return *this;
}