#ifndef TYPEDFUNCTION_H
#define TYPEDFUNCTION_H

#include "debugprint.h"

#include <cstddef>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <array>



namespace Qx::prv
{

template<typename Signature, x_count Capacity = QX_DEF_TYPED_FUNCTION_CAPTURE_SIZE>
class TypedFunction;

template<typename Ret, typename... Args, x_count Capacity>
class TypedFunction<Ret(Args...), Capacity> {
public:
    TypedFunction() = default;

    // Delete copy and move constructors and assignment operators
    TypedFunction(const TypedFunction&) = delete;
    TypedFunction& operator=(const TypedFunction&) = delete;
    TypedFunction(TypedFunction&&) = delete;
    TypedFunction& operator=(TypedFunction&&) = delete;

    ~TypedFunction() {
        if (destroyFn) destroyFn(storage.data());
    }



    // Assignment operator for any callable
    template<typename Callable>
    TypedFunction& operator=(Callable&& func) {
        using Decayed = std::decay_t<Callable>;


        static_assert(sizeof(Decayed) <= Capacity, "Callable too large for TypedFunction, check captured types size");
        static_assert(std::is_invocable_r_v<Ret, Decayed, Args...>, "Callable type mismatch");

        static_assert(alignof(Decayed) <= alignof(std::max_align_t),
                      "Callable has an alignment requirement greater than std::max_align_t. "
                      "TypedFunction's storage might not be sufficiently aligned.");

        dbg_assert( !invokeFn ) << "Callable can't be redefined once it's set";

        // Destroy previous callable if any
        if (destroyFn) {
            destroyFn(storage.data());
            destroyFn = nullptr;
            invokeFn = nullptr;
        }

        new (storage.data()) Decayed(std::forward<Callable>(func));

        invokeFn = [](void* self, Args... args) -> Ret {
            return (*static_cast<Decayed*>(self))(std::forward<Args>(args)...);
        };

        destroyFn = [](void* self) {
            static_cast<Decayed*>(self)->~Decayed();
        };

        return *this;
    }

    Ret operator()(Args... args) const {
        dbg_assert(invokeFn) << "TypedFunction: no callable bound";
        return invokeFn(const_cast<void*>(static_cast<const void*>(storage.data())), std::forward<Args>(args)...);
    }

    bool isValid() const { return invokeFn != nullptr; }

    operator bool const(){return isValid();}
    // operator bool      (){return isValid();}

private:
    using InvokeFn = Ret(*)(void*, Args...);
    using DestroyFn = void(*)(void*);

    alignas(std::max_align_t)
        std::array<std::byte, Capacity> storage{};

    InvokeFn invokeFn = nullptr;
    DestroyFn destroyFn = nullptr;
};

} // namespace Qx

#endif // TYPEDFUNCTION_H
