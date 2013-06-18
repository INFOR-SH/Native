#ifndef SYTELINE_CRAFT_CODE_SQLARGUMENT_H
#define SYTELINE_CRAFT_CODE_SQLARGUMENT_H

#ifndef SYTELINE_CRAFT_CODE_SQLFIELD_H
#include "Craft/Code/SqlField.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{ 
    class SYTELINE_LIBRARY_EXPORT CSqlArgument : public CSqlField
    {
    protected:
        wstring m_sLeftValue;
        wstring m_sRightValue;
        bool m_bOutput;

    public:
        CSqlArgument();
        CSqlArgument(const CSqlArgument& that);
        CSqlArgument(const CSqlArgument&& that);
        virtual ~CSqlArgument();

    public:
        void LeftValue(WSTRING& value);
        wstring LeftValue() const;
        void RightValue(WSTRING& value);
        wstring RightValue() const;
        void Output(bool value);
        bool Output() const;

    public:
        virtual void Clear();

    public:
        const CSqlArgument& operator=(const CSqlArgument& rvalue);
    };
}}}

#endif