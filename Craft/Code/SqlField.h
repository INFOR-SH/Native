#ifndef SYTELINE_CRAFT_CODE_SQLFIELD_H
#define SYTELINE_CRAFT_CODE_SQLFIELD_H

#ifndef SYTELINE_CRAFT_ECOTOPE_USAGE_H
#include "Craft/Ecotope/Usage.h"
#endif

namespace SyteLine { namespace Craft { namespace Code
{
    class SYTELINE_LIBRARY_EXPORT CSqlField
    {
    protected:
        size_t m_nStartingLine;
        size_t m_nEndingLine;

    public:
        CSqlField();
        CSqlField(const CSqlField& that);
        CSqlField(const CSqlField&& that);
        virtual ~CSqlField();

    public:
        void StartingLine(size_t value);
        size_t StartingLine() const;
        void EndingLine(size_t value);
        size_t EndingLine() const;
    public:
        virtual void Clear();

    public:
        virtual const CSqlField& operator=(const CSqlField& rvalue);
    };
}}}


#endif