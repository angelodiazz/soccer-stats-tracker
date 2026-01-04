#ifndef SOCCER_STATS_TRACKER_STATSTRACKER_H
#define SOCCER_STATS_TRACKER_STATSTRACKER_H
#pragma once
#include "Player.h"
#include <vector>
#include <string>
#include <optional>

class StatsTracker {
public:
    // Core
    bool addPlayer(const std::string& id, const std::string& name);
    Player* findPlayer(const std::string& id);
    const Player* findPlayer(const std::string& id) const;
    bool removePlayer(const std::string& id);
    bool recordMatchForPlayer(const std::string& id, int goals, int assists, int minutes);

    // Display
    void listPlayers() const;
    void printPlayerSummary(const std::string& id) const;
    void printAllSummaries() const;

    // CSV persistence
    // CSV format:
    // id,name,matches,goals,assists,minutes
    bool saveToCsv(const std::string& filePath) const;
    bool loadFromCsv(const std::string& filePath, bool replaceExisting = true);

    // Team summary
    void printTeamSummary() const;

private:
    std::vector<Player> players_;

    int indexOfId(const std::string& id) const;

    static std::string escapeCsv(const std::string& s);
    static bool parseCsvLine(const std::string& line, std::vector<std::string>& outFields);
};



#endif //SOCCER_STATS_TRACKER_STATSTRACKER_H