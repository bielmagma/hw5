#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool helper(
    size_t row,
    size_t column,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    map<Worker_T, int> track);

bool check_ifValid(unsigned int i, map<Worker_T, int> track);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    map<Worker_T, int> track;

      for(unsigned int i = 0; i < avail[0].size(); i++){

        track.insert(make_pair(i, maxShifts));

      }

    for(unsigned int i = 0; i < avail.size(); i++){

        vector<Worker_T> vect(dailyNeed, INVALID_ID);
        sched.push_back(vect);

    }


    bool result = helper(0,0, avail, dailyNeed, maxShifts, sched, track);
    return result;

  
}

bool helper(
    size_t row,
    size_t column,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    map<Worker_T, int> track)
{
    if(row == sched.size()){
        return true;
    } else{
      for(unsigned int i = 0; i < avail[row].size(); i++){
        if(sched[row].begin() + column != find(sched[row].begin(), sched[row].begin() + column, i)) continue;
        if(avail[row][i]){
            if(check_ifValid(i, track)){
              sched[row][column] = i;
              track[i] = track[i] - 1;
              if(column == sched[row].size()-1){
                bool status = helper(row+1,0, avail, dailyNeed, maxShifts, sched, track);
                if(status){
                  return true;
                } else{
                  track[i] = track[i] + 1;
                  sched[row][column] = 0;
                }
              }else{
                bool status = helper(row,column+1, avail, dailyNeed, maxShifts, sched, track);
                if(status){
                  return true;
                } else{
                  track[i] += 1;
                  sched[row][column] = 0;
                }
              }
            }
        }
      }
    }
        
    return false;
}

bool check_ifValid(unsigned int i,map<Worker_T, int> track){
	
  map<Worker_T, int>::iterator iterator; 

  for(iterator = track.begin(); iterator != track.end(); iterator++){
    if((*iterator).first == i)  if((*iterator).second > 0) return true;
  }

  return false;
}