#include "ublox_reader.h"
#include <fstream>
#include <iostream>
#include <vector>

// A simple UBX NAV-POSLLH message struct (latitude, longitude in 1e-7 deg)
struct UbxPosLLH {
    int lon; // longitude (1e-7 degrees)
    int lat; // latitude  (1e-7 degrees)
};

// Function to read a UBX file and extract start and goal
std::pair<GPS, GPS> readUbloxFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return {GPS{0,0}, GPS{0,0}};
    }

    // Read entire file into buffer
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)),
                                      std::istreambuf_iterator<char>());
    file.close();

    // UBX sync chars are 0xB5 0x62
    const unsigned char SYNC1 = 0xB5, SYNC2 = 0x62;

    GPS start{0,0}, goal{0,0};
    bool gotStart = false;

    for (size_t i = 0; i + 36 < buffer.size(); i++) {
        if (buffer[i] == SYNC1 && buffer[i+1] == SYNC2) {
            unsigned char cls = buffer[i+2];
            unsigned char id  = buffer[i+3];
            unsigned short len = buffer[i+4] | (buffer[i+5] << 8);

            // NAV-POSLLH has Class = 0x01, ID = 0x02, Length = 28
            if (cls == 0x01 && id == 0x02 && len == 28) {
                int lon = *reinterpret_cast<int*>(&buffer[i+10]); // offset 10
                int lat = *reinterpret_cast<int*>(&buffer[i+14]); // offset 14

                double lon_deg = lon / 1e7;
                double lat_deg = lat / 1e7;

                if (!gotStart) {
                    start = {lat_deg, lon_deg};
                    gotStart = true;
                } else {
                    goal = {lat_deg, lon_deg};
                    break;
                }
            }
        }
    }

    return {start, goal};
}
