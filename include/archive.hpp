#pragma once

#include <archive.h>
#include <archive_entry.h>
#include <filesystem>

namespace bull
{
    class Archive
    {
        private:
            void add_file_to_archive(struct archive *a, const std::filesystem::path &filepath);
        public:
            
            void create_archive(const std::filesystem::path &dir, const std::filesystem::path &archive_path);
            void extract_archive(const std::filesystem::path &archive_path, const std::filesystem::path &extract_dir);
    };
}
