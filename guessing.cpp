#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    char level;
    int lives, kick, usedlives = 0;
    srand(time(NULL));
    const int SECRET_NUMBER = rand() % 100;
    bool stillTrying = true;
    double points = 1000;

    cout << "---------------------------------" << endl;
    cout << "- Welcome to The Guessing Game! -" << endl;
    cout << "---------------------------------" << endl;

    cout << "Choose your difficulty level: (E) Easy (M) Medium (H) Hard" << endl;
    cin >> level;

    if (level == 'E'){
        lives = 15;
    }else if (level == 'M'){
        lives = 10;
    }else if (level == 'H'){
        lives = 5;
    }

    // cout << "Your secret number is " << SECRET_NUMBER << "." << endl;
    while (stillTrying && lives > 0){
        cout << "Guess the number: ";
        cin >> kick;
        cout << "YOU GUESS WAS NUMBER " << kick << "." << endl;
        lives--;
        usedlives++;

        points = points - abs(kick - SECRET_NUMBER)/2.0;

        if (kick == SECRET_NUMBER){
            cout << "\n\nCONGRATULATIONS!! YOU GUESSED IT RIGHT USING " << usedlives << " lives." << endl;
            stillTrying = false;
        }else if (kick > SECRET_NUMBER){
            cout << "Nah... your guess was too high. Lower it down" << endl;
        }else if (kick < SECRET_NUMBER){
            cout << "Level up! Your guess is too low." << endl;
        }
    }
    if (!lives){
        cout << "LIFE ENDED!!!" << endl;
    }
    cout.precision(2);
    cout << fixed;
    cout << "-------- TOTAL POINTS: " << points << endl;
}
