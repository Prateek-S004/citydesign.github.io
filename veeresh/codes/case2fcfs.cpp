#include <iostream>
#include <queue>

struct TrainingRequest
{
    std::string topic;
    int participants;
};

int main()
{
    std::queue<TrainingRequest> requests;

    // Training Requests
    requests.push({"AI", 20});
    requests.push({"Cybersecurity", 25});
    requests.push({"Data Science", 30});
    requests.push({"Software Development", 35});

    std::cout << "Training Sessions in FCFS order:\n";
    while (!requests.empty())
    {
        TrainingRequest request = requests.front();
        requests.pop();
        std::cout << "Topic: " << request.topic << ", Participants: " << request.participants << "\n";
    }

    return 0;
}
