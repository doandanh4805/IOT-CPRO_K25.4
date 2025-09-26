#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

/* Khởi tạo module nút (mô phỏng stdin non-blocking) */
void buttons_init(void);

/* Kiểm tra và xử lý input từ người dùng
   Trả về 1 nếu yêu cầu thoát chương trình */
int buttons_poll_and_process(void);

/* Hàm callback mà main/logic có thể override bằng cách extern (cách đơn giản) */
extern void user_pressed_toggle_mode(void);
extern void user_pressed_manual_water(void);

#endif /* BUTTONS_H */
