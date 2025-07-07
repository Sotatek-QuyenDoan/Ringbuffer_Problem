//
// Created by Nitro Tiger on 7/7/2025.
//

#include <gtest/gtest.h>
extern "C" {
    #include "../source/ringbuffer.h"  // Đảm bảo đúng path và dùng extern "C"
}
#define MAX_RB_SIZE 1024
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
/*
TEST(RingBufferTest, AddAndRemove) {
    ringbuffer_init(3);  // dùng size nhỏ để dễ đầy

    // Add 3 phần tử → buffer full
    EXPECT_EQ(ringbuffer_add(10), 0);
    EXPECT_EQ(ringbuffer_add(20), 0);
    EXPECT_EQ(ringbuffer_add(30), 0);

    // Thêm phần tử khi đầy → nên thất bại
    EXPECT_EQ(ringbuffer_add(40), -1);

    // Remove tất cả
    int val = 0;
    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 10);
    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 20);
    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 30);

    // Remove khi đã rỗng → nên thất bại
    EXPECT_EQ(ringbuffer_remove(&val), -1);

    EXPECT_TRUE(ringbuffer_is_empty());

    // Thử lại add/remove để test wrap-around logic
    EXPECT_EQ(ringbuffer_add(50), 0);
    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 50);
}
*/

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

TEST(RingBufferTest, SizeChecks) {
    ringbuffer_init(4);
    EXPECT_EQ(ringbuffer_size(), 0);

    ringbuffer_add(1);
    ringbuffer_add(2);
    EXPECT_EQ(ringbuffer_size(), 2);

    int val;
    ringbuffer_remove(&val);
    EXPECT_EQ(ringbuffer_size(), 1);

    ringbuffer_remove(&val);
    EXPECT_EQ(ringbuffer_size(), 0);
}

TEST(RingBufferTest, InitOversize) {
    ringbuffer_init(MAX_RB_SIZE + 100);
    EXPECT_EQ(ringbuffer_size(), 0);  // buffer mới init nên rỗng

    EXPECT_EQ(ringbuffer_add(42), 0);
    int val;
    EXPECT_EQ(ringbuffer_remove(&val), 0);
    EXPECT_EQ(val, 42);
}

int main(int argc, char **argv) {
    std::cout << "==> Google Test starting...\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}