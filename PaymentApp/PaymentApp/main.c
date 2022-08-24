#include"Std_types.h"
#include<stdio.h>
#include "Card.h"
#include"Terminal.h"

int main() {

    ST_cardData_t card;
    ST_terminalData_t date;
    EN_cardError_t result,r2,r3;
    EN_terminalError_t r4;
    result= getCardHolderName(&card);
    printf("result = %d\n", result);
    r2 = getCardExpiryDate(&card);
    printf("result = %d\n", r2);
    // Write C code here
    r3=getCardPAN(&card);
    printf("result = %d\n", r3);
    r4 = getTransactionDate(&date);
    printf("result = %d\n", r4);
    return 0;
}