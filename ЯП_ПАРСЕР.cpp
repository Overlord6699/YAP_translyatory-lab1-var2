#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;





int retrieveChoice(const int minValue, const int maxValue)
{
    int choice = 0;
    bool isIncorrect;

    cout << "\nВведите ваш выбор:";

    do {
        isIncorrect = false;
        try {
            cin >> choice;
        }
        catch (...) {
            cout << "Введено некорректное значение. Введите число: " << endl;
            isIncorrect = true;
        }
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число от " << minValue << " до " << maxValue << ": " << endl;
            isIncorrect = true;
        }
        if (choice < minValue || choice > maxValue && !isIncorrect) {
            isIncorrect = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число от " << minValue << " до " << maxValue << ": " << endl;
        }
    } while (isIncorrect);
    return choice;
}

string inputPathToFile() {
    bool isIncorrect;
    string path;

    do {
        isIncorrect = false;
        cin >> path;
        ifstream file(path);

        if (!file.is_open()) {
            cout << "Файл не найден! Введите правильную ссылку: ";
            isIncorrect = true;
        }

    } while (isIncorrect);

    return path;
}

vector<string> readLines(const string& path) {
    fstream fStream(path);
    vector<string> input;

    for (string line; getline(fStream, line);) {
        input.push_back(line);
    }

    return input;
}

vector<string> getUserInputFromConsole()
{
    vector<string> input;
    cout << "\nВведите вашу строку:\n";

    string stop = "stop";
    string word;

    fflush(stdin);
    while (getline(cin, word, '\n'))
    {
        if (word != "") {
            if (word == stop)
                break;

            input.push_back(word);
        } 
    }

    return input;
}

void processUserChoice(int& choice)
{
    int tmpElem;
    int value;

    /*
    do
    {
        switch (choice)
        {
        case 1:
            break;
        case 2:
            cout << "\n\t\tДобавление нового элемента." << endl;

            value = retrieveElem();
            q1.Push(value);

            break;
        case 3:
            cout << "\n\t\tУдаление элемента." << endl;
            if (!q1.isEmpty()) {
                q1.Pop();
                cout << "\nЭлемент был успешно удалён." << endl;
            }
            else {
                cout << "\nОчередь пуста! Удаление невозможно." << endl;
            }
            break;
        case 4:
            if (!q1.isEmpty()) {
                DoTask(q1);
            }
            else
                cout << "\nОчередь пуста!." << endl;
            break;
        case 5:
            cout << "\n\t\tОтображение очереди." << endl;
            q1.Print();
            cout << endl;
            break;

        }
        cout << endl;
        if (choice != 1) {
            system("pause");
            system("cls");
            processUserChoice(q1, choice);
        }
    } while (choice != 1);
    */
}

int countSymbols(const vector<string>& text, const regex symbol)
{
    int counter = 0;

    for (int i = 0; i < text.size(); i++) {
        auto words_begin =
            sregex_iterator(text[i].begin(), text[i].end(), symbol);
        auto words_end = sregex_iterator();

        counter += distance(words_begin, words_end);
    }

    return counter;
}

void changeNeededSymbols(vector<string>& text, const int numOfSymbols)
{
    int mySymbol = 39; //аски код апострофа
    int pos = 0;
    bool isEmpty; //учёт строк по типу ''

    for (int n = 0; n < text.size(); n++)
    {
        pos = 0;
        isEmpty = false;

        if (text[n].size() == 2)
            isEmpty = true;

        for (int i = 0; i < numOfSymbols; i++)
        {
            if(pos < text[n].size())
            { 
                pos = text[n].find("'", pos);

                if (text[n][pos + 1] != (char)mySymbol || isEmpty) { 
                    text[n].replace(pos, 1, 2, (char)mySymbol);
                }

                pos += 2;
            }
            else
                break;
            
        }
    }
       
}

bool checkInput(const int numOfSymb, const int numOfLit)
{
    bool isCorrect = true;
    return ((numOfSymb % 2 == 0) && (numOfSymb / 2 == numOfLit));
}

void outputData(const vector<string>& text)
{
    cout << "\nВывод:\n";

    for (int i = 0; i < text.size(); i++)
        cout << text[i] << '\n';
}

int main() {

    setlocale(LC_ALL, "RUS");

    static const regex litReg(R"(\'.*\')");
    static const regex symReg(R"(\')");
    static const regex doubleSymReg(R"((^\'[^\'{2}]*\'{2}[^\'{2}]*|[^\'{2}]*\'{2}[^\'{2}]*\'$|[\S]+\'{2}))");

    vector<string> input;

    cout << "Откуда Вы хотите считать данные? ";
    cout << "\n1 - файл";
    cout << "\n2 - консоль";

    int choice = retrieveChoice(1, 2);

 

    if (choice == 1) {
        cout << "Введите путь к файлу с кодом: ";
        input = readLines(inputPathToFile());
    }
    else
    {
        input = getUserInputFromConsole();
    }

    int numOfSymbols = countSymbols(input, symReg);
    int numOfDoubleSym = countSymbols(input, doubleSymReg);
    int numOfLiterals = countSymbols(input, litReg);

    cout << "\nКол-во одиночных апострофов: " << numOfSymbols;
    cout << "\nКол-во двойных апострофов: " << numOfDoubleSym;
    cout << "\nКол-во строковых литералов: " << numOfLiterals;

    //numOfSymbols - numOfDoubleSym * 2 = кол-во закрывающих апострафов
    if(checkInput(numOfSymbols - numOfDoubleSym * 2, numOfLiterals)){
        cout << "\nВвод корректный";

        changeNeededSymbols(input, numOfSymbols);

        outputData(input);
    }else
        cout << "\nВвод некорректный!";


}