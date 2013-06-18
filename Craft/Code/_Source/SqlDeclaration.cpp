#include "../SqlDeclaration.h"

using namespace SyteLine::Craft;
using namespace SyteLine::Craft::Code;

CSqlDeclaration::CSqlDeclaration()
{
}

CSqlDeclaration::CSqlDeclaration(const CSqlDeclaration& that)
    :CSqlField(that)
    ,m_sName(that.m_sName)
    ,m_sReturnType(that.m_sReturnType)
    ,m_tParameters(that.m_tParameters)
{
}

CSqlDeclaration::CSqlDeclaration(const CSqlDeclaration&& that)
{
    *this = move(that);
}

CSqlDeclaration::~CSqlDeclaration()
{
}

void CSqlDeclaration::Name(WSTRING& value)
{
    m_sName = value;
}

wstring CSqlDeclaration::Name() const
{
    return m_sName;
}

void CSqlDeclaration::ReturnType(WSTRING& value)
{
    m_sReturnType = value;
}

wstring CSqlDeclaration::ReturnType() const
{
    return m_sReturnType;
}

void CSqlDeclaration::Parameters(const TCollection<wstring, CSqlVariable>& value)
{
    m_tParameters = value;
}

TCollection<wstring, CSqlVariable> CSqlDeclaration::Parameters() const
{
    return m_tParameters;
}

void CSqlDeclaration::AppendParameter(const CSqlVariable& oParameter)
{
    m_tParameters.Append(UString::ToLower(oParameter.Name()), oParameter);
}

TQueried<CSqlVariable>  CSqlDeclaration::QueryParameter(WSTRING& sName) const
{
    return m_tParameters.Query(UString::ToLower(sName));
}

wstring CSqlDeclaration::ToString(size_t nTabSize)
{
    return L"";
}

TCollection<wstring, CSqlVariable>& CSqlDeclaration::QuoteParameters()
{
    return m_tParameters;
}

const CSqlDeclaration& CSqlDeclaration::operator=(const CSqlDeclaration& rvalue)
{
    CSqlField::operator=(rvalue);

    m_sName = rvalue.m_sName;
    m_sReturnType = rvalue.m_sReturnType;
    m_tParameters = rvalue.m_tParameters;

    return *this;
}