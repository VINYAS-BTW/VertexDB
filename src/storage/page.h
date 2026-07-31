#pragma once

#include <array>
#include <cstdint>

namespace mydb {

constexpr std::size_t PAGE_SIZE = 4096;

using page_id_t = int32_t;
using frame_id_t = int32_t;
using lsn_t = int64_t;

constexpr page_id_t INVALID_PAGE_ID = -1;

class Page {
public:
    Page();

    // access raw page memory
    auto GetData() -> char*;
    auto GetData() const -> const char*;

    auto GetPageId() const -> page_id_t;
    auto GetPinCount() const -> int;
    auto IsDirty() const -> bool;
    auto GetLSN() const -> lsn_t;

    void SetPageId(page_id_t page_id);
    void SetDirty(bool dirty);
    void SetLSN(lsn_t lsn);

    void Pin();
    void Unpin();

    void Reset();

private:
    std::array<char, PAGE_SIZE> data_;

    page_id_t page_id_;
    int pin_count_;
    bool is_dirty_;
    lsn_t lsn_;
};

} // namespace mydb