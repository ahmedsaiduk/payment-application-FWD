//
//  terminal.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//

#include "terminal.h"

const char *terminalStates[] = {"TERMINAL_OK", "WRONG_DATE", "EXPIRED_CARD", "INVALID_CARD", "INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT"};
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    uint8_t input[11];
    printf("Please Enter the transaction date[e.g 25/06/2022]: ");
    scanf("%s", input);
    u_int count=0;
    
    // number validation
    while(input[count]!= '\0'){
        if(!((input[0] - '0')*10 + (input[1] - '0') <=31 && input[2] == '/' && (input[3] - '0')*10 + (input[4] - '0') <= 12 && input[5] == '/' && (input[6] - '0') * 1000 + (input[7] - '0') * 100 + (input[8] - '0') * 10 + (input[9] - '0') >= 2022)){
            return WRONG_DATE;
        }
        count++;
    }
    if(count == 10){
        for(int i=0; i< count ; i++){
            termData->transactionDate[i] = input[i];
        }
    }else{
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    uint8_t Exp_year = (cardData->cardExpirationDate[3]-'0') *10 + (cardData->cardExpirationDate[4]-'0');
    uint8_t Term_year = (termData->transactionDate[8]-'0') * 10 + (termData->transactionDate[9]-'0');
    
    uint8_t Exp_month = (cardData->cardExpirationDate[0]-'0') *10 + (cardData->cardExpirationDate[1]-'0');
    uint8_t Term_month = (termData->transactionDate[3]-'0') * 10 + (termData->transactionDate[4]-'0');
    
    if(Exp_year < Term_year){
        return EXPIRED_CARD;
    }else if(Exp_year==Term_year){
        if(Exp_month < Term_month){
            return EXPIRED_CARD;
        } else{
            return TERMINAL_OK;
        }
    }else{
        return TERMINAL_OK;
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){

    float input;
    printf("Please enter the transaction amount [>0]: ");
    scanf("%f", &input);
    
    if(input <= 0){
        return INVALID_AMOUNT;
    } else{
        termData->transAmount = input;
        return TERMINAL_OK;
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }else{
        return TERMINAL_OK;
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    
    float input;
    printf("Please enter the Max amount: ");
    scanf("%f", &input);
    
    if(input <= 0){
        return INVALID_MAX_AMOUNT;
    } else{
        termData->maxTransAmount = input;
        return TERMINAL_OK;
    }
}
