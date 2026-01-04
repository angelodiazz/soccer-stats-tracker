#include <iostream>
#include "StatsTracker.h"
#include "Input.h"

static void printMenu() {
    std::cout << "\n=== Soccer Stats Tracker ===\n"
              << "1) Add player\n"
              << "2) Record match stats for player\n"
              << "3) View player summary\n"
              << "4) List players\n"
              << "5) View all summaries\n"
              << "6) Remove player\n"
              << "7) Team summary\n"
              << "8) Save to CSV\n"
              << "9) Load from CSV\n"
              << "0) Exit\n";
}

int main() {
    StatsTracker tracker;

    while (true) {
        printMenu();
        int choice = Input::readInt("Choose an option: ", 0, 9);

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        if (choice == 1) {
            std::string id = Input::readLine("Enter player ID (unique): ", 1, 20);
            std::string name = Input::readLine("Enter player name: ", 1, 60);

            if (tracker.addPlayer(id, name)) std::cout << "Player added.\n";
            else std::cout << "Failed to add player. (ID may already exist or input invalid)\n";
        }
        else if (choice == 2) {
            std::string id = Input::readLine("Enter player ID: ", 1, 20);

            int goals = Input::readInt("Goals this match (0-20): ", 0, 20);
            int assists = Input::readInt("Assists this match (0-20): ", 0, 20);
            int minutes = Input::readInt("Minutes played (0-150): ", 0, 150);

            if (tracker.recordMatchForPlayer(id, goals, assists, minutes))
                std::cout << "Match stats recorded.\n";
            else
                std::cout << "Player not found. No stats recorded.\n";
        }
        else if (choice == 3) {
            std::string id = Input::readLine("Enter player ID: ", 1, 20);
            tracker.printPlayerSummary(id);
        }
        else if (choice == 4) {
            tracker.listPlayers();
        }
        else if (choice == 5) {
            tracker.printAllSummaries();
        }
        else if (choice == 6) {
            std::string id = Input::readLine("Enter player ID to remove: ", 1, 20);
            if (tracker.removePlayer(id)) std::cout << "Player removed.\n";
            else std::cout << "Player not found.\n";
        }
        else if (choice == 7) {
            tracker.printTeamSummary();
        }
        else if (choice == 8) {
            std::string path = Input::readLine("Enter CSV file path to save (e.g., data.csv): ", 1, 200);
            if (tracker.saveToCsv(path)) std::cout << "Saved to " << path << "\n";
            else std::cout << "Failed to save. Check path/permissions.\n";
        }
        else if (choice == 9) {
            std::string path = Input::readLine("Enter CSV file path to load (e.g., data.csv): ", 1, 200);
            int mode = Input::readInt("Replace existing data? (1 = Yes, 0 = No): ", 0, 1);
            bool replace = (mode == 1);

            if (tracker.loadFromCsv(path, replace)) std::cout << "Loaded from " << path << "\n";
            else std::cout << "Failed to load. Ensure CSV format is valid.\n";
        }
    }

    return 0;
}