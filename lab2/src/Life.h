#ifndef LIFE_H
#define LIFE_H
#include "Cell.h"
#include <set>
#include <string>

class Life {
private:
    std::string universeName;
    int boardWidth = 0;
    int boardHeight = 0;
    std::set<int> survivalRules;
    std::set<int> birthRules;
    std::set<Cell> liveCells;

    int countLivingNeighbours(int x, int y) const;

public:
    Life() = default;

    void advanceToNextGeneration();
    bool cellExists(const int &x, const int &y) const;
    void printUniverse() const;

    std::string getUniverseName() const;

    int getBoardWidth() const;
    int getBoardHeight() const;

    std::set<int> getSurvivalRules() const;
    std::set<int> getBirthRules() const;

    void setUniverseName(const std::string &name);
    void setBoardWidth(const int &width);
    void setBoardHeight(const int &height);
    void addSurvivalRule(const int &i);
    void addBirthRule(const int &i);
    void addCell(const int &x, const int &y);
};

#endif

