#include "lru_replacer.h"

namespace mydb {

LRUReplacer::LRUReplacer(std::size_t capacity)
    : capacity_(capacity) {}

auto LRUReplacer::Victim(frame_id_t* frame_id)
    -> bool {

    std::lock_guard<std::mutex> guard(latch_);

    if (lru_list_.empty()) {
        return false;
    }

    *frame_id = lru_list_.back();

    page_table_.erase(*frame_id);
    lru_list_.pop_back();

    return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {

    std::lock_guard<std::mutex> guard(latch_);

    auto it = page_table_.find(frame_id);

    if (it == page_table_.end()) {
        return;
    }

    lru_list_.erase(it->second);
    page_table_.erase(it);
}

void LRUReplacer::Unpin(frame_id_t frame_id) {

    std::lock_guard<std::mutex> guard(latch_);

    // already inside the replacer
    if (page_table_.count(frame_id)) {
        return;
    }

    // don't exceed capacity
    if (lru_list_.size() >= capacity_) {
        return;
    }

    lru_list_.push_front(frame_id);

    page_table_[frame_id] = lru_list_.begin();
}

auto LRUReplacer::Size() const
    -> std::size_t {

    std::lock_guard<std::mutex> guard(latch_);

    return lru_list_.size();
}

} // namespace mydb