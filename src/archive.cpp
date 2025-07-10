#include "../include/archive.hpp"
#include <filesystem>
#include <archive.h>
#include <archive_entry.h>
#include <fstream>

void bull::Archive::add_file_to_archive(struct archive *a, const std::filesystem::path &filepath)
{
    struct archive_entry *entry = archive_entry_new();
    archive_entry_set_pathname(entry, filepath.c_str());
    archive_entry_set_size(entry, std::filesystem::file_size(filepath));
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);
    archive_write_header(a, entry);

    std::ifstream file(filepath, std::ios::binary);
    char buf[8192];

    while (file.read(buf, sizeof(buf))) 
    {
        archive_write_data(a, buf, file.gcount());
    }

    archive_write_data(a, buf, file.gcount());
    archive_entry_free(entry);
}

void bull::Archive::create_archive(const std::filesystem::path &dir, const std::filesystem::path &archive_path)
{
    struct archive *a = archive_write_new();
    archive_write_add_filter_gzip(a);
    archive_write_set_format_pax_restricted(a);
    archive_write_open_filename(a, archive_path.c_str());

    for (const auto &entry : std::filesystem::recursive_directory_iterator(dir)) 
    {
        if (entry.is_regular_file()) 
        {
            add_file_to_archive(a, entry.path());
        }
    }

    archive_write_close(a);
    archive_write_free(a);

}

void bull::Archive::extract_archive(const std::filesystem::path &archive_path, const std::filesystem::path &extract_dir)
{
    struct archive *a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_tar(a);
    archive_read_open_filename(a, archive_path.c_str(), 10240);

    struct archive_entry *entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) 
    {
        std::filesystem::path filepath = extract_dir / archive_entry_pathname(entry);

        if (archive_entry_filetype(entry) == AE_IFREG) 
        {
            std::filesystem::create_directories(filepath.parent_path());
            std::ofstream outfile(filepath, std::ios::binary);
            char buf[8192];
            size_t size;

            while ((size = archive_read_data(a, buf, sizeof(buf))) > 0) 
            {
                outfile.write(buf, size);
            }
        } 
        
        else if (archive_entry_filetype(entry) == AE_IFDIR) std::filesystem::create_directories(filepath);
    }


    archive_read_close(a);
    archive_read_free(a);

}