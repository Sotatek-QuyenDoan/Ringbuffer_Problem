//
// Created by Nitro Tiger on 7/7/2025.
//
/*
#include <gtest/gtest.h>

extern "C" {
#include "ringbuffer.h"
}

TEST (RingBufferTest, BasicAddRemove) {
    ringbuffer_init(3);
    EXPECT_EQ(ringbuffer_add(100), 0);
    int value = 0;
    EXPECT_EQ(ringbuffer_remove(&value), 0);
    EXPECT_EQ(value, 100);
}
*/
#include <gtest/gtest.h>
extern "C" {
    #include "../source/ringbuffer.h"  // Đảm bảo đúng path và dùng extern "C"
}

// Test case khởi tạo và kiểm tra trạng thái rỗng
TEST(RingBufferTest, InitAndEmpty) {
    ringbuffer_init(5);
    EXPECT_TRUE(ringbuffer_is_empty());
    EXPECT_FALSE(ringbuffer_is_full());
}

// Test thêm và loại bỏ phần tử
TEST(RingBufferTest, AddAndRemove) {
    ringbuffer_init(5);

    EXPECT_EQ(ringbuffer_add(10), 0);
    EXPECT_EQ(ringbuffer_add(20), 0);

    int val = 0;
    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 10);

    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 20);

    EXPECT_TRUE(ringbuffer_is_empty());
}

// Test buffer đầy
TEST(RingBufferTest, FullBuffer) {
    ringbuffer_init(3);
    EXPECT_EQ(ringbuffer_add(1), 0);
    EXPECT_EQ(ringbuffer_add(2), 0);
    EXPECT_EQ(ringbuffer_add(3), 0);
    EXPECT_EQ(ringbuffer_add(4), -1);  // buffer full
    EXPECT_TRUE(ringbuffer_is_full());
}

// Test lấy ra từ buffer rỗng
TEST(RingBufferTest, RemoveEmpty) {
    ringbuffer_init(3);
    int val = 0;
    EXPECT_EQ(ringbuffer_remove(&val), -1);  // buffer empty
}
int main(int argc, char **argv) {
    std::cout << "==> Google Test starting...\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}