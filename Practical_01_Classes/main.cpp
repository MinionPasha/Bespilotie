#include "drone.h"
#include <iostream>

int main() {
    // Вариант 1. Управление полётом
    std::cout << "Variant 1 flight control\n";

    Drone drone_1;
    drone_1.print_info();

    std::cout << "\nTakeoff\n";
    drone_1.takeoff();
    drone_1.print_info();

    std::cout << "\nMove\n";
    drone_1.move_to(10.0, 20.0, 50.0);
    drone_1.print_info();

    std::cout << "\nLanding\n";
    drone_1.land();
    drone_1.print_info();

    std::cout << "\nEmergency landing\n";
    drone_1.takeoff();
    drone_1.move_to(30.0, 40.0, 60.0);
    drone_1.set_battery(0.0);
    drone_1.emergency_land();
    drone_1.print_info();

    // Доп проверки


    std::cout << "\nLow battery\n";
    Drone low_battery_drone(2, 5.0);
    low_battery_drone.takeoff();


    std::cout << "\nRepeated takeoff\n";
    drone_1.set_battery(80.0);
    drone_1.takeoff();
    drone_1.takeoff();


    std::cout << "\nMove before takeoff\n";
    Drone drone_2(3, 80.0);
    drone_2.move_to(1.0, 2.0, 10.0);

    std::cout << "\nInvalid altitude\n";
    drone_1.move_to(10.0, 20.0, -5.0);
    drone_1.print_info();


    std::cout << "\nCritically low battery\n";
    drone_1.set_battery(4.0);
    drone_1.move_to(5.0, 5.0, 10.0);
    drone_1.land();


    std::cout << "\nRepeated landing\n";
    drone_1.land();

    std::cout << "\nBattery limits\n";
    drone_2.set_battery(150.0);
    std::cout << "Battery: "
              << drone_2.get_battery() << "%\n";

    drone_2.set_battery(-10.0);
    std::cout << "Battery: "
              << drone_2.get_battery() << "%\n";


    std::cout << "\nInitial battery limits\n";
    Drone high_battery_drone(4, 150.0);
    Drone negative_battery_drone(5, -20.0);

    high_battery_drone.print_info();
    negative_battery_drone.print_info();

    // Вариант 2. Контроль телеметрии

    std::cout << "\nVariant 2 telemetry\n";

    Drone telemetry_drone(6, 80.0);
    telemetry_drone.takeoff();

    std::cout << "\nUpdate telemetry\n";
    telemetry_drone.update_telemetry(10.0, 20.0, 50.0, 75.0);
    telemetry_drone.print_info();

    std::cout << "Telemetry status: "
              << (telemetry_drone.has_valid_telemetry()
                      ? "Valid" : "Invalid")
              << '\n';

    std::cout << "\nNegative X and Y\n";
    telemetry_drone.update_telemetry(-10.0, -20.0, 30.0, 60.0);
    telemetry_drone.print_info();

    std::cout << "\nInvalid altitude\n";
    telemetry_drone.update_telemetry(1.0, 2.0, -5.0, 50.0);
    telemetry_drone.print_info();

    std::cout << "\nBattery above 100\n";
    telemetry_drone.update_telemetry(10.0, 20.0, 30.0, 150.0);
    telemetry_drone.print_info();

    std::cout << "\nBattery below 0\n";
    telemetry_drone.update_telemetry(10.0, 20.0, 30.0, -15.0);
    telemetry_drone.print_info();

    std::cout << "Telemetry status: "
              << (telemetry_drone.has_valid_telemetry()
                      ? "Valid" : "Invalid")
              << '\n';

    telemetry_drone.land();

    std::cout << "\nInvalid drone ID\n";
    Drone invalid_drone(-1, 80.0);

    std::cout << "Drone ID: "
              << invalid_drone.get_id() << '\n';

    std::cout << "Telemetry status: "
              << (invalid_drone.has_valid_telemetry()
                      ? "Valid" : "Invalid")
              << '\n';

    // Вариант 3. Подключение к наземной станции

    std::cout << "\nVariant 3 ground station connection\n";

    Drone station_drone(5, "Survey-01", 85.0);

    std::cout << "\nInitial connection status\n";
    station_drone.print_connection_status();

    std::cout << "\nConnect\n";
    station_drone.connect();
    station_drone.print_connection_status();

    std::cout << "\nConnect again\n";
    station_drone.connect();

    std::cout << "\nDisconnect\n";
    station_drone.disconnect();
    station_drone.print_connection_status();

    std::cout << "\nDisconnect again\n";
    station_drone.disconnect();

    std::cout << "\nReconnect\n";
    station_drone.connect();
    station_drone.print_connection_status();
    station_drone.disconnect();

    std::cout << "\nAnother drone\n";
    Drone cargo_drone(7, "Cargo-01", 70.0);
    cargo_drone.connect();
    cargo_drone.print_connection_status();
    cargo_drone.disconnect();

    std::cout << "\nEmpty model name\n";
    Drone unnamed_drone(8, "", 90.0);
    unnamed_drone.print_connection_status();

    return 0;
}