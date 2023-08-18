#include "db.h"
#include <sqlite3.h>
#include <stdio.h>

int init_db(const char *db_path) {
  sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open(db_path, &db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return rc;
  }

  const char *queries[] = {
      "CREATE TABLE IF NOT EXISTS users("
      "id INTEGER PRIMARY KEY, "
      "name TEXT UNIQUE NOT NULL, "
      "password_hash TEXT NOT NULL, "
      "active BOOLEAN NOT NULL);",

      "CREATE TABLE IF NOT EXISTS accounts("
      "id INTEGER PRIMARY KEY, "
      "user_id INTEGER NOT NULL REFERENCES users(id), "
      "type TEXT NOT NULL, "
      "date DATE NOT NULL, "
      "balance DECIMAL(20,2) NOT NULL, "
      "country TEXT NOT NULL, "
      "name TEXT, "
      "phone TEXT NOT NULL);",

      "CREATE TABLE IF NOT EXISTS transactions("
      "id INTEGER PRIMARY KEY, "
      "sender_account_id INTEGER NOT NULL REFERENCES accounts(id), "
      "receiver_account_id INTEGER REFERENCES accounts(id), "
      "amount DECIMAL(20,2) NOT NULL, "
      "date DATE NOT NULL);",

      "CREATE TABLE IF NOT EXISTS account_transfers("
      "id INTEGER PRIMARY KEY, "
      "sender_user_id INTEGER NOT NULL REFERENCES users(id), "
      "receiver_user_id INTEGER NOT NULL REFERENCES users(id), "
      "transferred_account_id INTEGER NOT NULL REFERENCES accounts(id), "
      "date DATE NOT NULL);"};

  for (size_t i = 0; i < sizeof(queries) / sizeof(queries[0]); i++) {
    rc = sqlite3_exec(db, queries[i], 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return rc;
    }
  }

  sqlite3_close(db);
  return SQLITE_OK;
}
