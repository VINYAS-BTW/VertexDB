#pragma once

#include <fstream>
#include <mutex>
#include <string>

#include "page.h"

namespace mydb {

class DiskManager {
public:
    explicit DiskManager(const std::string &db_file);
    ~DiskManager();

    DiskManager(const DiskManager &) = delete;
    auto operator=(const DiskManager &) -> DiskManager & = delete;

    // write one page to disk
    void WritePage(page_id_t page_id, const char *page_data);

    // read one page from disk
    void ReadPage(page_id_t page_id, char *page_data);

    // allocate a new page id
    auto AllocatePage() -> page_id_t;

    // total pages allocated so far
    auto GetPageCount() const -> page_id_t;

private:
    // calculate file offset for a page
    auto GetOffset(page_id_t page_id) const -> std::streamoff;

    std::fstream db_io_;
    std::string db_file_name_;

    page_id_t next_page_id_{0};

    // file access isn't thread safe
    mutable std::mutex io_latch_;
};

} // namespace mydb