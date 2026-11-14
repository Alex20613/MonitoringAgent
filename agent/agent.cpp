#include <iostream>
#include <crow.h>
#include <cstdio>
#include <string>
#include <vector>


using namespace std;

class Functions {
public:
    Functions() {}
    ~Functions() {}

    string responseCommand(const string& command);
    string getProcessor();
    string getRamMemory();
    string getHardDisk();
    string getBoard();
    string getBios();
    string getProcesorResponse();
    string getOperationSystemInfo();
    string getNameDevice();
    string getInstalledSoftware();
    string getTopProcesses();
    string getNetworkInfo();
    string getUptime();
    string getLoggedUser();
    string getUpdates();
    string getAntivirus();
  
    string getMouse();
    string getKeyboard();
};



string Functions::responseCommand(const string& command) {
    try {
        char buffer[128];
        string result;

        FILE* fp = _popen(command.c_str(), "r");
        while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
            result += buffer;
        }
        _pclose(fp);

        return result;
    }
    catch (exception& e) {
        cout << "Error al convertir los datos: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getNameDevice() {
    try {
        return responseCommand("powershell -Command \" (Get-CimInstance Win32_ComputerSystem).Name | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener el nombre del dispositivo";
        return string(e.what());
    }
}
string Functions::getProcesorResponse() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject Win32_Processor | Select-Object LoadPercentage | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la informacion del consumo de procesador" << endl;
        return string(e.what());
    }
}

string Functions::getOperationSystemInfo() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject -Class Win32_OperatingSystem | Select-Object Caption, Version, OSArchitecture | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la informacion del sistema operativo" << endl;
        return string(e.what());
    }
}

string Functions::getProcessor() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject Win32_Processor | Select-Object Name, Manufacturer, NumberOfCores, NumberOfLogicalProcessors, MaxClockSpeed | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la información del procesador: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getBios() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject Win32_BIOS | Select-Object Manufacturer, SMBIOSBIOSVersion, ReleaseDate | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la información de la bios: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getBoard() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject Win32_BaseBoard | Select-Object Product, Manufacturer, SerialNumber | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la informaci+on de la placa base: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getRamMemory() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject Win32_PhysicalMemory | Select-Object Capacity, Speed, Manufacturer | ConvertTo-Json\"");
    }
    catch (exception& e) {
        cout << "Error al obtener la información de la memoria RAM: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getHardDisk() {
    try {
        return responseCommand("powershell -Command \"Get-WmiObject Win32_LogicalDisk | Select-Object DeviceID, Size, FreeSpace | ConvertTo-Json\"");
    }
    catch (exception& e) {
        cout << "Error al obtener la información de la memoria RAM: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getInstalledSoftware() {
    try {
        return responseCommand("powershell -Command \"Get-ItemProperty 'HKLM:\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\*','HKLM:\\Software\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\*' | Where-Object DisplayName | Select-Object DisplayName, DisplayVersion, Publisher | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener el software instalado: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getTopProcesses() {
    try {
        return responseCommand("powershell -Command \"Get-Process | Sort-Object WorkingSet -Descending | Select-Object -First 10 Name, Id, @{n='MemoryMB';e={[math]::Round($_.WorkingSet/1MB,1)}} | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener los procesos: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getNetworkInfo() {
    try {
        return responseCommand("powershell -Command \"Get-CimInstance Win32_NetworkAdapterConfiguration -Filter 'IPEnabled=true' | Select-Object Description, IPAddress, MACAddress, DefaultIPGateway, DNSServerSearchOrder | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la informacion de red: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getUptime() {
    try {
        return responseCommand("powershell -Command \"(Get-CimInstance Win32_OperatingSystem).LastBootUpTime.ToString('o') | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener el uptime: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getLoggedUser() {
    try {
        return responseCommand("powershell -Command \"Get-CimInstance Win32_ComputerSystem | Select-Object UserName, Domain | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener el usuario: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getUpdates() {
    try {
        return responseCommand("powershell -Command \"Get-HotFix | Select-Object HotFixID, Description, InstalledOn | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener las actualizaciones: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getAntivirus() {
    try {
        return responseCommand("powershell -Command \"Get-CimInstance -Namespace root/SecurityCenter2 -ClassName AntiVirusProduct | Select-Object displayName, productState | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener el antivirus: " << e.what() << endl;
        return string(e.what());
    }
}
string Functions::getMouse() {
    try {
       
        return responseCommand("powershell -Command \"Get-WmiObject Win32_PointingDevice | Select-Object Name, Manufacturer, PNPDeviceID | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener los datos del mouse: " << e.what() << endl;
        return string(e.what());
    }
}

string Functions::getKeyboard() {
    try {
        return responseCommand("powershell -Command \"(Get-WmiObject Win32_Keyboard | Select-Object Name, Manufacturer, PNPDeviceID)[0] | ConvertTo-Json\" ");
    }
    catch (exception& e) {
        cout << "Error al obtener la información del teclado: " << e.what() << endl;
        return string(e.what());
    }
}


class Agent : public Functions {
private:
    string port;

public:
    crow::SimpleApp Agente;
    Agent(string port);
    ~Agent();
    void startAgent();
};

Agent::Agent(string port) {
    try {
        this->port = port;
        CROW_ROUTE(this->Agente, "/Software")([this]() {
            string result;
            result = this->getInstalledSoftware();
            return result;
            });

        CROW_ROUTE(this->Agente, "/Processes")([this]() {
            string result;
            result = this->getTopProcesses();
            return result;
            });

        CROW_ROUTE(this->Agente, "/Network")([this]() {
            string result;
            result = this->getNetworkInfo();
            return result;
            });

        CROW_ROUTE(this->Agente, "/Uptime")([this]() {
            string result;
            result = this->getUptime();
            return result;
            });

        CROW_ROUTE(this->Agente, "/User")([this]() {
            string result;
            result = this->getLoggedUser();
            return result;
            });

        CROW_ROUTE(this->Agente, "/Updates")([this]() {
            string result;
            result = this->getUpdates();
            return result;
            });

        CROW_ROUTE(this->Agente, "/Antivirus")([this]() {
            string result;
            result = this->getAntivirus();
            return result;
            });
        CROW_ROUTE(this->Agente, "/")([]() {
            return "Ok";
        });

        CROW_ROUTE(this->Agente, "/OS")([this]() {
            string result;
            result = this->getOperationSystemInfo();
            return result;
            });

        CROW_ROUTE(this->Agente, "/ProcessorConsumer")([this]() {
            string result;
            result = this->getProcesorResponse();
            return result;
            });

        CROW_ROUTE(this->Agente, "/processor")([this]() {
            string result;
            result = this->getProcessor(); 
            return result;
        });
        CROW_ROUTE(this->Agente, "/Name")([this]() {
            string result;
            result = this->getNameDevice();
            return result;
            });

        CROW_ROUTE(this->Agente, "/ram")([this]() {
            string result;
            result = this->getRamMemory();
            return result;
        });

        CROW_ROUTE(this->Agente, "/disk")([this]() {
            string result;
            result = this->getHardDisk();
            return result;
        });

        CROW_ROUTE(this->Agente, "/Bios")([this]() {
            string result;
            result = this->getBios();
            return result;
        });

        CROW_ROUTE(this->Agente, "/MotherBoard")([this]() {
            string result;
            result = this->getBoard();
            return result;
        });
        
        CROW_ROUTE(this->Agente, "/Mouse")([this]() {
           string result;
            result = this->getMouse();
            return result;
        });

        CROW_ROUTE(this->Agente, "/Keyboard")([this]() {
            string result;
            result = this->getKeyboard();
            return result;
            });
    }
    catch (exception& e) {
        cout << "Error al crear el Agente: " << e.what() << endl;
        }
}

Agent::~Agent() {}

void Agent::startAgent() {
    try {
        this->Agente.port(stoi(port)).multithreaded().run();
    }
    catch (exception& e) {
        cout << "Error al iniciar el agente: " << e.what() << endl;
    }
}

int main() {
    try {
        Agent agente("4080");
        agente.startAgent();
    }
    catch (exception& e) {
        cout << "Error al instanciar el agente: " << e.what() << endl;
    }
    return 0;
}
