#include "chromeHistory.h"

time_t olderChromeItem;
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
 * Queries the history database of chrome, and verifies if it is legitimate
 * @return If the history could not be read: RESULT_UNKNOWN, else if the history is legitimate: RESULT_SUCCESS, else: RESULT_FAILURE
 */
int checkChromeLikeHistory(char* name, char* access, char* resultDescriptionBuffer){

    //Buffer for verbose output
    char tmp[2][128];

    //Initialize variables used to check if the history is legit or not
    olderChromeItem         = time(NULL);
    countRecentChromeItems  = 0;

    //Initialize variables used to query 'History'
    sqlite3 *db;
    char *err_msg = 0;

    //Various char pointers to build paths
    char path1[256]    = "";
    const char* path2;
    char path3[]       = "/Default/History";

    //Builds 'History' path
    path2 = getenv("HOME");
    strcat(path1, path2);
    strcat(path1, access);
    strcat(path1, path3);

    /* DOES NOT SOLVE THE PROBLEM
     * TODO: find a solution to read the history when a window is open
    //If chrome is open, the database is locked, so it is safer to work on a copy
    //The random string is just to avoid any collision with other programs, as 'history' is a common word
    char cpPath[] = "/tmp/History_n0jxYiru0t";
    cp(cpPath, path1);
     */

    //Open a connection to the copy of 'History'
    int rc = sqlite3_open(path1, &db);

    //If something went wrong
    if (rc != SQLITE_OK) {
        snprintf(tmp[0], 128, "--> Could not read history from %s\n", path1);
        strcat(resultDescriptionBuffer, tmp[0]);
        sqlite3_close(db);
        return RESULT_UNKNOWN;
    }

    //SQL query
    char *sql = "SELECT datetime(visit_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch', 'localtime') AS visit_date FROM visits ORDER BY visit_date ASC;";
    rc = sqlite3_exec(db, sql, chromeSqlCallback, 0, &err_msg);

    //If something went wrong
    if (rc != SQLITE_OK) {
        snprintf(tmp[0], 128, "--> Could not read history from %s\n", path1);
        strcat(resultDescriptionBuffer, tmp[0]);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return RESULT_UNKNOWN;
    }

    //Close 'History' connection
    sqlite3_close(db);

    //Final check
    int isOldEnough    = difftime(x_days_ago, olderChromeItem) > 0;
    int isDenseEnough  = countRecentChromeItems > MIN_NB_DURING_LAST_X_DAYS;

    //Fill the verbose description of the result
    if(!isOldEnough){
        strftime(tmp[1], 128, "%d-%m-%Y", localtime(&olderChromeItem));
        snprintf(tmp[0], 128, "--> %s history is not old enough (older item is from %s).\n", name, tmp[1]);
        strcat(resultDescriptionBuffer, tmp[0]);
    }
    if(!isDenseEnough){
        snprintf(tmp[0], 128, "--> %s recent history only contains %d items.\n", name, countRecentChromeItems);
        strcat(resultDescriptionBuffer, tmp[0]);
    }

    return (isOldEnough && isDenseEnough) ? RESULT_SUCCESS : RESULT_FAILURE;
}