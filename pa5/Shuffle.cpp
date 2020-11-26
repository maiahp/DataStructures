/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA5
* Shuffle.cpp
* Client module for the List ADT
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include "stdio.h"
#include "List.h"

using namespace std;

void Shuffle(List&);

int main(int argc, char * argv[]){
    
    // check command line for correct number of arguments
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << " <number>" << endl;
        return(EXIT_FAILURE);
    }
    
    
    cout<<"deck size       shuffle count" << endl;
    cout<<"------------------------------"<< endl;

    int num = atoi(argv[1]);
    //int num = 100; // delete this when turning in, we want the argv to be num
    int count = 0;
    
    List A;
    for(int i=0; i<num; i++){
        for(int j=0; j<=i; j++){
            A.insertBefore(j);
        }
        count = 0;
        List B = A; // B is original list, A is the shuffled list
        
        while(1) { // exit condition is that B == A
            Shuffle(A);
            count++;
            
            if (B == A) {
                // string formatting here
                cout << " ";
                cout << left << setw(16) << A.size();
                cout << count << endl;
                //cout<<"Finished! B==A"<<endl;
                break;
            }
        }
        A.clear();
    }
    return(0);
}

void Shuffle(List& D) {
    //split the list
    int n = D.size();
    int i = 0;
    D.moveFront();
    List firsthalf, lasthalf;
    
    for(i = 0; i <= n/2 - 1; i++){
        firsthalf.insertBefore(D.moveNext());
    }
    for(; i < n; i++){
        lasthalf.insertBefore(D.moveNext());
    }
    //cout << "first half " << firsthalf << endl;
    //cout << "last half" << lasthalf << endl;
    
    //merge lasthalf goes first
    int j = 0;
    int first_i = 0;
    int last_i = 0;
    int first_size = firsthalf.size();
    int last_size = lasthalf.size();
    firsthalf.moveFront();
    lasthalf.moveFront();
    D.clear();
    
    while(j < n){
        if(last_i < last_size){
            D.insertBefore(lasthalf.moveNext());
            last_i++;
            j++;
        }
        if(j == n)break;
        if(first_i<first_size){
            D.insertBefore(firsthalf.moveNext());
            first_i++;
            j++;
        }
    }
    //cout << "D " << D << endl << endl << endl << endl;
}


