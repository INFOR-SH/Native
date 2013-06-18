#ifndef SYTELINE_CRAFT_CODE_SQLFIE_H
#define SYTELINE_CRAFT_CODE_SQLFIE_H

#ifndef SYTELINE_CRAFT_CODE_SQLDECLARATION_H
#include "Craft/Code/SqlDeclaration.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLPROCEDURE_H
#include "Craft/Code/SqlProcedure.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{
    class SYTELINE_LIBRARY_EXPORT CSqlFile
    {
    protected:
        CSqlDeclaration m_oDeclaration;
        TCollection<wstring, TSqlProcedure> m_tProcedures;

    public:
        CSqlFile();
        CSqlFile(const CSqlFile& that);
        CSqlFile(const CSqlFile&& that);
        virtual ~CSqlFile();

    public:
        void Declaration(const CSqlDeclaration& value);
        CSqlDeclaration Declaration() const;
        void Procedures(const TCollection<wstring, TSqlProcedure>& value);
        TCollection<wstring, TSqlProcedure> Procedures() const;
    public:
        void AppendProcedure(const TSqlProcedure& oProcedure); 
        TQueried<CSqlVariable> QueryParameter(WSTRING& sName) const;
        TQueried<TSqlProcedure> QueryProcedure(WSTRING& sName) const;
    public:
        CSqlDeclaration& QuoteDeclaration();
        TCollection<wstring, TSqlProcedure>& QuoteProcedures();

    public:
        const CSqlFile& operator=(const CSqlFile& rvalue);
        
    };
}}}

#endif
