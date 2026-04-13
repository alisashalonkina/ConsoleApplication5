//Вариант 25.
//Занятие 9: Определить комбинированный(структурный) тип для представления информации
//по горным вершинам, состоящей из названия вершины, ее высоты, стране
//местонахождения, типе горы(вулканическая, складчатая, платообразная и др.).
//Ввести информацию по 20 вершинам.Вывести количество вершин на территории
//Швейцарии.Затем вывести информацию, отсортированную по возрастанию высоты
//вершины(рационально переставлять все поля структуры разом).Вывести сведения
//по странам местонахождения 3 - х шеститысячников.Реализовать функцию
//изменения данных горной вершины по ее высоте, а не по названию.В отдельный
//массив поместить все горные вершины в одной стране(страну вводить с
//клавиатуры).Реализовать вывод отфильтрованных данных в виде оберточной
//функции.
//Занятие 10: Считать из текстового файла данные числового поля. Сделать чтение / запись своей структуры в бинарный файл.
//Оформить в виде подпрограмм.
#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
using namespace std;

struct country {
    char name[30];      // название страны
    char continent[50]; // континент
};

enum typemountain {
    folded,   // складчатая
    volcanic, // вулканическая
    dome      // купольная
};

struct mountain {
    char name[30];          // название горной вершины
    int height;             // высота вершины в метрах
    country Country;        // страна местонахождения (вложенная структура) 
    typemountain Type;      // тип горной вершины (перечисляемый тип данных)
};

// функция вывода типа горной вершины
void print_typemountain(typemountain Type) {
    if (Type == folded) cout << "складчатая";
    else if (Type == volcanic) cout << "вулканическая";
    else if (Type == dome) cout << "купольная";
}

// функция вывода горной вершины
void print_mountain(mountain Mountain, int num) {
    cout << "\nГОРА " << num + 1 << endl; // num + 1, чтобы нумерация начиналась с 1, а не с 0
    cout << "Название: " << Mountain.name << endl;
    cout << "Высота: " << Mountain.height << "м" << endl;
    cout << "Страна: " << Mountain.Country.name << endl;
    cout << "Континент: " << Mountain.Country.continent << endl;
    cout << "Тип: ";
    print_typemountain(Mountain.Type);
    cout << endl;
}

// Количество вершин на территории Швейцарии
int count_mountains_Switzerland(mountain mountains[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(mountains[i].Country.name, "Швейцария") == 0) {
            count++;
        }
    }
    return count;
}

// Сортировка вершин по возрастанию высоты (сортировка пузырьком)
void sort_mountains_byheight(mountain mountains[], int size) {
    mountain t;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mountains[j].height > mountains[j + 1].height) {
                t = mountains[j];
                mountains[j] = mountains[j + 1];
                mountains[j + 1] = t;
            }
        }
    }
}

// Сведения по странам местонахождения трех шеститысячников (высота >=6000 метров)
void print_mountains_sixth(mountain mountains[], int size) {
    cout << "\n Страны местонахождения трех шеститысячников " << endl;
    int found = 0;
    for (int i = 0; i < size && found < 3; i++) { // цикл продолжается, пока не закончатся горы ИЛИ не найдено 3 горы
        if (mountains[i].height >= 6000) {
            found++;
            cout << found << ". " << mountains[i].name << " (" << mountains[i].height << "м) - " << mountains[i].Country.name << endl;
        }
    }
    if (found == 0) {
        cout << "Шеститысячников нет" << endl;
    }
}

// Изменение данных горной вершины по ее высоте
void update_mountains_byheight(mountain mountains[], int size, int searchHeight) {
    for (int i = 0; i < size; i++) {
        if (mountains[i].height == searchHeight) {
            cout << "\nНайдена гора: " << mountains[i].name << endl;
            cout << "Введите новые данные:" << endl;

            cout << "Название: ";
            cin.ignore();
            cin.getline(mountains[i].name, 30);

            cout << "Высота: ";
            cin >> mountains[i].height;

            cout << "Страна: ";
            cin.ignore();
            cin.getline(mountains[i].Country.name, 30);

            cout << "Континент: ";
            cin.getline(mountains[i].Country.continent, 50);

            int t;
            cout << "Тип (0-складчатая, 1-вулканическая, 2-купольная): ";
            cin >> t;
            mountains[i].Type = (typemountain)t;

            cout << "Данные обновлены!" << endl;
            return;
        }
    }
    cout << "Гора с высотой " << searchHeight << "м не найдена" << endl;
}

// Вывод всех горных вершин
void print_allmountains(mountain mountains[], int size) {
    for (int i = 0; i < size; i++) {
        print_mountain(mountains[i], i);
    }
}

// Массив с горными вершинами одной страны (Функция возвращает количество найденных гор и заполняет массив resultArray)
int count_mountains_bycountry(mountain mountains[], int size, const char searchCountry[], mountain resultArray[]) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(mountains[i].Country.name, searchCountry) == 0) {
            resultArray[found]=mountains[i];
            found++;
        }
    }
    return found;
}

//  Функция для вывода гор в стране
void mountains_bycountry(mountain mountains[], int size, const char countryName[]) {
    cout << "Горы в " << countryName << endl;
    if (size == 0) {
        cout << "Горы не найдены" << endl;
        return;
    }
    for (int i = 0; i < size;i++) {
        cout << i + 1 << "." << mountains[i].name << "(высота:" << mountains[i].height << "м)" << endl;
    }
    cout << "\nНайдено:" << size << " гор(ы)" << endl;
}

// Занятие 10
// Чтение высот гор из текстового файла для обновления массива
void update_heights_from_txtfile(mountain mountains[], int size, const char* filename) {
    ifstream fin;
    fin.open(filename);
    char name[30];
    int newHeight;
    while (fin>>name>>newHeight) { // Цикл продолжается, пока есть данные.
        for (int i = 0; i < size; i++) {
            if (strcmp(mountains[i].name, name)==0){ // Проверяем, совпадает ли название текущего элемента массива с названием горы из файла 
                cout << "Обновлена высота горы " << mountains[i].name << ":" << mountains[i].height << "м на " << newHeight << "м" << endl;
                mountains[i].height = newHeight;
                break;
            }
        }
    }
    fin.close();
}
// Запись структуры из бинарного файла
void save_to_binary_file(mountain mountains[], int size, const char* filename) {
    ofstream out(filename, ios::binary | ios::out);
    for (int i = 0; i < size;i++) {
        out.write((char*)&mountains[i], sizeof(mountain));
    }
    out.close();
    cout << "Данные сохранены в бинарный файл: " << filename << endl;
}
// Чтение массива структур из бинарного файла
int read_binary_file(mountain mountains[], int size, const char* filename) {
    ifstream in(filename, ios::binary | ios::in);
    int count = 0;
    while (in.read((char*)&mountains[count], sizeof(mountain)) && count < size) {
        count++;
    }
    in.close();
    cout << "Загружено " << count << " записей из файла " << filename << endl;
    return count;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);      // (устанавливаем кодировку ввода в CP1251) 
    SetConsoleOutputCP(1251); // (устанавливаем кодировку вывода в CP1251)

    struct mountain mountains[20];
    mountains[0] = { "Эверест", 8848, {"Китай","Евразия"}, folded };
    mountains[1] = { "Аконкагуа", 6962, {"Аргентина","Южная Америка"}, folded };
    mountains[2] = { "Денали", 6190, {"США","Северная Америка"}, folded };
    mountains[3] = { "Килиманджаро", 5895, {"Танзания","Африка"}, volcanic };
    mountains[4] = { "Эльбрус", 5642, {"Россия","Евразия"}, volcanic };
    mountains[5] = { "Лискамм", 4527, {"Швейцария", "Евразия"}, folded };
    mountains[6] = { "Юнгфрау", 4158, {"Швейцария","Евразия"}, folded };
    mountains[7] = { "Финстераархорн", 4274, {"Швейцария","Евразия"}, folded };
    mountains[8] = { "Фудзи", 3776, {"Япония","Евразия"}, volcanic };
    mountains[9] = { "Ключевская Сопка", 4754, {"Россия","Евразия"}, volcanic };
    mountains[10] = { "Монблан", 4810, {"Франция","Евразия"}, folded };
    mountains[11] = { "Маттерхорн", 4478, {"Швейцария","Евразия"}, folded };
    mountains[12] = { "Арарат", 5165, {"Турция","Евразия"}, volcanic };
    mountains[13] = { "Олимп", 2917, {"Греция","Евразия"}, folded };
    mountains[14] = { "Стоун-Маунтин", 514, {"США","Северная Америка"}, dome };
    mountains[15] = { "Чогори", 8614, {"Пакистан","Евразия"}, folded };
    mountains[16] = { "Митчелл", 2037, {"США","Северная Америка"}, folded };
    mountains[17] = { "Дыхтау", 5205, {"Россия","Евразия"}, folded };
    mountains[18] = { "Казбек", 5033, {"Грузия","Евразия"}, volcanic };
    mountains[19] = { "Иремель", 1589, {"Россия","Евразия"}, folded };

    // Вывод исходного массива
    cout << "Исходный массив " << endl;
    print_allmountains(mountains, 20);

    // Количество гор в Швейцарии
    int k = count_mountains_Switzerland(mountains, 20);
    cout << "\n>>> Количество гор на территории Швейцарии: " << k << endl;

    // Сортировка по высоте и вывод
    cout << "\n Горы, отсортированные по высоте " << endl;
    mountain sortedMountains[20];
    for (int i = 0; i < 20; i++) {
        sortedMountains[i] = mountains[i];
    }
    sort_mountains_byheight(sortedMountains, 20);
    for (int i = 0; i < 20; i++) {
        cout << i + 1 << ". " << sortedMountains[i].name
            << " - " << sortedMountains[i].height << "м" << endl;
    }

    // Три шеститысячника
    print_mountains_sixth(mountains, 20);

    // Изменение горы по высоте
    cout << "\n Изменение данных горы " << endl;
    cout << "Введите высоту горы для изменения: ";
    int searchH;
    cin >> searchH;
    update_mountains_byheight(mountains, 20, searchH);

    // Горы в выбранной стране
    cout << "\n Поиск гор по стране " << endl;
    cout << "Введите название страны: ";
    char searchCountry[30];
    cin.ignore();
    cin.getline(searchCountry, 30);

    mountain mountainsbycountry[20]; // Массив для гор из одной страны
    int bycountryCount = count_mountains_bycountry(mountains, 20, searchCountry, mountainsbycountry);
    mountains_bycountry(mountainsbycountry, bycountryCount, searchCountry);
    

    // Занятие 10:
    
    // Обновление высот из текстового файла
    cout << "\n Обновление высот из текстового файла " << endl;
    update_heights_from_txtfile(mountains, 20, "mountains.txt");

    // Вывод обновленного массива (высоты из текстового файла)
    cout << "Обновленный массив" << endl;
    print_allmountains(mountains, 20);

    // Запись в бинарный файл
    cout << "Создание бинарного файла и запись данных" << endl;
    save_to_binary_file(mountains, 20, "mountains.bin");

    // Чтение из бинарного файла
    cout << "\nЧтение данных из бинарного файла" << endl;
    mountain loadedMountains[20];
    int loadedCount = read_binary_file(loadedMountains, 20, "mountains.bin");

    // Вывод загруженных данных
    cout << "Проверка загруженных данных:" << endl;
    print_allmountains(loadedMountains, 20);

    cout << "\n Бинарный файл 'mountains.bin' успешно создан и прочитан!" << endl;

    return 0;
}
