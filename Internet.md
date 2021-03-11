## HTTP和HTTPS的区别

|          | HTTP                                         | HTTPS                                                    |
| -------- | -------------------------------------------- | -------------------------------------------------------- |
| 默认端口 | 80                                           | 443                                                      |
| 安全性   | 传输内容明文；客户端、服务端无法验证对方身份 | 传输内容对称加密，对称加密密钥来自服务器证书的非堆成对称 |
| 运行协议 | TCP                                          | SSL/TLS                                                  |

## 常见端口

| 端口 | 服务          |
| ---- | ------------- |
| 21   | FTP           |
| 22   | SSH           |
| 23   | Telnet        |
| 25   | SMTP          |
| 53   | DNS域名服务器 |
| 80   | HTTP          |
| 443  | HTTPS         |
| 1080 | Sockets       |
| 3306 | MySQL         |

## 常见协议

|            |                                           |
| ---------- | ----------------------------------------- |
| 应用层     | HTTP、HTTPS、SMTP、FTP、Telnet、DNS、DHCP |
| 传输层     | TCP、UDP                                  |
| 网络层     | IP、ICMP、ARP                             |
| 数据链路层 |                                           |
| 物理层     |                                           |



### ARQ，Automatic Repeat-reQuest，停止等待协议

位于层级：数据链路层和

## 三次握手、四次挥手

<img src="C:\Users\CR\OneDrive\LifeTips\Techniques\StudyNotes\img\Internet p1.jpg" style="zoom:50%;" />

握手1：client发送了Syn请求到server。

握手2：服务器确认收到client的请求，然后发送了Syn到client。

握手3：client确认收到server的请求。