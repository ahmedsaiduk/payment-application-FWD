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



void appStart(void){
    getCardHolderName(&a_cardData);
    getCardExpiryDate(&a_cardData);
    getCardPAN(&a_cardData);

    getTransactionDate(&a_termData);
    isCardExpired(&a_cardData, &a_termData);
    getTransactionAmount(&a_termData);
    setMaxAmount(&a_termData);
    isBelowMaxAmount(&a_termData);

    a_transData.cardHolderData = a_cardData;
    a_transData.terminalData = a_termData;

    recieveTransactionData(&a_transData);
    saveTransaction(&a_transData);
}
