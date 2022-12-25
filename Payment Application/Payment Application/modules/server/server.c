//
//  server.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//
#include <string.h>
#include "server.h"

uint32_t seq_num = 000000;
ST_accountsDB_t accountRefrence;
ST_accountsDB_t accountsDB[255] = {
    {1000, RUNNING, "4560392230689494"},
    {2000, RUNNING, "4929006859824424"},
    {3000, RUNNING, "4024007104373104"},
    {4000, RUNNING, "4532134935655932"},
    {5000, RUNNING, "4916515628632251"},
    {6000, BLOCKED, "4716054078699158"},
    {7000, BLOCKED, "4024007119953353"},
    {8000, BLOCKED, "4916759623367675"},
    {9000, BLOCKED, "4024007107591116"},
    {10000,BLOCKED, "4532921095940439"}
};
ST_transaction_t trans_arr[255] = {0};


EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    if(isValidAccount(&transData->cardHolderData, &accountRefrence) == ACCOUNT_NOT_FOUND){
        return FRAUD_CARD;
    }

    if(isBlockedAccount(&accountRefrence)){
        return DECLINED_STOLEN_CARD;
    }
    if(isAmountAvailable(&transData->terminalData, &accountRefrence)){
        return DECLINED_INSUFFECIENT_FUND;
    }

    accountRefrence.balance -= transData->terminalData.transAmount;
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
    u_char account_is_found = 0;
    for (int i = 0; i < 10; i++) {
        if (memcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber, sizeof(cardData->primaryAccountNumber))==0) {
            *accountRefrence = accountsDB[i];
            account_is_found = 1;
        }
    }
    if (account_is_found) {
        return SERVER_OK;
    } else {
        return ACCOUNT_NOT_FOUND;
    }
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
        printf("account %u\n", accountRefrence->state);
        if(accountRefrence->state == BLOCKED){
            printf("BLOCKED_ACCOUNT\n");
            return BLOCKED_ACCOUNT;
        } else{
            return SERVER_OK;
        }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
    if (termData->transAmount > accountRefrence->balance) {
        return LOW_BALANCE;
    }else{
        return SERVER_OK;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    transData->transactionSequenceNumber = seq_num;
    trans_arr[seq_num] = *transData;
    listSavedTransactions();
    seq_num+=1;
    return SERVER_OK;
}

void listSavedTransactions(void){
    for (int i=0; i<=seq_num; i++){
        printf("#########################\n");
        printf("Transaction Sequence Number: %u\n", trans_arr[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n", trans_arr[i].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", trans_arr[i].terminalData.transAmount);
        printf("Transaction State: %u\n", trans_arr[i].transState);
        printf("Terminal Max Amount: %f\n", trans_arr[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", trans_arr[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n", trans_arr[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", trans_arr[i].cardHolderData.cardExpirationDate);
    }
}
