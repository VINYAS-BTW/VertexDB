#pragma once
#include <cstdint>
#include <cstring>

static constexpr int PAGE_SIZE = 4096;

using page_id_t = int32_t;
using lsn_t = int64_t;

static constexpr page_id_t INVALID_PAGE_ID = -1;

class Page {
public:
    Page() { reset(); }

    inline uint8_t* data() { return data_; }
    inline page_id_t page_id() const { return page_id_; }
    inline bool is_dirty() const { return is_dirty_; }
    inline int pin_count() const { return pin_count_; }
    inline lsn_t lsn() const { return lsn_; }

    void set_page_id(page_id_t id) { page_id_ = id; }
    void set_dirty(bool dirty) { is_dirty_ = dirty; }
    void set_lsn(lsn_t lsn) { lsn_ = lsn; }

    void pin() { pin_count_++; }
    void unpin() { if (pin_count_ > 0) pin_count_--; }

    void reset() {
        memset(data_, 0, PAGE_SIZE);
        page_id_ = INVALID_PAGE_ID;
        is_dirty_ = false;
        pin_count_ = 0;
        lsn_ = 0;
    }

private:
    uint8_t data_[PAGE_SIZE];
    page_id_t page_id_{INVALID_PAGE_ID};
    bool is_dirty_{false};
    int pin_count_{0};
    lsn_t lsn_{0};
};