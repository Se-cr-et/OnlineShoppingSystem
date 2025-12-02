#include "OnlineShop.h"


//
Product::Product(string pName, string pDescription, int pProductID, int pPrice, int pQuantity):
 name(pName), description(pDescription), productID(pProductID), price(pPrice), quantity(pQuantity) {}

string Product::getName(){
    return name;
}

string Product::getDescription(){
    return description;
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

Cart& Cart::addProduct(Product& P, int pPrice){
    product.push_back(&P);
    productQuantity.push_back(pPrice);
    return *this;
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

void Catalog::Save(){
    fstream file;
    file.open("Catalog.txt", ios::out);
    if (file.is_open()){
        for (int i = 0; i < category.size(); i++){
            file << category[i] << "|";
        }
        file << "\n";

        for (int i = 0; i < product.size(); i++){
            file << product[i]->getName() << "|";
            file << product[i]->getDescription() << "|";
            file << product[i]->getPrice() << "|";
            file << product[i]->getQuantity() << "|";
            file << "\n";
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