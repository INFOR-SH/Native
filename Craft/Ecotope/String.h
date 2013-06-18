#ifndef SYTELINE_CRAFT_ECOTOPE_STRING_H
#define SYTELINE_CRAFT_ECOTOPE_STRING_H

#ifndef SYTELINE_SYSTEM_ECOTOPE_BASE_H
#include "Craft/Ecotope/Base.h"
#endif

namespace SyteLine { namespace Craft
{
    const static wstring S_BLANK = L"";

    struct SYTELINE_LIBRARY_EXPORT UString
    {
        static const size_t N_BUFFER_SIZE = 255;

        inline static wstring ToWideString(MSTRING& sInput, bool bAppended = false);
        inline static wstring TrimLeftBlank(WSTRING& sInput);
        inline static wstring TrimRightBlank(WSTRING& sInput);
        inline static wstring TrimBlank(WSTRING& sInput);
        inline static vector<wstring> Split(WSTRING& sInput, wchar_t cSeparator);
        inline static wstring ToLower(WSTRING& sInput);
        inline static wstring ToUpper(WSTRING& sInput);
    };
}}

#endif
