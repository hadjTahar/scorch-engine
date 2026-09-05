#ifndef METAOBJECT_H
#define METAOBJECT_H

#include "metaempty.h"
#include <misc/debug.h>


#define QX_META_OBJECT( metaName, metaType, metChldType )                  \
public: std::string   meta_type_name()  const override{return #metaName;}    \
public: prv::MetaItemType  meta_item_type()  const override{return metaType;}     \
public: prv::MetaItemType  meta_child_type() const override{return metChldType;}  \

namespace Qx::prv
{


class NonCopyable
{

public:
    NonCopyable(){}
    ~NonCopyable(){}

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
};

/// ## --------------------------------------------------------
/// ##

class MetaRecord;

struct MetaRecord
{
    void         *ptr{nullptr};
    x_count       size{0};
    x_count       padding{0};
    MetaItemType  meta_item_type{MetaItemType::None};
    MetaItemType  meta_child_type{MetaItemType::None};
    std::string   meta_type_name{""};

    bool operator==(const MetaRecord& other) const
    {
        return ptr             == other.ptr       &&
               meta_type_name  == other.meta_type_name  &&
               meta_item_type  == other.meta_item_type  &&
               meta_child_type == other.meta_child_type &&
               size            == other.size      &&
               padding         == other.padding
            ;
    }
};



/// ## --------------------------------------------------------
/// ##
class MetaObject : public NonCopyable
{
    using SizeKey = std::tuple<x_count, x_count, MetaItemType, MetaItemType, std::string>;
    friend class GraphicsView;
protected:

    MetaObject()
    {
        ++itemCounter;
    }
    virtual ~MetaObject()
    {
        if constexpr( !QX_DEF_ENABLE_META_DEBUGGING )
            return;

        --itemCounter;
        records.erase( findItem() );
    }

    auto inline findItem()
    {
        auto it = std::find_if(records.begin(), records.end(),
                               [this](const MetaRecord &rcd)
                               {
                                   return this == rcd.ptr;
                               });
        const auto found = (it != records.end() );

        dbg_assert_st( found ) <<
            "MetaObject (" << meta_type_name() << ") at: " << this <<
            " can't be found in MetaObject::::records, " <<
            "either it was not tracked or constructed without "
            "MetaObject::make_unique_meta";

        return it;
    }

    static inline void check_is_alive( MetaObject const*const itm)
    {
        if constexpr( !QX_DEF_ENABLE_META_DEBUGGING )
            return;

        if ( !itm )
            return;
        auto it = std::find_if(records.begin(), records.end(),
                               [itm](const MetaRecord &rcd)
                               {
                                   return (itm == rcd.ptr);
                               });
        const auto found = (it != records.end() );
        dbg_assert_st( found ) <<
            "MetaObject (" << "it->meta_type_name" << ") at: " << itm <<
            " can't be found in ::records, " <<
            "probably it was destructed and is now dangling";

    }


    virtual MetaItemType meta_item_type()  const{return MetaItemType::NA;}
    virtual MetaItemType meta_child_type() const{return MetaItemType::NA;}
    virtual std::string  meta_type_name()  const{return "0";}


    // The actual function definition
    friend std::ostream& operator<<(std::ostream& os, const MetaObject& obj)
    {
        os << obj.meta_type_name() << "( " << &obj <<" )";
        return os;
    }

    // The actual function definition
    friend std::ostream& operator<<(std::ostream& os, const MetaObject* obj)
    {
        const void *ptr = obj;
        os << obj->meta_type_name() << "( " << ptr <<" )";
        return os;
    }


public:
    virtual void propertyChanged(PropertyStates){}

    static inline void checkRecords( MetaObject *exempt)
    {
        if constexpr( !QX_DEF_ENABLE_META_DEBUGGING )
            return;
        const auto res = (records.size() == 1 ) && (itemCounter == 1);
        if( res ){
            dbg_info_st() << "No MetaObject's leaked";
            const auto rootExempt = (records[ 0 ].ptr == exempt);
            dbg_assert_st( rootExempt ) << "Only root exempt can be left in records";
            displaySizes();
            return;
        }

        for ( const auto &rcd : records) {
            dbg_print_st() << "Leaked MetaObject: " <<
                rcd.ptr << " : " <<
                rcd.meta_type_name;
        }
        displaySizes();


        dbg_assert_st( res ) << "There are leaks: " <<
            "::records.size: " << records.size() <<
            " and ::itemCounter: " << itemCounter;


    }

    static void displaySizes()
    {
        if( !QX_DEF_ENABLE_PRINT_SIZES )
            return;
        dbg_print_st() << "------------------------------";
        dbg_print_st() <<
            "Type:"    << "MetaObject" << ", " <<
            "Size:"    << sizeof( MetaObject )
            ;

        for ( const SizeKey &szKey : sizeSet) {


            dbg_print_st() <<
                "Type:"    << std::get<4>(szKey) << ", " <<
                "Size:"    << std::get<0>(szKey)
                ;
        }
    }

protected:
    /// ## Helps preventing access to m_children
    /// ## while edits by "children"


    inline void lock( bool lck)
    {
        if constexpr( !QX_DEF_ENABLE_META_DEBUGGING )
            return;
        meta_vector_locked = lck;
    }
    inline bool locked() const
    {
        if constexpr( !QX_DEF_ENABLE_META_DEBUGGING )
            return false;
        return meta_vector_locked;
    }

protected:

    static std::set<SizeKey> sizeSet;
    static std::vector<MetaRecord> records;
    static x_count  itemCounter;


    QX_DEF_UNIQUE_ADDRESS std::conditional_t<QX_DEF_ENABLE_META_DEBUGGING,bool, MetaEmpty> meta_vector_locked{false};


    // A modern, safe wrapper GPT
    template <typename T, typename... Args>
        requires std::derived_from<T, MetaObject>
    static inline auto make_unique_meta(Args&&... args)
    {
        auto ret = std::make_unique<T>(std::forward<Args>(args)...);
        if constexpr( !QX_DEF_ENABLE_META_DEBUGGING )
            return ret;

        else
        {
            MetaRecord rec;
            auto ptr             = ret.get();
            rec.ptr              = ptr;
            rec.size             = sizeof( T );
            rec.padding          = alignof( T );
            rec.meta_item_type   = ptr->meta_item_type();
            rec.meta_child_type  = ptr->meta_child_type();
            rec.meta_type_name   = ptr->meta_type_name();

            dbg_assert_st( !rec.meta_type_name.empty() ) <<
                "Can't add a meta item with empty meta_type_name";


            sizeSet.insert(
                {
                    rec.size,
                    rec.padding,
                    rec.meta_item_type,
                    rec.meta_child_type,
                    rec.meta_type_name, }
                );
            records.push_back( rec );
        }

        return ret;
    }


};



}
#endif // METAOBJECT_H
