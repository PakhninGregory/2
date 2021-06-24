#pragma once

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;
namespace func {
    /// <summary>
    /// Generic метод для ввода не чисел и параллельной обработки невалидных значений
    /// </summary>
    /// <typeparam name="T">Тип необходимых данных</typeparam>
    /// <param name="input">Выходящая результирующая переменная</param>
    template<typename T>
    void ValidateInput(T& input) {
        do {
            cin >> input;
            if (cin.fail()) {
                cout << "Введено некорректное значение. Повторите ввод:  ";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            return;
        } while (true);
    }

    /// <summary>
    /// TryParse но от мира говна
    /// </summary>
    /// <typeparam name="T">Либо int, либо float</typeparam>
    /// <param name="newVar">Переменная для ввода данных</param>
    /// <param name="inputData">Вводимая строка</param>
    /// <returns>Успешность парсинга. True - спарсился int, False - спарсился float, Exception - введена строка</returns>
    template<typename T>
    bool TryParse_trash(T& newVar, string& inputData) {
        std::stringstream stream(inputData);
        char test;

        if ((!(stream >> newVar)) || (stream >> test)) {
            if (typeid(newVar) != typeid(float)) {
                float test;
                if (TryParse_trash(test, inputData)) {
                    return false;
                }
            }

            throw exception("Введена строка. Выхожу из меню");
        }

        return true;
    }

    /// <summary>
    /// Проверка на число для строки
    /// </summary>
    /// <param name="test">Строка для проверки</param>
    /// <returns>True - если строка число, False - если нет</returns>
    bool IsNumericStr(string test);

    /// <summary>
    /// Метод для получения случайного значения в диапазоне
    /// </summary>
    /// <param name="lowBar">Нижняя  граница</param>
    /// <param name="topBar">Верхняя граница</param>
    /// <returns></returns>
    int Randomize(int lowBar, int topBar);

    /// <summary>
    /// Метод для установки в массив случайных значений. Граница - от 1 до INT8_MAX 
    /// </summary>
    /// <param name="arr">Динамический массив</param>
    /// <param name="length">Количнство элементов</param>
    void Randomize(int* arr, int length);

    /// <summary>
    /// Метод аналог Replace
    /// </summary>
    /// <param name="str">Строка в которой нужна замена</param>
    /// <param name="from">Подстрока для замены</param>
    /// <param name="to">Подстрока для того, на что заменить</param>
    void replaceText(string& str, const string& from, const string& to);

    /// <summary>
    /// Метод валидации числа-выбора в выбранных границах
    /// </summary>
    /// <param name="lowBar">Нижняя граница</param>
    /// <param name="highBar">Верхняя граница</param>
    /// <returns>Число-выбор</returns>
    int32_t InputHub(int32_t lowBar, int32_t highBar);

    /// <summary>
    /// Метод для форматированной печати условия задачи
    /// </summary>
    /// <param name="condition">Условие задачи</param>
    void PrintCondition(string condition);

    /// <summary>
    /// Метод аналог Split
    /// </summary>
    /// <param name="s">Строка</param>
    /// <param name="delimiter">Разделитель</param>
    /// <returns>Массив строк</returns>
    vector<string> Split(const string& s, char delimiter);

    /// <summary>
    /// Метод аналог Trim
    /// </summary>
    /// <param name="s">Строка</param>
    /// <returns>Очищенная строка</returns>
    string Trim(string& s);
}





bool func::IsNumericStr(string message) {
    std::stringstream stream(message);
    char test;
    long result;

    if ((!(stream >> result)) || (stream >> test))
        return false;

    return true;
}

int func::Randomize(int lowBar, int topBar) {
    return (rand() % (topBar - lowBar) + lowBar);
}

void func::Randomize(int* arr, int length) {
    for (int i = 0; i < length; i++)
        arr[i] = Randomize(1, INT8_MAX);
}

void func::replaceText(string& str, const string& from, const string& to) {
    if (from.empty())
        return;

    int16_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
};

int32_t func::InputHub(int32_t lowBar, int32_t topBar) {
    if (lowBar > topBar)
        throw new exception("Проблема с границами в inputHub'e");

    int userChoise = 0;
    do {
        ValidateInput(userChoise);
        if (userChoise < lowBar || userChoise > topBar) cout << "Такого варианта нет, повторите попытку : ";
    } while (userChoise < lowBar || userChoise > topBar);

    return userChoise;
}

void func::PrintCondition(string condition) {
    system("CLS");
    cout << "###################\n";
    cout << "Условие:\n";

    vector<string> splitedCond = Split(condition, '.');
    for (int i = 0; i < splitedCond.size(); i++)
        cout << Trim(splitedCond[i]) << ".\n";

    //cout << condition << "\n";
    cout << "###################\n\n";
    cout << "Работа программы:\n\n";
}

vector<string> func::Split(const string& s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

string func::Trim(string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));

    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());

    return s;
}





#include <windows.h>
HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
const int moveX = 10, moveY = 10;

#pragma region Fibonachi
long fib_cycle(short iter) {
    short cpos = 1;
    long result = 1, ppos1 = 1;

    while (cpos++ < iter) {
        long tempVault = ppos1;
        ppos1 = result;
        result += tempVault;
    }

    return result;
}



long fib_rec(int pos) {
    return (pos <= 1) ? 1 : fib_rec(pos - 1) + fib_rec(pos - 2);
}
#pragma endregion

#pragma region FractalMinkovskogo
void moveRight(float& x, float& y, int& reachX, int& reachY, int stage);
void moveDown(float& x, float& y, int& reachX, int& reachY, int stage);
void moveLeft(float& x, float& y, int& reachX, int& reachY, int stage);
void moveUp(float& x, float& y, int& reachX, int& reachY, int stage);


void moveRight(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveRight(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX += moveX;
        for (x; x < reachX; x += 0.05)
            SetPixel(hdc, x, y, RGB(8, 232, 255));
    }
}


void moveDown(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveDown(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachY += moveY;
        for (y; y < reachY; y += 0.05)
            SetPixel(hdc, x, y, RGB(42, 42, 255));
    }
}

void moveLeft(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
        moveDown(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX -= moveX;
        for (x; x > reachX; x -= 0.05)
            SetPixel(hdc, x, y, RGB(25, 17, 255));
    }
}


void moveUp(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveUp(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveLeft(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
        moveRight(x, y, reachX, reachY, stage - 1);
        moveUp(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachY -= moveY;
        for (y; y > reachY; y -= 0.05)
            SetPixel(hdc, x, y, RGB(255, 213, 65));
    }
}

#pragma endregion

#pragma region Koh

void moveLeft_live(float& x, float& y, int& reachX, int& reachY, int stage);
void moveRigthDown_live(float& x, float& y, int& reachX, int& reachY, int stage);
void moveLeftUp_live(float& x, float& y, int& reachX, int& reachY, int stage);
void moveLeftDown_live(float& x, float& y, int& reachX, int& reachY, int stage);
void moveRigth_live(float& x, float& y, int& reachX, int& reachY, int stage);
void moveRigthUp_live(float& x, float& y, int& reachX, int& reachY, int stage);


void moveLeft_live(float& x, float& y, int& reachX, int& reachY, int stage)
{
    reachX -= moveX;
    for (x; x > reachX; x -= 0.05)
        SetPixel(hdc, x, y, RGB(0, 145, 255));
}

void moveRigthDown_live(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveRigthDown_live(x, y, reachX, reachY, stage - 1);
        moveRigth_live(x, y, reachX, reachY, stage - 1);
        moveLeftDown_live(x, y, reachX, reachY, stage - 1);
        moveRigthDown_live(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX += moveX;
        reachY += moveY;
        for (x, y; x < reachX; x += 0.05, y += 0.05)
            SetPixel(hdc, x, y, RGB(0, 255, 128));
    }
}

void moveLeftUp_live(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveLeftUp_live(x, y, reachX, reachY, stage - 1);
        moveLeft_live(x, y, reachX, reachY, stage - 1);
        moveRigthUp_live(x, y, reachX, reachY, stage - 1);
        moveLeftUp_live(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX -= moveX;
        reachY -= moveY;
        for (x, y; x > reachX; x -= 0.05, y -= 0.05)
            SetPixel(hdc, x, y, RGB(9, 255, 0));
    }
}

void moveLeftDown_live(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveLeftDown_live(x, y, reachX, reachY, stage - 1);
        moveRigthDown_live(x, y, reachX, reachY, stage - 1);
        moveLeft_live(x, y, reachX, reachY, stage - 1);
        moveLeftDown_live(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX -= moveX;
        reachY += moveY;
        for (x, y; x > reachX; x -= 0.05, y += 0.05)
            SetPixel(hdc, x, y, RGB(239, 255, 0));
    }
}

void moveRigth_live(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveRigth_live(x, y, reachX, reachY, stage - 1);
        moveRigthUp_live(x, y, reachX, reachY, stage - 1);
        moveRigthDown_live(x, y, reachX, reachY, stage - 1);
        moveRigth_live(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX += moveX;
        for (x; x < reachX; x += 0.05)
            SetPixel(hdc, x, y, RGB(17, 0, 255));
    }
}

void moveRigthUp_live(float& x, float& y, int& reachX, int& reachY, int stage)
{
    if (stage > 1) {
        moveRigthUp_live(x, y, reachX, reachY, stage - 1);
        moveLeftUp_live(x, y, reachX, reachY, stage - 1);
        moveRigth_live(x, y, reachX, reachY, stage - 1);
        moveRigthUp_live(x, y, reachX, reachY, stage - 1);
    }
    else {
        reachX += moveX;
        reachY -= moveY;
        for (x, y; x < reachX; x += 0.05, y -= 0.05)
            SetPixel(hdc, x, y, RGB(0, 255, 255));
    }
}
#pragma endregion


void FractHub() {
    cout << "Введите размерность от " << 1 << " до " << 5 << " : ";
    int test = func::InputHub(1, 5);
    system("cls");
    float x = 300, y = 300;
    int reachX = 300, reachY = 300;

    moveRight(x, y, reachX, reachY, test);
    moveDown(x, y, reachX, reachY, test);
    moveLeft(x, y, reachX, reachY, test);
    moveUp(x, y, reachX, reachY, test);
}

void KohHub() {
    cout << "Введите размерность от " << 1 << " до " << 6 << " : ";
    int test = func::InputHub(1, 6);
    system("cls");
    float x = 200, y = 1100;
    int reachX = 200, reachY = 1100;

    moveRigth_live(x, y, reachX, reachY, test);
    moveRigthUp_live(x, y, reachX, reachY, test);
    moveRigthDown_live(x, y, reachX, reachY, test);
    moveRigth_live(x, y, reachX, reachY, test);
}

void FibHub() {
    system("cls");
    for (int i = 0; i < 8; i++) {
        cout << "Значение фибб./цикл/   (" << i << ") = " << fib_cycle(i) << '\n';
        cout << "Значение фибб./рекурс/ (" << i << ") = " << fib_rec(i) << "\n\n";
    }
    system("pause");
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Введите номер задачи (от 1 до 3): ";
    int labNum = func::InputHub(1, 3);

    switch (labNum) {
    case 1: FibHub(); break;
    case 2: FractHub(); break;
    case 3: KohHub(); break;
    }
}