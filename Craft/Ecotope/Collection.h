#ifndef SYTELINE_CRAFT_ECOTOPE_COLLECTION_H
#define SYTELINE_CRAFT_ECOTOPE_COLLECTION_H

#ifndef SYTELINE_SYSTEM_ECOTOPE_BASE_H
#include "Craft/Ecotope/Base.h"
#endif

namespace SyteLine { namespace Craft
{
    template<typename TClass>
    class SYTELINE_LIBRARY_EXPORT TQueried
    {
    protected:
        vector<TClass> m_tArray;

    public:
        TQueried()
        {
        }

        TQueried(const TQueried& that)
            :m_tArray(that.m_tArray)
        {
        }

        TQueried(const TQueried&& that)
        {
            *this = move(that);
        }

        virtual ~TQueried()
        {
        }

    public:
        vector<TClass> Array() const
        {
            return m_tArray;
        }

    public:
        bool Empty() const
        {
            return m_tArray.empty();
        }

        size_t Size() const
        {
            return m_tArray.size();
        }

        void Clear()
        {
            m_tArray.clear();
        }

        void Append(const TClass& tRecord)
        {
            m_tArray.push_back(tRecord);
        }

        TClass First() const
        {
            return m_tArray[0];
        }

        TClass Last() const
        {
            return m_tArray[m_tArray.size()-1];
        }

        TClass Get(size_t nIndex) const
        {
            return m_tArray[nIndex];
        }

    public:
        virtual const TQueried& operator=(const TQueried& rvalue)
        {
            m_tArray = rvalue.m_tArray;

            return *this;
        }

        virtual TClass operator[](size_t nIndex)
        {
            return Get(nIndex);
        }
    };

    template<typename TKey, typename TClass>
    class SYTELINE_LIBRARY_EXPORT TCollection
    {
    protected:
        vector<TClass> m_tCollection;
        map<TKey, size_t> m_tMapping;
        map<TKey, vector<size_t>> m_tCollision;

    public:
        TCollection()
        {
        }

        TCollection(const TCollection& that)
            :m_tCollection(that.m_tCollection)
            ,m_tMapping(that.m_tMapping)
            ,m_tCollision(that.m_tCollision)
        {
        }

        TCollection(const TCollection&& that)
        {
            *this = move(that);
        }

        virtual ~TCollection()
        {
        }

    public:
        void Append(const TKey& tKey, const TClass& tObject)
        {
            size_t nSubscript = m_tCollection.size();

            m_tCollection.push_back(tObject);
            m_tCollision[tKey].push_back(nSubscript);
            m_tMapping[tKey] = nSubscript;
        }

        TQueried<TClass> Query(const TKey& tKey) const
        {
            auto aCollision = m_tCollision.find(tKey);

            if(aCollision != m_tCollision.end())
            {
                TQueried<TClass> tResults;

                auto aVector = aCollision->second;

                for(int i = 0; i < aVector.size(); i++)
                {
                    tResults.Append(TClass(m_tCollection[aVector[i]]));
                }

                return move(tResults);
            }
            else
            {
                return move(TQueried<TClass>());
            }
        }

        TClass Last() const
        {
            return move(TClass(m_tCollection[m_tCollection.size()-1]));
        }

        TClass First() const
        {
            return move(TClass(m_tCollection[0]));
        }

        void Clear()
        {
            m_tCollection.clear();
            m_tMapping.clear();
        }

    public:
        virtual const TCollection& operator=(const TCollection& rvalue)
        {
            m_tCollection = rvalue.m_tCollection;
            m_tMapping = rvalue.m_tMapping;
            m_tCollision = rvalue.m_tCollision;

            return *this;
        }

        TQueried<TClass> operator[](const TKey& tKey)
        {
            return Query(tKey);
        }

        TClass operator[](size_t nIndex)
        {
            return m_tCollection[nIndex];
        }
    };
}}

#endif