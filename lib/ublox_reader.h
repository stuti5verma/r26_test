#ifndef UBLOX_READER_H
#define UBLOX_READER_H

#include <string>
#include <utility>

// Basic GPS struct (lat, lon)
struct GPS {
    double lat;
    double lon;
};

// Reads UBX file and extracts start & goal
std::pair<GPS, GPS> readUbloxFile(const std::string &filename);

#endif
