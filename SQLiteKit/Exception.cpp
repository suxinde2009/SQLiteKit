//
//  Exception.cpp
//  SQLiteKit
//
//  Created by SuXinDe on 2020/6/30.
//  Copyright © 2020 Skyprayer Studio. All rights reserved.
//

#include "Exception.hpp"
#include "Internal/Sqlite3/sqlite3.h"

namespace SQLite {
    
    Execption::Execption(const char* errMsg) :
        std::runtime_error(errMsg),
        mErrCode(-1),
        mExtendedErrCode(-1) {
        NULL;
    }
    
    
    Execption::Execption(const std::string& errMsg) :
        std::runtime_error(errMsg),
        mErrCode(-1),
        mExtendedErrCode(-1) {
        NULL;
    }
    
    Execption::Execption(const char *errMsg, int retCode) :
        std::runtime_error(errMsg),
        mErrCode(retCode),
        mExtendedErrCode(-1) {
        NULL;
    }
    Execption::Execption(const std::string& errMsg, int retCode) :
        std::runtime_error(errMsg),
        mErrCode(retCode),
        mExtendedErrCode(-1) {
        NULL;
    }
    
    Execption::Execption(sqlite3 *apSQLite) :
        std::runtime_error(sqlite3_errmsg(apSQLite)),
        mErrCode(sqlite3_errcode(apSQLite)),
        mExtendedErrCode(sqlite3_extended_errcode(apSQLite)) {
        NULL;
    }
    
    Execption::Execption(sqlite3 *apSQLite, int retCode) :
        std::runtime_error(sqlite3_errmsg(apSQLite)),
        mErrCode(retCode),
        mExtendedErrCode(sqlite3_extended_errcode(apSQLite)) {
        NULL;
    }
}
