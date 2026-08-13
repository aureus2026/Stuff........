#include <iostream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// Fixed: Added variable name 'sig' and missing semicolon
const std::string sig = "Created by Aureus the Femboy";

// Fixed: Added underscore to function name
void establish_baseline(const std::string& target_dir, std::unordered_map<std::string, fs::file_time_type>& map_to_fill) {
    if (!fs::exists(target_dir)) {
        fs::create_directory(target_dir);
    }
    for (const auto& entry : fs::recursive_directory_iterator(target_dir)) {
        if (fs::is_regular_file(entry.path())) {
            map_to_fill[entry.path().string()] = fs::last_write_time(entry.path());
        }
    }
}

int main() {
    // Fixed: Moved signature print to the top so it actually runs
    std::cout << sig << "\n\n";

    std::unordered_map<std::string, fs::file_time_type> baseline_map;
    std::string folder_to_watch = "./sandbox";
    
    // Fixed: Added underscore to variable and function names
    establish_baseline(folder_to_watch, baseline_map);

    // Fixed: Set an actual default value of 3.0 seconds
    double timeoutInSeconds = 3.0; 
    std::cout << "Set timeout in seconds (default is 3): ";
    
    // Fixed: Corrected namespace syntax and handled safe user input
    if (!(std::cin >> timeoutInSeconds)) {
        timeoutInSeconds = 3.0;
    }

    while (true) {
        // Fixed: Cast the double to a duration safely
        std::this_thread::sleep_for(std::chrono::duration<double>(timeoutInSeconds));
        
        std::unordered_map<std::string, fs::file_time_type> current_map;
        if (fs::exists(folder_to_watch)) {
            for (const auto& entry : fs::recursive_directory_iterator(folder_to_watch)) {
                if (fs::is_regular_file(entry.path())) {
                    current_map[entry.path().string()] = fs::last_write_time(entry.path());
                }
            }
        }

        // Check for created files
        for (const auto& pair : current_map) {
            if (baseline_map.find(pair.first) == baseline_map.end()) {
                std::cout << "[🚨 CREATED] " << pair.first << std::endl;
            }
        }

        // Check for deleted or modified files
        for (const auto& pair : baseline_map) {
            auto current_iterator = current_map.find(pair.first);
            if (current_iterator == current_map.end()) {
                std::cout << "[🔥 DELETED] " << pair.first << std::endl;
            } else if (current_iterator->second != pair.second) {
                std::cout << "[⚠️ MODIFIED] " << pair.first << std::endl;
            }
        }

        // Fixed: Use std::move to prevent expensive copying of the maps
        baseline_map = std::move(current_map);
    }

    return 0;
}
