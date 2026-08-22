#include "RecursionToTheRescue.h"
#include "map.h"
#include <climits>
#include <iostream>
#include "Disasters.h"
using namespace std;

/* * * * Doctors Without Orders * * * */

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist. 主函数已经设Map<string, Set<string>> schedule;
 * @return Whether or not a schedule was found.
 */
// 最最关键拖慢效率的就是问选哪几个结果做加入顺序！！！！！！！！！
// 遍历的是选择（explore）， 不是start！
// 碎碎念（没啥用）：
// 下面的方法，何尝不是一种“whether to include”的多种分配（m叉数哈哈，看看printSubVectors）
// 这种分配模式很好解决了顺序的重复，关键在于不遍历patient
// 以前很多想法是遍历patient然后用set查重，这岂不是麻烦了。又多重循环又递归是什么鬼，如果真的循环，
// 那可以主函数循环helper函数做选择和探索吗？不可以。和最初我写的是等价的，重复了。
bool canAllPatientsBeSeenHelper(const Vector<Doctor>& doctors,
                                const Vector<Patient>& patients,
                                Map<string, Set<string>>& schedule,
                                Map<string, int>& remaining,
                                int index) {
    if (index == patients.size()) return true;
    Patient patient = patients[index];
    for (Doctor doctor : doctors) {
        if (patient.hoursNeeded <= remaining[doctor.name]) {
            remaining[doctor.name] -= patient.hoursNeeded;
            schedule[doctor.name].add(patient.name);
            if (canAllPatientsBeSeenHelper(doctors, patients, schedule, remaining, index + 1)) return true;
            remaining[doctor.name] += patient.hoursNeeded;
            schedule[doctor.name].remove(patient.name);
        }
    }
    return false;
}

bool canAllPatientsBeSeen(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {
    Map<string, int> remaining;
    for (Doctor doctor : doctors) {
        remaining[doctor.name] = doctor.hoursFree;
    }
    return canAllPatientsBeSeenHelper(doctors,patients, schedule, remaining, 0);
}


/* 最初我是这么写的，时间复杂度O(m*n * m^n * n!),导致TooManyEvens.dwo突破可预期的time limit
 * 核心原因在于顺序重复，[1, 2] 和 [2, 1]
bool canAllPatientsBeSeenHelper(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule,
                          Map<string, int>& remaining,
                          Set<string>& ordered) {
    if (patients.size() == ordered.size()) {
        // nothing to choose
        return true;
    }

    for (Patient patient : patients) {
        for (Doctor doctor : doctors) {
            if (patient.hoursNeeded <= remaining[doctor.name] && !ordered.contains(patient.name)) {
                schedule[doctor.name].add(patient.name); // 如果不存在key会自动创建空的。
                ordered.add(patient.name);
                remaining[doctor.name] -= patient.hoursNeeded;
                if (canAllPatientsBeSeenHelper(doctors, patients, schedule , remaining,ordered)) {
                    return true;
                }
                schedule[doctor.name].remove(patient.name);
                ordered.remove(patient.name);
                remaining[doctor.name] += patient.hoursNeeded;
            }
        }
    }
    return false;
}

bool canAllPatientsBeSeen(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {
    Set <string> ordered;
    Map<string, int> remaining;
    for (Doctor doctor : doctors) {
        remaining[doctor.name] = doctor.hoursFree;
    }
    return canAllPatientsBeSeenHelper(doctors,patients, schedule, remaining, ordered);
}
*/

/* * * * Disaster Planning * * * */

/**
 * Given a transportation grid for a country or region, along with the number of cities where disaster
 * supplies can be stockpiled, returns whether it's possible to stockpile disaster supplies in at most
 * the specified number of cities such that each city either has supplies or is connected to a city that
 * does.
 * <p>
 * This function can assume that every city is a key in the transportation map and that roads are
 * bidirectional: if there's a road from City A to City B, then there's a road from City B back to
 * City A as well.
 *
 * @param roadNetwork The underlying transportation network. 自身：邻居
 * @param numCities   How many cities you can afford to put supplies in.
 * @param locations   An outparameter filled in with which cities to choose if a solution exists. 即chosen。
 * @return Whether a solution exists.
 */
string findUncoveredCity(const Map<string, Set<string>>& roadNetwork,
                         Set<string>& locations) {
    for (string city : roadNetwork.keys()) {
        bool covered = false;
        for (string location : locations) {
            if (roadNetwork[location].contains(city) || location == city) {
                covered = true;
                break;
            }
        }
        if (!covered) return city;
    }
    return "";
}

bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& locations) {
    string city = findUncoveredCity(roadNetwork, locations);
    if (city == "") return true;
    if (numCities == 0) return false;

    Set<string> choices = roadNetwork[city];
    choices.add(city);
    for (string choice : choices) {
        locations.add(choice);
        if (canBeMadeDisasterReady(roadNetwork, numCities - 1, locations)) return true;
        locations.remove(choice);
    }
    return false;
}

/* 下面的做法是该复杂度较高思路下的很标致做法。当然，会导致VeryHard测试突破可接受的time limit
bool allCovered(const Map<string, Set<string>>& roadNetwork,
                Set<string>& locations) {
    for (string city : roadNetwork.keys()) {
        bool covered= false;
        for (string location : locations) {
            if (roadNetwork[location].contains(city) || location == city) {
                covered = true;
                break; //最近总忘
            }
        }
        if (!covered) return false;
    }
    return true;
}

bool canBeMadeDisasterReadyHelper(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& locations,
                                  const Vector<string>& cities,
                                  int index) {
    if (locations.size() > numCities || index >= cities.size()) return false;
    if (allCovered(roadNetwork, locations)) return true;
    // include
    locations.add(cities[index]);
    if (canBeMadeDisasterReadyHelper(roadNetwork, numCities, locations, cities,index+1)) return true;
    // not include
    locations.remove(cities[index]);
    if (canBeMadeDisasterReadyHelper(roadNetwork, numCities, locations, cities,index+1)) return true;

    return false;
}

bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                                int numCities,
                                Set<string>& locations) {
    Vector<string>cities;
    for (string city : roadNetwork.keys()) {
        cities.add(city);
    }
    return canBeMadeDisasterReadyHelper(roadNetwork, numCities, locations, cities,0);
}
*/

/* * * * Winning the Election * * * */

/** 这道题的亮点在于返回结构体，以及需要选择which is better
 * Given a list of the states in the election, including their popular and electoral vote
 * totals, and the number of electoral votes needed, as well as the index of the lowest-indexed
 * state to consider, returns information about how few popular votes you'd need in order to
 * win that at least that many electoral votes.
 *
 * @param electoralVotesNeeded the minimum number of electoral votes needed MORE
 * @param states All the states in the election (plus DC, if appropriate) MORE
 * @param minStateIndex the lowest index in the states Vector that SHOULD BE CONSIDERED（递归状态定义，不就是前面两道题的index）
 */
MinInfo minPopularVoteToGetAtLeast(int electoralVotesNeeded, const Vector<State>& states, int minStateIndex) {
    if (electoralVotesNeeded <= 0) {
        return {0, {}};
    }
    if (minStateIndex == states.size()) {
        return {INT_MAX, {}};
    }

    // not include this
    MinInfo skip = minPopularVoteToGetAtLeast(electoralVotesNeeded, states, minStateIndex + 1);
    // include this
    MinInfo take = minPopularVoteToGetAtLeast(electoralVotesNeeded - states[minStateIndex].electoralVotes, states, minStateIndex + 1);
    if (take.popularVotesNeeded != INT_MAX) take.popularVotesNeeded += states[minStateIndex].popularVotes / 2 + 1; // 条件防溢出。
    take.statesUsed.add(states[minStateIndex]);
    return (skip.popularVotesNeeded > take.popularVotesNeeded) ? take : skip;
}

/**
 * Given a list of all the states in an election, including their popular and electoral vote
 * totals, returns information about how few popular votes you'd need to win in order to win
 * the presidency.
 *
 * @param states All the states in the election (plus DC, if appropriate)
 * @return Information about how few votes you'd need to win the election.
 */
MinInfo minPopularVoteToWin(const Vector<State>& states) {
    int electoralVotesTotal = 0;
    for (State state : states) {
        electoralVotesTotal += state.electoralVotes;
    }
    int electoralVotesNeeded = electoralVotesTotal / 2 + 1;
    return minPopularVoteToGetAtLeast(electoralVotesNeeded, states, 0);
}
