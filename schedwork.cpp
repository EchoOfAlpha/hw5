#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& hours, size_t currDay, unsigned int numWorkers);

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
    unsigned int numWorkers = 0;
    numWorkers = avail[0].size();

    vector<size_t> hours(avail[0].size());

    // outer for loop goes through each day
    for(size_t i = 0; i < avail.size(); i++)
    {
        vector<Worker_T> workers;
        sched.push_back(workers);

        // inner for loop goes through each worker - currently not being used
        // for(size_t j = 0; j < dailyNeed; j++)
        // {
        //     //sched[i].push_back(INVALID_ID);
        // }

    }

    if(scheduleHelper(avail, dailyNeed, maxShifts, sched, hours, 0, numWorkers))
    {
        return true;
    }

    return false;
}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& hours, size_t currDay, unsigned int numWorkers)
{
    //cout << currDay << endl;
    // Missing information check if dailyNeed was met

    // segfault protection
    if(currDay == avail.size())
    {
        return true;
    }
    // goes through each worker
    for(Worker_T i = 0; i < numWorkers; i++)
    {
       if(avail[currDay][i] == true && sched[currDay].size() <= dailyNeed)
       {
            if(hours[i] < maxShifts)
            {
                // assign that shift 
                sched[currDay].push_back(i);
                hours[i]++;
            }

            if(sched[currDay].size() == dailyNeed)
            {
                if(scheduleHelper(avail, dailyNeed, maxShifts, sched, hours, currDay + 1, numWorkers))
                {
                    return true;
                }
                sched[currDay].pop_back();
                hours[i]--;
            }
       }
    }

    // returns false when daily need not met
    if(sched[currDay].size() == dailyNeed)
    {
        return false;
    }

    // returns false if not a viable solution
    return false;
}