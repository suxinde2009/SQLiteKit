//
//  Backup.cpp
//  SQLiteKit
//
//  Created by ak on 2021/12/10.
//  Copyright © 2021 Skyprayer Studio. All rights reserved.
//

#include "Backup.hpp"
#include "Exception.hpp"

#include "sqlite3.h"

namespace SQLite
{

// Initialize resource for SQLite database backup
Backup::Backup(Database&    aDestDatabase,
               const char*  apDestDatabaseName,
               Database&    aSrcDatabase,
               const char*  apSrcDatabaseName) :
    mpSQLiteBackup(NULL)
{
    mpSQLiteBackup = sqlite3_backup_init(aDestDatabase.getHandle(),
                                         apDestDatabaseName,
                                         aSrcDatabase.getHandle(),
                                         apSrcDatabaseName);
    if (NULL == mpSQLiteBackup)
    {
        // If an error occurs, the error code and message are attached to the destination database connection.
        throw SQLite::Exception(aDestDatabase.getHandle());
    }
}

// Initialize resource for SQLite database backup
Backup::Backup(Database&            aDestDatabase,
               const std::string&   aDestDatabaseName,
               Database&            aSrcDatabase,
               const std::string&   aSrcDatabaseName) :
    mpSQLiteBackup(NULL)
{
    mpSQLiteBackup = sqlite3_backup_init(aDestDatabase.getHandle(),
                                         aDestDatabaseName.c_str(),
                                         aSrcDatabase.getHandle(),
                                         aSrcDatabaseName.c_str());
    if (NULL == mpSQLiteBackup)
    {
        // If an error occurs, the error code and message are attached to the destination database connection.
        throw SQLite::Exception(aDestDatabase.getHandle());
    }
}

// Initialize resource for SQLite database backup
Backup::Backup(Database &aDestDatabase, Database &aSrcDatabase) :
    mpSQLiteBackup(NULL)
{
    mpSQLiteBackup = sqlite3_backup_init(aDestDatabase.getHandle(),
                                         "main",
                                         aSrcDatabase.getHandle(),
                                         "main");
    if (NULL == mpSQLiteBackup)
    {
        // If an error occurs, the error code and message are attached to the destination database connection.
        throw SQLite::Exception(aDestDatabase.getHandle());
    }
}

// Release resource for SQLite database backup
Backup::~Backup()
{
    if (NULL != mpSQLiteBackup)
    {
        sqlite3_backup_finish(mpSQLiteBackup);
    }
}

// Execute backup step with a given number of source pages to be copied
int Backup::executeStep(const int aNumPage /* = -1 */)
{
    const int res = sqlite3_backup_step(mpSQLiteBackup, aNumPage);
    if (SQLITE_OK != res && SQLITE_DONE != res && SQLITE_BUSY != res && SQLITE_LOCKED != res)
    {
        throw SQLite::Exception(sqlite3_errstr(res), res);
    }
    return res;
}

// Get the number of remaining source pages to be copied in this backup process
int Backup::getRemainingPageCount()
{
    return sqlite3_backup_remaining(mpSQLiteBackup);
}

// Get the number of total source pages to be copied in this backup process
int Backup::getTotalPageCount()
{
    return sqlite3_backup_pagecount(mpSQLiteBackup);
}

}  // namespace SQLite
