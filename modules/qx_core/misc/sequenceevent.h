#ifndef SEQUENCEEVENT_H
#define SEQUENCEEVENT_H



#include "defs.h"
#include "event.h"

namespace Qx
{


struct SequenceEvent : public Event
{
    SequenceEvent(x_keycode   k0,
                x_keycode   k1,
                x_keycode   k2,
                x_modifiers mod):
        Event{},
        key0{k0},
        key1{k1},
        key2{k2},
        modifiers{mod},
        index{0}
    {
    }
    x_keycode   key0;       // First key (0 if none)
    x_keycode   key1;       // Second key (0 if none)
    x_keycode   key2;       // Third key (0 if none)
    x_modifiers modifiers;  // SDL_Keymod bits (16-bit)
    x_modifiers index;

    // Blazingly fast equality check (compilers can optimize this into SIMD instructions)
    bool operator==(const SequenceEvent& other) const {
        return key0      == other.key0      &&
               key1      == other.key1      &&
               key2      == other.key2      &&
               modifiers == other.modifiers;
    }

    // Strict ordering for std::map usage
    bool operator<(const SequenceEvent& other) const {
        return std::tie(key0, key1, key2, modifiers) <
               std::tie(other.key0, other.key1, other.key2, other.modifiers);
    }

    void addKey( x_keycode key )
    {
        if( index == 0 )
            key0 = key;
        else if( index == 1 )
            key1 = key;
        else if( index == 2 )
            key2 = key;
        else{
            index = 0;
            key0  = key;
        }
        ++index;
    }

    void remKey()
    {
        if( index == 2 )
            key2 = 0;
        else if( index == 1 )
            key1 = 0;
        else if( index == 0 ){
            key0  = 0;
            index = 1;
        }
        --index;
    }
};

}

#endif // SEQUENCEEVENT_H
