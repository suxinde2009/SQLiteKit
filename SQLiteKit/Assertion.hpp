//
//  Assertion.hpp
//  SQLiteKit
//
//  Created by SuXinDe on 2020/6/30.
//  Copyright © 2020 Skyprayer Studio. All rights reserved.
//

#ifndef Assertion_hpp
#define Assertion_hpp

#include <stdio.h>
#include <cassert>

#ifdef SQLITE_KIT_ENABLE_ASSERT_HANDLER

namespace SQLite {
    // if an assert handler is provided by user code, use it instead of assert()
    void assertion_failed(const char* apFile,
                          const long apLine,
                          const char* apFunc,
                          const char* apExpr,
                          const char* apMsg);
    
#ifdef _MSC_VER
#define __func__ __FUNCTION__
#endif
    
    // call the assert handler provided by user code
#define SQLITE_KIT_ASSERT(expression, message) \
    if (!(expression)) {   \
        SQLite::assertion_failed(__FILE__, __LINE__, __func__, #expression, message) \
    }
}

#else

// if no assert handler provided by user code, use standard assert()
// (note: in release mode assert() does nothing)
#define SQLITE_KIT_ASSERT(expression, message)   assert(expression && message)

#endif

#endif /* Assertion_hpp */
