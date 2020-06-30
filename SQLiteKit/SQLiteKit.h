//
//  SQLiteKit.h
//  SQLiteKit
//
//  Created by SuXinDe on 2020/6/30.
//  Copyright © 2020 Skyprayer Studio. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for SQLiteKit.
FOUNDATION_EXPORT double SQLiteKitVersionNumber;

//! Project version string for SQLiteKit.
FOUNDATION_EXPORT const unsigned char SQLiteKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <SQLiteKit/PublicHeader.h>

#include "Exception.hpp"
#include "NullPtr.hpp"
#include "Assertion.hpp"
#include "Statement.hpp"
#include "Column.hpp"
#include "Transaction.hpp"
#include "Database.hpp"
#include "VariadicBind.hpp"


/**
 * @brief Version numbers for SQLiteKit are provided in the same way as sqlite3.h
 *
 * The [SQLITECPP_VERSION] C preprocessor macro in the SQLiteC++.h header
 * evaluates to a string literal that is the SQLite version in the
 * format "X.Y.Z" where X is the major version number
 * and Y is the minor version number and Z is the release number.
 *
 * The [SQLITE_KIT_VERSION] C preprocessor macro resolves to an integer
 * with the value (X*1000000 + Y*1000 + Z) where X, Y, and Z are the same
 * numbers used in [SQLITE_KIT_VERSION].
 *
 * Dependency Sqlite3 v3.20.1
 * #define SQLITE_VERSION        "3.20.1"
 * #define SQLITE_VERSION_NUMBER 3020001
 * #define SQLITE_SOURCE_ID      "2017-08-24 16:21:36 8d3a7ea6c5690d6b7c3767558f4f01b511c55463e3f9e64506801fe9b74dce34"
 *
 */
#define SQLITE_KIT_VERSION           "2.02.00"   // 2.2.0
#define SQLITE_KIT_VERSION_NUMBER     2002000    // 2.2.0
