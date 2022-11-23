# common_lib
将c++的一些常用功能进行封装，并以库的方式提供
* zh-google-styleguide-20220529.pdf为google c++编程开发指南, 描述了c++的一些开发规范
* HexConverter
可以将十六进制字符串与各种数据类型（int, double....）进行相互转换，支持跨平台，可在小端机器上使用,
[详情](./HexConverter/README.md)
* TimerQueue
定时器队列, 支持跨平台, [详情](./TimerQueue/README.md)
* TimeStamp
时间戳功能相关函数, 支持跨平台, [详情](./TimeStamp/README.md)
* ftplibpp
ftp客户端库, 支持跨平台, [详情](./ftplibpp/README.md); **注意：在确定要对ftp服务器进行操作时，才与ftp服务器建立
连接，如果连接后，长时间（大概120s左右）不与ftp服务器通信，ftp服务器将主动发送RST关闭连接，进而会引发段错误**