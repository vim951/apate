#include "firefoxHistory.h"

time_t olderFirefoxItem, now, x_days_ago;
struct tm x_days_ago_tm;
int countRecentFirefoxItems;

/**
 * Reads the profiles.ini file of firefox, to extract the default profile name
 * @param path Path of the 'profiles.ini' file
 * @param buffer Where the result should be written
 */
void getProfileName(char* path, char* buffer){
    char profile[64];
    readFileLine(path, 1, profile);
    char* current_pos = strchr(profile, '=')+1;
    char* eol = strchr(profile, '\n');
    *eol = '\0';
    strcpy(buffer, current_pos);
}

int firefoxSqlCallback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;
    struct tm ltm = {0};
    time_t tmpTime;

    for (int i = 0; i < argc; i++) {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        if(argv[i]) {

            strptime(argv[i], "%Y-%m-%d %H:%M:%S", &ltm);

            //Is it the older item?
            tmpTime = mktime(&ltm);
            if (difftime(olderFirefoxItem, tmpTime)>0){
                olderFirefoxItem = tmpTime;
            }

            //Is it a recent item?
            if (difftime(tmpTime, x_days_ago)>0){
                countRecentFirefoxItems++;
            }
        }
    }

    return 0;
}

/**
 * Queries the history database of firefox, and verifies it is legitimate
 * @return If the history could not be read: RESULT_UNKNOWN, else if the history is legitimate: RESULT_SUCCESS, else: RESULT_FAILURE
 */
int checkFirefoxHistory(){

    //Initialize variables used to check if the history is legit or not
    now                      = time(NULL);
    x_days_ago_tm            = *localtime(&now);
    x_days_ago_tm.tm_mday   -= COUNT_OVER_LAST_X_DAYS;
    x_days_ago               = mktime(&x_days_ago_tm);
    olderFirefoxItem         = time(NULL);
    countRecentFirefoxItems  = 0;

    //Initialize variables used to query 'places.sqlite'
    sqlite3 *db;
    char *err_msg = 0;

    //Various char pointers to build paths
    char path1[256]    = "";
    const char* path2;
    char path3[]       = "/.mozilla/firefox/";
    char path4[64];
    char path5[]       = "/places.sqlite";

    //Builds 'profiles.ini' path
    path2 = getenv("HOME");
    char profilesPath[128];
    strcpy(profilesPath, path2);
    strcat(profilesPath, "/.mozilla/firefox/profiles.ini");

    //Reads 'profiles.ini'
    getProfileName(profilesPath, path4);

    //Builds 'places.sqlite' path
    strcat(path1, path2);
    strcat(path1, path3);
    strcat(path1, path4);
    strcat(path1, path5);

    //Open a connection to 'places.sqlite'
    int rc = sqlite3_open(path1, &db);

    //If something went wrong
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return RESULT_UNKNOWN;
    }

    //SQL query
    char *sql = "SELECT datetime(visit_date/1000000,'unixepoch') AS visit_date FROM moz_historyvisits ORDER BY visit_date ASC;";
    rc = sqlite3_exec(db, sql, firefoxSqlCallback, 0, &err_msg);

    //If something went wrong
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return RESULT_UNKNOWN;
    }

    //Close 'places.sqlite' connection
    sqlite3_close(db);

    //Final check
    int isOldEnough    = difftime(x_days_ago, olderFirefoxItem) > 0;
    int isDenseEnough  = countRecentFirefoxItems > MIN_NB_DURING_LAST_X_DAYS;
    return (isOldEnough && isDenseEnough) ? RESULT_SUCCESS : RESULT_FAILURE;
}