#include "StatsTracker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

int StatsTracker::indexOfId(const std::string& id) const {
    for (int i = 0; i < static_cast<int>(players_.size()); ++i) {
        if (players_[i].id() == id) return i;
    }
    return -1;
}

bool StatsTracker::addPlayer(const std::string& id, const std::string& name) {
    if (id.empty() || name.empty()) return false;
    if (indexOfId(id) != -1) return false;
    players_.emplace_back(id, name);
    return true;
}

Player* StatsTracker::findPlayer(const std::string& id) {
    int idx = indexOfId(id);
    if (idx == -1) return nullptr;
    return &players_[idx];
}

const Player* StatsTracker::findPlayer(const std::string& id) const {
    int idx = indexOfId(id);
    if (idx == -1) return nullptr;
    return &players_[idx];
}

bool StatsTracker::removePlayer(const std::string& id) {
    int idx = indexOfId(id);
    if (idx == -1) return false;
    players_.erase(players_.begin() + idx);
    return true;
}

bool StatsTracker::recordMatchForPlayer(const std::string& id, int goals, int assists, int minutes) {
    Player* p = findPlayer(id);
    if (!p) return false;
    p->addMatchStats(goals, assists, minutes);
    return true;
}

void StatsTracker::listPlayers() const {
    if (players_.empty()) {
        std::cout << "No players yet.\n";
        return;
    }
    std::cout << "Players:\n";
    for (const auto& p : players_) {
        std::cout << " - " << p.name() << " (ID: " << p.id() << ")\n";
    }
}

void StatsTracker::printPlayerSummary(const std::string& id) const {
    const Player* p = findPlayer(id);
    if (!p) {
        std::cout << "Player not found.\n";
        return;
    }
    std::cout << "\n" << p->summary() << "\n";
}

void StatsTracker::printAllSummaries() const {
    if (players_.empty()) {
        std::cout << "No players yet.\n";
        return;
    }
    std::cout << "\n=== All Player Summaries ===\n\n";
    for (const auto& p : players_) {
        std::cout << p.summary() << "\n";
    }
}

/* =========================
   CSV Helpers
   ========================= */

std::string StatsTracker::escapeCsv(const std::string& s) {
    bool needsQuotes = false;
    for (char c : s) {
        if (c == ',' || c == '"' || c == '\n' || c == '\r') {
            needsQuotes = true;
            break;
        }
    }
    if (!needsQuotes) return s;

    std::string out;
    out.reserve(s.size() + 2);
    out.push_back('"');
    for (char c : s) {
        if (c == '"') out += "\"\"";
        else out.push_back(c);
    }
    out.push_back('"');
    return out;
}

bool StatsTracker::parseCsvLine(const std::string& line, std::vector<std::string>& outFields) {
    outFields.clear();
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (inQuotes) {
            if (c == '"') {
                // double quote inside quoted field => literal quote
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    field.push_back('"');
                    ++i;
                } else {
                    inQuotes = false;
                }
            } else {
                field.push_back(c);
            }
        } else {
            if (c == '"') {
                inQuotes = true;
            } else if (c == ',') {
                outFields.push_back(field);
                field.clear();
            } else {
                field.push_back(c);
            }
        }
    }
    outFields.push_back(field);
    return !inQuotes; // invalid if still in quotes at end
}

bool StatsTracker::saveToCsv(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file) return false;

    file << "id,name,matches,goals,assists,minutes\n";
    for (const auto& p : players_) {
        file << escapeCsv(p.id()) << ","
             << escapeCsv(p.name()) << ","
             << p.matches() << ","
             << p.goals() << ","
             << p.assists() << ","
             << p.minutes() << "\n";
    }
    return true;
}

bool StatsTracker::loadFromCsv(const std::string& filePath, bool replaceExisting) {
    std::ifstream file(filePath);
    if (!file) return false;

    std::string line;
    std::vector<std::string> fields;

    if (!std::getline(file, line)) return false;

    if (replaceExisting) players_.clear();

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (!parseCsvLine(line, fields)) {
            // malformed CSV line
            return false;
        }

        // Expect: id,name,matches,goals,assists,minutes
        if (fields.size() != 6) return false;

        const std::string id = fields[0];
        const std::string name = fields[1];

        // Convert ints safely
        auto toInt = [](const std::string& s, int& out) -> bool {
            try {
                size_t pos = 0;
                long v = std::stol(s, &pos);
                if (pos != s.size()) return false;
                if (v < 0 || v > 1'000'000) return false; // sanity cap
                out = static_cast<int>(v);
                return true;
            } catch (...) {
                return false;
            }
        };

        int matches{}, goals{}, assists{}, minutes{};
        if (!toInt(fields[2], matches)) return false;
        if (!toInt(fields[3], goals)) return false;
        if (!toInt(fields[4], assists)) return false;
        if (!toInt(fields[5], minutes)) return false;

        if (id.empty() || name.empty()) return false;

        // Avoid duplicates if loading into existing list
        if (indexOfId(id) != -1) {
            // If duplicate ID, fail to keep data clean
            return false;
        }

        Player p{id, name};
        if (!p.setTotals(matches, goals, assists, minutes)) return false;
        players_.push_back(p);
    }

    return true;
}

/* =========================
   Team Summary
   ========================= */

void StatsTracker::printTeamSummary() const {
    if (players_.empty()) {
        std::cout << "No players yet.\n";
        return;
    }

    long totalGoals = 0, totalAssists = 0, totalMinutes = 0, totalMatches = 0;

    const Player* topScorer = &players_[0];
    const Player* topAssist = &players_[0];
    const Player* topMinutes = &players_[0];

    for (const auto& p : players_) {
        totalGoals += p.goals();
        totalAssists += p.assists();
        totalMinutes += p.minutes();
        totalMatches += p.matches();

        if (p.goals() > topScorer->goals()) topScorer = &p;
        if (p.assists() > topAssist->assists()) topAssist = &p;
        if (p.minutes() > topMinutes->minutes()) topMinutes = &p;
    }

    std::cout << "\n=== Team Summary ===\n";
    std::cout << "Players: " << players_.size() << "\n";
    std::cout << "Total Matches Logged (sum of player matches): " << totalMatches << "\n";
    std::cout << "Total Goals: " << totalGoals << "\n";
    std::cout << "Total Assists: " << totalAssists << "\n";
    std::cout << "Total Minutes: " << totalMinutes << "\n\n";

    std::cout << "Top Scorer: " << topScorer->name()
              << " (ID: " << topScorer->id()
              << ") - " << topScorer->goals() << " goals\n";

    std::cout << "Top Assists: " << topAssist->name()
              << " (ID: " << topAssist->id()
              << ") - " << topAssist->assists() << " assists\n";

    std::cout << "Most Minutes: " << topMinutes->name()
              << " (ID: " << topMinutes->id()
              << ") - " << topMinutes->minutes() << " minutes\n";
}