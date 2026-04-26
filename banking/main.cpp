#include <iostream>
#include "include/Account.hpp"
#include "include/Transaction.hpp"

int main() {
    Account alice("Alice", 1000);
    Account bob("Bob", 500);
    
    std::cout << "Alice: " << alice.GetBalance() << std::endl;
    std::cout << "Bob: " << bob.GetBalance() << std::endl;
    
    Transaction txn(300, "Alice", "Bob");
    
    if (txn.Execute(alice, bob)) {
        std::cout << "Transaction OK!" << std::endl;
        std::cout << "Alice: " << alice.GetBalance() << std::endl;
        std::cout << "Bob: " << bob.GetBalance() << std::endl;
    }
    
    return 0;
}
