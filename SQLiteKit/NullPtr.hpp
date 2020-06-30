//
//  NullPtr.hpp
//  SQLiteKit
//
//  Created by SuXinDe on 2020/6/30.
//  Copyright © 2020 Skyprayer Studio. All rights reserved.
//

#ifndef NullPtr_hpp
#define NullPtr_hpp

#include <stdio.h>
#include <cstddef>

/**
 * @brief A macro to disallow the copy constructor and operator= functions.
 *
 * This should be used in the private: declarations for a class
 *
 * @param[in] TypeName  Class name to protect
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName)  \
    TypeName(const TypeName&);              \
    void operator=(const TypeName&)

#ifdef _MSC_VER
#if _MSC_VER < 1600
/// A macro to enable the use of the nullptr keyword (NULL on older MSVC compilers, as they do not accept "nullptr_t")
#ifndef nullptr
#define nullptr NULL
#endif  // nullptr
#endif  // _MSC_VER < 1600
#elif defined(__APPLE__) // AppleClang
#elif defined(__clang__) && __has_feature(cxx_nullptr) // Clang 3.0+
#else // GCC or older Clang
#if (__cplusplus < 201103L) && !defined(__GXX_EXPERIMENTAL_CXX0X__) // before C++11 on GCC4.7 and Visual Studio 2010
#ifndef HAVE_NULLPTR
#define HAVE_NULLPTR    ///< A macro to avoid double definition of nullptr


/// `nullptr_t` is the type of the null pointer literal, nullptr.
class nullptr_t {
public:
    template<typename T>
    inline operator T* () const { ///< convertible to any type of null non-member pointer...
        return 0;
    }
    
    template<typename C, typename T>
    inline operator T C::* () const { ///< convertible to any type of null member pointer...
        return 0;
    }
    
private:
    void operator&() const; ///< Can't take address of nullptr NOLINT
};


const nullptr_t nullptr = {};

#endif // HAVE_NULLPTR
#endif // (__cplusplus < 201103L) && !defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // _MSC_VER

// A macro for snprintf support in Visual Studio
#if _MSC_VER
#define snprintf _snprintf

#endif /* NullPtr_hpp */
