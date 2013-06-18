// FixFlex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

wstring GetOutputFileName(const wstring& sInputFileName)
{
    size_t nIndex = sInputFileName.find_last_of(L".");
    wstring sInputExt = sInputFileName.substr(nIndex, sInputFileName.length()-nIndex);

    if(sInputExt==L".out")
    {
        wstring sOutputFileFullName(sInputFileName.substr(0, nIndex));

        return sOutputFileFullName.append(L".cpp");
    }
    else
    {
        return L"";
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    if(argc == 2)
    {
        wstring sInputFileFullName(argv[1]);
        wstring sOutputFileFullName = GetOutputFileName(sInputFileFullName);

        if(sOutputFileFullName.size() > 0 )
        {
            wifstream stlInputFileStream(sInputFileFullName);
            wofstream stlOuptuFileStream(sOutputFileFullName, ios::trunc);

            wchar_t wcsBuffer[1024] = {0};
            bool bFound = false;

            while(stlInputFileStream.getline(wcsBuffer, 1024))
            {
                if(wstring(wcsBuffer) == L"class istream;" && bFound == false)
                {
                    wstring sString = L"#include <iostream>\n";

                    sString.append(L"using namespace std;\n");

                    stlOuptuFileStream.write(sString.c_str(), sString.length());

                    bFound = true;
                }
                else
                {
                    stlOuptuFileStream.write(wcsBuffer, wstring(wcsBuffer).length());
                    stlOuptuFileStream.write(L"\n", wstring(L"\n").length());
                }
            }

            stlInputFileStream.close();
            stlOuptuFileStream.close();

            wcout<<L"<FIXED FILE SUCCESSFULLY>: "<<sOutputFileFullName.c_str()<<L" :-)"<<endl;
        }
        else
        {
            wcerr<<L"[INVALID INPUT FILE NAME]:"<<sInputFileFullName.c_str()<<L" :-("<<endl;
        }
    }
    else
    {
        wcerr<<L"[INVALID INPUT ARGUMENTS]"<<L" :-("<<endl;
    }

    return 0;
}

