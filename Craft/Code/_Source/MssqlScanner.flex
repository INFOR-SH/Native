%{
#include "../MssqlScanner.h"

using namespace std;
using namespace SyteLine::Craft;
using namespace SyteLine::Craft::Code;
%}

%option c++
%option prefix = "CMssqlScanner"
%option debug
%option noyywrap
%option yylineno
%option outfile = "MssqlScanner.flex.out"
%option case-insensitive

%x M_COMMENT1
%x M_COMMENT2
%x M_PROCEDURE_DECLARATION
%x M_PROCEDURE_DECLARATION_END
%x M_FUNCTION_DECLARATION
%x M_FUNCTION_DECLARATION_END

%x M_DECLARE_VARIABLES
%x M_PROCEDURE
%x M_ARGUMENTS

RKeyword        "ADD"|"EXISTS"|"PRECISION"|"ALL"|"EXIT"|"PRIMARY"|"ALTER"|"EXTERNAL"|"PRINT"|"AND"|"FETCH"|"PROC"|"ANY"|"FILE"|"PROCEDURE"|"AS"|"FILLFACTOR"|"PUBLIC"|"ASC"|"FOR"|"RAISERROR"|"AUTHORIZATION"|"FOREIGN"|"READ"|"BACKUP"|"FREETEXT"|"READTEXT"|"BEGIN"|"FREETEXTTABLE"|"RECONFIGURE"|"BETWEEN"|"FROM"|"REFERENCES"|"BREAK"|"FULL"|"REPLICATION"|"BROWSE"|"FUNCTION"|"RESTORE"|"BULK"|"GOTO"|"RESTRICT"|"BY"|"GRANT"|"RETURN"|"CASCADE"|"GROUP"|"REVERT"|"CASE"|"HAVING"|"REVOKE"|"CHECK"|"HOLDLOCK"|"RIGHT"|"CHECKPOINT"|"IDENTITY"|"ROLLBACK"|"CLOSE"|"IDENTITY_INSERT"|"ROWCOUNT"|"CLUSTERED"|"IDENTITYCOL"|"ROWGUIDCOL"|"COALESCE"|"IF"|"RULE"|"COLLATE"|"IN"|"SAVE"|"COLUMN"|"INDEX"|"SCHEMA"|"COMMIT"|"INNER"|"SECURITYAUDIT"|"COMPUTE"|"INSERT"|"SELECT"|"CONSTRAINT"|"INTERSECT"|"SESSION_USER"|"CONTAINS"|"INTO"|"SET"|"CONTAINSTABLE"|"IS"|"SETUSER"|"CONTINUE"|"JOIN"|"SHUTDOWN"|"CONVERT"|"KEY"|"SOME"|"CREATE"|"KILL"|"STATISTICS"|"CROSS"|"LEFT"|"SYSTEM_USER"|"CURRENT"|"LIKE"|"TABLE"|"CURRENT_DATE"|"LINENO"|"TABLESAMPLE"|"CURRENT_TIME"|"LOAD"|"TEXTSIZE"|"CURRENT_TIMESTAMP"|"MERGE"|"THEN"|"CURRENT_USER"|"NATIONAL"|"TO"|"CURSOR"|"NOCHECK"|"TOP"|"DATABASE"|"NONCLUSTERED"|"TRAN"|"DBCC"|"NOT"|"TRANSACTION"|"DEALLOCATE"|"NULL"|"TRIGGER"|"DECLARE"|"NULLIF"|"TRUNCATE"|"DEFAULT"|"OF"|"TSEQUAL"|"DELETE"|"OFF"|"UNION"|"DENY"|"OFFSETS"|"UNIQUE"|"DESC"|"ON"|"UNPIVOT"|"DISK"|"OPEN"|"UPDATE"|"DISTINCT"|"OPENDATASOURCE"|"UPDATETEXT"|"DISTRIBUTED"|"OPENQUERY"|"USE"|"DOUBLE"|"OPENROWSET"|"USER"|"DROP"|"OPENXML"|"VALUES"|"DUMP"|"OPTION"|"VARYING"|"ELSE"|"OR"|"VIEW"|"END"|"ORDER"|"WAITFOR"|"ERRLVL"|"OUTER"|"WHEN"|"ESCAPE"|"OVER"|"WHERE"|"EXCEPT"|"PERCENT"|"WHILE"|"EXEC"|"PIVOT"|"WITH"|"EXECUTE"|"PLAN"|"WRITETEXT"
RString         "N"?\'{1}.*\'{1}
RInteger        [0-9]+
RDigit          [0-9\.]+
RKeywordBlank   [ \t\r\n]+
ROperatorBlank      [ \t\r\n]*
RMethodName     ([_a-zA-Z\[-\]]+"."{1}[_a-zA-Z0-9\[-\]]+)|[_a-zA-Z0-9\[-\]]+
RVariableName   "@"[_a-zA-Z0-9]+
RVariableType   [_a-zA-z0-9]+
RVariableSubtype [0-9\,]+
RVariableValue  "NULL"|"@"[_a-zA-Z0-9]+|"N"?\'{1}.*\'{1}|[0-9\.]+
%%

<M_COMMENT1>"*/" {
    m_nEndingCommentLine = yylineno;

    BEGIN m_nLastStatus;
}

<M_COMMENT2>\n {
    m_nEndingCommentLine = yylineno;

    BEGIN m_nLastStatus;
}

"CREATE"{RKeywordBlank}"PROCEDURE" {
    m_oDeclaration.StartingLine(yylineno);
    m_eStage = E_STAGE_PRCEDURE_DECLARATION;

    BEGIN M_PROCEDURE_DECLARATION;
}

<M_PROCEDURE_DECLARATION>"/*" {
    m_nLastStatus = M_PROCEDURE_DECLARATION;
    m_nStartingCommentLine = yylineno;

    BEGIN M_COMMENT1;
}

<M_PROCEDURE_DECLARATION>"--" {
    m_nLastStatus = M_PROCEDURE_DECLARATION;
    m_nStartingCommentLine = yylineno;

    BEGIN M_COMMENT2;
}

<M_PROCEDURE_DECLARATION>{RMethodName} {
    m_oDeclaration.Name(UString::ToWideString(yytext));
}

<M_PROCEDURE_DECLARATION>"(" {
    BEGIN M_DECLARE_VARIABLES;
}

<M_PROCEDURE_DECLARATION>. {
    ;
}

<M_PROCEDURE_DECLARATION_END>"AS" {
    m_oDeclaration.AppendParameter(m_oVariable);
    m_oDeclaration.EndingLine(yylineno);

    m_oVariable.Clear();

    pCapturer->CaptureDeclaration(m_oDeclaration);
    
    m_eStage = E_STAGE_BODY;

    BEGIN INITIAL;
}

<M_DECLARE_VARIABLES>"/*" {
    m_nLastStatus = M_DECLARE_VARIABLES;
    m_nStartingCommentLine = yylineno;

    BEGIN M_COMMENT1;
}

<M_DECLARE_VARIABLES>"--" {
    m_nLastStatus = M_DECLARE_VARIABLES;
    m_nStartingCommentLine = yylineno;

    BEGIN M_COMMENT2;
}

<M_DECLARE_VARIABLES>{RVariableName} {
    m_oVariable.StartingLine(yylineno);
    m_oVariable.Name(UString::ToWideString(yytext));
    m_oVariable.EndingLine(yylineno);
}

<M_DECLARE_VARIABLES>{RVariableType}|({RVariableType}{ROperatorBlank}"("{ROperatorBlank}{RVariableSubtype}{ROperatorBlank}")") {
    wstring sType;
    vector<wstring> gStrings = UString::Split(UString::ToWideString(yytext), L'(');

    if(gStrings.size() == 1)
    {
        sType = UString::ToWideString(yytext);
    }
    else
    {
        sType = UString::TrimBlank(gStrings[0]);
        
        sType.append(L"(");
        sType.append(UString::TrimBlank(gStrings[1].substr(0, gStrings[1].length()-1)));
        sType.append(L")");
    }

    m_oVariable.Type(sType);
    m_oVariable.EndingLine(yylineno);
}

<M_DECLARE_VARIABLES>"="{ROperatorBlank}{RVariableValue} {
    wstring sValue(UString::ToWideString(yytext));
    
    sValue = sValue.substr(1);
    m_oVariable.Value(UString::TrimBlank(sValue));
    m_oVariable.EndingLine(yylineno);
}

<M_DECLARE_VARIABLES>{RKeywordBlank}"OUTPUT" {
    m_oVariable.Output(true);
    m_oVariable.EndingLine(yylineno);
}

<M_DECLARE_VARIABLES>"," {
    m_oDeclaration.AppendParameter(m_oVariable);
    m_oVariable.Clear();
}

<M_DECLARE_VARIABLES>{ROperatorBlank}")" {
    if(E_STAGE_PRCEDURE_DECLARATION == m_eStage)
    {
        BEGIN M_PROCEDURE_DECLARATION_END;
    }
    else
    {
        BEGIN M_FUNCTION_DECLARATION_END;
    }
}

<M_DECLARE_VARIABLES>. {
    ;
}

"EXEC" {
    m_oProcedure.StartingLine(yylineno);

    BEGIN M_PROCEDURE;
}

<M_PROCEDURE>({RMethodName})|({RVariableName})|({RVariableName}{ROperatorBlank}"="{1}{ROperatorBlank}({RVariableName}|{RString})) {
    vector<wstring> gStrings = UString::Split(UString::ToWideString(yytext), L'=');
    wstring sRawName;

    if(gStrings.size() == 1)
    {
        sRawName = UString::TrimBlank(UString::ToWideString(yytext));
    }
    else
    {
        sRawName = UString::TrimBlank(gStrings[1]);
        m_oProcedure.ReturnVariableName(UString::TrimBlank(gStrings[0]));
    }

    int nIndex = sRawName.find(L".");

    if(nIndex == -1)
    {
        m_oProcedure.Name(sRawName);
    }
    else
    {
        m_oProcedure.Owner(UString::TrimBlank(sRawName.substr(0, nIndex)));
        m_oProcedure.Name(UString::TrimBlank(sRawName.substr(nIndex+1)));
    }

    BEGIN M_ARGUMENTS;
}

<M_ARGUMENTS>"/*" {
    m_nLastStatus = M_ARGUMENTS;
    m_nStartingCommentLine = yylineno;

    BEGIN M_COMMENT1;
}

<M_ARGUMENTS>"--" {
    m_nLastStatus = M_ARGUMENTS;
    m_nStartingCommentLine = yylineno;

    BEGIN M_COMMENT2;
}

<M_ARGUMENTS>{RVariableValue}|({RVariableName}{ROperatorBlank}"="{1}{ROperatorBlank}{RVariableValue}) {
    m_oArgument.StartingLine(yylineno);
    m_oArgument.EndingLine(yylineno);

    vector<wstring> gStrings = UString::Split(UString::ToWideString(yytext), L'=');

    if(gStrings.size() == 1)
    {
        m_oArgument.RightValue(UString::TrimBlank(gStrings[0]));
    }
    else
    {
        m_oArgument.LeftValue(UString::TrimBlank(gStrings[0]));
        m_oArgument.RightValue(UString::TrimBlank(gStrings[1]));
    }
}

<M_ARGUMENTS>"," {
    m_oProcedure.AppendArgument(m_oArgument);
    m_oProcedure.EndingLine(yylineno);
    m_oArgument.Clear();
}

<M_ARGUMENTS>"OUTPUT" {
    m_oArgument.EndingLine(yylineno);
    m_oArgument.Output(true);
}

<M_ARGUMENTS>{RKeywordBlank}/{RKeyword} {
    m_oProcedure.AppendArgument(m_oArgument);
    
    if(m_nStartingCommentLine >= m_oArgument.EndingLine())
    {
        m_oProcedure.EndingLine(m_oArgument.EndingLine());
    }
    else
    {
        m_oProcedure.EndingLine(yylineno);
    }

    pCapturer->CaptureProcedure(m_oProcedure);

    m_oArgument.Clear();
    m_oProcedure.Clear();

    BEGIN INITIAL;
}

<M_ARGUMENTS>. {
    ;
}

.|\n {
    ;
}
%%

namespace SyteLine { namespace Craft { namespace Code
{
    CMssqlScanner::CMssqlScanner(istream* pInStream, ostream* pOutStream)
        :CMssqlScannerFlexLexer(pInStream, pOutStream)
        ,m_nStartingCommentLine(0)
        ,m_nEndingCommentLine(0)
    {
    }

    CMssqlScanner::~CMssqlScanner()
    {
    }
}}}

#ifdef yylex
#undef yylex
#endif

int CMssqlScannerFlexLexer::yylex()
{
    std::cerr << "in CMssqlScannerFlexLexer::yylex() !" << std::endl;
    return 0;
}

