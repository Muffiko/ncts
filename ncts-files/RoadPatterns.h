#pragma once
#include <unordered_map>
#include <vector>
#include "RoadTypes.h" 

class RoadPatterns
{
private:
    RoadPatterns();  
    RoadPatterns(const RoadPatterns&) = delete;  
    RoadPatterns& operator=(const RoadPatterns&) = delete; 

    void initializePatterns();
    void setPossibleTurnDirections();

    static RoadPatterns* instance;

public:
    std::unordered_map<RoadTypes, std::vector<std::vector<unsigned int>>> patterns;
    std::unordered_map<int, std::vector<Direction>> possibleTurnDirections;


    static RoadPatterns& getInstance(); 
};