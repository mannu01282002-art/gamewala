#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

struct Question {
    string text;
    string options[4];
    int correctAns;
};

struct Player {
    string name;
    int score = 0;
    double totalTimeTaken = 0;
};

// Timer function prototype
void playUnit(int unitNum, vector<Question>& qList, Player& p) {
    cout << "\n==========================================" << endl;
    cout << "          STARTING UNIT " << unitNum << " (20 Questions)      " << endl;
    cout << "==========================================" << endl;

    int correctCount = 0;

    for (int i = 0; i < qList.size(); i++) {
        cout << "\n[Q" << i + 1 << "] " << qList[i].text << endl;
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << ". " << qList[i].options[j] << endl;
        }

        auto start = chrono::high_resolution_clock::now();
        
        int userAns;
        cout << "Enter option (1-4) [Fast answer = Extra Points!]: ";
        cin >> userAns;

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> timeTaken = end - start;

        if (timeTaken.count() > 15.0) {
            cout << "⏱️ TIME OUT! 15 seconds se zyada le liye.\n";
        } else if (userAns == qList[i].correctAns) {
            int speedBonus = (15 - (int)timeTaken.count()) * 10;
            int points = 100 + speedBonus;
            p.score += points;
            correctCount++;
            cout << "✅ CORRECT! Time: " << timeTaken.count() << "s | Points: +" << points << endl;
        } else {
            cout << "❌ WRONG ANSWER!\n";
        }

        p.totalTimeTaken += timeTaken.count();
    }

    if (correctCount >= 15) {
        cout << "\n🎉 UNIT " << unitNum << " CLEARED! Moving to Next Unit...\n";
    } else {
        cout << "\n⚠️ UNIT FAILED! Need at least 15/20 correct answers to unlock next unit.\n";
    }
}

int main() {
    Player p1;
    cout << "Enter Player Name: ";
    cin >> p1.name;

    // Yahan har unit ke 20 questions vector me add honge
    vector<Question> unit1 = {
        {"Vector quantity kaunsi hai?", {"Mass", "Velocity", "Time", "Energy"}, 2},
        // ... Total 20 questions
    };

    playUnit(1, unit1, p1);

    cout << "\n--- FINAL LEADERBOARD ---" << endl;
    cout << "Player: " << p1.name << " | Score: " << p1.score << " | Total Time: " << p1.totalTimeTaken << "s" << endl;

    return 0;
}
