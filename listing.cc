// Compiler Theory and Design
// Dr. Duane J. Jarc

// This file contains the bodies of the functions that produces the compilation
// listing

#include <cstdio>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

#include "listing.h"

static int lineNumber;
static queue<string> errors;
static int totalErrors = 0;
static int lexicalErrors = 0;
static int syntaxErrors = 0;
static int semanticErrors = 0;

static void displayErrors();

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ", lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ", lineNumber);
}

int lastLine()
{
	printf("\r");
	displayErrors();
	printf("     \n");
	if (totalErrors == 0)
	{
		printf("Compiled Successfully!");
	}
	else
	{
		printf("Lexical Errors: %d\n", lexicalErrors);
		printf("Syntax Errors: %d\n", syntaxErrors);
		printf("Semantic Errors: %d\n", semanticErrors);
	}
	return totalErrors;
}

void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = {"Lexical Error, Invalid Character ", "",
						 "Semantic Error, ", "Semantic Error, Duplicate Identifier: ",
						 "Semantic Error, Undeclared "};

	std::size_t lexFound = messages[errorCategory].find("Lexical");
	std::size_t semFound = messages[errorCategory].find("Semantic");
	std::size_t synFound = messages[errorCategory].find("Syntax");

	if (lexFound != string::npos)
	{
		lexicalErrors++;
	}
	if (semFound != string::npos)
	{
		semanticErrors++;
	}
	if (synFound != string::npos)
	{
		syntaxErrors++;
	}
	errors.push(messages[errorCategory] + message);
	totalErrors++;
}

void displayErrors()
{
	while (!errors.empty())
	{
		cout << " " << errors.front() << endl;
		errors.pop();
	}
	// if (error != "")
	// 	printf("%s\n", error.c_str());
	// error = "";
}
