#include "chromeHistory.h"

time_t olderChromeItem, now, x_days_ago;
struct tm x_days_ago_tm;
int countRecentChromeItems;


int chromeSqlCallback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;
    struct tm ltm = {0};
    time_t tmpTime;

    for (int i = 0; i < argc; i++) {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        if(argv[i]) {

            strptime(argv[i], "%Y-%m-%d %H:%M:%S", &ltm);

            //Is it the older item?
            tmpTime = mktime(&ltm);
            if (difftime(olderChromeItem, tmpTime)>0){
                olderChromeItem = tmpTime;
            }

            //Is it a recent item?
            if (difftime(tmpTime, x_days_ago)>0){
                countRecentChromeItems++;
            }
        }
    }

    return 0;
}

/**
 * Queries the history database of chrome, and verifies it is legitimate
 * @return If the history could not be read: RESULT_UNKNOWN, else if the history is legitimate: RESULT_SUCCESS, else: RESULT_FAILURE
 */
int checkChromeHistory(){

    //Initialize variables used to check if the history is legit or not
    olderChromeItem         = time(NULL);
    countRecentChromeItems  = 0;

    //Initialize variables used to query 'History'
    sqlite3 *db;
    char *err_msg = 0;

    //Various char pointers to build paths
    char path1[256]    = "";
    const char* path2;
    char path3[]       = "/.config/google-chrome/Default/History";

    //Builds 'History' path
    path2 = getenv("HOME");
    strcat(path1, path2);
    strcat(path1, path3);

    //If chrome is open, the database is locked, so it is safer to work on a copy
    //The random string is just to avoid any collision with other programs, as 'history' is a common word
    char cpPath[] = "/tmp/History_n0jxYiru0t";
    cp(cpPath, path1);

    //Open a connection to the copy of 'History'
    int rc = sqlite3_open(cpPath, &db);

    //If something went wrong
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return RESULT_UNKNOWN;
    }

    //SQL query
    char *sql = "SELECT datetime(visit_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch', 'localtime') FROM visits;";
    rc = sqlite3_exec(db, sql, chromeSqlCallback, 0, &err_msg);

    //If something went wrong
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return RESULT_UNKNOWN;
    }

    //Close 'History' connection
    sqlite3_close(db);

    //Final check
    int isOldEnough    = difftime(x_days_ago, olderChromeItem) > 0;
    int isDenseEnough  = countRecentChromeItems > MIN_NB_DURING_LAST_X_DAYS;
    return (isOldEnough && isDenseEnough) ? RESULT_SUCCESS : RESULT_FAILURE;
}