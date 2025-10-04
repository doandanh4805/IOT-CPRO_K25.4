# 🌱 Hệ thống tưới cây tự động thông minh (Smart Plant Watering System - SPWS)

Thiết kế và lập trình một hệ thống nhúng quản lý việc tưới nước cho cây trồng. Hệ thống phải có khả năng đọc dữ liệu cảm biến, đưa ra quyết định tưới nước dựa trên các tham số cấu hình, và thông báo trạng thái hoạt động. Đề bài tập trung vào việc hiểu và hiện thực hóa một hệ thống tự động hóa thực tế với các yêu cầu về quản lý trạng thái, dữ liệu và tương tác người dùng.

## ⚙️ Giả định phần cứng và tài nguyên:
- Vi điều khiển: Một vi điều khiển phổ biến với các tài nguyên cơ bản (GPIO, Timer, ADC, một lượng RAM/Flash đủ dùng cho ứng dụng nhỏ).
- Cảm biến:
  - Cảm biến độ ẩm đất: Đo phần trăm độ ẩm của đất (ví dụ: 0 - 100%).
  - Cảm biến nhiệt độ môi trường: Đo nhiệt độ không khí xung quanh.
- Thiết bị:
  - Bơm nước mini: Được điều khiển để BẬT/TẮT việc tưới nước.
  - LED trạng thái: Một LED RGB hoặc ba LED đơn sắc để hiển thị trạng thái hoạt động (ví dụ: Xanh - bình thường, Vàng - đang tưới, Đỏ - lỗi/cảnh báo).
  - Nút nhấn: Hai nút nhấn vật lý:
    - Nút 1: BẬT/TẮT chế độ tự động.
    - Nút 2: Kích hoạt tưới nước thủ công (khi hệ thống ở chế độ chờ)/
- Giao tiếp (mô phỏng): Hàm gửi thông báo trạng thái hoặc dữ liệu quan trọng đến một giao diện người dùng (ví dụ: in ra console, hoặc gửi qua UART/mô-đun không dây).

## 🖥️ Yêu cầu phần mềm:
### Định nghĩa các trạng thái hoạt động:
- Chế độ hệ thống:
  - MODE_AUTO: Hệ thống tự động quản lý việc tưới nước dựa trên cảm biến.
  - MODE_MANUAL: Hệ thống chờ lệnh thủ công hoặc bị khóa tự động.
- Trạng thái tưới nước của bơm:
  - PUMP_OFF: Bơm không hoạt động.
  - PUMP_ON: Bơm đang hoạt động.
- Trạng thái LED:
  - LED_NORMAL: Hệ thống hoạt động bình thường, không tưới.
  - LED_WATERING: Hệ thống đang tưới nước.
  - LED_LOW_MOISTURE_ALERT: Độ ẩm đất quá thấp (chưa tưới hoặc tưới không đủ).
  - LED_ERROR: Lỗi hệ thống (ví dụ: cảm biến hỏng, bơm kẹt).

### Cấu trúc dữ liệu chính:
- Dữ liệu cảm biến: Cần có một cấu trúc để lưu trữ giá trị đọc được từ cảm biến độ ẩm đất và nhiệt độ môi trường.
- Cài đặt hệ thống: Cần một cấu trúc để lưu trữ các tham số cấu hình như:
  - Ngưỡng độ ẩm tối thiểu để bắt đầu tưới.
  - Ngưỡng độ ẩm tối đa để dừng tưới.
  - Thời gian tưới tối đa cho mỗi lần.
  - Chu kỳ kiểm tra cảm biến (ví dụ: mỗi 5 phút).
  - Trạng thái chế độ hiện tại (Tự động/Thủ công).

### Yêu cầu chức năng:
- Khởi tạo hệ thống:
  - Thiết lập các chân GPIO cho cảm biến, bơm, LED, nút nhấn.
  - Đặt các giá trị mặc định ban đầu cho các cài đặt hệ thống (ngưỡng độ ẩm, thời gian tưới, v.v.).
  - Đưa hệ thống vào chế độ MODE_AUTO mặc định ban đầu.
- Đọc và xử lý dữ liệu cảm biến:
  - Định kỳ đọc giá trị từ cảm biến độ ẩm đất và nhiệt độ.
  - Lưu trữ các giá trị này vào cấu trúc dữ liệu cảm biến.
  - Có thể thực hiện làm mịn dữ liệu (averaging) nếu cần.
- Logic điều khiển tưới nước tự động:
  - Nếu hệ thống đang ở MODE_AUTO:
    - So sánh độ ẩm đất hiện tại với ngưỡng tưới tối thiểu.
    - Nếu độ ẩm quá thấp và đã hết thời gian chờ giữa các lần tưới, kích hoạt bơm.
    - Khi bơm hoạt động, tiếp tục theo dõi độ ẩm và dừng bơm khi đạt ngưỡng tối đa hoặc hết thời gian tưới tối đa.
  - Cần có một bộ đếm thời gian (timer) để quản lý chu kỳ kiểm tra cảm biến và thời gian tưới nước.
- Điều khiển bơm:
  - Bật/Tắt bơm nước dựa trên quyết định của logic điều khiển.
  - Cần có hàm điều khiển trạng thái bơm (turn_pump_on(), turn_pump_off()).
- Điều khiển LED trạng thái:
  - Luôn cập nhật màu LED dựa trên trạng thái hoạt động của hệ thống (bình thường, đang tưới, độ ẩm thấp, lỗi).
- Xử lý nút nhấn:
  - Nút BẬT/TẮT chế độ tự động: Khi nhấn, chuyển đổi giữa MODE_AUTO và MODE_MANUAL. Khi chuyển sang MODE_MANUAL, đảm bảo bơm nước đang TẮT.
  - Nút tưới thủ công: Chỉ có tác dụng khi hệ thống ở MODE_MANUAL. Khi nhấn, kích hoạt bơm nước trong một khoảng thời gian cố định (ví dụ: 10 giây), sau đó tự động tắt.
- Thông báo trạng thái:
  - Định kỳ hoặc khi có thay đổi trạng thái quan trọng, gửi thông báo về tình hình hệ thống (ví dụ: "Độ ẩm đất: 35%", "Đang tưới nước...", "Chế độ: Thủ công").
  - Tối ưu bộ nhớ: Tránh sử dụng quá nhiều chuỗi ký tự cố định (const char*) nếu không gian Flash hạn chế. Có thể sử dụng các mã số hoặc enum để biểu thị thông báo.

### Luồng hoạt động chính:
- Sau khi khởi tạo, hệ thống sẽ chạy trong một vòng lặp vô hạn.
- Trong mỗi vòng lặp, hệ thống sẽ:
  - Kiểm tra và xử lý các sự kiện nút nhấn.
  - Nếu ở chế độ tự động, kiểm tra và xử lý logic tưới nước.
  - Cập nhật trạng thái LED.
  - Có thể gửi báo cáo trạng thái định kỳ.
  - Có một độ trễ nhỏ để tiết kiệm năng lượng và phù hợp với chu kỳ hoạt động.

## 🚀 Yêu cầu triển khai:
- Triển khai toàn bộ chức năng của hệ thống SPWS bằng ngôn ngữ C.
- Tổ chức mã nguồn một cách rõ ràng, dễ đọc, với các file header và source file riêng biệt cho các module (ví dụ: main.c, sensors.c, watering_logic.c, actuators.c, buttons.c, config.h).
- Sử dụng enum và struct phù hợp để quản lý trạng thái và dữ liệu.
- Quản lý các biến static và extern một cách hợp lý để điều khiển phạm vi và chia sẻ dữ liệu giữa các module.
- Mô phỏng hoạt động của cảm biến, bơm nước, LED và nút nhấn bằng cách in ra console các thông báo và thay đổi trạng thái tương ứng.
- Đảm bảo hệ thống có thể chuyển đổi mượt mà giữa các chế độ và xử lý các tình huống như độ ẩm quá thấp, quá cao, hoặc người dùng can thiệp.
