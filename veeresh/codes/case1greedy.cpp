#include <iostream>
#include <vector>
#include <algorithm>

struct Zone
{
    std::string name;
    int population;
    int parks;
    int schools;
};

bool compare(Zone a, Zone b)
{
    return a.population > b.population;
}

int main()
{
    std::vector<Zone> zones = {
        {"Golf Course", 2500, 3, 2},
        {"High Court", 1800, 1, 1},
        {"IT Sector", 3200, 2, 3},
        {"Temple Lake", 1500, 1, 1},
        {"Industrial Area", 2100, 2, 2}
    };

    std::sort(zones.begin(), zones.end(), compare);

    std::cout << "Zones prioritized for resource allocation:\n";
    for (auto &zone : zones)
    {
        std::cout << zone.name << " - Population: " << zone.population << ", Parks: " << zone.parks << ", Schools: " << zone.schools << "\n";
    }

    return 0;
}
