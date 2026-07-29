#include "disk_manager.h"
#include <stdexcept>

DiskManager::DiskManager(const std::string& db_file) : file_name_(db_file) {
    db_file_.open(db_file, std::ios::binary | std::ios::in | std::ios::out);
    if (!db_file_.is_open()) {
        db_file_.clear();
        db_file_.open(db_file, std::ios::binary | std::ios::trunc | std::ios::out);
        db_file_.close();
        db_file_.open(db_file, std::ios::binary | std::ios::in | std::ios::out);
    }
    if (!db_file_.is_open()) throw std::runtime_error("Cannot open DB file");
}

DiskManager::~DiskManager() {
    if (db_file_.is_open()) db_file_.close();
}

void DiskManager::write_page(page_id_t page_id, const uint8_t* data) {
    size_t offset = static_cast<size_t>(page_id) * PAGE_SIZE;
    db_file_.seekp(offset);
    db_file_.write(reinterpret_cast<const char*>(data), PAGE_SIZE);
    db_file_.flush();
}

void DiskManager::read_page(page_id_t page_id, uint8_t* data) {
    size_t offset = static_cast<size_t>(page_id) * PAGE_SIZE;
    db_file_.seekg(offset);
    if (!db_file_.read(reinterpret_cast<char*>(data), PAGE_SIZE)) {
        memset(data, 0, PAGE_SIZE);
    }
}

page_id_t DiskManager::allocate_page() {
    return next_page_id_++;
}