//
//  card.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//

#include "card.h"
#include <stdlib.h>
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    char input[25];
    printf("Please enter the card holder name [20-24]:");
    scanf("%[^\n]", input);

    uint8_t count=0, i=0;
    
    //Validate input alphabet
    while(input[i]!= '\0'){
        if((input[i]>='a' && input[i]<= 'z') || (input[i]>='A' && input[i]<= 'Z') || (input[i] == ' ')){
            count++;
        }else {
            return WRONG_NAME;
        }
        i++;
    }
    
    if(count < 20 || count > 24){
        return WRONG_NAME;
    }else{
        for(int i=0; i< count ; i++){
            cardData->cardHolderName[i] = input[i];
        }
        return CARD_OK;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    uint8_t input[6];
    printf("Please Enter the card expiry date [MM/YY]: ");
    scanf("%s", input);
    uint8_t count = 0;
    
    // input count
    for (int i = 0; i <= 5; i++) {
        if (input[i] != '\n') {
            count++;
        }else{
            return WRONG_EXP_DATE;
        }
    }
    
    if((input[0] - '0')*10 + (input[1] - '0') <=12 && input[2] == '/' && (input[3] - '0')*10 + (input[4] - '0') <= 31){
        for(int i=0; i< 6; i++){
            cardData->cardExpirationDate[i] = input[i];
        }
        return CARD_OK;
    }else{
        return WRONG_EXP_DATE;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    uint8_t input[20];
    printf("Please Enter the PAN number[16-19]: ");
    scanf("%s", input);
    uint8_t count=0;
    
    // number validation
    while(input[count]!= '\0'){
        if(!(input[count] > '0' || input[count] < '9')){
            return WRONG_PAN;
        }
        count++;
    }
    
    if(count < 16 || count > 20){
        return WRONG_PAN;
    }else{
        for(int i=0; i< count ; i++){
            cardData->primaryAccountNumber[i] = input[i];
        }
        return CARD_OK;
    }
}


