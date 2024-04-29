#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

// Function to detect cycles using DFS
bool hasCycle(
    const std::string& course,
    const std::unordered_map<std::string, std::vector<std::string>>& catalog,
    std::unordered_set<std::string>& visited,
    std::unordered_set<std::string>& recursionStack) {
    if (recursionStack.count(course)) {
        // If a course is already in the recursion stack, there's a cycle
        return true;
    }

    if (visited.count(course)) {
        // If the course is already visited, no need to check again
        return false;
    }

    visited.insert(course);
    recursionStack.insert(course);

    for (const auto& dependency : catalog.at(course)) {
        if (hasCycle(dependency, catalog, visited, recursionStack)) {
            return true;
        }
    }

    recursionStack.erase(course);
    return false;
}

// Function to validate the catalog
bool isCatalogValid(const std::unordered_map<std::string, std::vector<std::string>>& catalog) {
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> recursionStack;

    for (const auto& course : catalog) {
        if (hasCycle(course.first, catalog, visited, recursionStack)) {
            return false; // Cycle found, invalid catalog
        }
    }

    return true; // No cycles found, catalog is valid
}

int main() {
    // Example course catalog
    std::unordered_map<std::string, std::vector<std::string>> catalog = {
        {"Databases", {"Security", "Logging"}},
        {"Security", {"Databases", "Logging"}},
        {"Logging", {}}
    };

    bool isValid = isCatalogValid(catalog);

    if (isValid) {
        std::cout << "The course catalog is valid." << std::endl;
    }
    else {
        std::cout << "The course catalog contains errors (cycle detected)." << std::endl;
    }

    return 0;
}
