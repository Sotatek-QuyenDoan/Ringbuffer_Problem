#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

    // Khởi tạo buffer với kích thước cố định
    void ringbuffer_init(int size);

    // Thêm 1 giá trị, trả về 0 nếu thành công, -1 nếu đầy
    int ringbuffer_add(int value);

    // Lấy 1 giá trị, trả về 0 nếu thành công (hoặc -1 nếu rỗng)
    int ringbuffer_remove(int *value);

    // Kiểm tra đầy/rỗng/đếm phần tử
    int ringbuffer_is_full(void);
    int ringbuffer_is_empty(void);
    int ringbuffer_size(void);

#ifdef __cplusplus
}
#endif
#endif // RINGBUFFER_H
