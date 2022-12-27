//
//  application.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//

#include "application.h"

// Three struct variables that save data over the whole process
ST_cardData_t a_cardData;
ST_terminalData_t a_termData;
ST_transaction_t a_transData;
EN_terminalError_t a_terminalDateError;
EN_terminalError_t a_terminalCardExpireError;
EN_terminalError_t a_terminalBelowAmountError;
EN_terminalError_t a_terminalMaxAmountError;
EN_terminalError_t a_terminalTransAmountError;
EN_transState_t a_transState;
EN_cardError_t cardHolderNameError;
EN_cardError_t cardExpiryError;
EN_cardError_t cardPanError;



void appStart(void){
    cardHolderNameError = getCardHolderName(&a_cardData);
    cardExpiryError = getCardExpiryDate(&a_cardData);
    cardPanError = getCardPAN(&a_cardData);

    a_terminalDateError = getTransactionDate(&a_termData);
    a_terminalCardExpireError = isCardExpired(&a_cardData, &a_termData);
    a_terminalTransAmountError = getTransactionAmount(&a_termData);
    a_terminalMaxAmountError = setMaxAmount(&a_termData);
    a_terminalBelowAmountError = isBelowMaxAmount(&a_termData);

    a_transData.cardHolderData = a_cardData;
    a_transData.terminalData = a_termData;

    
    a_transState = recieveTransactionData(&a_transData);
    a_transData.transState = cardHolderNameError == 0 && cardExpiryError == 0 && cardPanError == 0 && a_terminalDateError == 0 && a_terminalCardExpireError == 0 && a_terminalTransAmountError == 0 && a_terminalMaxAmountError == 0 && a_terminalBelowAmountError == 0 ? a_transState : INTERNAL_SERVER_ERROR ;
    saveTransaction(&a_transData);
}
