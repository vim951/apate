#include "browserHistory.h"


/**
 * Queries the history database of firefox, chromium and chrome, and verifies if it is legitimate
 * @return If the history could not be read: RESULT_UNKNOWN, else if the history is legitimate: RESULT_SUCCESS, else: RESULT_FAILURE
 */
int checkBrowserHistory(){

    //Initialize variables used to check if the history is legit or not
    now                      = time(NULL);
    x_days_ago_tm            = *localtime(&now);
    x_days_ago_tm.tm_mday   -= COUNT_OVER_LAST_X_DAYS;
    x_days_ago               = mktime(&x_days_ago_tm);

    //Checks histories one by one
    int results[] = {
            checkFirefoxHistory(),
            checkChromeLikeHistory("/snap/chromium/common/chromium"),
            checkChromeLikeHistory("/.config/google-chrome")
    };
    int length = 3;
    int tmpResult = RESULT_FAILURE;

    //Merges results from browsers
    for (int i=0 ; i<length ; i++){
        if(tmpResult==RESULT_SUCCESS || results[i]==RESULT_SUCCESS){
            tmpResult = RESULT_SUCCESS;
        }else if(tmpResult==RESULT_FAILURE && results[i]==RESULT_FAILURE){
            tmpResult = RESULT_FAILURE;
        }else{
            tmpResult = RESULT_UNKNOWN;
        }
    }

    return tmpResult;

}