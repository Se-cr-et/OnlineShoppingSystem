#include "OnlineShop.h"
using std::string;

//
Product::Product(string pName, string pCategory, int pPrice, int pQuantity):
name(pName), category(pCategory), price(pPrice), quantity(pQuantity) {
    productCount++;
    productID = productCount;
}

string Product::getName(){
    return name;
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

int Product::productCount = 0;
//



//
Person::Person(string uName, string uPassword): username(uName), password(uPassword) {}

string Person::getUsername(){
    return username;
}

string Person::getPassword(){
    return password;
}

Person::~Person(){}
//



//
Cart::Cart() {}

Cart& Cart::addProduct(Product& P, int pQuantity){
    product.push_back(&P);
    productQuantity.push_back(pQuantity);
    return *this;
}

void Cart::removeProduct(Product& P, int _prodID){
    int index;
    for (int i = 0; i < product.size(); i++){
        if(product[i]->getProductID() == _prodID){
            index = i;
        }
    }
    product.erase(product.begin() + index);
    productQuantity.erase(productQuantity.begin() + index);
}

Product* Cart::searchProduct(int _prodID){
    for (int i = 0; i < product.size(); i++){
        if(product[i]->getProductID() == _prodID){
            return product[i];
        }
    }
    return nullptr;
}

void Cart::loggingCart(fstream& _file){
    _file << product.size() << "\n";
    for (int i = 0; i < productQuantity.size(); i++){
        _file << productQuantity[i] << " ";
    }
    _file << "\n";

    for (int i = 0; i < product.size(); i++){
        _file << product[i]->getProductID() << " ";
    }
    _file << "\n";
}

void Cart::reloggingCart(fstream& _file, Catalog& Catalog){
    int productSize;
    int productQ;
    int prodID;

    _file >> productSize;
    for (int i = 0; i < productSize; i++){
        _file >> productQ;
        productQuantity.push_back(productQ);
    }

    for (int i = 0; i < productSize; i++){
        _file >> prodID;
        product.push_back(Catalog.searchProduct(prodID));
    }
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

User::User(string uName, string uPassword): Person(uName, uPassword) {
    userCount++;
    userID = userCount;
}


void User::display() {
    cout << "               " << username << endl;
}

int User::getUserID(){
    return userID;
}

void User::addProduct(Product& P, int pQuantity){
    cart.addProduct(P, pQuantity);
}

void User::removeProduct(Product& P, int prodID){
    cart.removeProduct(P, prodID);
}

void User::loggingUser(fstream& _file){
    _file << username << " ";
    _file << password << " ";
    _file << "\n";
    cart.loggingCart(_file);
}

void User::reloggingUser(fstream& _file, Catalog& Catalog){
    cart.reloggingCart(_file, Catalog);
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
    _file << category.size() << "\n";
    for (int i = 0; i < category.size();i++){
        _file << category[i] << " ";
    }
    _file << "\n";

    // Logging Product
    _file << product.size() << "\n";
    for (int i = 0; i < product.size(); i++){
        _file << product[i]->getName() << " ";
        _file << product[i]->getCategory() << " ";
        _file << product[i]->getPrice() << " ";
        _file << product[i]->getQuantity() << " ";
        _file << "\n";
    }
}

void Catalog::reloggingCatalog(fstream& _file){

    int categorySize;
    string cate;
    _file >> categorySize;
    for (int i = 0; i < categorySize; i++){
        _file >> cate;
        category.push_back(cate);
    }

    int productSize;
    _file >> productSize;

    int prodPrice, prodQuantity;
    string prodName, prodCategory;
    for (int i = 0; i < productSize; i++){
        _file >> prodName;
        _file >> prodCategory;
        _file >> prodPrice;
        _file >> prodQuantity;
        product.push_back(new Product(prodName, prodCategory, prodPrice, prodQuantity));
    }
}

Product* Catalog::searchProduct(int proID){
    for (int i = 0; i < product.size(); i++){
        if (product[i]->getProductID() == proID){
            return product[i];
        }
    }
    return nullptr;
}

int Catalog::searchProductIndex(int proID){
    for (int i = 0; i < product.size(); i++){
        if (product[i]->getProductID() == proID){
            return i;
        }
    }
    return -1;
}

void Catalog::categoryDisplay(){
    cout << "Category: ";
    for (int i = 0; i < category.size(); i++){
        cout << category[i] <<", ";
    }
    cout << endl;
}

void Catalog::unfilteredDisplay(){
    cout << "Products: " << endl;
    for (int i = 0; i < product.size(); i++){
        cout << product[i]->getProductID() << ". ";
        cout << product[i]->getName() << ", ";
        cout << product[i]->getPrice() << ", ";
        cout << product[i]->getQuantity() << ", ";
        cout << endl;
    }
    cout << endl << endl;
}

void Catalog::filteredDisplay(string categor){
    for (int i = 0; i < product.size(); i++){
        if (product[i]->getCategory() == categor){
            cout << product[i]->getProductID() << ". ";
            cout << product[i]->getName() << ", ";
            cout << product[i]->getPrice() << ", ";
            cout << product[i]->getQuantity() << ", ";
        }
    }
    cout << endl;
}

Catalog& Catalog::operator+=(string C){
    category.push_back(C);
    return *this;
}

Catalog& Catalog::operator+=(Product& P){
    product.push_back(&P);
    return *this;
}

Catalog& Catalog::operator-=(string C){
    for (int i = 0; i < category.size(); i++){
        if (category[i] == C){
            category.erase(category.begin() + i);
        }
    }
    return *this;
}
Catalog& Catalog::operator-=(int _prodID){
    product.erase(product.begin() + this->searchProductIndex(_prodID));
    return *this;
}

Catalog::~Catalog(){
    for (int i = 0; i < product.size(); i++){
        delete product[i];
    }
}
//



//
Manager::Manager(string uName, string uPassword): Person(uName, uPassword) {
    managerCount++;
    managerID = managerCount;
}

void Manager::display(){
    cout << "              " << username << endl;
}

void Manager::loggingManager(fstream& _file){
    _file << managerID << " ";
    _file << username << " ";
    _file << "\n";
}

void Manager::reloggingManager(fstream& _file){
    return;
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

void OnlineShop::RunSystem(){
    // Relogging FIle
    fstream file1, file2, file3;
    file1.open("Catalog.txt", ios::in);
    file2.open("User.txt", ios::in);
    file3.open("Manager.txt", ios::in);
    if (file1.is_open() && file2.is_open() && file3.is_open()){
        // Catalog Logging
        catalog.reloggingCatalog(file1);
        //


        // User Logging
        int userSize;
        file2 >> userSize;
        for (int i = 0; i < userSize; i++){
            string username;
            string password;
            file2 >> username;
            file2 >> password;

            User* u = new User(username, password);
            u->reloggingUser(file2, catalog);
            user.push_back(u);
        }
        //


        // Manager Logging
        int managerSize;
        file3 >> managerSize;
        for (int i = 0; i < managerSize; i++){
            string username;
            string password;
            file3 >> username;
            file3 >> password;

            Manager* m = new Manager(username, password);
            m->reloggingManager(file3);
        }
        //
    }
    //





    bool SystemRunning = true;
    while (SystemRunning){
        int Check_1;
        cout << "[ONLINE SHOPPING SYSTEM]" << endl << endl;
        cout << "0) Terminate Program" << endl;
        cout << "1) Signup" << endl;
        cout << "2) Login" << endl;
        cin >> Check_1;
        system("clear");

        if (Check_1 == 1){
            int Check_2;
            cout << "1) Signup as User" << endl;
            cout << "2) Signup as Manager" << endl;
            cin >> Check_2;
            system("clear");

            if (Check_2 == 1){
                string username, password;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                user.push_back(new User(username, password));
            }
            else if (Check_2 == 2){
                string username, password;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                manager.push_back(new Manager(username, password));
            }
        }
        else if (Check_1 == 2){
            int Check_2;
            cout << "1) Login as User" << endl;
            cout << "2) Login as Manager" << endl;
            cin >> Check_2;
            system("clear");

            if (Check_2 == 1){
                int Check_3;
                cout << "[SELECT USER]" << endl;
                for (int i = 0; i < user.size(); i++){
                    cout << user[i]->getUserID() << ") " << user[i]->getUsername() << endl;
                }
                cin >> Check_3;
                system("clear");

                User* currentUser = user[Check_3 - 1];

                string password;
                bool LoggedIn = false;
                cout << "Password: "; cin >> password;
                if (password == currentUser->getPassword()){
                    LoggedIn = true;
                }
                while (LoggedIn){
                    system("clear");
                    int Check_4;
                    cout << "[LOGGED IN AS: " << currentUser->getUsername() << "]" << endl << endl;
                    cout << "0) Return Back" << endl;
                    cout << "1) Unfiltered Products" << endl;
                    cout << "2) Filtered Products" << endl;
                    cin >> Check_4;
                    system("clear");

                    cout << "[CATALOG]" << endl << endl;
                    if (Check_4 == 1){
                        catalog.categoryDisplay();
                        catalog.unfilteredDisplay();
                    }
                    else if (Check_4 == 2){
                        catalog.categoryDisplay();
                        cout << "Category: ";
                        string choosenCategory;
                        cin >> choosenCategory;
                        catalog.filteredDisplay(choosenCategory);
                    }
                    else {
                        LoggedIn = false;
                        break;
                    }


                    int Check_5;
                    cout << "[CART]" << endl << endl;
                    cout << "1) Add Item to Cart" << endl;
                    cout << "2) Remove Item from Cart" << endl;
                    cout << "3) Checkout" << endl;
                    cin >> Check_5;

                    int ProdID, Quantity;
                    if (Check_5 == 1){
                        cout << "ProductID: ";
                        cin >> ProdID;
                        cout << "Quantity: ";
                        cin >> Quantity;
                        Product* Prod = catalog.searchProduct(ProdID);
                        currentUser->addProduct(*Prod, Quantity);
                    }
                    else if (Check_5 == 2){
                        cout << "ProductID: ";
                        cin >> ProdID;
                        Product* Prod = catalog.searchProduct(ProdID);
                        currentUser->removeProduct(*Prod, ProdID);
                    }
                    else if (Check_5 == 3){
                        currentUser->checkout();
                        return;
                    }
                }
            }
            else if (Check_2 == 2){
                int Check_3;
                cout << "[SELECT MANAGER]" << endl;
                for (int i = 0; i < manager.size(); i++){
                    cout << manager[i]->getManagerID() << ") " << manager[i]->getUsername() << endl;
                }
                cin >> Check_3;
                system("clear");

                Manager* currentManager = manager[Check_3 - 1];

                string password;
                bool LoggedIn = false;
                cout << "Password: "; cin >> password;
                if (password == currentManager->getPassword()){
                    LoggedIn = true;
                }
                while (LoggedIn){
                    system("clear");
                    int Check_4;
                    catalog.categoryDisplay();
                    catalog.unfilteredDisplay();
                    cout << endl;
                    cout << "[LOGGED IN AS: " << currentManager->getUsername() << "]" << endl << endl;
                    cout << "0) Return Back" << endl;
                    cout << "1) Add Product" << endl;
                    cout << "2) Remove Product" << endl;
                    cout << "3) Add Category" << endl;
                    cout << "4) Remove Category" << endl;
                    cin >> Check_4;
                    system("clear");

                    if (Check_4 == 1) {
                        int prodPrice, prodQuantity;
                        string prodName, prodCateory;
                        cout << "Name: "; cin >> prodName;
                        cout << "Category: "; cin >> prodCateory;
                        cout << "Price: "; cin >> prodPrice;
                        cout << "Quantity: "; cin >> prodQuantity;
                        Product* P = new Product(prodName, prodCateory, prodPrice, prodQuantity);
                        catalog += *P;
                    }
                    else if (Check_4 == 2){
                        int prodID;
                        cout << "ID: "; cin >> prodID;
                        catalog -= prodID;
                    }
                    else if (Check_4 == 3){
                        string Cate;
                        cout << "Category: "; cin >> Cate;
                        catalog += Cate;
                    }
                    else if (Check_4 == 4){
                        string Cate;
                        cout << "Category: "; cin >> Cate;
                        catalog -= Cate;
                    }
                    else {
                        LoggedIn = false;
                    }
                }
            }
        }
        else{
            SystemRunning = false;
        }
        
    }
}

void OnlineShop::CloseSystem(){
    fstream file1, file2, file3;
    file1.open("Catalog.txt", ios::out);
    file2.open("User.txt", ios::out);
    file3.open("Manager.txt", ios::out);
    if (file1.is_open() && file2.is_open() && file3.is_open()){
        // Catalog Logging
        catalog.loggingCatalog(file1);
        //


        // User Logging
        file2 << user.size() << "\n";
        for (int i = 0; i < user.size(); i++){
            user[i]->loggingUser(file2);
        }
        file2 << "\n";
        //


        // Manager Logging
        file3 << manager.size() << "\n";
        for (int i = 0; i < manager.size(); i++){
            manager[i]->loggingManager(file3);
        }
        file3 << "\n";
        //
    }
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