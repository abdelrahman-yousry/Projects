
#include "Server.h"

ST_accountsDB_t AccountDB[255];
int index = -1;
void readAccountDB(void) {
	FILE* ptr;
	ptr = fopen("./AccountsDB.txt", "r");
	if (!ptr) {
		printf("'AccountsDB.txt' File Corrupted/Not Found.\n");
		return;
	}
	uint8_t pan[20];
	float amount;
	int i = 0, j;
	while (fscanf(ptr, "%f %s", &amount, pan)) {
		if (i > 0 && AccountDB[i - 1].balance == amount && AccountDB[i - 1].primaryAccountNumber[6] == pan[6]) {
			break;
		}
		AccountDB[i].balance = amount;
		for (j = 0; j < 20; j++) {
			AccountDB[i].primaryAccountNumber[j] = pan[j];
		}
		i++;
	}
	fclose(ptr);
}

void updateAccountDB(void)
{
	FILE* ptr;
	int i;
	ptr = fopen("./AccountsDB.txt", "w");
	if (!ptr) {
		printf("'AccountsDB.txt' File Corrupted/Not Found.\n");
		return;
	}
	for (i = 0; i < 255; i++) {
		if (AccountDB[i].primaryAccountNumber[0] == '\0') {
			break;
		}
		fprintf(ptr, "%f %s\n", AccountDB[i].balance, AccountDB[i].primaryAccountNumber);
	}
}


EN_transStat_t recieveTransactionData(ST_transaction* transData)
{
	EN_transStat_t state;
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = DECLINED_STOLEN_CARD;
		state = DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		state = DECLINED_INSUFFECIENT_FUND;
	}
	transData->transState = APPROVED;
	AccountDB[index].balance -= transData->terminalData.transAmount;
	if (saveTransaction(transData) == SAVING_FAILED) {
		state = INTERNAL_SERVER_ERROR;
	}
	return state;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	EN_serverError_t err = OK;
	uint8_t* PanNo = cardData->primaryAccountNumber;
	char founded = 0;
	int i, j;
	for (i = 0; i < 255; i++) {
		if (AccountDB[i].primaryAccountNumber[0] != '\0') {
			char IsEqual = 1;
			for (j = 0; j < 20; j++) {
				if (AccountDB[i].primaryAccountNumber[j] != PanNo[j]) {
					IsEqual = 0;
					break;
				}
			}
			if (IsEqual) {
				founded = 1;
				index = i;
				break;
			}
		}
		else {
			break;
		}
	}
	if (!founded) {
		err = ACCOUNT_NOT_FOUND;
	}
	return err;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	EN_serverError_t err = OK;
	if (AccountDB[index].balance < termData->transAmount) {
		err= LOW_BALANCE;
	}
	return err;
}
EN_serverError_t saveTransaction(ST_transaction* transData)
{

}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData)
{

}