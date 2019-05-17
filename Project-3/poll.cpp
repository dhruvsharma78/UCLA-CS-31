#include <iostream>
#include <cassert>
#include <string>


using namespace std;

bool isValidUppercaseStateCode(string stateCode){
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isValidPartyResult(string partyResult){
    if(partyResult.size()==2){
        //Check if first character is digit and second is alpha
        return (isdigit(partyResult[0]) && isalpha(partyResult[1]));
    }else if (partyResult.size()==3){
        //Check if first and second character are digit and third is alpha
        return (isdigit(partyResult[0]) && isdigit(partyResult[1]) && isalpha(partyResult[2]));
    }else{
        return false;
    }
}

bool isValidStateForecast(string stateForecast){
    //Convert all to uppercase
    if(stateForecast.size()>=2){
        for(int i = 0; i < stateForecast.size(); i++){
            stateForecast[i] = toupper(stateForecast[i]);
        }
    }else{
        //State code MUST be greater than 2 characters long as it MUST include a 2 character state code
        return false;
    }
    
    //Check if statecode is valid
    if(!isValidUppercaseStateCode(stateForecast.substr(0,2))){
        return false;
    }
    
    //Check if party results are valid
    int numberOfContinuousDigits = 0;
    for(int i=2;i<stateForecast.size();i++){
        //Check for spaces
        if(stateForecast[i] == ' '){
            return false;
        }
        
        //Keep a digit count for current run. If it crosses 2,
        //the party result is INVALID as there CANNOT be
        //more than 2 digits
        if(isdigit(stateForecast[i])){
            numberOfContinuousDigits++;
        }
        if(numberOfContinuousDigits>2){
            return false;
        }
        
        //Check for valid party result
        if(isalpha(stateForecast[i])){
            
            if(!(isValidPartyResult(stateForecast.substr(i-2,3)) || isValidPartyResult(stateForecast.substr(i-1,2)))){
                return false;
            }
            //As a non digit character has been encountered,
            //numberOfContinuousDigits can be reset to 0
            numberOfContinuousDigits=0;
        }
    }
    
    //If stateForecast ends with a number, it is invalid
    if(isdigit(stateForecast[stateForecast.size()-1])){
        return false;
    }
    
    return true;
}

bool hasProperSyntax(string pollData){
    //Blank pollData
    if(pollData==""){
        return true;
    }
    //If begins or ends with comma
    if(pollData[0]==',' || pollData[pollData.size()-1]==','){
        return false;
    }
    int currentChar=0,stateResultStart=0,stateResultEnd=0;
    string currentStateData;
    while(currentChar<pollData.size()){
        //GET STATEFORECAST
        //If comma or end of pollData encountered
        if(pollData[currentChar] == ',' || currentChar == pollData.size()-1){
            //Fix ending point for state results
            stateResultEnd=currentChar;
            //Extract individual state results
            if(currentChar == pollData.size()-1){
                currentStateData = pollData.substr(stateResultStart);
            }else{
                currentStateData = pollData.substr(stateResultStart,(stateResultEnd-stateResultStart));
            }
            
            //VALIDATE INDIVIDUAL STATE FORECAST
            if(!isValidStateForecast(currentStateData)){
                return false;
            }
            //Set index of start
            stateResultStart=currentChar+1;
        }
        currentChar++;
    }
    return true;
}

int tallySeats(string pollData, char party, int& seatTally){
    
    //Convert pollData to all uppercase
    for(int charPos = 0;charPos<pollData.size();charPos++){
        pollData[charPos] = toupper(pollData[charPos]);
    }
    
    //Convert party to uppercase
    party = toupper(party);
    
    if(!hasProperSyntax(pollData)){
        return 1;
    }else if(!isalpha(party)){
        return 2;
    }
    seatTally=0;
    int currentChar=0;
    string currentStateData;
    int tempCount = 0;
    while(currentChar<pollData.size()){
        if(isdigit(pollData[currentChar])){
            tempCount = (tempCount*10) + (pollData[currentChar] - '0');
        }else if(pollData[currentChar] == party){
            seatTally+=tempCount;
            tempCount=0;
        }else{
            tempCount=0;
        }
        currentChar++;
    }
    return 0;
}

int main(){
    assert(hasProperSyntax("")); //Check for blank pollData
    assert(!hasProperSyntax(" ")); //Check for ' ' pollData
    assert(hasProperSyntax("CA")); //Check is only a single state code, without party results works as pollData
    assert(hasProperSyntax("ca")); //Check for case
    assert(hasProperSyntax("cA")); //Check for case
    assert(hasProperSyntax("Ca")); //Check for case
    assert(!hasProperSyntax("CF")); //Check invalid state code
    assert(!hasProperSyntax("CA1")); //Invalid state forecast (no party code)
    assert(!hasProperSyntax("CAD")); //Invalid state forecast (no digits)
    assert(hasProperSyntax("CA1D")); //Valid state forecast (1 digit followed by 1 char party code)
    assert(!hasProperSyntax("CA12")); //Invalid state forecast (no party code)
    assert(hasProperSyntax("CA12D")); //Valid state forecast (2 digits followed by 1 char party code)
    assert(hasProperSyntax("CA55d")); //Check for case of party code
    assert(hasProperSyntax("CA1D1R")); //Multiple single digit party results
    assert(hasProperSyntax("CA1D10R")); //One single digit state forecast, One double digit state forecast
    assert(hasProperSyntax("CA10D10R")); //Multiple double digit state forecasts
    assert(hasProperSyntax("CA1D,NY12D")); //Multiple valid state forecasts
    assert(!hasProperSyntax("CA1D,Ny,ct12")); //2 Valid state forecasts and 1 invalid forecast
    assert(!hasProperSyntax(",CA1D,Ny,ct12D")); //Begin with comma
    assert(!hasProperSyntax("CA1D,Ny,ct12D,")); //End with comma
    assert(!hasProperSyntax("CA1D,Ny,ct12 D")); //Space betwwen party result and party code
    assert(!hasProperSyntax("CA1D,Ny, ct12D")); //Space betwwen state forecasts
    assert(!hasProperSyntax("CA1D,N y,ct12D")); //Space between state code
    assert(!hasProperSyntax("CA 1D,Ny,ct12D")); //Space between state code and party results
    assert(!hasProperSyntax("CA1D,Ny ,ct12D")); //Space after state forecasr
    assert(!hasProperSyntax(" CA1D,Ny,ct12D")); //Space in start of pollData
    assert(!hasProperSyntax("CA1D,Ny,ct12D ")); //Space at end of pollData
    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D")); //Valid pollData
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VT,ne3rD")); //Invalid pollData
    assert(!hasProperSyntax(",CT5D,NY9R17D1I,VT,ne3r00D"));
    assert(hasProperSyntax("MA9D,KS4R")  &&  hasProperSyntax("KS4R,MA9D"));
    assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D")); //Test for blank state forecast (invalid)
    int seats;
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22);
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    
    seats = -999;
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'D', seats) == 0 && seats == 22); //Uppercase party code
    seats = -999;
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 22); //Lowercase party code
    seats = -999;
    assert(tallySeats("", 'd', seats) == 0 && seats == 0); //Empty string
    seats = -999;
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '2', seats) == 2 && seats == -999); //Invalid party code
    seats = -999;
    assert(tallySeats("CT5D,NY9R17D1I,VT50,ne3r00D", 'd', seats) == 1 && seats == -999); //Invalid pollData
    seats = -999;
    assert(tallySeats("CT5D,NY9R17D1I,VT50,ne3r00D", '?', seats) == 1 && seats == -999); //Invalid pollData and party code
    seats = -999;
    assert(tallySeats("CT0D,NY9R00D1I,VT,ne3r00D", 'd', seats)== 0 && seats == 0); //No votes
    seats = -999;
    assert(tallySeats("CT,Ny,vT,ne", 'd', seats) == 0 && seats == 0); //No party results
    seats = -999;

    
    cerr << "All tests succeeded" << endl;
}
