#ifndef SYTELINE_CRAFT_CODE_SQLVARIABLE_H
#define SYTELINE_CRAFT_CODE_SQLVARIABLE_H

#ifndef SYTELINE_CRAFT_CODE_SQLFIELD_H
#include "Craft/Code/SqlField.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{ 
    class SYTELINE_LIBRARY_EXPORT CSqlVariable : public CSqlField
    {
    protected:
        wstring m_sName;
        wstring m_sType;
        wstring m_sValue;
        bool m_bOutput;

    public:
        CSqlVariable();
        CSqlVariable(const CSqlVariable& that);
        CSqlVariable(const CSqlVariable&& that);
        virtual ~CSqlVariable();

    public:
        void Name(WSTRING& value);
        wstring Name() const;
        void Type(WSTRING& value);
        wstring Type() const;
        void Value(WSTRING& value);
        wstring Value() const;
        void Output(bool value);
        bool Output() const;
    public:
        virtual void Clear();

    public:
        virtual const CSqlVariable& operator=(const CSqlVariable& rvalue);
    };
}}}

#endif
