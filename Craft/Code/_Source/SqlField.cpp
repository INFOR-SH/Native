#include "../SqlField.h"

using namespace SyteLine::Craft::Code;

CSqlField::CSqlField()
    :m_nStartingLine(0)
    ,m_nEndingLine(0)
{
}

CSqlField::CSqlField(const CSqlField& that)
    :m_nStartingLine(that.m_nStartingLine)
    ,m_nEndingLine(that.m_nEndingLine)
{
}

CSqlField::CSqlField(const CSqlField&& that)
{
    *this = move(that);
}

CSqlField::~CSqlField()
{
}

void CSqlField::StartingLine(size_t value)
{
    m_nStartingLine = value;
}

size_t CSqlField::StartingLine() const
{
    return m_nStartingLine;
}

void CSqlField::EndingLine(size_t value)
{
    m_nEndingLine = value;
}


size_t CSqlField::EndingLine() const
{
    return m_nEndingLine;
}

void CSqlField::Clear()
{
    m_nStartingLine = 0;
    m_nEndingLine = 0;
}

const CSqlField& CSqlField::operator=(const CSqlField& rvalue)
{
    m_nStartingLine = rvalue.m_nStartingLine;
    m_nEndingLine = rvalue.m_nEndingLine;

    return *this;
}
