// 3Cpp_phone_book_Gerstein.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>

class PhoneBook
{
public:
    PhoneBook() = default;
    
    std::string& operator[](std::string name)
    {
        return dict_name_num[name];
    }
    void AddUser(std::string name, std::string number)
    {
        if (dict_name_num.count(name) > 0)std::cout << "Name "<<name<<" is already in the database! Overriding\n";
        dict_name_num[name] = number;
    }
    std::string FindNumber(std::string name) const
    {
        return dict_name_num.find(name)->second;
    }
    void DeleteNumber(std::string name)
    {
        dict_name_num.erase(name);
    }
    void Print();
    void Print(std::string num);

private:
    std::map<std::string, std::string> dict_name_num;
};

void PhoneBook::Print()
{
    std::cout << "***Phone book***\n";
    std::map<std::string, std::string>::iterator it;
    for (it = dict_name_num.begin(); it != dict_name_num.end(); it++)
        std::cout << it->first << "\t\t" << it->second << "\n";
    std::cout << "***\n";
}

void PhoneBook::Print(std::string num)
{
    std::cout << "***\n";
    std::cout << num << ":\n";
    std::map<std::string, std::string>::iterator it;
    bool found_non = true;
    for (it = dict_name_num.begin(); it != dict_name_num.end(); it++)
    {
        if (it->second == num)
        {
            std::cout << it->first << "\n";
            found_non = false;
        }
    }
    if (found_non) std::cout << "No such number in the book\n";
    std::cout << "***\n";
}

int main()
{
    PhoneBook my_phone_book;
    my_phone_book["Jephry"] = "123456789";
    my_phone_book["Holy"] = "123456545";
    my_phone_book["Janine"] = "098765432";
    my_phone_book["Barry"] = "123456789";
    my_phone_book.Print();
    my_phone_book.AddUser("Janine", "123");
    std::cout<<"Let's find out Barry's number: " << my_phone_book.FindNumber("Barry") << "\n";
    my_phone_book.DeleteNumber("Holy");
    my_phone_book.Print();
    my_phone_book.Print("123456789");
    my_phone_book.Print("1");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
