#include <iostream>
#include <queue>
#include <vector>

struct Region
{
    std::string name;
    int patient_count;
};

struct ComparePatientCount
{
    bool operator()(Region a, Region b)
    {
        return a.patient_count < b.patient_count;  // Max heap: allocate to regions with more patients first
    }
};

int main()
{
    std::priority_queue<Region, std::vector<Region>, ComparePatientCount> pq;

    // Regions with their respective patient counts
    pq.push({"Railway Station", 200});
    pq.push({"Golf Course", 350});
    pq.push({"Hills", 150});
    pq.push({"Dump Yard", 100});
    pq.push({"Lake", 400});

    int available_resources = 1000;

    std::cout << "Resource Allocation by Patient Count:\n";
    while (!pq.empty() && available_resources > 0)
    {
        Region region = pq.top();
        pq.pop();

        std::cout << region.name << " - Patient Count: " << region.patient_count << "\n";
        // Allocate resources based on the available count
        available_resources -= region.patient_count;  // Example allocation logic
        if (available_resources < 0) break;
    }

    return 0;
}
