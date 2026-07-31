#include "page.h"

#include <algorithm>

namespace mydb {

Page::Page() {
    Reset();
}

auto Page::GetData() -> char* {
    return data_.data();
}

auto Page::GetData() const -> const char* {
    return data_.data();
}

auto Page::GetPageId() const -> page_id_t {
    return page_id_;
}

auto Page::GetPinCount() const -> int {
    return pin_count_;
}

auto Page::IsDirty() const -> bool {
    return is_dirty_;
}

auto Page::GetLSN() const -> lsn_t {
    return lsn_;
}

void Page::SetPageId(page_id_t page_id) {
    page_id_ = page_id;
}

void Page::SetDirty(bool dirty) {
    is_dirty_ = dirty;
}

void Page::SetLSN(lsn_t lsn) {
    lsn_ = lsn;
}

void Page::Pin() {
    ++pin_count_;
}

void Page::Unpin() {
    if (pin_count_ > 0) {
        --pin_count_;
    }
}

void Page::Reset() {

    // clear everything before reusing the frame
    std::fill(data_.begin(), data_.end(), 0);

    page_id_ = INVALID_PAGE_ID;
    pin_count_ = 0;
    is_dirty_ = false;
    lsn_ = 0;
}

} // namespace mydb