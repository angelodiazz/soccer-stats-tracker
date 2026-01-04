#include "Player.h"
#include <sstream>
#include <iomanip>

Player::Player(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {}

const std::string& Player::id() const { return id_; }
const std::string& Player::name() const { return name_; }

int Player::goals() const { return goals_; }
int Player::assists() const { return assists_; }
int Player::minutes() const { return minutes_; }
int Player::matches() const { return matches_; }

void Player::addMatchStats(int g, int a, int m) {
    if (g < 0) g = 0;
    if (a < 0) a = 0;
    if (m < 0) m = 0;

    goals_ += g;
    assists_ += a;
    minutes_ += m;
    matches_ += 1;
}

bool Player::setTotals(int m, int g, int a, int mins) {
    if (m < 0 || g < 0 || a < 0 || mins < 0) return false;
    matches_ = m;
    goals_ = g;
    assists_ = a;
    minutes_ = mins;
    return true;
}

double Player::goalsPerMatch() const {
    return matches_ == 0 ? 0.0 : static_cast<double>(goals_) / matches_;
}

double Player::assistsPerMatch() const {
    return matches_ == 0 ? 0.0 : static_cast<double>(assists_) / matches_;
}

double Player::minutesPerMatch() const {
    return matches_ == 0 ? 0.0 : static_cast<double>(minutes_) / matches_;
}

std::string Player::summary() const {
    std::ostringstream out;
    out << "Player: " << name_ << " (ID: " << id_ << ")\n"
        << "Matches: " << matches_ << "\n"
        << "Goals:   " << goals_ << "\n"
        << "Assists: " << assists_ << "\n"
        << "Minutes: " << minutes_ << "\n"
        << std::fixed << std::setprecision(2)
        << "G/Match: " << goalsPerMatch() << "\n"
        << "A/Match: " << assistsPerMatch() << "\n"
        << "Min/Match: " << minutesPerMatch() << "\n";
    return out.str();
}