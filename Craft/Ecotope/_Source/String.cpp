#include "../String.h"

using namespace SyteLine::Craft;

wstring UString::ToWideString(const string& sInput, bool bAppended)
{
    size_t nMbsStringLength = sInput.length();
    wstring sOutput = S_BLANK;

    if(nMbsStringLength > 0)
    {
        size_t Offerset = 0;

        while(Offerset < nMbsStringLength)
        {
            wchar_t wcsBuffer[N_BUFFER_SIZE+1] = {0};

            size_t nConvertedCharacters = mbstowcs(wcsBuffer, sInput.c_str() + Offerset, N_BUFFER_SIZE);

            if(nConvertedCharacters == -1)
            {
                return S_BLANK;
            }

            Offerset += nConvertedCharacters;

            wcsBuffer[nConvertedCharacters] = L'\0';

            sOutput.append(wcsBuffer);
        }
    }

    return sOutput;
}

wstring UString::TrimLeftBlank(WSTRING& sInput)
{
    wstring sResult;
    size_t nLength = sInput.length();

    if(0 != nLength)
    {
        for(size_t i = 0; i < sInput.length(); i++)
        {
            if(sInput[i] != L' ' && sInput[i] != L'\t' && sInput[i] != L'\r' && sInput[i] != L'\n')
            {
                sResult = sInput.substr(i);

                break;
            }
        }
    }

    return move(sResult);
}

wstring UString::TrimRightBlank(WSTRING& sInput)
{
    wstring sResult;
    size_t nLength = sInput.length();

    if(0 != nLength)
    {
        for(size_t i = nLength-1; i >= 0; i--)
        {
            if(sInput[i] != L' ' && sInput[i] != L'\t' && sInput[i] != L'\r' && sInput[i] != L'\n')
            {
                sResult = sInput.substr(0, i+1);

                break;
            }
        }
    }

    return move(sResult);
}

wstring UString::TrimBlank(WSTRING& sInput)
{
    return TrimRightBlank(TrimLeftBlank(sInput));
}

vector<wstring> UString::Split(WSTRING& sInput, wchar_t tSeparator)
{
    wstring sOpertion(sInput);
    vector<wstring> gStrings;
    size_t nIndex;

    while((nIndex = sOpertion.find(tSeparator)) != -1)
    {
        gStrings.push_back(sOpertion.substr(0, nIndex));

        sOpertion = sOpertion.substr(nIndex+1, sOpertion.length());
    }

    if(sOpertion.length() > 0)
    {
        gStrings.push_back(sOpertion);
    }

    return move(gStrings);
}

wstring UString::ToLower(WSTRING& sInput)
{
    wstring sResult = sInput;

    transform(sResult.begin(), sResult.end(), sResult.begin(), tolower);

    return move(sResult);
}

wstring UString::ToUpper(WSTRING& sInput)
{
    wstring sResult = sInput;

    transform(sResult.begin(), sResult.end(), sResult.begin(), toupper);

    return move(sResult);
}