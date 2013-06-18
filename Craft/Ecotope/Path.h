#ifndef SYTELINE_CRAFT_ECOTOPE_PATH_H
#define SYTELINE_CRAFT_ECOTOPE_PATH_H

#ifndef SYTELINE_SYSTEM_ECOTOPE_BASE_H
#include "Craft/Ecotope/Base.h"
#endif

namespace SyteLine { namespace Craft
{
    class SYTELINE_LIBRARY_EXPORT CPath
    {
    private:
        wstring m_sPath;
        wchar_t m_cDivision;

    public:
        CPath();
        CPath(WSTRING& sPath, wchar_t cDivision=L'\\');
        CPath(WSTRING& sDirectory, WSTRING& sFileName, wchar_t cDivision=L'\\');
        CPath(const CPath& that);
        CPath(const CPath&& that);

        ~CPath();

    public:
        wstring Path() const;
        wstring FileName() const;
        wstring Directory() const;

    public:
        const CPath& operator=(const CPath& rvalue);
    };
}}

#endif