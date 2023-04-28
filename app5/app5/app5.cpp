#include <iostream>
#include <string>
using namespace std;
class ConcertHall {
private:
    string name;
    int capacity;
    double ticketPrice;
    int soldOut;

public:
    ConcertHall(const string& name, int capacity, double ticketPrice) {
        this->name = name;
        this->capacity = capacity;
        this->ticketPrice = ticketPrice;
        this->soldOut = 0;
    }

    void sellTickets(int count) {
        if (count < 0) {
            cout << "Количество билетов должно быть положительным\n";
        }
        else if (count + soldOut > capacity) {
            cout << "Зал полон\n";
        }
        else {
            soldOut += count;
            cout << "Продано " << count << " билеты на общую сумму " << count * ticketPrice << " рублей\n";
        }
    }

    void addTickets(int count) {
        if (count < 0) {
            cout << "Количество билетов должно быть положительным\n";
        }
        else {
            capacity += count;
            cout << "Добавлено " << count << " билетов. Новая емкость зала: " << capacity << endl;
        }
    }

    string getName() const {
        return name;
    }

    int getCapacity() const {
        return capacity;
    }

    double getTicketPrice() const {
        return ticketPrice;
    }

    int getSoldOut() const {
        return soldOut;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    ConcertHall hall("Главный зал", 5000, 100);
    cout << "Добро пожаловать в " << hall.getName() << endl;
    cout << "Стоимость билета: " << hall.getTicketPrice() << endl;

    int choice = 0;
    while (choice != 4) {
        cout << "Выберите:\n"
            << "1. Купить билеты \n"
            << "2. Добавить вместимость\n"
            << "3. Проверить доступные билеты\n"
            << "4. Выход\n"
            << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int count;
            cout << "Сколько билетов вы хотите купить? ";
            cin >> count;
            hall.sellTickets(count);
            break;
        }
        case 2: {
            int count;
            cout << "Сколько мест вы хотите добавить? ";
            cin >> count;
            hall.addTickets(count);
            break;
        }
        case 3: {
            cout << "Доступные билеты: " << hall.getCapacity() - hall.getSoldOut() << endl;
            break;
        }
        case 4:
            cout << "Пока\n";
            break;
        default:
            cout << "Повторите выбор\n";
            break;
        }
    }

    return 0;
}