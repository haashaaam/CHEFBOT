#include <iostream> // Required for input/output operations (e.g., cout, cin)
#include <string>   // Required for string manipulation
#include <vector>   // Required for using dynamic arrays (vectors)
#include <ctime>    // Required for time-related functions (e.g., getting current hour)
#include <algorithm> // Required for algorithms like transform (used in toLower)
#include <fstream>  // Required for file input/output operations (e.g., ofstream)
#include <map>      // Required for using associative arrays (maps)
#include <stdexcept> // Required for exception handling
#include <limits>   // Required for numeric limits
#include <iomanip>  // Required for formatting output

using namespace std; // Using the standard namespace to avoid prefixing std::

// Helper function to convert a string to lowercase
string toLower(string str)
{
    // Applies the tolower function to each character in the string
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str; // Returns the lowercase string
}

// Helper function to validate numeric input
double getValidPrice()
{
    double price;
    while (true)
    {
        if (cin >> price && price >= 0)
        {
            cin.ignore(); // Consume the leftover newline character
            return price;
        }
        else
        {
            cout << "Invalid input. Please enter a valid positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// -------------------- MenuItem Class --------------------
// Represents a single item on a restaurant's menu
class MenuItem
{
    string name;  // Name of the menu item
    double price; // Price of the menu item

public:
    // Constructor to initialize a MenuItem object
    MenuItem(string name, double price) : name(name), price(price) {}

    // Getter function for the item's name
    string getName() const { return name; }
    // Getter function for the item's price
    double getPrice() const { return price; }

    // Displays the menu item's name and price
    void show() const
    {
        cout << "   - " << name << ": Rs " << price << endl;
    }
};

// -------------------- Restaurant Base Class --------------------
// Base class for all restaurants, defining common properties and behaviors
class Restaurant
{
protected:
    string name;                            // Name of the restaurant
    vector<string> branches;                // List of branch names
    vector<string> addresses;               // List of branch addresses
    float rating;                           // Restaurant rating
    map<string, vector<MenuItem>> categorizedMenu; // Menu categorized by type (e.g., "Burgers", "Pizzas")

public:
    // Constructor to initialize a Restaurant object
    Restaurant(string n, vector<string> b, vector<string> a, float r)
        : name(n), branches(b), addresses(a), rating(r) {}

    // Virtual function to display the restaurant's menu
    // Marked virtual to allow derived classes to override it
    virtual void showMenu() const
    {
        for (const auto &category : categorizedMenu) // Iterate through each category in the menu map
        {
            cout << "  " << category.first << ":\n"; // Print the category name
            for (const auto &item : category.second) // Iterate through each item in the current category
            {
                item.show(); // Display the menu item
            }
        }
    }

    // Virtual function to display detailed information about the restaurant
    virtual void showDetails() const
    {
        cout << "\n" << string(50, '=') << "\n";
        cout << "  " << name << " (Rating: " << rating << "/5)" << "\n";
        cout << string(50, '=') << "\n";
        cout << " Branches:\n";
        for (size_t i = 0; i < branches.size(); i++) // Iterate through branches and their addresses
        {
            cout << "   • " << name << " " << branches[i] << " - " << addresses[i] << endl;
        }
        cout << "\n Menu:\n";
        showMenu(); // Display the menu
        cout << string(50, '=') << "\n";
    }

    // Virtual getter functions for restaurant properties
    virtual string getName() const { return name; }
    virtual float getRating() const { return rating; }
    virtual vector<string> getAddresses() const { return addresses; }
    virtual vector<string> getBranches() const { return branches; }

    // Virtual function to check if the restaurant is currently open (between 12 PM and 11 PM)
    virtual bool isOpenNow() const
    {
        try
        {
            time_t now = time(0);         // Get current time
            tm *ltm = localtime(&now);    // Convert to local time structure
            if (ltm == nullptr)
            {
                cout << "Error getting current time.\n";
                return false;
            }
            int hour = ltm->tm_hour;      // Extract the hour
            return (hour >= 12 && hour <= 23); // Check if hour is between 12 (noon) and 23 (11 PM)
        }
        catch (...)
        {
            cout << "Error checking time.\n";
            return false;
        }
    }

    // Virtual getter for the categorized menu
    virtual map<string, vector<MenuItem>> getCategorizedMenu() const
    {
        return categorizedMenu;
    }

    // Declares ChefBot as a friend class, allowing it to access protected/private members
    friend class ChefBot;
};

// -------------------- Derived Restaurant Classes --------------------
// Cheezious restaurant class, inheriting from Restaurant
class Cheezious : public Restaurant
{
public:
    // Constructor initializes base class with Cheezious's specific data
    Cheezious() : Restaurant("Cheezious", {"I-8", "G-10", "F-11"},
                            {"I-8 Islamabad", "G-10 Islamabad", "F-11 Islamabad"}, 4.5f)
    {
        // Populate the categorized menu for Cheezious
        categorizedMenu["Burgers"] = {
            MenuItem("Zinger Burger", 450),
            MenuItem("Cheese Zinger", 480),
            MenuItem("Double Zinger", 650),
            MenuItem("Spicy Zinger", 500)};
        categorizedMenu["Pizzas"] = {
            MenuItem("Fajita Pizza", 900),
            MenuItem("Pepperoni Pizza", 950)};
        categorizedMenu["Pastas"] = {
            MenuItem("Creamy Pasta", 600),
            MenuItem("Spicy Pasta", 650)};
    }
};

// Ranchers restaurant class, inheriting from Restaurant
class Ranchers : public Restaurant
{
public:
    // Constructor initializes base class with Ranchers's specific data
    Ranchers() : Restaurant("Ranchers", {"G-9", "F-6", "DHA"},
                            {"G-9 Islamabad", "F-6 Islamabad", "DHA Lahore"}, 4.2f)
    {
        // Populate the categorized menu for Ranchers
        categorizedMenu["Burgers"] = {
            MenuItem("Beef Burger", 480),
            MenuItem("Cheesy Beef Burger", 520),
            MenuItem("Ranch Beef Burger", 580),
            MenuItem("Double Decker", 620)};
        categorizedMenu["Wraps"] = {
            MenuItem("Grilled Wrap", 300),
            MenuItem("Zinger Wrap", 350)};
        categorizedMenu["Sandwiches"] = {
            MenuItem("Club Sandwich", 400),
            MenuItem("Cheese Sandwich", 370)};
    }
};

// Howdy restaurant class, inheriting from Restaurant
class Howdy : public Restaurant
{
public:
    // Constructor initializes base class with Howdy's specific data
    Howdy() : Restaurant("Howdy", {"Giga Mall", "Blue Area", "PWD"},
                            {"Giga Mall Islamabad", "Blue Area Islamabad", "PWD Islamabad"}, 4.0f)
    {
        // Populate the categorized menu for Howdy
        categorizedMenu["Burgers"] = {
            MenuItem("Howdy Burger", 550),
            MenuItem("Cheese Gun Burger", 580),
            MenuItem("Wild West Burger", 700),
            MenuItem("Bacon BBQ Burger", 680)};
        categorizedMenu["BBQ"] = {
            MenuItem("BBQ Platter", 1200),
            MenuItem("BBQ Ribs", 1300)};
        categorizedMenu["Steaks"] = {
            MenuItem("Ribeye Steak", 1400),
            MenuItem("T-Bone Steak", 1600)};
    }
};

// -------------------- ChefBot Class --------------------
// The main chatbot class that interacts with restaurants
class ChefBot
{
    vector<Restaurant *> restaurants; // A vector to hold pointers to all supported restaurants

public:
    // Constructor to initialize ChefBot, adding instances of derived restaurant classes
    ChefBot()
    {
        try
        {
            restaurants.push_back(new Cheezious());
            restaurants.push_back(new Ranchers());
            restaurants.push_back(new Howdy());
        }
        catch (const bad_alloc &e)
        {
            cout << "Memory allocation failed: " << e.what() << endl;
        }
    }

    // Greets the user and shows available commands
    void greet()
    {
        cout << "\n" << string(60, '=') << "\n";
        cout << " Welcome to ChefBot - Your Food Ordering Assistant!\n";
        cout << string(60, '=') << "\n";
        cout << "Type 'help' to see all available commands or 'exit' to quit.\n";
        cout << string(60, '=') << "\n";
    }

    // Shows help menu with all available commands
    void showHelp()
    {
        cout << "\n" << string(50, '=') << "\n";
        cout << " CHEFBOT COMMAND GUIDE\n";
        cout << string(50, '=') << "\n";
        
        cout << " INFORMATION COMMANDS:\n";
        cout << "   • 'tell me about restaurants' - Show all restaurant info\n";
        cout << "   • 'tell me about [restaurant name]' - Show specific restaurant\n";
        cout << "     Examples: 'tell me about cheezious'\n";
        cout << "               'tell me about ranchers'\n";
        cout << "               'tell me about howdy'\n";
        cout << "   • 'tell me about names' - Show restaurant names\n";
        cout << "   • 'tell me about ratings' - Show restaurant ratings\n";
        cout << "   • 'tell me about menu' - Show all menus\n";
        cout << "   • 'tell me about addresses' - Show all addresses\n";
        cout << "   • 'tell me about branches' - Show all branches\n\n";
        
        cout << " ORDERING COMMANDS:\n";
        cout << "   • 'order' - Start the ordering process\n";
        cout << "   • 'place order' - Alternative ordering command\n\n";
        
        cout << " RECOMMENDATION COMMANDS:\n";
        cout << "   • 'recommend' - Show all items under Rs 500\n";
        cout << "   • 'recommend burger' - Show burger recommendations\n";
        cout << "   • 'recommend pizza' - Show pizza recommendations\n";
        cout << "   • 'recommend pasta' - Show pasta recommendations\n";
        cout << "   • 'recommend wrap' - Show wrap recommendations\n";
        cout << "   • 'recommend sandwich' - Show sandwich recommendations\n\n";
        
        cout << " LOCATION COMMANDS:\n";
        cout << "   • 'nearest branch' - Find branches in your city\n";
        cout << "   • 'find branches' - Alternative branch finder\n\n";
        
        cout << " STATUS COMMANDS:\n";
        cout << "   • '[restaurant name] open now' - Check if restaurant is open\n";
        cout << "     Examples: 'cheezious open now'\n";
        cout << "               'ranchers open status'\n";
        cout << "               'howdy open now'\n\n";
        
        cout << " HELP & EXIT:\n";
        cout << "   • 'help' - Show this command guide\n";
        cout << "   • 'commands' - Show available commands\n";
        cout << "   • 'exit' - Quit ChefBot\n";
        
        cout << string(50, '=') << "\n";
        cout << " TIP: Commands are not case-sensitive!\n";
        cout << string(50, '=') << "\n";
    }

    // Shows a quick command summary
    void showQuickCommands()
    {
        cout << "\n Quick Commands:\n";
        cout << "• help - Show full command guide\n";
        cout << "• tell me about restaurants - Show all info\n";
        cout << "• order - Place an order\n";
        cout << "• recommend - Get recommendations under Rs 500\n";
        cout << "• nearest branch - Find branches near you\n";
        cout << "• [restaurant] open now - Check opening status\n";
        cout << "• exit - Quit ChefBot\n";
    }

    // Displays details for all registered restaurants
    void showAllInfo()
    {
        cout << "\n ALL RESTAURANTS INFORMATION:\n";
        for (auto r : restaurants) // Iterate through each restaurant
            r->showDetails();     // Call showDetails for each restaurant
    }

    // Displays specific information (name, rating, menu, address) for all restaurants
    void showByField(string field)
    {
        cout << "\n";
        if (field == "name")
        {
            cout << " RESTAURANT NAMES:\n";
            for (auto r : restaurants)
                cout << "   • " << r->getName() << endl;
        }
        else if (field == "rating")
        {
            cout << " RESTAURANT RATINGS:\n";
            for (auto r : restaurants)
                cout << "   • " << r->getName() << ": " << r->getRating() << "/5\n";
        }
        else if (field == "menu" || field == "prices")
        {
            cout << " ALL RESTAURANT MENUS:\n";
            for (auto r : restaurants)
            {
                cout << "\n" << r->getName() << ":\n";
                r->showMenu();
            }
        }
        else if (field == "address" || field == "branches")
        {
            cout << " RESTAURANT ADDRESSES:\n";
            for (auto r : restaurants)
            {
                cout << "\n" << r->getName() << ":\n";
                for (auto a : r->getAddresses())
                    cout << "   • " << a << endl;
            }
        }
        else
        {
            cout << " Sorry, I don't understand that field.\n";
            cout << "Try: names, ratings, menu, addresses, or branches\n";
        }
    }

    // Handles the order process
    void order()
    {
        cout << "\n ORDER PROCESS STARTED\n";
        cout << string(30, '-') << "\n";
        
        string restName;
        cout << "Which restaurant would you like to order from?\n";
        cout << "Available: Cheezious, Ranchers, Howdy\n";
        cout << "Enter restaurant name: ";
        getline(cin, restName); // Get restaurant name from user

        Restaurant *selected = nullptr; // Pointer to store the selected restaurant
        for (auto r : restaurants)      // Iterate through restaurants to find a match
        {
            if (toLower(r->getName()) == toLower(restName))
            {
                selected = r; // Found the restaurant
                break;
            }
        }

        if (!selected) // If no restaurant was found
        {
            cout << " Restaurant '" << restName << "' not found.\n";
            cout << "Available restaurants: Cheezious, Ranchers, Howdy\n";
            return;
        }

        selected->showDetails(); // Show details of the selected restaurant

        string category;
        cout << "\nWhich category would you like to order from? ";
        getline(cin, category); // Get category from user

        auto menu = selected->getCategorizedMenu(); // Get the menu of the selected restaurant
        if (menu.find(category) == menu.end())     // Check if the category exists
        {
            cout << " Category '" << category << "' not found.\n";
            cout << "Available categories: ";
            for (const auto &cat : menu)
                cout << cat.first << " ";
            cout << "\n";
            return;
        }

        cout << "\n Available items in " << category << ":\n";
        for (auto &item : menu[category]) // Display items in the selected category
            item.show();

        string itemName;
        cout << "\nEnter item name: ";
        getline(cin, itemName); // Get item name from user

        for (auto &item : menu[category]) // Iterate through items in the category to find a match
        {
            if (toLower(item.getName()) == toLower(itemName))
            {
                cout << "\n ORDER SUMMARY:\n";
                cout << "Restaurant: " << selected->getName() << "\n";
                cout << "Item: " << item.getName() << "\n";
                cout << "Price: Rs " << item.getPrice() << "\n";
                
                string confirm;
                cout << "\nConfirm order? (yes/no): ";
                getline(cin, confirm); // Ask for order confirmation

                if (toLower(confirm) == "yes" || toLower(confirm) == "y") // If user confirms
                {
                    double tax = 0.15 * item.getPrice(); // Calculate 15% tax
                    cout << "\n ORDER CONFIRMED!\n";
                    cout << string(25, '-') << "\n";
                    cout << " BILL SUMMARY:\n";
                    cout << "Item: " << item.getName() << " - Rs " << fixed << setprecision(2) << item.getPrice() << "\n";
                    cout << "Tax (15%): Rs " << tax << "\n";
                    cout << "Total: Rs " << item.getPrice() + tax << "\n";
                    cout << string(25, '-') << "\n";

                    // Log the order to a file
                    try
                    {
                        ofstream fout("order_history.txt", ios::app); // Open file in append mode
                        if (fout) // Check if file opened successfully
                        {
                            fout << "Restaurant: " << selected->getName() << "\n";
                            fout << "Item: " << item.getName() << "\n";
                            fout << "Price: Rs " << item.getPrice() << "\n";
                            fout << "Tax: Rs " << tax << "\n";
                            fout << "Total: Rs " << item.getPrice() + tax << "\n";
                            fout << "-----------------------------\n";
                            fout.close(); // Close the file
                            cout << " Order logged successfully.\n";
                        }
                        else
                        {
                            cout << " Warning: Could not log order to file.\n";
                        }
                    }
                    catch (...)
                    {
                        cout << " Warning: Error occurred while logging order.\n";
                    }
                    
                    cout << " Your order will be prepared shortly!\n";
                }
                else // If order is canceled
                {
                    cout << " Order canceled.\n";
                }
                return; // Exit after handling the order
            }
        }

        cout << " Item '" << itemName << "' not found in " << category << ".\n"; // If item was not found in the category
    }

    // Recommends all menu items under 500 Rs based on optional keyword
    void recommend(string keyword = "")
    {
        const double maxPrice = 500.0; // Fixed maximum price of 500
        
        // If keyword is empty, prompt user for it
        if (keyword.empty())
        {
            cout << "Enter item keyword (burger, pizza, pasta, wrap, sandwich) or press Enter for all: ";
            getline(cin, keyword);
        }

        bool found = false; // Flag to track if any recommendations are found
        cout << "\n RECOMMENDATIONS UNDER Rs " << maxPrice;
        if (!keyword.empty())
            cout << " (Keyword: " << keyword << ")";
        cout << ":\n";
        cout << string(50, '-') << "\n";

        for (auto r : restaurants) // Iterate through each restaurant
        {
            auto menu = r->getCategorizedMenu(); // Get the restaurant's menu
            bool restaurantHasItems = false;
            
            for (const auto &category : menu) // Iterate through all categories
            {
                for (const auto &item : category.second) // Iterate through items in each category
                {
                    if (item.getPrice() <= maxPrice) // Check if item price is within limit
                    {
                        // Check if keyword is empty or if item name contains the keyword
                        if (keyword.empty() || toLower(item.getName()).find(toLower(keyword)) != string::npos)
                        {
                            if (!restaurantHasItems) {
                                cout << "\n " << r->getName() << ":\n";
                                restaurantHasItems = true;
                            }
                            cout << "   • " << item.getName() << " (" << category.first << ") - Rs " << item.getPrice() << "\n";
                            found = true; // Set found flag to true
                        }
                    }
                }
            }
        }

        if (found) // If recommendations were found, log them
        {
            cout << string(50, '-') << "\n";
            cout << " Use 'order' command to place an order!\n";
            
            try
            {
                ofstream fout("recommendations.txt", ios::app); // Open file in append mode
                if (fout)
                {
                    fout << "Keyword: " << keyword << ", MaxPrice: " << maxPrice << endl;
                    fout.close();
                }
            }
            catch (...)
            {
                // Silent failure for logging
            }
        }
        else // If no recommendations were found
        {
            cout << " No matching items found under Rs " << maxPrice;
            if (!keyword.empty())
                cout << " with keyword '" << keyword << "'";
            cout << ".\n";
        }
    }

    // Finds and displays nearest branches with exact locations based on city input
    void nearestBranch()
    {
        string city;
        cout << "\n BRANCH FINDER\n";
        cout << string(20, '-') << "\n";
        cout << "Enter city name (e.g., Islamabad, Lahore): ";
        getline(cin, city); // Get city name from user

        bool found = false; // Flag to track if any branches are found
        cout << "\n Branches in " << city << ":\n";
        cout << string(30, '-') << "\n";
        
        for (auto r : restaurants) // Iterate through each restaurant
        {
            vector<string> addresses = r->getAddresses();
            vector<string> branches = r->getBranches();
            
            bool restaurantFound = false;
            for (size_t i = 0; i < addresses.size(); i++) // Iterate through each address of the restaurant
            {
                if (toLower(addresses[i]).find(toLower(city)) != string::npos) // Check if address contains the city
                {
                    if (!restaurantFound) {
                        cout << "\n " << r->getName() << ":\n";
                        restaurantFound = true;
                    }
                    cout << "   • " << branches[i] << " Branch\n";
                    cout << "     " << addresses[i] << "\n";
                    found = true; // Set found flag to true
                }
            }
        }

        if (!found) // If no branches found in the specified city
        {
            cout << " No branches found in '" << city << "'.\n";
            cout << "Available cities: Islamabad, Lahore\n";
        }
    }

    // Checks and displays the open/closed status of a specific restaurant
    void checkOpenStatus(string restName)
    {
        bool restaurantFound = false;
        
        for (auto r : restaurants) // Iterate through each restaurant
        {
            if (toLower(r->getName()) == toLower(restName))
            {
                restaurantFound = true;
                cout << "\n OPENING STATUS:\n";
                cout << string(20, '-') << "\n";
                if (r->isOpenNow()) // Check if the restaurant is open
                {
                    cout << " " << r->getName() << " is OPEN now! (12 PM - 11 PM)\n";
                }
                else // If the restaurant is closed
                {
                    cout << " " << r->getName() << " is CLOSED now.\n";
                    cout << "Opening hours: 12 PM - 11 PM\n";
                }
                break; // Stop after finding the restaurant
            }
        }

        if (!restaurantFound)
        {
            cout << " '" << restName << "' is not a recognized restaurant.\n";
            cout << "Available restaurants: Cheezious, Ranchers, Howdy\n";
        }
    }

    // Main function to handle user input and direct to appropriate functions
    void handleInput(string input)
    {
        // Log user input to a chat log file
        try
        {
            ofstream chatlog("chat_log.txt", ios::app); // Open file in append mode
            if (chatlog)
            {
                chatlog << "User: " << input << "\n";
                chatlog.close();
            }
        }
        catch (...)
        {
            // Silent failure for chat logging to not interrupt user experience
        }

        string lowerInput = toLower(input); // Convert input to lowercase for easier comparison

        // Check for help requests
        if (lowerInput == "help" || lowerInput == "commands" || lowerInput == "what can you do")
        {
            showHelp();
        }
        // Check for recommendation requests (now for all menu items under 500)
        else if (lowerInput.find("recommend") != string::npos || 
            (lowerInput.find("tell me about") != string::npos && lowerInput.find("under") != string::npos))
        {
            string keyword = "";
            // Extract keyword if present
            if (lowerInput.find("burger") != string::npos)
                keyword = "burger";
            else if (lowerInput.find("pizza") != string::npos)
                keyword = "pizza";
            else if (lowerInput.find("pasta") != string::npos)
                keyword = "pasta";
            else if (lowerInput.find("wrap") != string::npos)
                keyword = "wrap";
            else if (lowerInput.find("sandwich") != string::npos)
                keyword = "sandwich";
            
            recommend(keyword);
        }
        // Check for order requests
        else if (lowerInput.find("order") != string::npos || lowerInput.find("place order") != string::npos)
        {
            order();
        }
        // Check for nearest branch requests
        else if (lowerInput.find("nearest") != string::npos || lowerInput.find("branch") != string::npos || lowerInput.find("find branches") != string::npos)
        {
            nearestBranch();
        }
        // Check for open status requests for specific restaurants
        else if (lowerInput.find("open now") != string::npos || lowerInput.find("open status") != string::npos)
        {
            if (lowerInput.find("cheezious") != string::npos)
                checkOpenStatus("cheezious");
            else if (lowerInput.find("ranchers") != string::npos)
                checkOpenStatus("ranchers");
            else if (lowerInput.find("howdy") != string::npos)
                checkOpenStatus("howdy");
            else
            {
                cout << " Please specify which restaurant's opening status you want to check.\n";
                cout << "Available: Cheezious, Ranchers, Howdy\n";
                cout << "Example: 'cheezious open now'\n";
            }
        }
        // Check for "tell me about" requests (broadest category, checked last)
        else if (lowerInput.find("tell me about") != string::npos)
        {
            // Check if a specific restaurant name is mentioned
            if (lowerInput.find("cheezious") != string::npos ||
                lowerInput.find("ranchers") != string::npos ||
                lowerInput.find("howdy") != string::npos)
            {
                for (auto r : restaurants)
                {
                    if (lowerInput.find(toLower(r->getName())) != string::npos)
                        r->showDetails(); // Show details for the mentioned restaurant
                }
            }
            // Check for specific fields within "tell me about"
            else if (lowerInput.find("name") != string::npos ||
                     lowerInput.find("address") != string::npos ||
                     lowerInput.find("menu") != string::npos ||
                     lowerInput.find("branches") != string::npos ||
                     lowerInput.find("rating") != string::npos ||
                     lowerInput.find("prices") != string::npos)
            {
                // Call showByField for each identified field
                if (lowerInput.find("name") != string::npos)
                    showByField("name");
                else if (lowerInput.find("address") != string::npos)
                    showByField("address");
                else if (lowerInput.find("menu") != string::npos)
                    showByField("menu");
                else if (lowerInput.find("branches") != string::npos)
                    showByField("branches");
                else if (lowerInput.find("rating") != string::npos)
                    showByField("rating");
                else if (lowerInput.find("prices") != string::npos)
                    showByField("prices");
            }
            else if (lowerInput.find("restaurants") != string::npos)
            {
                showAllInfo(); // Show all restaurant info
            }
            else
            {
                cout << " I need more specific information. Try:\n";
                showQuickCommands();
            }
        }
        else // If no recognized command
        {
            cout << " Sorry, I don't understand '" << input << "'.\n";
            cout << "Type 'help' to see all available commands.\n";
            showQuickCommands();
        }
    }

    // Destructor to free dynamically allocated Restaurant objects
    ~ChefBot()
    {
        for (auto r : restaurants)
            delete r; // Delete each restaurant pointer to prevent memory leaks
    }
};

// -------------------- Main --------------------
// Entry point of the program
int main()
{
    try
    {
        ChefBot bot; // Create an instance of ChefBot
        bot.greet(); // Display welcome message and initial instructions
        
        string userInput; // Variable to store user input
        
        // Main program loop - continues until user types 'exit'
        while (true)
        {
            cout << "\n ChefBot: What can I help you with today? ";
            getline(cin, userInput); // Get complete line of user input
            
            // Check if user wants to exit the program
            if (toLower(userInput) == "exit" || toLower(userInput) == "quit" || 
                toLower(userInput) == "bye" || toLower(userInput) == "goodbye")
            {
                cout << "\n" << string(40, '=') << "\n";
                cout << " Thank you for using ChefBot!\n";
                cout << " Happy eating and see you next time!\n";
                cout << string(40, '=') << "\n";
                break; // Exit the main loop
            }
            
            // Handle empty input
            if (userInput.empty())
            {
                cout << " Please enter a command. Type 'help' for assistance.\n";
                continue; // Skip to next iteration
            }
            
            // Process the user's input through ChefBot
            bot.handleInput(userInput);
        }
    }
    catch (const exception& e)
    {
        // Handle any standard exceptions that might occur
        cout << " An error occurred: " << e.what() << endl;
        cout << "Please restart the program.\n";
        return 1; // Return error code
    }
    catch (...)
    {
        // Handle any other unexpected exceptions
        cout << " An unexpected error occurred. Please restart the program.\n";
        return 1; // Return error code
    }
    
    return 0; // Successful program termination
}