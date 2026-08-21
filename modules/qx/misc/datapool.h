#ifndef DATAPOOL_H
#define DATAPOOL_H

#include "vecs.h"
#include "debug.h"
#include <vector>



namespace Qx {


template <typename DataType,
         x_count poolSize,
         x_count entitySize>
class DataPool
{
public:
    DataPool():
        m_pool(poolSize),
        m_nextAvailableIndex(0)
    {
    }

    x_count request()
    {
        /// ## Replace
        if( !m_freeIndices.empty() )
        {
            auto repIndex = m_freeIndices.back();
            m_freeIndices.pop_back();
            return repIndex;
        }

        /// ## Full
        else if (m_nextAvailableIndex + entitySize > m_pool.size())
        {
            dbg_assert( false ) << "Request exceeded pool range";
            return -1;
        }

        /// ## Allocate
        auto startIndex = m_nextAvailableIndex;
        m_nextAvailableIndex += entitySize;
        return startIndex;
    }

    void reset()
    {
        m_freeIndices.clear();
        m_nextAvailableIndex = 0;
    }
    void remove(x_count index)
    {
        m_freeIndices.push_back( index );
        /// ## Remove
    }

    // Access raw data for GPU upload
    auto dataPtr()
    {
        return m_pool.data();
    }

    // Access raw data for GPU upload
    void* data()
    {
        return m_pool.data();
    }

    x_count  size() const
    {
        return m_nextAvailableIndex;
    }

    auto sizeInBytes() const
    {
        return size() * sizeof(DataType);
    }


// private:
    std::vector<DataType>   m_pool;
    std::vector<x_count>    m_freeIndices;
    x_count m_nextAvailableIndex;
};

}


#endif // DATAPOOL_H
