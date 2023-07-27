#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Item {
public:
    Item(const string& name, int quantity, double price)
        : name(name), quantity(quantity), price(price) {}

    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void display() const {
        cout << "Item: " << name << "\tQuantity: " << quantity << "\tPrice: $" << price << endl;
    }

    void incrementQuantity(int amount) {
        quantity += amount;
    }

    void decrementQuantity(int amount) {
        if (quantity >= amount)
            quantity -= amount;
        else
            cout << "Not enough quantity available to decrement." << endl;
    }

    // Overload == operator for easy comparison
    bool operator==(const Item& other) const {
        return name == other.name && quantity == other.quantity && price == other.price;
    }

    // Overload < operator to enable sorting by name
    bool operator<(const Item& other) const {
        return name < other.name;
    }

    // Overload > operator to enable sorting by price
    bool operator>(const Item& other) const {
        return price > other.price;
    }

private:
    string name;
    int quantity;
    double price;
};

class Inventory {
public:
    void addItem(const string& name, int quantity, double price) {
        auto it = find_if(items.begin(), items.end(), [&](const Item& item) { return item.getName() == name; });
        if (it != items.end()) {
            it->incrementQuantity(quantity);
            cout << "Item quantity updated." << endl;
        } else {
            items.push_back(Item(name, quantity, price));
            cout << "Item added to the inventory." << endl;
        }
    }

    void removeItem(const string& name) {
        auto it = find_if(items.begin(), items.end(), [&](const Item& item) { return item.getName() == name; });
        if (it != items.end()) {
            items.erase(it);
            cout << "Item removed from the inventory." << endl;
        } else {
            cout << "Item not found in the inventory." << endl;
        }
    }

    void displayInventory() const {
        cout << "Inventory:" << endl;
        for (const auto& item : items) {
            item.display();
        }
    }

    void updateQuantity(const string& name, int newQuantity) {
        auto it = find_if(items.begin(), items.end(), [&](const Item& item) { return item.getName() == name; });
        if (it != items.end()) {
            it->incrementQuantity(newQuantity);
            cout << "Item quantity updated." << endl;
        } else {
            cout << "Item not found in the inventory." << endl;
        }
    }

    void decrementQuantity(const string& name, int amount) {
        auto it = find_if(items.begin(), items.end(), [&](const Item& item) { return item.getName() == name; });
        if (it != items.end()) {
            it->decrementQuantity(amount);
        } else {
            cout << "Item not found in the inventory." << endl;
        }
    }

    void findItemByName(const string& name) const {
        auto it = find_if(items.begin(), items.end(), [&](const Item& item) { return item.getName() == name; });
        if (it != items.end()) {
            it->display();
        } else {
            cout << "Item not found in the inventory." << endl;
        }
    }

    void findItemByPriceRange(double minPrice, double maxPrice) const {
        cout << "Items within price range $" << minPrice << " to $" << maxPrice << ":" << endl;
        for (const auto& item : items) {
            if (item.getPrice() >= minPrice && item.getPrice() <= maxPrice) {
                item.display();
            }
        }
    }

    void sortByName() {
        sort(items.begin(), items.end());
        cout << "Inventory sorted by name." << endl;
    }

    void sortByPrice() {
        sort(items.begin(), items.end(), greater<Item>());
        cout << "Inventory sorted by price." << endl;
    }

    void displayTotalValue() const {
        double totalValue = 0.0;
        for (const auto& item : items) {
            totalValue += item.getQuantity() * item.getPrice();
        }
        cout << "Total value of the inventory: $" << totalValue << endl;
    }

    void displayMostExpensiveItem() const {
        auto it = max_element(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getPrice() < b.getPrice();
        });
        if (it != items.end()) {
            cout << "Most expensive item in the inventory: ";
            it->display();
        } else {
            cout << "Inventory is empty." << endl;
        }
    }

    void displayCheapestItem() const {
        auto it = min_element(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getPrice() < b.getPrice();
        });
        if (it != items.end()) {
            cout << "Cheapest item in the inventory: ";
            it->display();
        } else {
            cout << "Inventory is empty." << endl;
        }
    }

private:
    vector<Item> items;
};

void printMenu() {
    cout << "\n----- Inventory Management Menu -----" << endl;
    cout << "1. Display Inventory" << endl;
    cout << "2. Add Item" << endl;
    cout << "3. Remove Item" << endl;
    cout << "4. Update Item Quantity" << endl;
    cout << "5. Decrement Item Quantity" << endl;
    cout << "6. Find Item by Name" << endl;
    cout << "7. Find Items by Price Range" << endl;
    cout << "8. Sort Inventory by Name" << endl;
    cout << "9. Sort Inventory by Price" << endl;
    cout << "10. Display Total Value" << endl;
    cout << "11. Display Most Expensive Item" << endl;
    cout << "12. Display Cheapest Item" << endl;
    cout << "13. Exit" << endl;
    cout << "Enter your choice: ";
}

int getUserChoice() {
    int choice;
    while (!(cin >> choice) || (cin.peek() != '\n')) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

int getUserIntInput() {
    int input;
    while (!(cin >> input) || (cin.peek() != '\n')) {
        cout << "Invalid input. Please enter a valid integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

double getUserDoubleInput() {
    double input;
    while (!(cin >> input) || (cin.peek() != '\n')) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

int main() {
    Inventory inventory;

    int option;
    string itemName;
    int quantity;
    double price;
    double minPrice, maxPrice;

    do {
        printMenu();
        option = getUserChoice();

        switch (option) {
        case 1:
            inventory.displayInventory();
            break;
        case 2:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter item quantity: ";
            quantity = getUserIntInput();
            cout << "Enter item price: $";
            price = getUserDoubleInput();
            inventory.addItem(itemName, quantity, price);
            break;
        case 3:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            inventory.removeItem(itemName);
            break;
        case 4:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter new quantity: ";
            quantity = getUserIntInput();
            inventory.updateQuantity(itemName, quantity);
            break;
        case 5:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter quantity to decrement: ";
            quantity = getUserIntInput();
            inventory.decrementQuantity(itemName, quantity);
            break;
        case 6:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            inventory.findItemByName(itemName);
            break;
        case 7:
            cout << "Enter minimum price: $";
            minPrice = getUserDoubleInput();
            cout << "Enter maximum price: $";
            maxPrice = getUserDoubleInput();
            inventory.findItemByPriceRange(minPrice, maxPrice);
            break;
        case 8:
            inventory.sortByName();
            break;
        case 9:
            inventory.sortByPrice();
            break;
        case 10:
            inventory.displayTotalValue();
            break;
        case 11:
            inventory.displayMostExpensiveItem();
            break;
        case 12:
            inventory.displayCheapestItem();
            break;
        case 13:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    } while (option != 13);

    return 0;
}
