#include "Std_types.h"
#include <stdio.h>
#include "Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t err;
	uint8_t idx;
	uint8_t counter = 0;
	gets(cardData->cardHolderName);
	for (idx = 0; cardData->cardHolderName[idx] != '\0'; idx++)
	{
		counter++;

	}
	if (counter > 24 || counter < 20 || counter == NULL)
	{
	
		err = WRONG_NAME;

	}
	else
	{
		
		err = OK;
	}
	return err;
}

//This function will ask for the card expiry dateand store it in card data.
//Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
//If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return WRONG_EXP_DATE error, else return OK.

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t month;
	uint8_t year;
	EN_cardError_t err;
	gets(cardData->cardExpirationDate);
	if (cardData->cardExpirationDate[5] != '\0')
	{
		err = WRONG_EXP_DATE;
	}
	else
	{
		month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
		year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
		if (month < 1 || month>12 || cardData->cardExpirationDate[2] != '/' || (year > 99 || year < 0)) {
			err= WRONG_EXP_DATE;
		}
		else
		{
			err = OK;
		}
	}
	return err;

}
//This function will ask for the card's Primary Account Number and store it in card data.
//PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
//If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error, else return OK.
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t err= OK;
	uint8_t counter=0;
	uint8_t idx;
	gets(cardData->primaryAccountNumber);
	for (idx = 0; cardData->primaryAccountNumber[idx] != '\0'; idx++)
	{
		if (isdigit(cardData->primaryAccountNumber[idx]))
		{
			counter++;
		}
		else
		{
			err = WRONG_PAN;
		}

	}
	if (err == WRONG_PAN)
	{

		return err;

	}
	return err;

}