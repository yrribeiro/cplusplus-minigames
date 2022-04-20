#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool verifyLetter(char kick, string sw);
void showVector(vector<char> vc);
bool verifyPlayerHasWon(string sw, map<char, bool> mapping);
bool verifyHanging(vector<char> vc);
void showLoserMessage(string sw);
string chooseSecretWord();

int main(){
    // const string SECRET_WORD = "oliver";
    const string SECRET_WORD = chooseSecretWord();
    map<char, bool> hasGuessed;
    vector<char> wrongKicks;
    bool hasMissed=true, notHanged=true;
    char kick;
    // cout << SECRET_WORD << endl;

    cout << "---------------------------------" << endl;
    cout << "- Welcome to The Hangman Game! -" << endl;
    cout << "---------------------------------" << endl;

    while (hasMissed && notHanged){
        for (char letter : SECRET_WORD){
            if (hasGuessed[letter]){
                cout << letter << " ";
            }else{
                cout << "_ ";
            }
        }

        cout << "\n\n- Guess a letter:" << endl;
        cin >> kick;
        kick = tolower(kick);

        if (verifyLetter(kick, SECRET_WORD)){
            hasGuessed[kick] = true;
            cout << "\n\nCONGRATULATIONS!! YOU GUESSED IT RIGHT" << endl;
            hasMissed = verifyPlayerHasWon(SECRET_WORD, hasGuessed);
        }else{
            wrongKicks.push_back(kick);
            cout << "\n\nYou missed! The man is closer to his death..." << endl;
            notHanged = verifyHanging(wrongKicks);
        }

        cout << "- Wrong letters: ";
        showVector(wrongKicks);
        cout << "\n\n";
    }

    if (!notHanged)
        showLoserMessage(SECRET_WORD);
}

bool verifyLetter(char kick, string sw){
    return (sw.find(kick) != std::string::npos) ? 1 : 0;
}

void showVector(vector<char> vc){
    for (char letter : vc){
        cout << letter << " ";
    }
}

bool verifyPlayerHasWon(string sw, map<char, bool> mapping){
    for (char letter : sw){
        if (!mapping[letter])
            return true;
    }
    return false;
}

bool verifyHanging(vector<char> vc){
    return vc.size() < 6;
}

void showLoserMessage(string sw){
    cout << "---------------------------------" << endl;
    cout << "- You've sentenced the man to die by hanging!! -" << endl;
    cout << "---------------------------------" << endl;
    cout << "The right word was [" << sw << "]" << endl;
}

string chooseSecretWord(){
    vector<string> words;
    string line;
    ifstream file("secret_words.txt");
    while (getline(file, line)) words.push_back(line);

    srand(time(NULL));
    return words[rand() % words.size()];
}
