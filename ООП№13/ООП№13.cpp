#include <iostream>
#include <fstream>
#include <string>
/*Задание 

Создать:

Класс Connector -  который осуществляет работу с абстрактным Device. Устройство можно менять по необходимости, для этого реализовать соответствующий функционал.

Класс Device имеющим возможность что-то выводить на устройство и что-то получать с устройства.

Класс Data который может быть использован для разных видов данных. 

Разработать классы устройств — Монитор, файл, принтер, сеть, сканер.

Разработать классы для хранения разных видов данных.

Устройства Монитор и файл реализовать полноценно, а остальные  устройства  выполнить условно реализованными.

Разработать приложение в котором есть обьект Data. Данный обьект может быть отправлен на любое выбранное устройство с помощью  Connector.
*/

// Абстрактный класс Device
class Device {
public:
    virtual void send(const std::string& data) = 0; // Отправка данных на устройство
    virtual std::string receive() = 0; // Получение данных с устройства
    virtual ~Device() = default;
};

// Класс Monitor (реализация устройства - монитор)
class Monitor : public Device {
public:
    void send(const std::string& data) override {
        std::cout << "Отправка на монитор: " << data << std::endl;
    }

    std::string receive() override {
        return "Данные с монитора";
    }
};

// Класс File (реализация устройства - файл)
class File : public Device {
private:
    std::string filename;
public:
    File(const std::string& fname) : filename(fname) {}

    void send(const std::string& data) override {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << data;
            file.close();
            std::cout << "Данные записаны в файл: " << filename << std::endl;
        }
        else {
            std::cout << "Не удалось открыть файл: " << filename << std::endl;
        }
    }

    std::string receive() override {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
            return data;
        }
        else {
            return "Не удалось прочитать файл: " + filename;
        }
    }
};

// Условная реализация устройства Printer
class Printer : public Device {
public:
    void send(const std::string& data) override {
        std::cout << "Отправка данных на принтер: " << data << std::endl;
    }

    std::string receive() override {
        return "Данные с принтера";
    }
};

// Условная реализация устройства Network
class Network : public Device {
public:
    void send(const std::string& data) override {
        std::cout << "Отправка данных по сети: " << data << std::endl;
    }

    std::string receive() override {
        return "Данные из сети";
    }
};

// Условная реализация устройства Scanner
class Scanner : public Device {
public:
    void send(const std::string& data) override {
        std::cout << "Сканеры не отправляют данные. Эта операция недоступна." << std::endl;
    }

    std::string receive() override {
        return "Данные со сканера";
    }
};

// Класс Data для хранения и передачи данных
class Data {
private:
    std::string content;
public:
    Data(const std::string& data) : content(data) {}

    std::string getContent() const {
        return content;
    }
};

// Класс Connector для работы с устройствами
class Connector {
private:
    Device* device;
public:
    Connector(Device* dev = nullptr) : device(dev) {}

    void setDevice(Device* dev) {
        device = dev;
    }

    void sendData(const Data& data) {
        if (device) {
            device->send(data.getContent());
        }
        else {
            std::cout << "Устройство не выбрано." << std::endl;
        }
    }

    void receiveData() {
        if (device) {
            std::cout << "Получено: " << device->receive() << std::endl;
        }
        else {
            std::cout << "Устройство не выбрано." << std::endl;
        }
    }
};


int main() {
    setlocale(LC_ALL, "RU");
    // Создаем объекты устройств
    Monitor monitor;
    File file("output.txt");
    Printer printer;
    Network network;
    Scanner scanner;

    // Создаем объект данных
    Data myData("Это тестовые данные");

    Connector connector(&monitor);
    connector.sendData(myData);

    connector.setDevice(&file);
    connector.sendData(myData);  

    connector.receiveData();

    connector.setDevice(&printer);
    connector.sendData(myData);

    connector.setDevice(&network);
    connector.sendData(myData);

    connector.setDevice(&scanner);
    connector.receiveData();

    return 0;
}
