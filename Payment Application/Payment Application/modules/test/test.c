//
//  test.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/24/22.
//

#include "test.h"
#include "../terminal/terminal.h"
#include "../card/card.h"
#include "../server/server.h"


ST_cardData_t cardData;
ST_terminalData_t terminalData;
ST_transaction_t transData;
EN_transState_t transState;
ST_accountsDB_t accountReference;
EN_cardError_t cardError;
EN_serverError_t serverError;
EN_terminalError_t terminalError;


const char *transactionStates[] = {"APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR"};
const char *serverStates[] = {"SERVER_OK", "SAVING_FAILED", "TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND", "LOW_BALANCE", "BLOCKED_ACCOUNT"};
void runAllTests(void){
    getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    getTransactionDateTest();
    isCardExpriedTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    recieveTransactionDataTest();
    isValidAccountTest();
    isBlockedAccountTest();
    isAmountAvailableTest();
    saveTransactionTest();
    listSavedTransactionsTest();
}

void getCardHolderNameTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: getCardHolderName\n");
    
    printf("Test Case 1:\n");
    printf("Input Data: Ahmed Mohamed Abdelwahab\n");
    getCardHolderName(&cardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result: ");
    printf("Actual Result: %s\n", cardError ? "WRONG_NAME" : "CARD_OK");
    
    printf("Test Case 2:\n");
    printf("Input Data: $\n");
    cardError = getCardHolderName(&cardData);
    printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_NAME" : "CARD_OK" );
    
    printf("Test Case 3:\n");
    printf("Input Data: Ahmed Mohamed Abdelwahab Said\n");
    cardError = getCardHolderName(&cardData);
    printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_NAME" : "CARD_OK" );
}

void getCardExpiryDateTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: getCardExpiryDate\n");
    
    printf("Test Case 1:\n");
    printf("Input Data: 11/11\n");
    cardError = getCardExpiryDate(&cardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_EXP_DATE" : "CARD_OK");
    
    printf("Test Case 2:\n");
    printf("Input Data: 13/11\n");
    cardError = getCardExpiryDate(&cardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_EXP_DATE" : "CARD_OK");
    
    printf("Test Case 3:\n");
    printf("Input Data: . \n");
    cardError = getCardExpiryDate(&cardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_EXP_DATE" : "CARD_OK");
    
}

void getCardPANTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: getCardPAN\n");
    
    printf("Test Case 1:\n");
    printf("Input Data: 4929139493758482\n");
    cardError = getCardPAN(&cardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_PAN" : "CARD_OK");
    
    printf("Test Case 2:\n");
    printf("Input Data: 492913949375\n");
    cardError = getCardPAN(&cardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_PAN" : "CARD_OK");
    
    printf("Test Case 3:\n");
    printf("Input Data: ffff\n");
    cardError = getCardPAN(&cardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result: %s\n", cardError ? "WRONG_PAN" : "CARD_OK");
}

void getTransactionDateTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: getTransactionDate\n");
    
    printf("Test Case 1:\n");
    printf("Input Data: 25/06/2022\n");
    terminalError = getTransactionDate(&terminalData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
    
    
    printf("Test Case 2:\n");
    printf("Input Data: 25/30/2022\n");
    terminalError = getTransactionDate(&terminalData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
    
    printf("Test Case 3:\n");
    printf("Input Data: 32/12/2022\n");
    terminalError = getTransactionDate(&terminalData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
    
    printf("Test Case 4:\n");
    printf("Input Data: 30/12/2021\n");
    terminalError = getTransactionDate(&terminalData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
}
void isCardExpriedTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: isCardExpried\n");
    
    printf("Test Case 1:\n");
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    for (int i = 0; i<5; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    printf("card expire date: 2024\n");
    printf("terminal year: 2022\n");
    terminalError = isCardExpired(&cardData, &terminalData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", terminalError ? "EXPIRED_CARD" : "TERMINAL_OK");
    
    printf("Test Case 2:\n");
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    for (int i = 0; i< 6; i++)
        cardData.cardExpirationDate[i] = "12/21"[i];
    printf("card expire date: 2021\n");
    printf("terminal year: 2022\n");
    terminalError = isCardExpired(&cardData, &terminalData);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", terminalError ? "EXPIRED_CARD" : "TERMINAL_OK");
}

void getTransactionAmountTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: getTransactionAmount\n");
    
    printf("Test Case 1:\n");
    printf("Input Data: 0\n");
    terminalError = getTransactionAmount(&terminalData);
    printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result: %s\n", terminalError ? "INVALID_AMOUNT" : "TERMINAL_OK");
    
    printf("Test Case 2:\n");
    printf("Input Data: 100\n");
    terminalError = getTransactionAmount(&terminalData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", terminalError ? "INVALID_AMOUNT" : "TERMINAL_OK");
}

void isBelowMaxAmountTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: isBelowMaxAmount\n");
    
    printf("Test Case 1:\n");
    printf("when transaction > max transaction amount\n");
    terminalData.transAmount = 100;
    terminalData.maxTransAmount = 50;
    terminalError = isBelowMaxAmount(&terminalData);
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", terminalError ? "EXCEED_MAX_AMOUNT" : "TERMINAL_OK");
    
    printf("Test Case 2:\n");
    printf("when transaction < max transaction amount\n");
    terminalData.transAmount = 50;
    terminalData.maxTransAmount = 100;
    terminalError = isBelowMaxAmount(&terminalData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", terminalError ? "EXCEED_MAX_AMOUNT" : "TERMINAL_OK");
}

void setMaxAmountTest(void) {
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: setMaxAmount\n");
    
    printf("Test Case 1:\n");
    printf("Input Data: 100\n");
    terminalError = setMaxAmount(&terminalData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", terminalError ? "INVALID_MAX_AMOUNT" : "TERMINAL_OK");
    
    printf("Test Case 2:\n");
    printf("Input Data: 0\n");
    terminalError = setMaxAmount(&terminalData);
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", terminalError ? "INVALID_MAX_AMOUNT" : "TERMINAL_OK");
}

void recieveTransactionDataTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    
    printf("Function Name: recieveTransactionData\n");
    
    printf("Test Case 1:\n");
    printf("with not existing account\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="1111000011110000"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 100;
    terminalData.maxTransAmount = 1000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transState = recieveTransactionData(&transData);
    printf("Expected Result: FRAUD_CARD\n");
    printf("Actual Result: %s\n", transactionStates[transState]);
    
    printf("Test Case 2:\n");
    printf("with exceeded limit\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4929006859824424"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
    terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 4000;
    terminalData.maxTransAmount = 1000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transState = recieveTransactionData(&transData);
    printf("Expected Result: DECLINED_INSUFFECIENT_FUND\n");
    printf("Actual Result: %s\n", transactionStates[transState]);
    
    printf("Test Case 3:\n");
    printf("For a Blocked card\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4716054078699158"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
    terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 100;
    terminalData.maxTransAmount = 1000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transState = recieveTransactionData(&transData);
    printf("Expected Result: DECLINED_STOLEN_CARD\n");
    printf("Actual Result: %s\n", transactionStates[transState]);
    
    printf("Test Case 4:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4560392230689494"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
    terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 100;
    terminalData.maxTransAmount = 1000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transState = recieveTransactionData(&transData);
    printf("Expected Result: APPROVED\n");
    printf("Actual Result: %s\n", transactionStates[transState]);
}

void isValidAccountTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    printf("Function Name: isValidAccountTest\n");
    printf("Test Case 1:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4024007104373104"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    printf("When An account exists\n");
    serverError = isValidAccount(&cardData, &accountReference);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
    
    printf("Test Case 2:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="1111000011110000"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    printf("When An account does not exists\n");
    serverError = isValidAccount(&cardData, &accountReference);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
}

void isBlockedAccountTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    printf("Function Name: isBlockedAccountTest\n");
    printf("Test Case 1:\n");
    accountReference.balance= 3000;
    accountReference.state = RUNNING;
    for (int i = 0; i < 6; i++)
        accountReference.primaryAccountNumber[i] = "4024007104373104"[i];
    printf("When An account is running\n");
    serverError = isBlockedAccount(&accountReference);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
    
    printf("Test Case 2:\n");
    accountReference.balance= 10000;
    accountReference.state = BLOCKED;
    for (int i = 0; i < 6; i++)
        accountReference.primaryAccountNumber[i] = "4532921095940439"[i];
    printf("When An account is not on running state\n");
    serverError = isBlockedAccount(&accountReference);
    printf("Expected Result: BLOCKED_ACCOUNT\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
}

void isAmountAvailableTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    printf("Function Name: isAmountAvailableTest\n");
    printf("Test Case 1:\n");
    accountReference.balance= 3000;
    accountReference.state = RUNNING;
    for (int i = 0; i < 6; i++)
        accountReference.primaryAccountNumber[i] = "4024007104373104"[i];
    terminalData.transAmount = 2000;
    printf("When An account Balance > transaction amount\n");
    serverError = isAmountAvailable(&terminalData, &accountReference);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
    
    printf("Test Case 2:\n");
    accountReference.balance= 3000;
    accountReference.state = RUNNING;
    for (int i = 0; i < 6; i++)
        accountReference.primaryAccountNumber[i] = "4024007104373104"[i];
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 4000;
    
    printf("When An account Balance < transaction amount\n");
    serverError = isAmountAvailable(&terminalData, &accountReference);
    printf("Expected Result: LOW_BALANCE\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
}

void saveTransactionTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    printf("Function Name: saveTransactionTest\n");
    printf("Test Case 1:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4024007104373104"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 4000;
    terminalData.maxTransAmount = 1000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transData.transState = APPROVED;
    serverError = saveTransaction(&transData);
    printf("Expected one record\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
    
    printf("Test Case 2:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4024007104373104"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 8000;
    terminalData.maxTransAmount = 2000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transData.transState = DECLINED_STOLEN_CARD;
    serverError = saveTransaction(&transData);
    printf("Expected two record\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
}

void listSavedTransactionsTest(void){
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");
    printf("Function Name: saveTransactionTest\n");
    printf("Test Case 1:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4024007104373104"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 4000;
    terminalData.maxTransAmount = 1000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transData.transState = APPROVED;
    serverError = saveTransaction(&transData);
    printf("Expected one record\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
    
    printf("Test Case 2:\n");
    for(int i = 0; i < 25; i++)
        cardData.cardHolderName[i] = "Ahmed Mohamed Abdelwahab"[i];
    for(int i = 0; i < 17; i++)
        cardData.primaryAccountNumber[i] ="4024007104373104"[i];
    for (int i = 0; i < 6; i++)
        cardData.cardExpirationDate[i] = "12/24"[i];
    for(int i = 0; i < 11; i++)
        terminalData.transactionDate[i] = "30/12/2022"[i];
    terminalData.transAmount = 8000;
    terminalData.maxTransAmount = 2000;
    transData.cardHolderData = cardData;
    transData.terminalData = terminalData;
    transData.transState = DECLINED_STOLEN_CARD;
    serverError = saveTransaction(&transData);
    printf("Expected two record\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", serverStates[serverError]);
}
