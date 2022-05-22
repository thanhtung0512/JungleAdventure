# JungleAdventure_Game 
## Advanced Programming 's Project _ VNU University of Engineering and Technology 
### Nguyễn Vũ Thanh Tùng  _ K66-CQ-C-C 
####    1. Cách cài đặt : 
- Tải ***[Codeblock](https://www.codeblocks.org/downloads/)*** và folder source code, giải nén từ ***[Github](https://github.com/thanhtung0512/JungleAdventure_Game)*** . 
- Copy đường dẫn folder ./bin trong installation folder của Codeblock, add vào ***environment path***.
- Chạy file ***Main.exe*** để chơi game.

<p align="center">
<img src="https://i.imgur.com/7lngNhs.jpg">
</p>

<p align="center">
<img src="https://i.imgur.com/UTfw6iS.jpg">
</p>


<p align="center">
<img src="https://i.imgur.com/hIChH7T.png">
</p>




 

#### 2. Mô tả chung về trò chơi 
- Tựa game side-scrolling 2D đơn giản lấy bối cảnh trong 1 khu rừng, bạn sẽ hoá thân thành một anh hùng đang bị 1 con phượng hoàng lửa truy đuổi phía sau và liên tục phun lửa vào bạn, và trước mặt bạn là vô vàn những con quái vật sẵn sàng lấy mạng của bạn, nhiệm vụ của bạn là hãy né những quả cầu lửa, tiêu diệt những con quái trên đường và sống sót càng lâu càng tốt . Với mỗi lần bạn tiêu diệt được 10 con quái vật thì bạn sẽ có khả năng tàng hình trong 30 giây. 

#### 3. Các chức năng đã cài đặt 
- Menu 
    - Nút Play để chơi game. 
    - Nút Information để hiện thông tin của người phát triển.
    - Nút Exit để thoát game.
- In-Game
    - Parallax background giúp người chơi cảm nhận được chiều sâu của nền . 
    - Nhân vật chính có các animation chạy, nhảy, 2 chiêu chém kiếm, cùng với các con quái vật, quả cầu lửa, phượng hoàng .... 
    - Sau mỗi lần giết 10 quái liên tiếp, nhân vật sẽ có chiêu thức tàng hình và không nhận damage từ bất kì thứ gì khác, và người chơi vẫn có thể điều khiển nhân vật để giết quái.
    - Khi đạt 100 điểm thì con quái Boss sẽ xuất hiện và thả những quả cầu lửa xanh từ trên trời xuống. 
    - Âm thanh tiếng kiếm, tiếng chạy, âm thanh của quái ...
    - Kiểm soát va chạm giữa nhân vật với quả cầu lửa, với quái ... 
    - Hiển thị điểm và số lượng quái bạn đã giết, khi vào chế độ tàng hình thì sẽ có dòng chữ thông báo bạn đang tàng hình và có đồng hồ đếm ngược để trở lại trạng thái visible ( không tàng hình ).
    
- Màn hình kết thúc 
    - Nút Return để chơi lại.
    - Nút Exit để thoát. 
    - Hiển thị điểm số của người chơi. 
    
    
#### 4. Các kỹ thuật lập trình sử dụng trong trò chơi 
- Sử dụng thư viện hỗ trợ SDL 2.0 để vẽ đồ hoạ . 
- Kiến thức cơ  bản về OOP ( Lập trình hướng đối tượng ) chia trò chơi thành các đối tượng có những thuộc tính và phương thức.
- Sử dụng mảng để lưu các con quái vật
- Đối với 2 chiêu thức chém kiếm của nhân vật chính, phải xét những frame của hành động chém kiếm và tính toán sao cho chém trúng thì quái phải chết . 
- Parallax background thì phải cài đặt vận tốc chạy đối với từng layer... 
- Sử dụng con trỏ làm tham số cho hàm để tránh việc copy giá trị vào hàm -> tránh sử dụng thêm bộ nhớ, giúp game đỡ giật lag.

#### 5.Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình 
- Kết luận: Game vẫn còn hơi đơn giản và thiếu những chức năng như điều chỉnh âm lượng của âm thanh, thiếu những vật phẩm để hỗ trợ nhân vật ,... và khi chạy game vẫn chiếm khá nhiều bộ nhớ, code vẫn còn xấu, chưa thể clean được một cách tối ưu do từ ban đầu không thiết kế khung xương trước . 

- Hướng phát triển : Có thể thêm nhiều chức năng mới, ví dụ như phát nhạc trong quá trình chơi, chọn bài hát , chọn nhân vật để chơi và thêm nhiều những item hoặc level để tăng độ khó cho game . Tuy nhiên trước hết phải tối ưu hoá game tốt nhất có thể . 

- Các điều tâm đắc rút ra được sau khi hoàn thiện chương trình :
    - Chỉ tham khảo trên mạng code phần load đồ hoạ ( cách sử dụng SDL2.0) còn lại về logic game đều tự tay code toàn bộ -> Nâng cao kỹ năng lập trình .
    - Biết sử dụng Photoshop để chỉnh sửa đồ hoạ theo ý mình .
    - Có được sản phẩm để có thể chơi cùng bạn bè . 