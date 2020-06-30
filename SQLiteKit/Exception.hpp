//
//  Exception.hpp
//  SQLiteKit
//
//  Created by SuXinDe on 2020/6/30.
//  Copyright © 2020 Skyprayer Studio. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

#include <stdio.h>
#include <stdexcept>
#include <string>

struct sqlite3;

#ifndef __has_feature
#define __has_feature(x) 0
#endif

// Detect whether the compiler supports C++11 noexcept exception specifications.
#if (  defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 7) || (__GNUC__ > 4)) \
&& defined(__GXX_EXPERIMENTAL_CXX0X__))
// GCC 4.7 and following have noexcept
#elif defined(__clang__) && __has_feature(cxx_noexcept)
// Clang 3.0 and above have noexcept
#elif defined(_MSC_VER) && _MSC_VER > 1800
// Visual Studio 2015 and above have noexcept
#else
// Visual Studio 2013 does not support noexcept, and "throw()" is deprecated by C++11
#define noexcept
#endif


namespace SQLite {
    
    class Execption: public std::runtime_error {
    public:
        explicit Execption(const char* errMsg);
        explicit Execption(const std::string& errMsg);
        
        Execption(const char *errMsg, int retCode);
        Execption(const std::string& errMsg, int retCode);
        
        explicit Execption(sqlite3 *apSQLite);
        Execption(sqlite3 *apSQLite, int retCode);
        
        inline int getErrorCode() const noexcept {
            return mErrCode;
        }
        inline int getExtendedErrCode() const noexcept {
            return mExtendedErrCode;
        }
        
    private:
        int mErrCode;           ///< Error code value
        int mExtendedErrCode;   ///< Detailed error code if any
    };
    
}


#endif /* Exception_hpp */
