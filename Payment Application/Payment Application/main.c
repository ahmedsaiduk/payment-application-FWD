//
//  main.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//

#include <stdio.h>
#include <stdbool.h>
#include "modules/card/card.h"
#include "modules/terminal/terminal.h"


ST_cardData_t cardData;
ST_terminalData_t terminalData;
EN_cardError_t cardError;
EN_terminalError_t terminalError;

int main(int argc, const char * argv[]) {
    printf("Tester Name: Ahmed Mohamed Abdelwahab Said\n");

//  ======================getCardHolderName==================================
//
//    printf("Function Name: getCardHolderName\n");
//
//    printf("Test Case 1:\n");
//    printf("Input Data: Ahmed Mohamed Abdelwahab\n");
//    getCardHolderName(&cardData);
//    printf("Expected Result: CARD_OK\n");
//    printf("Actual Result: ");
//    printf("Actual Result: %s\n", cardError ? "WRONG_NAME" : "CARD_OK");
//
//    printf("Test Case 2:\n");
//    printf("Input Data: $\n");
//    cardError = getCardHolderName(&cardData);
//    printf("Expected Result: WRONG_NAME\n");
//    printf("Actual Result: %s\n", cardError ? "WRONG_NAME" : "CARD_OK" );
//
//    printf("Test Case 3:\n");
//    printf("Input Data: Ahmed Mohamed Abdelwahab Said\n");
//    cardError = getCardHolderName(&cardData);
//    printf("Expected Result: WRONG_NAME\n");
//    printf("Actual Result: %s\n", cardError ? "WRONG_NAME" : "CARD_OK" );

//  ======================getCardExpiryDate======================================

//    printf("Function Name: getCardExpiryDate\n");
//
//    printf("Test Case 1:\n");
//    printf("Input Data: 11/11\n");
//    cardError = getCardExpiryDate(&cardData);
//    printf("Expected Result: CARD_OK\n");
//    printf("Actual Result: %s\n", cardError ? "WRONG_EXP_DATE" : "CARD_OK");
//
//    printf("Test Case 2:\n");
//    printf("Input Data: 13/11\n");
//    cardError = getCardExpiryDate(&cardData);
//    printf("Expected Result: WRONG_EXP_DATE\n");
//    printf("Actual Result: %s\n", cardError ? "WRONG_EXP_DATE" : "CARD_OK");
//
//    printf("Test Case 3:\n");
//    printf("Input Data: . \n");
//    cardError = getCardExpiryDate(&cardData);
//    printf("Expected Result: WRONG_EXP_DATE\n");
//    printf("Actual Result: %s\n", cardError ? "WRONG_EXP_DATE" : "CARD_OK");
    
//  ============================getCardPAN====================================
//        printf("Function Name: getCardPAN\n");
//
//        printf("Test Case 1:\n");
//        printf("Input Data: 4929139493758482\n");
//        cardError = getCardPAN(&cardData);
//        printf("Expected Result: CARD_OK\n");
//        printf("Actual Result: %s\n", cardError ? "WRONG_PAN" : "CARD_OK");
//
//        printf("Test Case 2:\n");
//        printf("Input Data: 492913949375\n");
//        cardError = getCardPAN(&cardData);
//        printf("Expected Result: WRONG_PAN\n");
//        printf("Actual Result: %s\n", cardError ? "WRONG_PAN" : "CARD_OK");
//
//        printf("Test Case 3:\n");
//        printf("Input Data: ffff\n");
//        cardError = getCardPAN(&cardData);
//        printf("Expected Result: WRONG_PAN\n");
//        printf("Actual Result: %s\n", cardError ? "WRONG_PAN" : "CARD_OK");
    
    
//  ============================getTransactionDateTest====================================
//    printf("Function Name: getTransactionDate\n");
//
//    printf("Test Case 1:\n");
//    printf("Input Data: 25/06/2022\n");
//    terminalError = getTransactionDate(&terminalData);
//    printf("Expected Result: TERMINAL_OK\n");
//    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
//
//
//    printf("Test Case 2:\n");
//    printf("Input Data: 25/30/2022\n");
//    terminalError = getTransactionDate(&terminalData);
//    printf("Expected Result: WRONG_DATE\n");
//    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
//
//    printf("Test Case 3:\n");
//    printf("Input Data: 32/12/2022\n");
//    terminalError = getTransactionDate(&terminalData);
//    printf("Expected Result: WRONG_DATE\n");
//    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
//
//    printf("Test Case 4:\n");
//    printf("Input Data: 30/12/2021\n");
//    terminalError = getTransactionDate(&terminalData);
//    printf("Expected Result: WRONG_DATE\n");
//    printf("Actual Result: %s\n", terminalError ? "WRONG_DATE" : "TERMINAL_OK");
//  ============================isCardExpriedTest====================================
    

    printf("Function Name: isCardExpried\n");
    
    printf("Test Case 1:\n");
    ST_cardData_t cardData = {"","","12/24"};
    ST_terminalData_t terminalData = {0.0,0.0,"30/12/2022"};
    printf("card expire date: 2024\n");
    printf("terminal year: 2022\n");
    terminalError = isCardExpired(&cardData, &terminalData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", terminalError ? "EXPIRED_CARD" : "TERMINAL_OK");
    
//    printf("Test Case 1:\n");
//    ST_cardData_t cardData = {"","","12/21"};
//    ST_terminalData_t terminalData = {0.0,0.0,"30/12/2022"};
//    printf("card expire date: 2021\n");
//    printf("terminal year: 2022\n");
//    terminalError = isCardExpired(&cardData, &terminalData);
//    printf("Expected Result: EXPIRED_CARD\n");
//    printf("Actual Result: %s\n", terminalError ? "EXPIRED_CARD" : "TERMINAL_OK");
    
}
