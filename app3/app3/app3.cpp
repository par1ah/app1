#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

class Timer {
public:
    Timer() : m_time(0), m_running(false) {}
    void setTime(int time) { m_time = time; }
    void start() {
        m_running = true;
        m_thread = std::thread(&Timer::countdown, this);
    }
    void stop() {
        m_running = false;
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }
    void subscribe(void (*callback)()) {
        m_callbacks.push_back(callback);
    }
private:
    int m_time;
    bool m_running;
    std::thread m_thread;
    std::vector<void (*)()> m_callbacks;

    void countdown() {
        auto start = std::chrono::steady_clock::now();
        while (m_running && std::chrono::steady_clock::now() - start < std::chrono::seconds(m_time)) {
            auto remaining = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start);
            std::cout << "Осталось " << m_time - remaining.count() << " секунд\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        for (auto& callback : m_callbacks) {
            callback();
        }
        std::cout << "Таймер завершен!\n";
    }
};

int main() {
    Timer timer;
    std::string command;
    setlocale(LC_ALL, "Russian");
    int time;

    while (true) {
        std::cout << "Введите команду: ";
        std::cin >> command;

        if (command == "set" && std::cin >> command && command == "time" && std::cin >> time) {
            timer.setTime(time);
            std::cout << "Время установлено на " << time << " секунд.\n";
        }
        else if (command == "start") {
            timer.start();
            std::cout << "Отсчет начат.\n";
        }
        else if (command == "stop") {
            timer.stop();
            std::cout << "Отсчет остановлен.\n";
        }
        else {
            std::cout << "Неверная команда.\n";
        }
    }

    return 0;
}