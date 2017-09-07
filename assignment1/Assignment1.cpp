/*
 * Assignment1.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: dwlambiri
 */
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
static char key[keySize_c] = "";
static char message[messageSize_c] = "";
static char eMessage[messageSize_c] = "";
static char dMessage[messageSize_c] = "";

static bool readFile(char* configFileName){
	FILE* fptr = NULL;
	if (configFileName == NULL) {
		return false;
	} else {
		fptr = fopen(configFileName, "r");
		if (fptr == NULL) {
			return false;
		} //end-of-if(fptr == NULL)
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
		} //end-of-if(key[i] == '\n')
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

static bool encrypt(){
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
		} //end-of-for
	} //end-of-for
	return true;
}

static bool dencrypt(){
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
			dMessage[i*keySize + j] = eMessage[i*keySize + j] - (key[j] - 'A');
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

	if (readFile(configFileName) == false) {
		return 2;
	} //end-of-if(readFile(configFileName) == false)


	std::cout << key << std::endl;
	std::cout << message << std::endl;

	if (encrypt() == false) {
		return 3;
	} //end-of-if(encrypt() == false)

	std::cout << eMessage << std::endl;

	if (dencrypt() == false) {
		return 3;
	} //end-of-if(encrypt() == false)

	std::cout << dMessage << std::endl;
	if (strcmp(message, dMessage) == 0) {
		std::cout << "Message is the same" << std::endl;
	} //end-of-if(strcmp(message, dMessage) == 0)
	return 0;
}


