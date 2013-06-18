#include "../Capturer.h"

using namespace SyteLine::Craft::Code;

CCapturer::CCapturer()
    :m_nCharacters(0)
    ,m_nLines(0)
{
}

void CCapturer::IncreaseCharacters(size_t nAmount)
{
    m_nCharacters += nAmount;
}

void CCapturer::IncreaseLines(size_t nAmount)
{
    m_nLines += nAmount;
}

const CCapturer& CCapturer::operator=(const CCapturer& rvalue)
{
    m_nCharacters = rvalue.m_nCharacters;
    m_nLines = rvalue.m_nLines;

    return *this;
}