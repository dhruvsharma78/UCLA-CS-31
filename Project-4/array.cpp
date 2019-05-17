//
//  main.cpp
//  array
//
//  Created by Dhruv Sharma on 11/1/18.
//  Copyright © 2018 Dhruv Sharma. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool isValidNumber(int n);
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);


int main() {
    /*
    * Testing appendToAll
    */
    string people[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    //All values modified
    assert(appendToAll(people, 5, "!") == 5 && people[0]=="dianne!" && people[3] == "xavier!" && people[4] == "greg!");
    //No values modified
    assert(appendToAll(people, 0, "!!") == 0 && people[0] == "dianne!");
    //Some values modified
    assert(appendToAll(people, 3, "!!") == 3 && people[2] == "ed!!!" && people[3] == "xavier!");
    //Value of n is invalid
    assert(appendToAll(people, -5, "!!") == -1 && people[0] == "dianne!!!");
    
    /*
    * Testing lookup
    */
    string people2[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    //Succesful search within full array
    assert(lookup(people2, 5, "ed") == 2);
    //Unsuccesful search within a part of array
    assert(lookup(people2, 2, "ed") == -1);
    //Unsuccessful search within full array
    assert(lookup(people2, 5, "david") == -1);
    //Sucessful search within part of array
    assert(lookup(people2, 5, "fiona") == 1);
    //Value of n is invalid
    assert(lookup(people2, -3, "ed") == -1);
    //Searching 0 elements
    assert(lookup(people2, 0, "ed") == -1);
    //Capitalization
    assert(lookup(people2, 0, "Ed") == -1);
    
    /*
    * Testing positionOfMax
    */
    //Only 1 max value in array
    string h[7] = { "greg", "gavin", "ed", "", "xavier", "eleni", "fiona" };
    assert(positionOfMax(h, 7) == 4);
    //All vlaues in array are same
    string people3[5] = {"ed","ed","ed","ed","ed"};
    assert(positionOfMax(people3, 5) == 0);
    //Last few values in array are same
    string people5[5] = {"al","al","ed","ed","ed"};
    assert(positionOfMax(people5, 5) == 2);
    //Some values in array are same
    string people6[7] = {"al","ed","ed","al","ed","a","a"};
    assert(positionOfMax(people6, 7) == 1);
    //Search only part of array
    assert(positionOfMax(h, 4) == 0);
    //Invalid value of n
    assert(positionOfMax(h, -7) == -1);
    //Search within no part of array
    assert(positionOfMax(h, 0) == -1);
    //Test capitalization
    string people7[7] = {"al","Ed","Ed","al","ed","a","a"};
    assert(positionOfMax(people7, 7) == 4); 
    //Find max of just 1 array index
    assert(positionOfMax(people7, 1) == 0);

    /*
    *Testing rotateLeft
    */
    //All inputs valid
    string politician[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    assert(rotateLeft(politician, 5, 1) == 1 && politician[1] == "fiona" && politician[4] == "dianne");
    //Value of n is invalid
    assert(rotateLeft(politician, -4, 1) == -1);
    //Value of pos is less than 0
    assert(rotateLeft(politician, 5, -4) == -1);
    //Value of pos and n are invalid
    assert(rotateLeft(politician, -5, -4) == -1);
    //Value of pos is greater than n
    assert(rotateLeft(politician, 5, 34) == -1);
    //Value of pos is same as n
    assert(rotateLeft(politician, 5, 5) == -1);
    //Value of pos and n are 0
    assert(rotateLeft(politician, 0, 0) == -1);
    //Rotate only part of array
    string politician2[6] = { "eleni", "dianne", "obama", 
                              "fiona", "kevin", "gavin" };
    assert(rotateLeft(politician2, 5, 2) == 2 && politician2[4] == "obama" && politician2[2] == "fiona");
    //When only 1 element is rotated
    string politician3[6] = { "eleni", "dianne", "obama", 
                              "fiona", "kevin", "gavin" };
    assert(rotateLeft(politician3, 1, 0) == 0 && politician3[0] == "eleni" && politician3[1] == "dianne");
    //pos points to last element
    assert(rotateLeft(politician3, 6, 5) == 5 && politician3[4] == "kevin" && politician3[5] == "gavin");

    /*
    * Testing countRuns
    */
    string d[9] = {"xavier", "betty", "john", 
                   "john"  , "ed"   , "ed", 
                   "ed"    , "john" , "john"};

    string letters[16] = {"a", "a", "c", "d",
                          "a", "a", "a", "a",
                          "x", "x", "y", "y",
                          "y", "b", "b", "c"};
    //Normal case
    assert(countRuns(d,9) == 5);
    assert(countRuns(letters,16) == 8);
    //Value of n is invalid
    assert(countRuns(d,-3) == -1);
    //Value of n is 0
    assert(countRuns(d,0) == 0);
    //Value of n is 1
    assert(countRuns(d,1) == 1);
    //Array begins with blank string
    string a[5] = {"","","w","",""};
    assert(countRuns(a,5) == 3);

    /*
    * Testing flip
    */
    string folks[6] = { "betty" , "john" , "", 
                        "xavier", "kevin", "dianne" };
    string people4[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    //Flip full array (Even number of elements)
    assert(flip(folks,6) == 6 && folks[0] == "dianne" && folks[5] == "betty");
    flip(folks,6);
    //Flip part of array
    assert(flip(folks,4) == 4 && folks[0] == "xavier" && folks[3] == "betty");
    //Flip full array (odd number of elements)
    assert(flip(people4,5) == 5 && people4[0] == "greg" && people4[4] == "dianne" && people4[2] == "ed");
    //Value of n is invalid
    assert(flip(people4,-3) == -1);
    //Flip nothing
    string people8[5] = { "dianne", "fiona", "ed", "xavier", "greg" };
    assert(flip(people8, 0) == 0 && people8[0] == "dianne" && people8[4] == "greg");

    /*
    * Testing differ
    */
    string folks1[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string folks2[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string group[5] = { "betty", "john", "dianne", "", "xavier" };
    //Comparing both arrays
    assert(differ(folks1, 6, group, 5) == 2); 
    //Comparing part of the arrays
    assert(differ(folks1, 2, group, 2) == 2);
    //a2 ends before a difference is found
    assert(differ(folks1, 2, group, 1) == 1);
    //No difference
    assert(differ(folks1,6,folks2,6) == 6);
    //Invalid value of n1
    assert(differ(folks1, -2, group, 5) == -1); 
    //Invalid value of n2
    assert(differ(folks1, 6, group, -5) == -1); 
    //n1 and n2 invalid
    assert(differ(folks1, -6, group, -5) == -1); 
    //n1 is 0
    assert(differ(folks1, 0, group, 1) == 0);
    //n2 is 0
    assert(differ(folks1, 1, group, 0) == 0);
    //m1 and n2 are 0
    assert(differ(folks1, 0, group, 0) == 0);
    

    /*
    *Testing subsequence
    */
    //subsequence exists
    string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string names1[10] = { "gavin", "kevin", "greg" };
    assert(subsequence(names, 6, names1, 3) == 1); 
    //subsequence does not exist
    string names2[10] = { "eleni", "greg" };
    assert(subsequence(names, 5, names2, 2) == -1);  
    //n1 is invalid
    assert(subsequence(names, -6, names1, 3) == -1); 
    //n2 is invalid
    assert(subsequence(names, 6, names1, -3) == -1); 
    //n1 and n2 are invalid
    assert(subsequence(names, -6, names1, -3) == -1); 
    //n1 is 0
    assert(subsequence(names, 0, names1, 3) == -1); 
    //n2 is 0
    assert(subsequence(names, 6, names1, 0) == 0); 
    //n1 and n2 are 0
    assert(subsequence(names, 0, names1, 0) == 0); 


    /*
    * Testing lookupAny
    */
    string names3[6] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string set1[5] = { "dianne", "betty", "greg", "gavin", "ed"};
    //Successful search
    //Goes through both arrays completely
    assert(lookupAny(names3, 6, set1, 5) == 1);  // returns 1 (a1 has "gavin" there)
    string set2[2] = { "xavier", "ed" };
    //Unsuccessful search
    assert(lookupAny(names3, 6, set2, 2) == -1);  // returns -1 (a1 has none)
    //Unsuccessful search
    //Only checks with first element of a2
    assert(lookupAny(names3, 6, set1, 1) == -1);
    //Unsuccessful search
    //Only checks first 5 elements of a1
    assert(lookupAny(set1, 4, set2, 2) == -1);
    //n1 is invalid
    assert(lookupAny(names3, -6, set1, 5) == -1);
    //n2 is invalid
    assert(lookupAny(names3, 6, set1, -5) == -1);
    //n1 and n2 are invalid
    assert(lookupAny(names3, -6, set1, -5) == -1);
    //n1 is 0
    assert(lookupAny(names3, 0, set1, 5) == -1);
    //n2 is 0
    assert(lookupAny(names3, 6, set1, 0) == -1);
    //n1 and n2 are 0
    assert(lookupAny(names3, 0, set1, 0) == -1);


    /*
    * Testing divide
    */
    string candidate[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
    //divider doesnt exist in array
    assert(divide(candidate, 6, "eleni") == 3);  //  returns 3
    string candidate2[4] = { "gavin", "kevin", "fiona", "john" };
    //divider exists in array
    assert(divide(candidate2, 4, "john") == 2);  //  returns 2
    //all items are less than divider
    assert(divide(letters, 16, "z") == 16);
    //all items are more than divider
    assert(divide(candidate, 6, "a") == 0);
    //Invalid value of n
    assert(divide(candidate, -6, "eleni") == -1);
    //Only divide part of array
    string letters2[5] = {"a","d","e","b","a"};
    assert(divide(letters2, 4, "c") == 2 && letters2[4] == "a");
    //n is 0
    assert(divide(candidate, 0, "eleni") == 0);
    //divider exists in array multiple times
    string letters3[6] = {"e", "f", "g",
                          "a", "d", "d"};
    assert(divide(letters3, 6, "d") == 1 && letters3[1] == "d" && letters3[2] == "d");

    cerr<<endl<<"All tests successfully passed"<<endl<<endl;

    return 0;
}

bool isValidNumber(int n){
    //Return false if n is negative
    return !(n<0);
}

int appendToAll(string a[], int n, string value){
    //Check if n is valid
    if(!isValidNumber(n)) return (-1);

    for(int i=0; i<n; i++){
        //Add value to end of string in array
        a[i]+=value;
    }

    //Return n
    return n;
}

int lookup(const string a[], int n, string target){
    //Check if n is valid
    if(!isValidNumber(n)) return (-1);

    for(int i=0; i<n; i++){
        if(a[i]==target){
            //Return current position if string is equal to target
            return i;
        }
    }

    //Return -1 if nothing found
    return -1;
}

int positionOfMax(const string a[], int n){
    //Check if n is valid
    if(!isValidNumber(n)) return (-1);

    for(int i=0; i<n ;i++){
        for(int j=0; j<n; j++){
            //if a[i] is less than a[j],
            //a[i] cannot be max value,
            //therefore break and move to next index
            if(a[i]<a[j]) break;
            //If no breaks have occured by this point,
            //a[i] must be the maximum possible value
            if(j==(n-1)) return i;
        }
    }
    //Return -1 if no values exist in array
    //or value of n is invalid
    return -1;
}

int rotateLeft(string a[], int n, int pos){
    //Check if n is valid
    if(!isValidNumber(n)) return (-1);
    //Check if pos is valid
    if(!isValidNumber(pos)) return (-1);
    //Check is pos is greater than n
    if(pos >= n) return (-1);

    string temp;
    //Begin loop from pos and move each element one step to the right
    for(int i=pos; i<(n-1); i++){
        //Using temp variable to swap elements
        temp = a[i];
        a[i] = a[i+1];
        a[i+1] = temp;
    }

    //Returning initial position of element 
    //that was sent to the end
    return pos;
}

int countRuns(const string a[], int n){
    //Check if n is valid
    if(!isValidNumber(n)) return (-1);

    int run = 0;
    string temp = "";
    for(int i=0; i<n; i++){
        //Increment run if string is not equal to temp
        //or if i is 0 and first string is blank
        if(a[i] != temp || (i==0 && a[0]=="")){
            //temp stores the value of current string
            //Because of the above condition, this block
            //will not be entered until a new sequence of strings starts
            temp = a[i];
            //Increment run to count number of runs
            //of same string
            run++;
        }
    }

    return run;
}

int flip(string a[], int n){
    //Check if n is valid
    if(!isValidNumber(n)) return -1;

    string temp = "";
    //Run loop through only half the arrays
    for(int i=0; i<(n/2); i++){
        //Swap element in i with corresponding 
        //element from the back of the array
        //(n-i-1) represents the index of element that corresponds to
        //element at index i
        temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    //Check if n1 and n2 are valid
    if(!isValidNumber(n1)) return -1;
    if(!isValidNumber(n2)) return -1;
    //Find minimum value
    int min = (n1<n2)?n1:n2;
    for(int i=0; i<min; i++){
        //Find index when element in a1 and a2 are not equal
        if(a1[i] != a2[i])
            //Return index
            return i;
    }

    //Return minimum value of n1 and n2 if no difference found
    return min;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    //Check if n1 and n2 are invalid
    if(!isValidNumber(n1)) return -1;
    if(!isValidNumber(n2)) return -1;
    if(n2 == 0) return 0;

    //If n2 is greater than n1, a2 definitely doesnt exist in a1
    if(n2 > n1) return -1;

    bool check = false;
    int pos = 0;
    for(int i=0; i<n1; i++){
        //Keep check true as long as elements are same 
        //in corresponding arrays
        if(a1[i] == a2[pos]){
            check = true;
            //increment pos
            pos++;
        }else{
            //If elements are not same,
            //change check to false
            check = false;
            pos=0;
        }

        //If check is true and end of a2 is reached
        //a1 contains a2 
        if(check && (pos == n2)){
            return (i-pos+1);
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    //Check if n1 and n2 are invalid
    if(!isValidNumber(n1)) return -1;
    if(!isValidNumber(n2)) return -1;
    string temp = "";

    for(int i=0; i<n1; i++){
        temp = a1[i];
        //Search for element i in a2
        for(int j=0; j<n2; j++){
            //If element is found in a2, return i
            if(a1[i] == a2[j])
                return i;
        }
    }
    return -1;
}

int divide(string a[], int n, string divider){
    //Check if n1 is valid
    if(!isValidNumber(n)) return -1;
    string temp = "";
    //Sort array
    for(int i=0; i<n; i++){
        for(int j=0; j<(n-1); j++){
            if(a[j] > a[j+1]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    //Find element that is greater than or equal to divider
    for(int i=0; i<n; i++){
        if(a[i] >= divider){
            return i;
        }
    }

    //If no value is greater than or equal to 
    return n;
}
