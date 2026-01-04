#ifndef SOCCER_STATS_TRACKER_PLAYER_H
#define SOCCER_STATS_TRACKER_PLAYER_H
#pragma once
#include <string>

class Player {
public:
    Player(std::string id, std::string name);

    const std::string& id() const;
    const std::string& name() const;

    int goals() const;
    int assists() const;
    int minutes() const;
    int matches() const;

    void addMatchStats(int goals, int assists, int minutesPlayed);

    // Used for loading CSV where totals already exist
    bool setTotals(int matches, int goals, int assists, int minutes);

    double goalsPerMatch() const;
    double assistsPerMatch() const;
    double minutesPerMatch() const;

    std::string summary() const;

private:
    std::string id_;
    std::string name_;

    int goals_{0};
    int assists_{0};
    int minutes_{0};
    int matches_{0};
};



#endif //SOCCER_STATS_TRACKER_PLAYER_H