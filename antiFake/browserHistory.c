#include "browserHistory.h"

int checkBrowserHistory(){

    //Initialize variables used to check if the history is legit or not
    now                      = time(NULL);
    x_days_ago_tm            = *localtime(&now);
    x_days_ago_tm.tm_mday   -= COUNT_OVER_LAST_X_DAYS;
    x_days_ago               = mktime(&x_days_ago_tm);

    //Checks histories one by one
    int isChromeHistoryLegit = checkChromeHistory();
    int isFirefoxHistoryLegit = checkFirefoxHistory();
    int isChromiumHistoryLegit = RESULT_FAILURE;

    if (isChromeHistoryLegit==RESULT_SUCCESS || isFirefoxHistoryLegit==RESULT_SUCCESS || isChromiumHistoryLegit==RESULT_SUCCESS){
        return RESULT_SUCCESS;
    }else if (isChromeHistoryLegit==RESULT_FAILURE && isFirefoxHistoryLegit==RESULT_FAILURE && isChromiumHistoryLegit==RESULT_FAILURE){
        return RESULT_FAILURE;
    }else{
        return RESULT_UNKNOWN;
    }

}