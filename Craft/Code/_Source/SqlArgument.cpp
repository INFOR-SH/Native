#include "../SqlArgument.h"

using namespace SyteLine::Craft::Code;

CSqlArgument::CSqlArgument()
    :m_bOutput(false)
{
}

CSqlArgument::CSqlArgument(const CSqlArgument& that)
    :CSqlField(that)
    ,m_sLeftValue(that.m_sLeftValue)
    ,m_sRightValue(that.m_sRightValue)
    ,m_bOutput(that.m_bOutput)
{
}

CSqlArgument::CSqlArgument(const CSqlArgument&& that)
{
    *this = move(that);
}

CSqlArgument::~CSqlArgument()
{
}

void CSqlArgument::LeftValue(WSTRING& value)
{
    m_sLeftValue = value;
}

wstring CSqlArgument::LeftValue() const
{
    return m_sLeftValue;
}

void CSqlArgument::RightValue(WSTRING& value)
{
    m_sRightValue = value;
}

wstring CSqlArgument::RightValue() const
{
    return m_sRightValue;
}

void CSqlArgument::Output(bool value)
{
    m_bOutput = value;
}

bool CSqlArgument::Output() const
{
    return m_bOutput;
}

void CSqlArgument::Clear()
{
    CSqlField::Clear();

    m_sLeftValue = S_BLANK;
    m_sRightValue = S_BLANK;
    m_bOutput = false;
}

const CSqlArgument& CSqlArgument::operator=(const CSqlArgument& rvalue)
{
    CSqlField::operator=(rvalue);

    m_sLeftValue = rvalue.m_sLeftValue;
    m_sRightValue = rvalue.m_sRightValue;
    m_bOutput = rvalue.m_bOutput;

    return *this;
}
