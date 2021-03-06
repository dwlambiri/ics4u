/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   Assignment1.cpp
 *	Course: ICS4U
 *	Date:   Sep 6, 2017
 *
 *	Purpose:
 *		Assignment 1, encoding messages
 *
 *	Usage:
 *		For a usage message see usage function below
 *
 *	Revision History:
 *
 *	Known Issues:
 *		None
 *****************************************************************************/

#include <iostream>
#include <string.h>
#include <stdio.h>

static void
Usage(void) {
	std::cout<< "Program Options:" << 12 << "   " << 23 << "   " << 45 << std::endl;
	std::cout<< "  -c configFileName - selects the config file, if no config file present, default is config.txt"<< std::endl;
	std::cout<< "  -h - displays command line parameters" << std::endl;

} // end-of-function Usage


static char* configFileName;
static const int keySize_c = 200;
static const int messageSize_c = 1000;
static char keyBuffer[keySize_c] = "";
static char readBuffer[messageSize_c] = "";
static char messageBuffer[messageSize_c] = "";
static char eMessageBuffer[messageSize_c] = "";
static char dMessageBuffer[messageSize_c] = "";

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Sep 11, 2017
   @mname   textOnly
   @details
	  \n
  --------------------------------------------------------------------------
 */
static bool
textOnly(char message[], char messageText[]) {
	int i = 0;
	int j = 0;
	while(message[i]) {
		if ((message[i] >= 'A') && (message[i] <= 'Z')) {
			messageText[j] = message[i];
			j++;
		} //end-of-if
		i++;
	} //end-of-while
	messageText[j] = 0;
	return true;
} // end-of-method textOnly



static bool readFile(char* configFileName, char key[], char message[]){
	FILE* fptr = NULL;
	if (configFileName == NULL) {
		return false;
	} else {
		fptr = fopen(configFileName, "r");
		if (fptr == NULL) {
			return false;
		} //end-of-if
	}
	//read the file contents
	if ( fgets (key , keySize_c , fptr) == NULL ){
		std::cerr << "ERROR: Cannot read key" << std::endl;
		fclose(fptr);
		return false;
	}

	for (int i = 0; i < keySize_c; i++ ) {
		if (key[i] == '\n') {
			key[i] = 0;
			break;
		} //end-of-if
	} //end-of-for

	if ( fgets (message , messageSize_c , fptr) == NULL ){
		std::cerr << "ERROR: Cannot read message" << std::endl;
		fclose(fptr);
		return false;
	}


	for (int i = 0; i < messageSize_c; i++ ) {
		if (message[i] == '\n') {
			message[i] = 0;
			break;
		} //end-of-if(message[i] == '\n')
	} //end-of-for

	fclose(fptr);
	return true;
}

static bool encrypt(char key[], char message[], char eMessage[]){
	int keySize = strlen(key);
	int messageSize = strlen(message);

	int numLoops = messageSize / keySize;
	int remainder = messageSize % keySize;
	if (remainder != 0) {
		numLoops++;
	} //end-of-if(remainder != 0)

	for (int i = 0; i < numLoops; i++ ) {
		for (int j = 0; j < keySize; j++ ) {
			//key[j];
			//message[i*keySize + j];
			if (message[i*keySize + j] == 0) {
				return true;
			} //end-of-if(message[i*keySize + j] == 0;)
			eMessage[i*keySize + j] = message[i*keySize + j] + (key[j] - 'A');
			if(eMessage[i*keySize + j] > 'Z' ) {
				eMessage[i*keySize + j] -= 'Z' + 1 - 'A';
			}
		} //end-of-for
	} //end-of-for
	return true;
}

static bool dencrypt(char key[], char eMessage[], char dMessage[]){
	int keySize = strlen(key);
	int messageSize = strlen(eMessage);

	int numLoops = messageSize / keySize;
	int remainder = messageSize % keySize;
	if (remainder != 0) {
		numLoops++;
	} //end-of-if(remainder != 0)

	for (int i = 0; i < numLoops; i++ ) {
		for (int j = 0; j < keySize; j++ ) {
			//key[j];
			//message[i*keySize + j];
			if (eMessage[i*keySize + j] == 0) {
				return true;
			} //end-of-if
			dMessage[i*keySize + j] = eMessage[i*keySize + j] - (key[j] - 'A');
			if (dMessage[i*keySize + j] < 'A') {
				dMessage[i*keySize + j] += 'Z' + 1 - 'A';
			} //end-of-if(dMessage[i*keySize + j] < 'A')
		} //end-of-for
	} //end-of-for
	return true;
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Sep 6, 2017
   @name    main
   @param   argc number of command line arguments
   @param   argv command line arguments
   @return  the return code
   @details
	The main function of the program.
	\n
  --------------------------------------------------------------------------
 */
int
main(int argc, char **argv) {
	for (int  param = 1; param < argc; param++ ) {
		if (strcmp(argv[param], "-c") == 0) {
			if (++param < argc) {
				configFileName = argv[param];
			} //end-of-if(++param < argc)
		} else if (strcmp(argv[param], "-h") == 0) {
			Usage();
			return 1;
		}
	}

	if (configFileName == NULL) {
		return 1;
	} //end-of-if(configFileName == NULL)

	if (readFile(configFileName, keyBuffer, readBuffer) == false) {
		return 2;
	} //end-of-if(readFile(configFileName) == false)


	std::cout << keyBuffer << std::endl;
	std::cout << readBuffer << std::endl;

	if (textOnly(readBuffer, messageBuffer) == false) {
		return 4;
	} //end-of-if(textOnly(readBuffer, messageBuffer) == false)

	std::cout << messageBuffer << std::endl;

	if (encrypt(keyBuffer, messageBuffer, eMessageBuffer) == false) {
		return 3;
	} //end-of-if(encrypt() == false)

	std::cout << eMessageBuffer << std::endl;

	if (dencrypt(keyBuffer, eMessageBuffer, dMessageBuffer) == false) {
		return 3;
	} //end-of-if(encrypt() == false)

	std::cout << dMessageBuffer << std::endl;
	if (strcmp(messageBuffer, dMessageBuffer) == 0) {
		std::cout << "Message is the same" << std::endl;
	} //end-of-if(strcmp(message, dMessage) == 0)
	return 0;
}


