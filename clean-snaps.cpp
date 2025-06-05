#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

int main() {
    // Use popen to capture output of disabled snaps
    FILE* checkPipe = popen("snap list --all | awk '/disabled/{print $1}'", "r");
    if (!checkPipe) {
        std::cerr << "Failed to check for disabled snaps." << std::endl;
        return 1;
    }

    std::vector<std::string> disabledSnaps;
    char buffer[128];

    while (fgets(buffer, sizeof(buffer), checkPipe) != nullptr) {
        std::string snapName(buffer);
        // Remove trailing newline
        snapName.erase(snapName.find_last_not_of(" \n\r\t") + 1);
        if (!snapName.empty()) {
            disabledSnaps.push_back(snapName);
        }
    }
    pclose(checkPipe);

    if (disabledSnaps.empty()) {
        std::cout << "No snaps to remove." << std::endl;
        return 0;
    }

    // Show list of snaps to be removed
    std::cout << "Following snaps to be removed:" << std::endl;
    for (const auto& name : disabledSnaps) {
        std::cout << " " << name << std::endl;
    }

    // Prompt the user for confirmation
    std::cout << "Continue (y/n): ";
    char reply;
    std::cin >> reply;

    if (reply == 'y' || reply == 'Y') {
        // Get full list with revision
        FILE* removePipe = popen("snap list --all | awk '/disabled/{print $1, $3}'", "r");
        if (!removePipe) {
            std::cerr << "Failed to get snap revisions." << std::endl;
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), removePipe) != nullptr) {
            std::istringstream iss(buffer);
            std::string snapname, revision;
            iss >> snapname >> revision;

            std::string cmd = "snap remove \"" + snapname + "\" --revision=\"" + revision + "\"";
            std::system(cmd.c_str());
        }
        pclose(removePipe);
    } else {
        std::cout << "Aborted by user." << std::endl;
    }

    return 0;
}

