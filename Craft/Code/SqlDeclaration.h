#ifndef SYTELINE_CRAFT_CODE_SQLDECLARATION_H
#define SYTELINE_CRAFT_CODE_SQLDECLARATION_H

#ifndef SYTELINE_CRAFT_CODE_SQLFIELD_H
#include "Craft/Code/SqlField.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLVARIABLE_H
#include "Craft/Code/SqlVariable.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{
    class SYTELINE_LIBRARY_EXPORT CSqlDeclaration : public CSqlField
    {
    protected:
        wstring m_sName;
        wstring m_sReturnType;
        TCollection<wstring, CSqlVariable> m_tParameters;

    public:
        CSqlDeclaration();
        CSqlDeclaration(const CSqlDeclaration& that);
        CSqlDeclaration(const CSqlDeclaration&& that);
        virtual ~CSqlDeclaration();

    public:
        void Name(WSTRING& value);
        wstring Name() const;
        void ReturnType(WSTRING& value);
        wstring ReturnType() const;
        void Parameters(const TCollection<wstring, CSqlVariable>& value);
        TCollection<wstring, CSqlVariable> Parameters() const;
    public:
        void AppendParameter(const CSqlVariable& oParameter);
        TQueried<CSqlVariable> QueryParameter(WSTRING& sName) const;
        wstring ToString(size_t nTabSize = 3);
    public:
        TCollection<wstring, CSqlVariable>& QuoteParameters();

    public:
        virtual const CSqlDeclaration& operator=(const CSqlDeclaration& rvalue);
    };
}}}

#endif