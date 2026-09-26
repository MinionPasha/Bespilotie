#ifndef DRONE_H
#define DRONE_H

#include <string>

class Drone {
private:
    int id;
    double x;
    double y;
    double z;
    double battery;
    bool flying;

    //для варианта 3
    std::string model;
    bool connected;

public:

    Drone();
    Drone(int drone_id, double initial_battery);

    void set_position(double new_x,
                      double new_y,
                      double new_z);

    int get_id() const;
    double get_battery() const;
    bool is_flying() const;

    // Вариант 1. Управление полётом
    void takeoff();
    void land();

    void move_to(double new_x,
                 double new_y,
                 double new_z);

    void set_battery(double value);
    void print_info() const;
    void emergency_land();

    // Вариант 2. Контроль телеметрии
    void update_telemetry(double new_x,
                          double new_y,
                          double new_z,
                          double new_battery);

    bool has_valid_telemetry() const;

    // Вариант 3. Подключение к наземной станции
    Drone(int drone_id,
          const std::string& drone_model,
          double initial_battery);

    void connect();
    void disconnect();
    bool is_connected() const;
    void print_connection_status() const;
};

#endif