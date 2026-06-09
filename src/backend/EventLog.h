#pragma once
#include <string>
#include <vector>

class EventLog{
    private:
    std::vector<std::string> events;
    public:
    void log(const std::string& event) {events.push_back(event); }
    std::vector<std::string> getevents() const { return events; }
    void clear() {events.clear(); }
};