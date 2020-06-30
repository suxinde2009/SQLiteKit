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



#define SQLITE_KIT_VERSION           "2.02.00"   // 2.2.0
#define SQLITE_KIT_VERSION_NUMBER     2002000    // 2.2.0
