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
void addMoreWords();

int main(){
    // const string SECRET_WORD = "caçarola";
    const string SECRET_WORD = chooseSecretWord();
    if (SECRET_WORD.size() == 1){
        cout << "Cannot find secret words file." << endl;
        exit(0);
    }

    map<char, bool> hasGuessed;
    vector<char> wrongKicks;
    bool hasMissed=true, notHanged=true;
    char kick, res;

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
    cout << "\nDo you wish to add more words to the database? [y/n]" << endl;
    cin >> res;
    if (res == 'y')
        addMoreWords();
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
    ifstream file("secret_words.txt");
    if (!file.fail()){
        vector<string> words;
        string line;
        while (getline(file, line))
            words.push_back(line);
        file.close();
        srand(time(NULL));
        return words[rand() % words.size()];
    }
    return "!";
}

void addMoreWords(){
    ofstream outfile;
    string newWord;
    cout << "- Type the new word [english and lowercased] -" << endl;
    cin >> newWord;
    outfile.open("secret_words.txt", std::ios_base::app); // append instead of overwrite
    outfile << "\n";
    outfile << newWord;
    outfile.close();

    cout << "\n---- Word successfully added!" << endl;
}
