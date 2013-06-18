#ifndef SYTELINE_CRAFT_CODE_SQLPROCEDURE_H
#define SYTELINE_CRAFT_CODE_SQLPROCEDURE_H

#ifndef SYTELINE_CRAFT_CODE_SQLFIELD_H
#include "Craft/Code/SqlField.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLARGUMENT_H
#include "Craft/Code/SqlArgument.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{
    class SYTELINE_LIBRARY_EXPORT TSqlProcedure : public CSqlField
    {
    protected:
        //Owner and name have not '[' and ']'
        wstring m_sOwner;
        wstring m_sName;
        wstring m_sReturnVariableName;
        TCollection<wstring, CSqlArgument> m_tArguments;

    public:
        static wstring MakeFullName(WSTRING& sName, WSTRING& sOwner=S_BLANK);

    public:
        TSqlProcedure();
        TSqlProcedure(const TSqlProcedure& that);
        TSqlProcedure(const TSqlProcedure&& that);
        virtual ~TSqlProcedure();

    public:
        void Owner(WSTRING& value);
        wstring Owner();
        void Name(WSTRING& value);
        wstring Name() const;
        void ReturnVariableName(WSTRING& value);
        wstring ReturnVariableName() const;

    public:
        virtual void AppendArgument(const CSqlArgument& oArgument);
        virtual TQueried<CSqlArgument> QueryArgument(WSTRING& sName) const;
    public:
        virtual void Clear();
        virtual wstring ToFullName() const;

    public:
        TCollection<wstring, CSqlArgument>& QuoteArguments();

    public:
        virtual const TSqlProcedure& operator=(const TSqlProcedure& rvalue);
    };
}}}

#endif
