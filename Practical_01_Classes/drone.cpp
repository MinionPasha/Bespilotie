#include "drone.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// Конструкторы и общие методы

Drone::Drone()
    : id(0),
    x(0.0),
    y(0.0),
    z(0.0),
    battery(100.0),
    flying(false),
    model("Unknown"),
    connected(false) {
}

Drone::Drone(int drone_id, double initial_battery)
    : id(drone_id),
    x(0.0),
    y(0.0),
    z(0.0),
    battery(0.0),
    flying(false),
    model("Unknown"),
    connected(false) {
    set_battery(initial_battery);

}

void Drone::set_position(double new_x,
                         double new_y,
                         double new_z) {
    // Проверяем высоту
    if (new_z < 0.0) {
        std::cout << "Error: altitude cannot be negative\n";
        return;
    }

    x = new_x;
    y = new_y;
    z = new_z;
}

int Drone::get_id() const {
    return id;
}

double Drone::get_battery() const {
    return battery;
}

bool Drone::is_flying() const {
    return flying;
}

// Вариант 1. Управление полётом

void Drone::takeoff() {
    // Проверяем заряд перед взлётом
    if (battery < 10.0) {
        std::cout << "Takeoff denied: low battery\n";
        return;
    }

    if (flying) {
        std::cout << "Drone is already flying\n";
        return;
    }

    // Поднимаем аппарат на 1 метр
    flying = true;
    z = 1.0;
    battery -= 1.0;

    std::cout << "Drone took off\n";
}

void Drone::land() {
    if (!flying) {
        std::cout << "Drone is already on the ground\n";
        return;
    }

    // Обнуляем высоту при посадке
    flying = false;
    z = 0.0;

    std::cout << "Drone landed\n";
}

void Drone::move_to(double new_x,
                    double new_y,
                    double new_z) {
    // Проверяем состояние, высоту и заряд
    if (!flying) {
        std::cout << "Move denied: drone is not flying\n";
        return;
    }

    if (new_z < 0.0) {
        std::cout << "Move denied: invalid altitude\n";
        return;
    }

    if (battery < 5.0) {
        std::cout << "Move denied: critically low battery\n";
        return;
    }

    // Меняем координаты и уменьшаем заряд
    x = new_x;
    y = new_y;
    z = new_z;
    battery -= 1.0;

    std::cout << "Drone moved to new position\n";
}

void Drone::set_battery(double value) {
    // Ограничиваем заряд от 0 до 100%
    if (value < 0.0) {
        battery = 0.0;
    } else if (value > 100.0) {
        battery = 100.0;
    } else {
        battery = value;
    }
}

void Drone::print_info() const {
    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Drone ID: " << id << '\n';

    std::cout << "Position: ("
              << x << ", "
              << y << ", "
              << z << ")\n";

    std::cout << "Battery: "
              << battery << "%\n";

    std::cout << "Status: "
              << (flying ? "Flying" : "On ground")
              << '\n';
}

void Drone::emergency_land() {
    // Сажаем аппарат без проверки заряда
    z = 0.0;
    flying = false;

    std::cout << "WARNING: Emergency landing activated\n";
    std::cout << "Drone landed immediately\n";
}

// Вариант 2. Контроль телеметрии

void Drone::update_telemetry(double new_x,
                             double new_y,
                             double new_z,
                             double new_battery) {
    // Проверяем координаты
    if (!std::isfinite(new_x) ||
        !std::isfinite(new_y) ||
        !std::isfinite(new_z)) {
        std::cout << "Error: invalid coordinates\n";
        return;
    }

    if (new_z < 0.0) {
        std::cout << "Error: altitude cannot be negative\n";
        return;
    }

    if (!std::isfinite(new_battery)) {
        std::cout << "Error: invalid battery value\n";
        return;
    }

    // Записываем данные после проверок
    set_position(new_x, new_y, new_z);
    set_battery(new_battery);

    std::cout << "Telemetry updated successfully\n";
}

bool Drone::has_valid_telemetry() const {
    // Отрицательный ID считаем ошибкой
    if (id < 0) {
        return false;
    }

    if (!std::isfinite(x) ||
        !std::isfinite(y) ||
        !std::isfinite(z) ||
        !std::isfinite(battery)) {
        return false;
    }

    if (z < 0.0) {
        return false;
    }

    if (battery < 0.0 || battery > 100.0) {
        return false;
    }

    return true;
}

// Вариант 3. Подключение к наземной станции

Drone::Drone(int drone_id,
             const std::string& drone_model,
             double initial_battery)
    : Drone(drone_id, initial_battery) {
    // Если название пустое, остаётся Unknown
    if (!drone_model.empty()) {
        model = drone_model;
    }
}

void Drone::connect() {
    // Проверяем повторное подключение
    if (connected) {
        std::cout << "Drone is already connected\n";
        return;
    }

    connected = true;

    std::cout << "Connecting to drone " << model << "...\n";
    std::cout << "Drone ID: " << id << '\n';
    std::cout << "Connection established\n";
}

void Drone::disconnect() {
    if (!connected) {
        std::cout << "Drone is already disconnected\n";
        return;
    }

    // Сбрасываем состояние подключения
    connected = false;

    std::cout << "Connection closed\n";
}

bool Drone::is_connected() const {
    return connected;
}

void Drone::print_connection_status() const {
    std::cout << "Model: " << model << '\n';
    std::cout << "Drone ID: " << id << '\n';

    std::cout << "Connection status: "
              << (is_connected() ? "Connected" : "Disconnected")
              << '\n';
}