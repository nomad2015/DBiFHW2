//
//  main.cpp
//  HW2
//
//  Created by Xiaobo on 3/9/16.
//  Copyright © 2016 Xiaobo. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <time.h>

using namespace std;

int main() {
    
    //number of how many dates data we will generate
    //change this number will change the data.cvs file size
    int N = 50;
    
    //format time; initial time 20180101, 09:00:00
    struct tm timeinfo;
    timeinfo.tm_year = 118;
    timeinfo.tm_mon  = 0;
    timeinfo.tm_mday = 1;
    timeinfo.tm_hour = 9;
    timeinfo.tm_min  = 0;
    timeinfo.tm_sec  = 0;
    
    int volume;
    int price_dol, price_cent;
    string symbol = "stock";
    int num_symbol;
    
    //random generators
    random_device rd;
    default_random_engine generator( rd() );
    uniform_int_distribution<int> unif_sym(1,30), unif_price_dol(10, 200), unif_price_cent(0, 99), unif_vol(100,5000);
    
    //set up output csv file
    ofstream out_file;
    
    //****************************************//
    //**** The path need to be modified!! ****//
    //****************************************//
    out_file.open("/Users/xiaobohe/Desktop/c++/9898_BDiF_HW/HW2/data.csv");
    
    //write header
    string header = "Date,time,Symbol,Price,Volume";
    out_file << header << endl;
    
    //write data
    for (int i_date = 0; i_date <= N; ++i_date) {
        timeinfo.tm_mday = 1 + i_date%30;
        timeinfo.tm_mon  = 0 + (i_date/30)%12;
        timeinfo.tm_year = 118 + i_date/360;
                
        for (int i_hour = 0; i_hour <= 7; ++i_hour) {
            timeinfo.tm_hour = 9 + i_hour;
                    
            for (int i_min = 0; i_min <= 59; ++i_min) {
                timeinfo.tm_min  = 0 + i_min;
                        
                for (int i_sec = 0; i_sec <= 59; ++i_sec) {
                    timeinfo.tm_sec  = 0 + i_sec;
                            
                    //get one data record
                    stringstream ss;
                            
                    char buffer_date[80], buffer_time[80];
                    strftime(buffer_date,80,"%Y%m%d,", &timeinfo);
                    strftime(buffer_time,80,"%H:%M:%S,", &timeinfo);
                    num_symbol = unif_sym(generator);
                    price_dol = unif_price_dol(generator);
                    price_cent = unif_price_cent(generator);
                    volume = unif_vol(generator);
                            
                    ss << buffer_date <<buffer_time << symbol << num_symbol << "," << price_dol
                    << "." << price_cent << "," << volume << endl;
                            
                    out_file << ss.str();
                }
            }
        }

    }

    out_file.close();

    return 0;
}
