#ifndef SYTELINE_CRAFT_CODE_MSSQLCAPTURER_H
#define SYTELINE_CRAFT_CODE_MSSQLCAPTURER_H

#ifndef SYTELINE_CRAFT_CODE_CAPTURER_H
#include "Craft/Code/Capturer.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLFIE_H
#include "Craft/Code/SqlFile.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLDECLARATION_H
#include "Craft/Code/SqlDeclaration.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLPROCEDURE_H
#include "Craft/Code/SqlProcedure.h"
#endif
#ifndef SYTELINE_CRAFT_CODE_SQLVARIABLE_H
#include "Craft/Code/SqlVariable.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{
    class SYTELINE_LIBRARY_EXPORT CMssqlCapturer : public CCapturer
    {
    protected:
        CSqlFile m_oSqlFile;

    public:
        CMssqlCapturer();
        CMssqlCapturer(const CMssqlCapturer& that);
        virtual ~CMssqlCapturer();

    public:
        virtual void CaptureDeclaration(const CSqlDeclaration& oDeclaration);
        virtual void CaptureProcedure(const TSqlProcedure& oProcedure);
        virtual void CaptureVariable(const CSqlVariable& oVariable);
        virtual TQueried<CSqlVariable> QueryParameter(WSTRING& sName) const;
        virtual TQueried<TSqlProcedure> QueryProcedure(WSTRING& sName) const;

    public:
        const CSqlFile& QuoteSqlFile() const;

    public:
        virtual const CMssqlCapturer& operator=(const CMssqlCapturer& rvalue);
    };
}}}

#endif
