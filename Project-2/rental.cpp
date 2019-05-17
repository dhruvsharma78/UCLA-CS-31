//
//  rental.cpp
//  rental
//
//  Created by Dhruv Sharma on 10/10/18.
//  Copyright © 2018 Dhruv Sharma. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main(){
	//Initializing variables
    int odometerStart,odometerEnd,rentalDays,month;
    string customerName,luxury;
	
	//Initializing constants
    const double BASE_RATE_REGULAR = 33, BASE_RATE_LUXURY = 61, FIRST_100 = 0.27, NEXT_300_WINTER = 0.27, NEXT_300_REGULAR =0.21, EXTRA = 0.19;
	
	//Accepting values from user
    cout << "Odometer at start: ";
    cin >> odometerStart;
    cout << "Odometer at end: ";
    cin >> odometerEnd;
    cout << "Rental days: ";
    cin >> rentalDays;
    cin.ignore(10000, '\n');
    cout << "Customer name: ";
    getline(cin,customerName);
    cout << "Luxury car? (y/n): ";
    getline(cin,luxury);
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    cout << "---" << endl;
	
	//Checking for invalid inputs
    if(odometerStart<0){
        cout << "The starting odometer reading must be nonnegative." << endl;
    }else if (odometerEnd<odometerStart){
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
    }else if(rentalDays<=0){
        cout << "The number of rental days must be positive." << endl;
    }else if (customerName==""){
        cout << "You must enter a customer name." << endl;
    }else if (luxury!="y" && luxury!="n"){
        cout <<"You must enter y or n." << endl;
    }else if (month<1 || month >12){
        cout <<"The month number must be in the range 1 through 12." << endl;
    }else{
		
        int milesTravelled = odometerEnd - odometerStart;
        double cost;
		
		//Check if rented car was a luxury car or regular
		//Check if car was rented during the winter months
        double base = BASE_RATE_REGULAR;//Initially assumed that rented car is a regular car
        double next300 = NEXT_300_REGULAR;//Initially assumed that car was not rented out during the winter
        if(month == 1 || month == 2 || month == 3 || month ==12 ){ 
            next300 = NEXT_300_WINTER;//Adjusting value if winter months
        }
        if(luxury=="y"){
            base = BASE_RATE_LUXURY;//Adjusting value if luxury car
        }
        
        //Calculation of cost according to miles driven
        if(milesTravelled > 400){
			//Calculating and adding rates for the first 100 miles, next 300 and remaining miles
            cost = (100*FIRST_100) + (300*next300) + ((milesTravelled-400)*EXTRA);
        }else if (milesTravelled > 100){
			//Calculating and adding rates for the first 100 miles and remaining miles
            cost = (100*FIRST_100) + ((milesTravelled-100)*next300);
        }else{
			//Calculating rate for less than 100 miles
            cost = milesTravelled*FIRST_100;
        }
		
		//Adding base rate to total cost
        cost += (base*rentalDays);
        
        //Setting print precision to 2 decimal places as output is cost
        cout.setf(ios::fixed);
        cout.precision(2);

        //Displaying final output
        cout << "The rental charge for " << customerName << " is $" << cost << endl;
    }
    
}

