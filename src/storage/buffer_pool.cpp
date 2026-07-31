#include "buffer_pool.h"

namespace mydb {

BufferPoolManager::BufferPoolManager(
    std::size_t pool_size,
    DiskManager *disk_manager)
    : pool_size_(pool_size),
      disk_manager_(disk_manager),
      pages_(pool_size),
      replacer_(pool_size) {

    for (frame_id_t i = 0; i < static_cast<frame_id_t>(pool_size); ++i) {
        free_list_.push_back(i);
    }
}

auto BufferPoolManager::FindFreeFrame(frame_id_t *frame)
    -> bool {

    if (!free_list_.empty()) {

        *frame = free_list_.back();
        free_list_.pop_back();

        return true;
    }

    return replacer_.Victim(frame);
}