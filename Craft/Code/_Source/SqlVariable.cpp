#include "../SqlVariable.h"

using namespace SyteLine::Craft::Code;

CSqlVariable::CSqlVariable()
    :m_bOutput(false)
{
}

CSqlVariable::CSqlVariable(const CSqlVariable& that)
    :CSqlField(that)
    ,m_sName(that.m_sName)
    ,m_sType(that.m_sType)
    ,m_sValue(that.m_sValue)
    ,m_bOutput(that.m_bOutput)
{
}

CSqlVariable::CSqlVariable(const CSqlVariable&& that)
{
    *this = move(that);
}

CSqlVariable::~CSqlVariable()
{
}

void CSqlVariable::Name(WSTRING& value)
{
    m_sName = value;
}

wstring CSqlVariable::Name() const
{
    return m_sName;
}

void CSqlVariable::Type(WSTRING& value)
{
    m_sType = value;
}

wstring CSqlVariable::Type() const
{
    return m_sType;
}

void CSqlVariable::Value(WSTRING& value)
{
    m_sValue = value;
}

wstring CSqlVariable::Value() const
{
    return  m_sValue;
}

void CSqlVariable::Output(bool value)
{
    m_bOutput = value;
}

bool CSqlVariable::Output() const
{
    return m_bOutput;
}

void CSqlVariable::Clear()
{
    CSqlField::Clear();

    m_sName = S_BLANK;
    m_sType = S_BLANK;
    m_sValue = S_BLANK;
    m_bOutput = false;
}

const CSqlVariable& CSqlVariable::operator=(const CSqlVariable& rvalue)
{
    CSqlField::operator=(rvalue);

    m_sName = rvalue.m_sName;
    m_sType = rvalue.m_sType;
    m_sValue = rvalue.m_sValue;
    m_bOutput = rvalue.m_bOutput;

    return *this;
}
