#include"Std_types.h"
#include "Terminal.h"


//This function will ask for the transaction dataand store it in terminal data.
//Transaction date is 10 characters string in the format DD / MM / YYYY, e.g 25 / 06 / 2022.
//If the transaction date is NULL, less than 10 characters or wrong format will return WRONG_DATE error, else return OK.
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t err= OK;
	uint8_t day;
	uint8_t month;
	uint8_t year;
	gets(termData->transactionDate);
	if (termData->transactionDate[10] != '\0')
	{
		err = WRONG_DATE;
	}
	else
	{
		day = (termData->transactionDate[0] - '0') * 10 + (termData->transactionDate[1] - '0');
		month = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
		year = (termData->transactionDate[6] - '6') * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10+(termData->transactionDate[9] - '0');
		if (day<1 || day> 30 || termData->transactionDate[2] != '/'||month < 1 || month>12 || termData->transactionDate[5] != '/' || (year > 2050 || year < 0)) {
			err = WRONG_DATE;
		}
		else
		{
			err = OK;
		}
	}
	return err;

}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	int cardmonth = (cardData.cardExpirationDate[0] - '0') * 10 + cardData.cardExpirationDate[1] - '0';
	int cardyear = (cardData.cardExpirationDate[3] - '0') * 10 + cardData.cardExpirationDate[4] - '0' + 2000;
	int terminalmonth = (termData.transactionDate[3] - '0') * 10 + termData.transactionDate[4] - '0';
	int terminalyear = (termData.transactionDate[6] - '0') * 1000 + (termData.transactionDate[7] - '0') * 100 + (termData.transactionDate[8] - '0') * 10 + +termData.transactionDate[9] - '0';
	if (terminalyear > cardyear) {
		return EXPIRED_CARD;
	}
	if (terminalyear == cardyear && terminalmonth > cardmonth) {
		return EXPIRED_CARD;
	}
	return OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t err= OK;
	float amount = -1;
	scanf_s("%f", &amount);
	if (amount <= 0) {
		err = INVALID_AMOUNT;
	}
	termData->transAmount = amount;
	return err;
}
//This function compares the transaction amount with the terminal max amount.
//If the transaction amount is larger than the terminal max amount will return EXCEED_MAX_AMOUNT, else return OK.
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t err = OK;
	if (termData->transAmount > termData->maxTransAmount) {
		err =  EXCEED_MAX_AMOUNT;
	}
	return err;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t err = OK;
	float mxamount;
	scanf("%f", &mxamount);
	if (mxamount <= 0) {
		err = INVALID_MAX_AMOUNT;
	}
	termData->maxTransAmount = mxamount;
	return err;
}
