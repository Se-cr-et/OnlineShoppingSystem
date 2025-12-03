#include "OnlineShop.h"
using std::string;

//
Product::Product(string pName, string pDescription, int pProductID, int pPrice, int pQuantity):
 name(pName), description(pDescription), productID(pProductID), price(pPrice), quantity(pQuantity) {}

string Product::getName(){
    return name;
}

string Product::getDescription(){
    return description;
}

string Product::getCategory(){
    return category;
}

int Product::getProductID(){
    return productID;
}

int Product::getPrice(){
    return price;
}

int Product::getQuantity(){
    return quantity;
}

Product& Product::operator--(){
    quantity--;
    return *this;
}

Product::~Product(){}
//



//
Person::Person(string uName): username(uName) {}

Person::~Person(){}
//



//
Cart::Cart() {}

Cart& Cart::addProduct(Product& P, int pQuantity){
    product.push_back(&P);
    productQuantity.push_back(pQuantity);
    return *this;
}

Product& Cart::searchProduct(int _prodID){
    for (int i = 0; i < product.size(); i++){
        if(product[i]->getProductID() == _prodID){
            return *product[i];
        }
    }
}

void Cart::loggingCart(fstream& _file){
    for (int i = 0; i < productQuantity.size(); i++){
        _file << productQuantity[i] << "|";
    }
    _file << "\n";

    for (int i = 0; i < product.size(); i++){
        _file << product[i]->getProductID() << "|";
    }
    _file << "\n";
}

void Cart::reloggingCart(fstream& _file){

}

void Cart::checkout_helper(fstream& _file){
    _file << "Name|";
    _file << "ProductID|";
    _file << "Price|";
    _file << "Quantity|";
    _file << "Amount|";
    _file << "\n";

    for (int i = 0; i < product.size(); i++){
        _file << product[i]->getName() << "|";
        _file << product[i]->getProductID() << "|";
        _file << product[i]->getPrice() << "|";
        _file << productQuantity[i] << "|";
        _file << productQuantity[i]*product[i]->getPrice() << "|";
        _file << "\n";
    }

    _file << "\nTotal Cost: ";
    int sum = 0;
    for (int i = 0; i < product.size(); i++){
        sum += productQuantity[i]*product[i]->getPrice();
    }
    _file << sum;
}

Cart::~Cart(){}
//



//
int User::userCount = 0;

User::User(string uName): Person(uName) {
    userCount++;
    userID = userCount;
}


void User::display() {
    cout << "               " << username << endl;
}

int User::getUserID(){
    return userID;
}

string User::getUsername(){
    return username;
}

void User::loggingUser(fstream& _file){
    _file << userID << "|";
    _file << username << "|";
    _file << "\n";
    _file << "@@Cart\n";
    cart.loggingCart(_file);
    _file << "@@/Cart\n";
}

void User::reloggingUser(fstream& _file){
    string check;
    while (true){
        getline(_file,check,'|');
        if (check == "@@Category"){
            cart.reloggingCart(_file);
        }
    }
}

void User::checkout(){
    fstream file;
    file.open("UserCart" + to_string(userID) + ".txt", ios::out);

    if (file.is_open()){
        file << userID << "\n";
        cart.checkout_helper(file);
    }
}

User::~User(){}
//



//
Catalog::Catalog(){}

void Catalog::loggingCatalog(fstream& _file){
    // Logging Category
    _file << "@@Category\n";
    for (int i = 0; i < category.size();i++){
        _file << category[i] << "|";
    }
    _file << "\n";
    _file << "@@/Category\n";

    // Logging Product
    _file << "@@Product\n";
    _file << product.size() << "\n";
    for (int i = 0; i < product.size(); i++){
        _file << product[i]->getProductID() << "|";
        _file << product[i]->getName() << "|";
        _file << product[i]->getDescription() << "|";
        _file << product[i]->getPrice() << "|";
        _file << product[i]->getQuantity() << "|";
    }
    _file << "\n";
    _file << "@@/Product\n";
}

void Catalog::reloggingCatalog(fstream& _file){
    string check;

    getline(_file, check, '|');
    if (check == "@@Category"){
        while (true){
            getline(_file, check, '|');
            if (check == "@@/Category"){
                break;
            }
            category.push_back(check);
        }
    }

    getline(_file, check, '|');
    if (check == "@@Product"){
        getline(_file, check, '|');
        for (int i = 0; i < stoi(check); i++){
            getline(_file, check, '|');
            int ID = stoi(check);

            getline(_file, check, '|');
            string name = check;

            getline(_file, check, '|');
            string description = check;

            getline(_file, check, '|');
            int price = stoi(check);

            getline(_file, check, '|');
            int quantity = stoi(check);
        }
        getline(_file, check, '|');
        if (check == "@@/Product"){
            return;
        }
    }
}

void Catalog::categoryDisplay(){
    cout << "Category: ";
    for (int i = 0; i < category.size(); i++){
        cout << category[i] <<", ";
    }
    cout << endl;
}

void Catalog::normalDisplay(){
    cout << "Products: " << endl;
    for (int i = 0; i < product.size(); i++){
        cout << product[i]->getProductID() << ". ";
        cout << product[i]->getName() << ", ";
        cout << product[i]->getDescription() << ", ";
        cout << product[i]->getPrice() << ", ";
        cout << product[i]->getQuantity() << ", ";
    }
    cout << endl;
}

void Catalog::searchDisplay(string categor){
    for (int i = 0; i < product.size(); i++){
        if (product[i]->getCategory() == categor){
            cout << product[i]->getProductID() << ". ";
            cout << product[i]->getName() << ", ";
            cout << product[i]->getDescription() << ", ";
            cout << product[i]->getPrice() << ", ";
            cout << product[i]->getQuantity() << ", ";
        }
    }
}

Catalog& Catalog::operator+=(string C){
    category.push_back(C);
    return *this;
}

Catalog& Catalog::operator+=(Product& P){
    product.push_back(&P);
    return *this;
}

Catalog::~Catalog(){
    for (int i = 0; i < product.size(); i++){
        delete product[i];
    }
}
//



//
Manager::Manager(string uName): Person(uName) {
    managerCount++;
    managerID = managerCount;
}

void Manager::display(){
    cout << "              " << username << endl;
}

void Manager::loggingManager(fstream& _file){
    _file << managerID << "|";
    _file << username << "|";
    _file << "\n";
}

int Manager::getManagerID(){
    return managerID;
}

Manager::~Manager() {}

int Manager::managerCount = 0;
//



//
OnlineShop::OnlineShop(){}

OnlineShop* OnlineShop::getInstance(){
    if (shopPtr == nullptr){
        shopPtr = new OnlineShop();
    }
    else{
        cout << "[SYSTEM ALREADY RUNNING]\n\n";
    }
    return shopPtr;
}

void OnlineShop::addCategory(string C){
    catalog += C;
}

void OnlineShop::addProduct(Product& P){
    catalog += P;
}

void OnlineShop::addUser(User* U){
    user.push_back(U);
}

void OnlineShop::addManager(Manager* M){
    manager.push_back(M);
}

void OnlineShop::displayUsers(){
    cout << "<-------------[USERS]-------------->" << endl;
    for (int i = 0; i < user.size(); i++){
        cout << "            ----ID" + to_string(user[i]->getUserID()) + "----" << endl;
        user[i]->display();
        cout << "            -----------" << endl;
    }
    cout << endl;
}

void OnlineShop::displayManager(){
    cout << "<-------------[MANAGERS]-------------->" << endl;
    for (int i = 0; i < manager.size(); i++){
        cout << "            ----ID" + to_string(manager[i]->getManagerID()) + "----" << endl;
        manager[i]->display();
        cout << "            -----------" << endl;
    }
    cout << endl;
}


void OnlineShop::RunSystem(){
    // Relogging FIle
    fstream file;
    file.open("ShopDatabase.txt", ios::in);

    string check;
    if (file.is_open()){
        while (true){
            getline(file, check, '|');
            if (check == "@Catalog"){
                catalog.reloggingCatalog(file);
                getline(file, check, '|');
            }

            if (check == "@User"){
                while (true){
                    
                }
            }

            if (check == "@Manager"){

            }

            if (check == "@END"){
                break;
            }
        }
    }
    //
    while (true){
        int _Person;
        cout << "[ONLINE SHOPPING SYSTEM]" << endl;
        cout << "1) Login as User" << endl;
        cout << "2) Login as Manager" << endl;
        cin >> _Person;

        if (_Person == 1){
            int _User;
            cout << "[SELECT YOUR USER]" << endl;
            for (int i = 0; i < user.size(); i++){
                cout << user[i]->getUserID() << ") " << user[i]->getUsername();
            }
            cin >> _User;
            User* currentUser = user[_User - 1];
            system("cls");
            while (true) {
                int _SearchBy;
                cout << "You are logged in as " << currentUser->getUsername() << endl << endl;
                cout << "PRESS '1', TO NORMAL SEARCH" << endl;
                cout << "PRESS '2', TO SEARCH BY CATEGORY" << endl;
                cin >> _SearchBy;

                cout << "[CATALOG]" << endl;
                if (_SearchBy == 1){
                    catalog.categoryDisplay();
                    catalog.normalDisplay();
                }

                if (_SearchBy == 2){
                    string Categor;
                    catalog.categoryDisplay();
                    cout << "Category: ";
                    cin >> Categor;
                    catalog.searchDisplay(Categor);
                }

                int ProdID;
                cout << endl << "[Add to Cart]" << endl;
                while (true){
                    cout << "ProductID: ";
                    cin >> ProdID;
                    if (ProdID == 0){
                        break;
                    }

                }
            }

        }
    }
}

void OnlineShop::CloseSystem(){
    fstream file;
    file.open("ShopDatabase.txt", ios::out);
    if (file.is_open()){

        file << "@Catalog\n";
        catalog.loggingCatalog(file);
        file << "@/Catalog\n";
        file << "\n";

        file << "@User\n";
        for (int i = 0; i < user.size(); i++){
            user[i]->loggingUser(file);
        }
        file << "@/User\n";
        file << "\n";

        file << "@Manager\n";
        for (int i = 0; i < manager.size(); i++){
            manager[i]->loggingManager(file);
        }
        file << "@/Manager\n";
        file << "\n";
    }
    file.close();
}

OnlineShop::~OnlineShop(){
    for (int i = 0; i < user.size(); i++){
        delete user[i];
    }

    for (int i = 0; i < manager.size(); i++){
        delete manager[i];
    }
}

OnlineShop* OnlineShop::shopPtr = nullptr;
//