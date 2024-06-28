#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Abstract Base class for User
class User {
protected:
    string username;
    string name;
    string password;

public:
    User(const string& username, const string& name, const string& password)
        : username(username), name(name), password(password) {}

    virtual ~User() {}

    // Pure virtual function to make User abstract
    virtual void displayProfile() = 0;

    // Public member functions to access protected variables
    const string& getUsername() const {
        return username;
    }

    const string& getName() const {
        return name;
    }

    const string& getPassword() const {
        return password;
    }
};

// Donor class derived from User
class Donor : public User {
private:
    string bloodGroup;
    int age;

public:
    Donor(const string& username, const string& name, const string& password,
          const string& bloodGroup, int age)
        : User(username, name, password), bloodGroup(bloodGroup), age(age) {}

    void displayProfile() override {
        cout << "Name: " << getName() << endl;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Age: " << age << endl;
    }

    void updateAge(int newAge) {
        age = newAge;
    }

    const string& getBloodGroup() const {
        return bloodGroup;
    }
};

// BloodBank class
class BloodBank {
private:
    vector<User*> users;

public:
    ~BloodBank() {
        for (User* user : users) {
            delete user;
        }
    }

    void signUp();
    void login();
    void displayDonorList();
    void searchByBloodGroup();
    void saveToFile(User* user);
};

// ... [rest of the code remains unchanged]

void BloodBank::signUp() {
    int choice;
    cout << "1. User Signup\n2. Donor Signup\n3. Exit\n";
    cin >> choice;

    if (choice == 1) {
        string username, name, password;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Password: ";
        cin >> password;

        // Directly creating an object of the derived class Donor
        User* newUser = new Donor(username, name, password, "", 0);  // For user, bloodGroup and age are not needed
        users.push_back(newUser);
        saveToFile(newUser);
        cout << "User signup successful!" << endl;
    } 
    else if (choice == 2) {
        string username, name, password, bloodGroup;
        int age;

        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Blood Group: ";
        cin >> bloodGroup;
        cout << "Enter Age: ";
        cin >> age;

        User* donor = new Donor(username, name, password, bloodGroup, age);
        users.push_back(donor);
        saveToFile(donor);
        cout << "Donor signup successful!" << endl;
    } 
    else {
        cout << "Invalid choice!" << endl;
    }
}

// ... [rest of the code remains unchanged]

void BloodBank::login() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    bool found = false;
    for (User* user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            found = true;
            cout << "Login successful!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Invalid username or password!" << endl;
    }
}

void BloodBank::displayDonorList() {
    cout << "Donor List:" << endl;
    cout << "----------------------------------" << endl;
    for (User* user : users) {
        Donor* donor = dynamic_cast<Donor*>(user);
        if (donor) {
            cout << "Name: " << donor->getName() << "\tBlood Group: "
                 << donor->getBloodGroup() << "\tAge: " << donor->getBloodGroup() << endl;
        }
    }
    cout << "----------------------------------" << endl;
}

void BloodBank::searchByBloodGroup() {
    string bloodGroup;
    cout << "Enter Blood Group to search: ";
    cin >> bloodGroup;

    bool found = false;
    cout << "Search Results:" << endl;
    cout << "----------------------------------" << endl;
    for (User* user : users) {
        Donor* donor = dynamic_cast<Donor*>(user);
        if (donor && donor->getBloodGroup() == bloodGroup) {
            donor->displayProfile();
            found = true;
        }
    }
    if (!found) {
        cout << "No donors found with the given blood group." << endl;
    }
    cout << "----------------------------------" << endl;
}

void BloodBank::saveToFile(User* user) {
    ofstream outFile("users.txt", ios::app);
    if (!outFile) {
        cerr << "Unable to open file!" << endl;
        return;
    }
    outFile << user->getUsername() << "," << user->getName() << "," << user->getPassword() << endl;
    outFile.close();
}

int main() {
    BloodBank bloodBank;
    int choice;

    while (true) {
        cout << "\nMenu:\n1. Sign Up\n2. Login\n3. Exit\n";
        cout<<"Enter an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                bloodBank.signUp();
                break;
            case 2:
                bloodBank.login();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}

