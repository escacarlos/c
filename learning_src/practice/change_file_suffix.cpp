#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void change_file_suffix(const fs::path& path) {
    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            const fs::path& filename = entry.path().filename();
            if (filename.extension() == ".cc") {
                fs::path new_filename = filename.stem();
                new_filename += ".c";
                fs::path new_path = entry.path().parent_path() / new_filename;
                fs::rename(entry.path(), new_path);
                std::cout << "Renamed: " << entry.path() << " -> " << new_path << std::endl;
            }
        }
    }
}

int main() {
    const fs::path root_directory = "."; // Change this to the root directory path
    change_file_suffix(root_directory);
    return 0;
}