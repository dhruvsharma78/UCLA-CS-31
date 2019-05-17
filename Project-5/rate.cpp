//
//  main.cpp
//  rate
//
//  Created by Dhruv Sharma on 11/12/18.
//  Copyright © 2018 Dhruv Sharma. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cctype>
#include <cstring>

using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 251;

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns);
void removeElement(char word1[][MAX_WORD_LENGTH+1],
               	   char word2[][MAX_WORD_LENGTH+1],
                   int separation[]);
int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns);
void removeChar(char document[], int documentLength, int index);


int main(){

	//TESTING makeProper
	char word1A[][MAX_WORD_LENGTH+1] = {"mad" , "deranged" , "NEFARIOUS"   ,
								   	    "kid" , "have"     , "half-witted" ,
								   	    "hi"  , "car"};


	char word2A[][MAX_WORD_LENGTH+1] = {"scientist"  , "robot" , "PLOT" ,
								        "AdUlT"      , "mad"   , "half" ,
								    	"hello"      , "bike"};
	int separationA[] = {1 , 3 , 0 ,
						 2 ,12 , 4 ,
						 12, -3};

    char word1B[][MAX_WORD_LENGTH+1] = {"mad"        , ""   , "NEFARIOUS" ,
								   	   "halfwitted"  , ""};
	char word2B[][MAX_WORD_LENGTH+1] = {"scientist"  , ""   , "PLOT"      ,
								       "groan"       , "mad"};
	int separationB[] = {1 , 3 , 0 ,
					     2 ,12};

	char word1C[][MAX_WORD_LENGTH+1] = {"m@d", "have", "123GO", "UCLA" };
	char word2C[][MAX_WORD_LENGTH+1] = {"tin", "some", "groan", "1234" };
	int separationC[] =                {1    , -1    , 4      , 12};

	char word1D[][MAX_WORD_LENGTH+1] = {"mad", "have", "great", "UCLA", "hi"};
	char word2D[][MAX_WORD_LENGTH+1] = {"tin", "some", "groan", "UCBB", "by"};
	int separationD[] =                {1    , -1    , 4      , -12   , 2};

	char word1E[][MAX_WORD_LENGTH+1] = {"mad" , "deranged" , "NEFARIOUS"   ,
								   	    "kid" , "have"     , "half-witted" ,
								   	    "hi"  , "car"};


	char word2E[][MAX_WORD_LENGTH+1] = {"scientist"  , "robot" , "PLOT" ,
								        ""           , "mad"   , "half" ,
								    	"hello"      , "bike"};
	int separationE[] = {1 , 3 , 0 ,
						 2 ,-12 , 4 ,
						 12, -3};

	char word1F[][MAX_WORD_LENGTH+1] = {"mad" , "deranged" , "scientist"   ,
								   	    "kid" , "hello"    , "halfwitted" ,
								   	    "hi"  , "mad"};

	char word2F[][MAX_WORD_LENGTH+1] = {"scientist"  , "robot" , "mad"  ,
								        "AdUlT"      , "hi"    , "half" ,
								    	"hello"      , "scientist" };
	int separationF[] = {1 , 3 , 10 ,
						 2 , 1 , 4  , 
						 12, 13};

	char word1G[][MAX_WORD_LENGTH+1] = {"MAD", "GREAT", "HI"};
	char word2G[][MAX_WORD_LENGTH+1] = {"tin", "some" , "by"};
	int separationG[] =                {1    , 4      , 2};

	char word1H[][MAX_WORD_LENGTH+1] = {"mad", "have", "tin", "UCLA" };
	char word2H[][MAX_WORD_LENGTH+1] = {"tin", "some", "mad", "UCLA" };
	int separationH[] =                {1    , 1     , 1      , 12};

	char word1I[][MAX_WORD_LENGTH+1] = {"mad" , "deranged" , "scientist"   ,
								   	    "kid" , "hello"    , "halfwitted" ,
								   	    "him" , "mad"};

	char word2I[][MAX_WORD_LENGTH+1] = {"scientist"  , "robot" , "mad"  ,
								        "AdUlT"      , "hi"    , "half" ,
								    	"hello"      , "scientist" };
	int separationI[] = {1 , 3 , 10 ,
						 2 , 1 , 4  , 
						 12, 13};

	//TEST 1
	assert(makeProper(word1A,word2A,separationA,5) == 5 &&
			!strcmp(word1A[0],"mad")       && !strcmp(word1A[1],"deranged") && !strcmp(word1A[2],"nefarious") &&
			!strcmp(word1A[3],"kid")       && !strcmp(word1A[4],"have")     &&

			!strcmp(word2A[0],"scientist") && !strcmp(word2A[1],"robot")    && !strcmp(word2A[2],"plot")      &&
			!strcmp(word2A[3],"adult")     && !strcmp(word2A[4],"mad")      &&

			separationA[0] == 1            && separationA[1] == 3           && separationA[2] == 0            &&
			separationA[3] == 2            && separationA[4] == 12);

	//TEST 2
	assert(makeProper(word1C,word2C,separationC,4) == 0);

	//TEST 3
	assert(makeProper(word1A,word2A,separationA,7) == 6 &&
			!strcmp(word1A[0],"mad")       && !strcmp(word1A[1],"deranged") && !strcmp(word1A[2],"nefarious") &&
			!strcmp(word1A[3],"kid")       && !strcmp(word1A[4],"have")     && !strcmp(word1A[5],"hi")        &&

			!strcmp(word2A[0],"scientist") && !strcmp(word2A[1],"robot")    && !strcmp(word2A[2],"plot")      &&
			!strcmp(word2A[3],"adult")     && !strcmp(word2A[4],"mad")      && !strcmp(word2A[5],"hello")     &&

			separationA[0] == 1            && separationA[1] == 3           && separationA[2] == 0            &&
			separationA[3] == 2            && separationA[4] == 12          && separationA[5] == 12);

	//TEST 4
	assert(makeProper(word1B,word2B,separationB,5) == 3 &&
			!strcmp(word1B[0],"mad")       && !strcmp(word1B[1],"nefarious") && !strcmp(word1B[2],"halfwitted") &&	

			!strcmp(word2B[0],"scientist") && !strcmp(word2B[1],"plot")      && !strcmp(word2B[2],"groan")      &&

			separationB[0] == 1            && separationB[1] == 0            && separationB[2] == 2          );	

	//TEST 5
	assert(makeProper(word1D,word2D,separationD,5) == 3 &&
			!strcmp(word1D[0],"mad") && !strcmp(word1D[1],"great") && !strcmp(word1D[2],"hi") &&	

			!strcmp(word2D[0],"tin") && !strcmp(word2D[1],"groan") && !strcmp(word2D[2],"by") &&

			separationB[0] == 1            && separationD[1] == 4  && separationD[2] == 2);

	//TEST 6 and 7
	assert(makeProper(word1E,word2E,separationE,8) == 4 &&
			!strcmp(word1E[0],"mad")       && !strcmp(word1E[1],"deranged") && !strcmp(word1E[2],"nefarious") &&
			!strcmp(word1E[3],"hi")        &&

			!strcmp(word2E[0],"scientist") && !strcmp(word2E[1],"robot")    && !strcmp(word2E[2],"plot")      &&
			!strcmp(word2E[3],"hello")     && 

			separationE[0] == 1            && separationE[1] == 3           && separationE[2] == 0            &&
			separationE[3] == 12);

	//TEST 8
	assert(makeProper(word1C,word2C,separationC,-5) == 0);

	//TEST 9
	assert(makeProper(word1C,word2C,separationC,0) == 0);

	//TEST 10
	assert(makeProper(word1G,word2G,separationG,3) == 3 &&
			!strcmp(word1G[0],"mad") && !strcmp(word1G[1],"great") && !strcmp(word1G[2],"hi") &&	

			!strcmp(word2G[0],"tin") && !strcmp(word2G[1],"some")  && !strcmp(word2G[2],"by") &&

			separationG[0] == 1      && separationG[1] == 4        && separationG[2] == 2);

	//TEST 11
	assert(makeProper(word1F,word2F,separationF,6) == 5 &&
			!strcmp(word1F[0],"deranged")   && !strcmp(word1F[1],"scientist")  && !strcmp(word1F[2],"kid")   &&
			!strcmp(word1F[3],"hello")      && !strcmp(word1F[4],"halfwitted") &&

			!strcmp(word2F[0],"robot")      && !strcmp(word2F[1],"mad")        && !strcmp(word2F[2],"adult") &&
			!strcmp(word2F[3],"hi")         && !strcmp(word2F[4],"half")       &&

			separationF[0] == 3             && separationF[1] == 10            && separationF[2] == 2         &&
			separationF[3] == 1             && separationF[4] == 4);

	//TEST 12
	assert(makeProper(word1H,word2H,separationH,4) == 3 &&
			!strcmp(word1H[0],"mad") && !strcmp(word1H[1],"have") && !strcmp(word1H[2],"ucla") &&	

			!strcmp(word2H[0],"tin") && !strcmp(word2H[1],"some") && !strcmp(word2H[2],"ucla") &&

			separationH[0] == 1      && separationH[1] == 1       && separationH[2] == 12);

	//TEST 13
	assert(makeProper(word1I,word2I,separationI,8) == 6 &&
			!strcmp(word1I[0],"deranged")   && !strcmp(word1I[1],"kid")   && !strcmp(word1I[2],"hello")         &&
			!strcmp(word1I[3],"halfwitted") && !strcmp(word1I[4],"him")   && !strcmp(word1I[5],"mad")           &&

			!strcmp(word2I[0],"robot")      && !strcmp(word2I[1],"adult") && !strcmp(word2I[2],"hi")            &&
			!strcmp(word2I[3],"half")       && !strcmp(word2I[4],"hello") && !strcmp(word2I[5],"scientist")     &&

			separationI[0] == 3             && separationI[1] == 2        && separationI[2] == 1                &&
			separationI[3] == 4             && separationI[4] == 12       && separationI[5] == 13);

	cerr<<"ALL TESTS PASSED FOR makeProper"<<endl;

	const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
       	"mad",       "deranged", "nefarious", "have"
     };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
    	"scientist", "robot",    "plot",      "mad"
     };
  	int test1dist[TEST1_NRULES] = {
 		1,           3,          0,           12
	};
	char doc1[MAX_DOCUMENT_LENGTH] = "The mad UCLA scientist unleashed a deranged evil giant robot";
	char doc2[MAX_DOCUMENT_LENGTH] = "The mad        UCLA scientist     unleashed    a deranged robot";
	char doc3[MAX_DOCUMENT_LENGTH] = "**** 2018 ****";
	char doc4[MAX_DOCUMENT_LENGTH] = "  That plot: NEFARIOUS!";
	char doc5[MAX_DOCUMENT_LENGTH] = "deranged deranged robot deranged robot robot";
	char doc6[MAX_DOCUMENT_LENGTH] = "";
	char doc7[MAX_DOCUMENT_LENGTH] = "     The mad UCLA scientist unleashed a deranged evil giant robot";
	char doc8[MAX_DOCUMENT_LENGTH] = "The mad UCLA scientist unleashed a deranged evil giant robot    ";
	char doc9[MAX_DOCUMENT_LENGTH] = "    The mad        UCLA scientist     unleashed    a deranged robot       ";
	char doc10[MAX_DOCUMENT_LENGTH] = "The mad UCLA scientist unleashed 478 deranged evil people-killing giant robots!!!!!";
	char doc11[MAX_DOCUMENT_LENGTH] = "      The mad UCLA     scientist unleashed 478 deranged evil         people-killing giant         robots! !!   !!       ";
	char doc12[MAX_DOCUMENT_LENGTH] = "robot car tree metal deranged man robot tree";

	//TEST 1
    assert(rate(doc1,test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    //TEST 2
    assert(rate(doc2,test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    //TEST 3
    assert(rate(doc7,test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    //TEST 4
    assert(rate(doc8,test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    //TEST 5
    assert(rate(doc9,test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    //TEST 6
    assert(rate(doc10,test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    //TEST 7
    assert(rate(doc11,test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    //TEST 8
    assert(rate(doc3,test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    //TEST 9
    assert(rate(doc6,test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    //TEST 10
    assert(rate(doc5,test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    //TEST 11
    assert(rate(doc4,test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    //TEST 12
    assert(rate(doc12,test1w1, test1w2, test1dist, TEST1_NRULES) == 1);

	cerr<<"ALL TESTS PASSED FOR rate"<<endl;
	cerr<<"ALL TESTS PASSED"<<endl;
}

/*
*Removes element in index n from word1, word2, and separation
*/
void removeElement(char word1[][MAX_WORD_LENGTH+1],
               	   char word2[][MAX_WORD_LENGTH+1],
                   int separation[],int nPatterns,int n){
	//Move element at n one step forward until it is the last element
	for(int i=n; i < nPatterns-1; i++){
		strcpy(word1[i]   , word1[i+1]);
		strcpy(word2[i]   , word2[i+1]);
		separation[i]   = separation[i+1];
	}
}

/*
*Converts word1, word2 and separation to proper form
*/
int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns){
	//if nPatterns is 0, no patterns are made to proper form
	//if nPatterns is negative, it is treated as if it were
	if(nPatterns <= 0) return 0;

	//Convert everything in word1 & word2 to lowercase
	for(int i=0; i < nPatterns; i++){
		for(int j=0; j<strlen(word1[i]); j++){
			word1[i][j] = tolower(word1[i][j]);
		}
		for(int j=0; j<strlen(word2[i]); j++){
			word2[i][j] = tolower(word2[i][j]);
		}
	}
	//Check for blank string or non letter character
	for(int i=0; i < nPatterns ;){
		//Check for blank string
		if(word1[i][0] == '\0' || word2[i][0] == '\0'){
			removeElement(word1,word2,separation,nPatterns,i);
			nPatterns--;
			continue;
		}

		//Remove negative separations
		if(separation[i] < 0){
			removeElement(word1,word2,separation,nPatterns,i);
			nPatterns--;
			continue;
		}

		//Check if word in word1 contains ONLY alphabets
		for(int j=0; j < strlen(word1[i]); j++){
			if(!isalpha(word1[i][j])){
				removeElement(word1,word2,separation,nPatterns,i);
				nPatterns--;
				continue;
			}
		}

		//Check if word in word2 contains ONLY alphabets
		for(int j=0; j < strlen(word2[i]); j++){
			if(!isalpha(word2[i][j])){
				removeElement(word1,word2,separation,nPatterns,i);
				nPatterns--;
				continue;
			}
		}
		i++;
	}

	//Checking for duplicates
	for(int i=0; i<nPatterns; i++){
		//Store first and second word of current pattern
		char firstWord[MAX_WORD_LENGTH+1];
		char secondWord[MAX_WORD_LENGTH+1];
		strcpy(firstWord, word1[i]);
		strcpy(secondWord, word2[i]);

		//Cycle through all patterns and see if the same pattern appears again
		for(int j=0; j<nPatterns; j++){
			//Don't check the same pattern again
			if(j==i) continue;

			//Check if pattern appears again, in ANY order
			if((!strcmp(firstWord,word1[j]) && !strcmp(secondWord,word2[j]))
				||
			   (!strcmp(firstWord,word2[j]) && !strcmp(secondWord,word1[j]))){

				//Store the index of pattern which has the lower separation value
				//If both have the same separation value, remove the first one
				int min = (separation[j] <= separation[i]) ? j : i;

				//Remove element with lower separation value
				removeElement(word1,word2,separation,nPatterns,min);
				//Decrement nPatterns to account for the deleted element
				nPatterns--;
				break;
			}
		}
	}

	//The previous loops may take nPatterns to a negative value, so corrent the negative values to 0
	if(nPatterns<0) return 0;


	return nPatterns;
}

/*
*Remove character at position index from document 
*/
void removeChar(char document[], int documentLength, int index){
	//Move character at index one step forward until it is the last element
	for(int i=index; i<documentLength-1; i++){
		document[i]   = document[i+1];
 	}
}

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns){

	//if nPatterns is negative, treat as 0
	if(nPatterns <= 0) return 0;

	int documentLength = strlen(document);

	//Copy document into a temporary cstring that can be modified
	char tempDocument[MAX_DOCUMENT_LENGTH];
	strcpy(tempDocument, document);

	//Remove any special charaters (characters other than spaces and alphabets)
	for(int i=0; i < documentLength; i++){
		//Check if character is alphabet or space
		if(!isalpha(tempDocument[i]) && !isspace(tempDocument[i])){
			//Remove character
			removeChar(tempDocument, documentLength, i);
			//Decrement documentLength to account for deleted character
			documentLength--;
			i--;
		}
	}

	//Convert to lowercase
	for(int i=0; i<documentLength; i++){
		tempDocument[i] = tolower(tempDocument[i]);
	}

	//Remove extra spaces
	for(int i=1; i < documentLength-1 && documentLength > 1; i++){
		if(tempDocument[i] == ' ' && tempDocument[i-1] == ' '){
			removeChar(tempDocument, documentLength, i-1);
			//Decrement documentLength to account for deleted character
			documentLength--;
			i--;
		}
	}
	

	//Remove leading spaces
	if(documentLength>=1){
		while(isspace(tempDocument[0])){
			if(documentLength<0) break;
			removeChar(tempDocument, documentLength, 0);
			//Decrement documentLength to account for deleted character
			documentLength--;
			if(documentLength<=0) break;
		}
	}

	//Remove trailing spaces
	if(documentLength>1){
		while(isspace(tempDocument[documentLength-1])){
			//Decrement documentLength to account for deleted character
			documentLength--;
		}
	}

	
	//Create 2D array to store words individually in separate cstrings
	char wordsInDocument[MAX_DOCUMENT_LENGTH+1][MAX_DOCUMENT_LENGTH+1];
	int wordStartIndex=0;
	int wordCount=0;
	int charIndex=0;

	//Separate words in document into individual cstrings
	for(int wordPicker=0; wordPicker<documentLength; wordPicker++){
		//When a space is found, make a cstring from wordStartIndex to current index
		if(isspace(tempDocument[wordPicker])){
			charIndex = 0;
			for(int j=wordStartIndex; j<wordPicker; j++){
				//
				wordsInDocument[wordCount][charIndex] = tempDocument[j];
				charIndex++;
			}
			//Add null terminator
			wordsInDocument[wordCount][charIndex] = '\0';
			wordCount++;
			//Start index of next word is the end index of current word
			wordStartIndex = wordPicker+1;
		}
		//If the end of document is reached, use end of document as end point for current word
		if(wordPicker==(documentLength-1)){
			charIndex = 0;
			for(int j=wordStartIndex; j<=wordPicker; j++){
				//Store letters
				wordsInDocument[wordCount][charIndex] = tempDocument[j];
				charIndex++;
			}
			//Add null terminator
			wordsInDocument[wordCount][charIndex] = '\0';
			wordCount++;
			wordStartIndex = wordPicker+1;
		}
	}

	int count = 0;

	//Check for occurrences of patterns
	for(int i=0; i<nPatterns; i++){
		//Store first and second word of pattern
		char firstWord[MAX_WORD_LENGTH+1];
		strcpy(firstWord,word1[i]);
		char secondWord[MAX_WORD_LENGTH+1];
		strcpy(secondWord,word2[i]);
		bool patternFound = false;

		//Loop through words 
		for(int j=0; j<wordCount; j++){
			//If first word of pattern doesnt match current word, move on to next word
			if(strcmp(firstWord,wordsInDocument[j])) continue;

			//If words match, we may have a pattern and need to check for the occurence of the second word
			//Check for separation words before and after
			int startVal = j - (separation[i] + 1);
			int endVal = j + (separation[i] + 1);

			//Adjust startVal and endVal to valid indices
			if(startVal<0) startVal = 0;
			if(endVal>(wordCount-1)) endVal = wordCount-1;

			//Loop therough words from index startVal to endVal
			for(int k = startVal; k<=endVal; k++){
				//Don't check the same word
				if(j==k) continue;

				//If word match is found for second word in this range
				//Pattern found
				if(!strcmp(secondWord,wordsInDocument[k])){
					//Account for found pattern
					count++;
					patternFound = true;
					break;
				}
			}

			//If current pattern has been found once, move on to next pattern
			if(patternFound) break;

		}
	}

	return count;
}