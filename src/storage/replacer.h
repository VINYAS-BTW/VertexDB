#pragma once

#include <list>
#include <mutex>
#include <unordered_map>

#include "page.h"

namespace mydb {

class LRUReplacer {
public:
    explicit LRUReplacer(std::size_t capacity);

    LRUReplacer(const LRUReplacer&) = delete;
    auto operator=(const LRUReplacer&) -> LRUReplacer& = delete;

    // remove and return the least recently used frame
    auto Victim(frame_id_t* frame_id) -> bool;

    // frame is in use now
    void Pin(frame_id_t frame_id);

    // frame can now be replaced
    void Unpin(frame_id_t frame_id);

    auto Size() const -> std::size_t;

private:
    std::size_t capacity_;

    std::list<frame_id_t> lru_list_;

    std::unordered_map<
        frame_id_t,
        std::list<frame_id_t>::iterator
    > page_table_;

    mutable std::mutex latch_;
};

} // namespace mydb