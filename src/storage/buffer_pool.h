#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "disk_manager.h"
#include "lru_replacer.h"
#include "page.h"

namespace mydb {

class BufferPoolManager {
public:
    BufferPoolManager(
        std::size_t pool_size,
        DiskManager *disk_manager);

    BufferPoolManager(const BufferPoolManager &) = delete;
    auto operator=(const BufferPoolManager &) -> BufferPoolManager & = delete;

    // fetch an existing page
    auto FetchPage(page_id_t page_id) -> Page *;

    // create a brand new page
    auto NewPage(page_id_t *page_id) -> Page *;

    // release a page after use
    auto UnpinPage(page_id_t page_id, bool is_dirty) -> bool;

    // write one page back
    auto FlushPage(page_id_t page_id) -> bool;

    // write every dirty page
    void FlushAllPages();

private:
    auto FindFreeFrame(frame_id_t *frame) -> bool;

    std::size_t pool_size_;

    DiskManager *disk_manager_;

    std::vector<Page> pages_;

    std::unordered_map<
        page_id_t,
        frame_id_t
    > page_table_;

    std::vector<frame_id_t> free_list_;

    LRUReplacer replacer_;
};

}