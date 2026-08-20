#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
//C++17 required
// bash: compile with $g++ -std=c++17 main.cpp -o program, then run, $./program
//macos: compile with $clang++ -std=c++17 incriptifi.cpp -o program, then run, $./program
//MinGw or GCC: compile with $g++ -std=c++17 incriptifi.cpp -o program.exe, then run, $.\program.exe
// Visul C++: compile with $cl /EHsc /std:c++17 incriptifi.cpp, then run,  .\incriptifi.exe
//dont include $ in script.........
namespace fs = std::filesystem;
const string Signature = "Created by Aureus The Femboy"
const std::string INDEX_FILE = ".passwords.dat";

// Helper function: Reads the password tracking index into memory
std::unordered_map<std::string, std::string> loadPasswordIndex() {
    std::unordered_map<std::string, std::string> index;
    if (!fs::exists(INDEX_FILE)) return index;

    std::ifstream file(INDEX_FILE);
    std::string fname, pass;
    while (file >> fname >> pass) {
        index[fname] = pass;
    }
    return index;
}

// Helper function: Saves the password tracking index back to disk
void savePasswordIndex(const std::unordered_map<std::string, std::string>& index) {
    std::ofstream file(INDEX_FILE);
    for (const auto& [fname, pass] : index) {
        file << fname << " " << pass << "\n";
    }
}

// The core byte-level encode worker
void encodeByte(char inputByte, char keyByte, std::ofstream& outputFile) {
    char encodedByte = inputByte ^ keyByte; 
    outputFile.put(encodedByte);
}

// The requested void decode function
void decode(const std::string& filename, const std::string& password) {
    // 1. Verify file exists
    if (!fs::exists(filename)) {
        std::cerr << "Error: File '" << filename << "' not found.\n";
        return;
    }

    // 2. Look up the assigned password for this file
    auto index = loadPasswordIndex();
    if (index.find(filename) == index.end()) {
        std::cerr << "Error: No password assignment tracking found for this file.\n";
        return;
    }

    // 3. Verify password match
    if (index[filename] != password) {
        std::cerr << "Error: Incorrect password! Access denied.\n";
        return;
    }

    // Calculate a simple byte key from the password string to run the XOR algorithm
    char keyByte = 0;
    for (char c : password) keyByte ^= c;
    if (keyByte == 0) keyByte = 0xAA; // Fallback block to prevent zeroing out data

    std::string tempFilename = filename + ".dec";
    std::ifstream srcFile(filename, std::ios::binary);
    std::ofstream destFile(tempFilename, std::ios::binary);

    if (!srcFile || !destFile) {
        std::cerr << "Error opening file streams for decoding.\n";
        return;
    }

    // 4. Decode the file
    char currentByte;
    while (srcFile.get(currentByte)) {
        encodeByte(currentByte, keyByte, destFile); 
    }

    srcFile.close();
    destFile.close();

    // 5. Replace original file and clean up tracking assignment
    try {
        fs::remove(filename);
        fs::rename(tempFilename, filename);
        
        // Remove file from the password index since it's now completely decoded
        index.erase(filename);
        savePasswordIndex(index);

        std::cout << "Success! '" << filename << "' has been decoded and unlocked.\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error during final save: " << e.what() << "\n";
    }
}

int main() {
    std::string filename;
    std::string password;
    int choice;

    std::cout << "1. Encode a file (Set Password)\n2. Decode a file (Enter Password)\nChoose an option (1-2): ";
    std::cin >> choice;
    std::cin.ignore(); // Clear the input buffer newline

    std::cout << "Enter the filename: ";
    std::getline(std::cin, filename);

    std::cout << "Enter the password: ";
    std::getline(std::cin, password);

    if (choice == 1) {
        if (!fs::exists(filename)) {
            std::cerr << "Error: File not found.\n";
            return 1;
        }

        // Generate a single byte encryption key based on the chosen password text
        char keyByte = 0;
        for (char c : password) keyByte ^= c;
        if (keyByte == 0) keyByte = 0xAA; 

        std::string tempFilename = filename + ".enc";
        std::ifstream srcFile(filename, std::ios::binary);
        std::ofstream destFile(tempFilename, std::ios::binary);
        
        char currentByte;
        while (srcFile.get(currentByte)) {
            encodeByte(currentByte, keyByte, destFile);
        }
        srcFile.close(); 
        destFile.close();
        
        fs::remove(filename);
        fs::rename(tempFilename, filename);

        // Assign and save the password to the index file
        auto index = loadPasswordIndex();
        index[filename] = password;
        savePasswordIndex(index);

        std::cout << "Success! '" << filename << "' is now encoded and locked with your password.\n";
        std::cout << Signature << std::endl;       
    } else if (choice == 2) {
        // Calls the requested decode handler which checks the assignment details natively
        decode(filename, password);
    } else {
        std::cerr << "Invalid choice.\n";
    }

    return 0;
}
