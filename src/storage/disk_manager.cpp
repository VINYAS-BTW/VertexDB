#include "disk_manager.h"

#include <cstring>
#include <filesystem>
#include <stdexcept>

namespace mydb {

DiskManager::DiskManager(const std::string &db_file)
    : db_file_name_(db_file) {

    // create the file if it doesn't exist
    if (!std::filesystem::exists(db_file_name_)) {
        std::ofstream create(db_file_name_, std::ios::binary);
        create.close();
    }

    db_io_.open(
        db_file_name_,
        std::ios::binary |
        std::ios::in |
        std::ios::out
    );

    if (!db_io_.is_open()) {
        throw std::runtime_error("failed to open database file");
    }

    // determine how many pages already exist
    db_io_.seekg(0, std::ios::end);

    const auto file_size = db_io_.tellg();

    next_page_id_ =
        static_cast<page_id_t>(file_size / PAGE_SIZE);
}

DiskManager::~DiskManager() {

    if (db_io_.is_open()) {
        db_io_.close();
    }
}

auto DiskManager::GetOffset(page_id_t page_id) const
    -> std::streamoff {

    return static_cast<std::streamoff>(page_id) * PAGE_SIZE;
}

void DiskManager::WritePage(
    page_id_t page_id,
    const char *page_data) {

    std::lock_guard<std::mutex> guard(io_latch_);

    db_io_.seekp(GetOffset(page_id));

    db_io_.write(page_data, PAGE_SIZE);

    db_io_.flush();
}

void DiskManager::ReadPage(
    page_id_t page_id,
    char *page_data) {

    std::lock_guard<std::mutex> guard(io_latch_);

    db_io_.seekg(GetOffset(page_id));

    if (!db_io_.read(page_data, PAGE_SIZE)) {

        // reading past eof returns an empty page
        std::memset(page_data, 0, PAGE_SIZE);

        db_io_.clear();
    }
}

auto DiskManager::AllocatePage()
    -> page_id_t {

    return next_page_id_++;
}

auto DiskManager::GetPageCount() const
    -> page_id_t {

    return next_page_id_;
}

} // namespace mydb