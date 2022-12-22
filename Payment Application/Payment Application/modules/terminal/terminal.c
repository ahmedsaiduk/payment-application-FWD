//
//  terminal.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//

#include "terminal.h"
#include<time.h>
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    uint8_t input[11];
    printf("Please Enter the transaction date[e.g 25/06/2022]: ");
    scanf("%s", input);
    uint8_t count=0;
    
    // number validation
    while(input[count]!= '\0'){
        if(!((input[0] - '0')*10 + (input[1] - '0') <=31 && input[2] == '/' && (input[3] - '0')*10 + (input[4] - '0') <= 12 && input[5] == '/' && (input[6] - '0') * 1000 + (input[7] - '0') * 100 + (input[8] - '0') * 10 + (input[9] - '0') >= 2022)){
            return WRONG_DATE;
        }
        count++;
    }
    if(0){
        return WRONG_DATE;
    }else{
        for(int i=0; i< count ; i++){
            termData->transactionDate[i] = input[i];
        }
        return TERMINAL_OK;
    }
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
