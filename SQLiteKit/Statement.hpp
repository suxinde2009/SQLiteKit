//
//  Statement.hpp
//  SQLiteKit
//
//  Created by SuXinDe on 2020/6/30.
//  Copyright © 2020 Skyprayer Studio. All rights reserved.
//

// TODO:

#ifndef Statement_hpp
#define Statement_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <climits> // For INT_MAX

#include "Exception.hpp"

// Forward declarations to avoid inclusion of <sqlite3.h> in a header
struct sqlite3;
struct sqlite3_stmt;

namespace SQLite {
    
    // Forward declaration
    class Database;
    class Column;
    
    extern const int OK;
    
    class Statement {
        friend class Column;
        
    public:
        
        Statement(Database& db, const char* query);
        
        Statement(Database& db, const std::string& query);
        
        ~Statement();
        
        void reset();
        
        int tryReset() noexcept;
        
        void clearBindings(); // throw(SQLite::Exception)
        
        void bind(const int index, const int value);
        
        void bind(const int index, const unsigned value);
        
#if (LONG_MAX == INT_MAX) // sizeof(long)==4 means the data model of the system is ILP32 (32bits OS or Windows 64bits)
        /**
         * @brief Bind a 32bits long value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (aIndex >= 1)
         */
        void bind(const int index, const long value) {
            bind(index, static_cast<int>(value));
        }
#else // sizeof(long)==8 means the data model of the system is LLP64 (64bits Linux)
        /**
         * @brief Bind a 64bits long value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (aIndex >= 1)
         */
        void bind(const int index, const long value) {
            bind(index, static_cast<long long>(value));
        }
#endif
        
        void bind(const int index, const long long value);
        
        void bind(const int index, const double value);
        
        void bind(const int index, const std::string& value);
        
        void bind(const int index, const char* value);
        
        void bind(const int index, const void* value, const int size);
        
        void bindNoCopy(const int index, const std::string& value);
        
        void bindNoCopy(const int index, const char* value);
        
        void bindNoCopy(const int index, const void* value, const int size);
        
        void bind(const int index);
        
        void bind(const char* apName, const int value);
        
        void bind(const char* apName, const unsigned value);
        
#if (LONG_MAX == INT_MAX) // sizeof(long)==4 means the data model of the system is ILP32 (32bits OS or Windows 64bits)
        /**
         * @brief Bind a 32bits long value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (aIndex >= 1)
         */
        void bind(const char* apName, const long value) {
            bind(apName, static_cast<int>(value));
        }
#else // sizeof(long)==8 means the data model of the system is LLP64 (64bits Linux)
        /**
         * @brief Bind a 64bits long value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (aIndex >= 1)
         */
        void bind(const char* apName, const long value) {
            bind(apName, static_cast<long long>(value));
        }
#endif
        void bind(const char* apName, const long long value);
        
        void bind(const char* apName, const double value);
        
        void bind(const char* apName, const std::string& value);
       
        void bind(const char* apName, const char* value);
       
        void bind(const char* apName, const void* value, const int size);
       
        void bindNoCopy(const char* apName, const std::string& value);
        
        void bindNoCopy(const char* apName, const char* value);
        
        void bindNoCopy(const char* apName, const void* value, const int size);
        
        void bind(const char* apName); // bind NULL value
        
        inline void bind(const std::string& name, const long long value) {
            bind(name.c_str(), value);
        }
        
        inline void bind(const std::string& name, const double value) {
            bind(name.c_str(), value);
        }
        
        
        
        
    private:
        class Ptr {
        public:
            
            Ptr(sqlite3* apSQLite, std::string& query);
            
            Ptr(const Ptr& ptr);
            
            ~Ptr();
            
            inline operator sqlite3*() const {
                return mpSQLite;
            }
            
            inline operator sqlite3_stmt*() const {
                return mpStmt;
            }
            
        private:
            Ptr& operator=(const Ptr& ptr);
            
        private:
            sqlite3*        mpSQLite;    //!< Pointer to SQLite Database Connection Handle
            sqlite3_stmt*   mpStmt;      //!< Pointer to SQLite Statement Object
            unsigned int*   mpRefCount;  //!< Pointer to the heap allocated reference counter of the sqlite3_stmt
                                         //!< (to share it with Column objects)
        };
        
    private:
        /// @{ Statement must be non-copyable
        Statement(const Statement&);
        Statement& operator=(const Statement&);
        /// @}
        
        /// Check if a return code equals SQLITE_OK, else throw a SQLite::Exception with the SQLite error message
        /// @param retCode SQLite return code to test against the SQLITE_OK expected value
        inline void check(const int retCode) const {
            if (SQLite::OK != retCode) {
                throw SQLite::Exception(mStmtPtr, retCode);
            }
        }
        
        /// Check if there is a row of result returned by executeStep(), else throw a SQLite::Exception.
        inline void checkRow() const {
            if (false == mbHasRow) {
                throw SQLite::Exception("No row to get a column from. executeStep() was not called, or returned false.");
            }
        }
        
        /// Check if there is a Column index is in the range of columns in the result.
        /// @param index index of column to be checked
        inline void checkIndex(const int index) const {
            if ((index < 0) || (index >= mColumnCount)) {
                throw SQLite::Exception("Column index out of range.");
            }
        }
        
    private:
        /// Map of columns index by name (mutable so getColumnIndex can be const)
        typedef std::map<std::string, int> TColumnNames;
    
    private:
        std::string             mQuery;         //!< UTF-8 SQL Query
        Ptr                     mStmtPtr;       //!< Shared Pointer to the prepared SQLite Statement Object
        int                     mColumnCount;   //!< Number of columns in the result of the prepared statement
        mutable TColumnNames    mColumnNames;   //!< Map of columns index by name (mutable so getColumnIndex can be const)
        bool                    mbHasRow;       //!< true when a row has been fetched with executeStep()
        bool                    mbDone;         //!< true when the last executeStep() had no more row to fetch
    };
}


#endif /* Statement_hpp */
