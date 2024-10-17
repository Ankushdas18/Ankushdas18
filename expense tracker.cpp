#include <iostream>
#include <string>
using namespace std;


struct Expense {
    string date;
    string category;
    double amount;
    Expense* next; 
};


class ExpenseTracker {
private:
    Expense* head; 
    double totalExpenses; 

public:
    ExpenseTracker() {
        head = nullptr;
        totalExpenses = 0.0;
    }

    
    void addExpense(string date, string category, double amount) {
        Expense* newExpense = new Expense();
        newExpense->date = date;
        newExpense->category = category;
        newExpense->amount = amount;
        newExpense->next = head;
        head = newExpense;
        totalExpenses += amount;
        cout << "Expense added successfully.\n";
    }

   
    void viewExpenses() {
        if (!head) {
            cout << "No expenses to show.\n";
            return;
        }
        Expense* temp = head;
        while (temp != nullptr) {
            cout << "Date: " << temp->date << ", Category: " << temp->category << ", Amount: $" << temp->amount << endl;
            temp = temp->next;
        }
    }

    
    void searchByCategory(string category) {
        Expense* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->category == category) {
                cout << "Date: " << temp->date << ", Amount: $" << temp->amount << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No expenses found in this category.\n";
        }
    }

  
    void deleteExpense(string date) {
        if (!head) {
            cout << "No expenses to delete.\n";
            return;
        }
        Expense* temp = head;
        Expense* prev = nullptr;

        while (temp != nullptr && temp->date != date) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Expense not found.\n";
            return;
        }

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        totalExpenses -= temp->amount;
        delete temp;
        cout << "Expense deleted successfully.\n";
    }

   
    void displayTotalExpenses() {
        cout << "Total expenses: $" << totalExpenses << endl;
    }

   
    ~ExpenseTracker() {
        while (head) {
            Expense* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;
    string date, category;
    double amount;

    while (true) {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Search Expense by Category\n";
        cout << "4. Delete Expense\n";
        cout << "5. Display Total Expenses\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            tracker.addExpense(date, category, amount);
            break;
        case 2:
            tracker.viewExpenses();
            break;
        case 3:
            cout << "Enter category to search: ";
            cin >> category;
            tracker.searchByCategory(category);
            break;
        case 4:
            cout << "Enter date of expense to delete (YYYY-MM-DD): ";
            cin >> date;
            tracker.deleteExpense(date);
            break;
        case 5:
            tracker.displayTotalExpenses();
            break;
        case 6:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
