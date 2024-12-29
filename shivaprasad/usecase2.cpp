#include <bits/stdc++.h>

using namespace std;

struct InvestmentProject {
    string projectName;
    double amountRemaining;
    bool operator>(const InvestmentProject& other) const {
        return amountRemaining > other.amountRemaining;
    }
};

string shiftPassword(const string& password) {
    string shiftedPassword = password;
    for (int i = 0; i < password.length(); i++) {
        shiftedPassword[i] = password[i] + 1;
    }
    return shiftedPassword;
}

void displayUserInfo(double balance, double totalInvested, double profit) {
    cout << "Balance: " << balance << "\nTotal Invested: " << totalInvested << "\nProfit Generated: " << profit << endl;
}

void displayProjects(priority_queue<InvestmentProject, vector<InvestmentProject>, greater<InvestmentProject>>& projects) {
    cout << "Investment Projects Available:\n";
    priority_queue<InvestmentProject, vector<InvestmentProject>, greater<InvestmentProject>> tempProjects = projects;
    while (!tempProjects.empty()) {
        InvestmentProject project = tempProjects.top();
        cout << "Project: " << project.projectName << " | Amount Remaining: $" << project.amountRemaining << endl;
        tempProjects.pop();
    }
}

void investInProject(priority_queue<InvestmentProject, vector<InvestmentProject>, greater<InvestmentProject>>& projects, double& balance, double& totalInvested, double& profit) {
    if (projects.empty()) {
        cout << "No investment projects available.\n";
        return;
    }
    InvestmentProject project = projects.top();
    projects.pop();
    cout << "Invest in " << project.projectName << " | Amount Remaining: $" << project.amountRemaining << "\nEnter amount: $";
    double investmentAmount;
    cin >> investmentAmount;
    if (investmentAmount <= balance) {
        if (investmentAmount <= project.amountRemaining) {
            project.amountRemaining -= investmentAmount;
            balance -= investmentAmount;
            totalInvested += investmentAmount;
            profit += investmentAmount * 0.10;
        } else {
            balance -= project.amountRemaining;
            totalInvested += project.amountRemaining;
            profit += project.amountRemaining * 0.10;
        }
    } else {
        cout << "Insufficient balance!\n";
    }
    if (project.amountRemaining > 0) {
        projects.push(project);
    }
}

void displayLoginHistory(queue<string> history) {
    if (history.empty()) {
        cout << "No login attempts yet.\n";
        return;
    }
    cout << "Login History:\n";
    while (!history.empty()) {
        cout << history.front() << endl;
        history.pop();
    }
}

int main() {
    map<string, tuple<string, double, double, double>> users;
    users["sam03"] = make_tuple("tbn14", 1000, 0, 0);
    users["jack55"] = make_tuple("jkl98", 1500, 200, 50);

    priority_queue<InvestmentProject, vector<InvestmentProject>, greater<InvestmentProject>> projects;
    projects.push({"Project A", 5000});
    projects.push({"Project B", 3000});
    projects.push({"Project C", 7000});

    queue<string> loginHistory;

    string username, password;
    int choice;
    cout << "1. Login\n2. Register New User\n3. History\nEnter choice: ";
    cin >> choice;

    while (choice != 4) {
        if (choice == 1) {
            cout << "Username: ";
            cin >> username;
            loginHistory.push(username);
            cout << "Password: ";
            cin >> password;

            if (users.find(username) != users.end() && get<0>(users[username]) == shiftPassword(password)) {
                cout << "Login Successful!\n";
                double balance = get<1>(users[username]);
                double totalInvested = get<2>(users[username]);
                double profit = get<3>(users[username]);

                while (true) {
                    cout << "\n1. Check Balance\n2. Invest in Project\n3. View Investment Status\n4. View Projects\n5. Log Out\nEnter choice: ";
                    int action;
                    cin >> action;
                    if (action == 1) {
                        displayUserInfo(balance, totalInvested, profit);
                    } else if (action == 2) {
                        investInProject(projects, balance, totalInvested, profit);
                    } else if (action == 3) {
                        displayUserInfo(balance, totalInvested, profit);
                    } else if (action == 4) {
                        displayProjects(projects);
                    } else if (action == 5) {
                        users[username] = make_tuple(get<0>(users[username]), balance, totalInvested, profit);
                        cout << "Logging out...\n";
                        break;
                    } else {
                        cout << "Invalid choice!\n";
                    }
                }
            } else {
                cout << "Invalid username or password!\n";
            }
        } else if (choice == 2) {
            cout << "New Username: ";
            cin >> username;
            cout << "New Password: ";
            cin >> password;
            users[username] = make_tuple(shiftPassword(password), 1000, 0, 0);
            cout << "User registered successfully!\n";
        } else if (choice == 3) {
            displayLoginHistory(loginHistory);
        } else {
            cout << "Invalid choice!\n";
        }

        cout << "1. Login\n2. Register New User\n3. History\nEnter choice: ";
        cin >> choice;
    }

    return 0;
}