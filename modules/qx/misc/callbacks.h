#ifndef CALLBACKS_H
#define CALLBACKS_H


#include "typedfunction.h"

namespace Qx
{
class MouseEvent;
class KeyEvent;
class SequenceEvent;
}

namespace Qx::prv
{

template <class Type>
using x_callback = std::conditional_t<QX_DEF_TYPED_FUNCTION_CALLBACK,
                                         TypedFunction<Type>,
                                         std::function<Type>
                                      >;


// using x_singleCall    = std::function<void()>;
// using x_timerCallback      = x_callback<void()>;
using x_timerCallback       = std::function<void(void)>;
using x_processCallback     = x_callback<void(x_real)>;
using x_progressCallback    = x_callback<void(x_real, bool)>;
using x_polynomialCallback  = x_callback<x_real(x_real)>;
using x_clickCallback       = x_callback<bool(const Qx::MouseEvent &)>;
using x_keyCallback         = x_callback<bool(const Qx::KeyEvent &)>;
using x_sequenceCallback    = x_callback<bool(const Qx::SequenceEvent &)>;
using x_simpleCallback      = x_callback<void()>;

}

#endif // CALLBACKS_H
