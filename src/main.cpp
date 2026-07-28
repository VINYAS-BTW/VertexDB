#include <iostream>
#include "storage/disk_manager.h"
#include "storage/page.h"

int main() {
    std::cout << "mydb starting..." << std::endl;
    DiskManager dm("test.db");
    Page p;
    p.set_page_id(dm.allocate_page());
    const char* msg = "hello mydb";
    memcpy(p.data(), msg, strlen(msg));
    dm.write_page(p.page_id(), p.data());
    std::cout << "Page 0 written to disk." << std::endl;
    return 0;
}