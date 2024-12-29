#include <iostream>
#include <vector>
#include <algorithm>

struct TrainingCenter
{
    std::string name;
    int trainers;
    int capacity;
    std::string topic;
};

bool compare(TrainingCenter a, TrainingCenter b)
{
    return a.capacity > b.capacity;  // Prioritize by capacity for maximum utilization
}

int main()
{
    std::vector<TrainingCenter> centers = {
        {"Bus Terminal", 12, 50, "AI, Cybersecurity"},
        {"Hospital", 8, 30, "Data Science, Software Development"},
        {"Airport", 15, 60, "AI, Data Science"},
        {"Hotel", 10, 40, "Cybersecurity, Software Development"}
    };

    std::sort(centers.begin(), centers.end(), compare);

    std::cout << "Trainer allocation based on available capacity:\n";
    for (auto &center : centers)
    {
        std::cout << center.name << " - Trainers: " << center.trainers << ", Capacity: " << center.capacity << ", Topics: " << center.topic << "\n";
    }

    return 0;
}
