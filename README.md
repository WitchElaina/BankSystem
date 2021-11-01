# BankSystem
C++大作业，基于QT开发的银行系统

已经支持的功能：
- 用户登录
- 用户注册
- 账户数据库读写
- 账户数据存储
- 账户数据打印
- 存取款
- 查询指定日期流水
- 账户登出
- 注销账户
- Mac安装程序

## 使用方法

### Mac OS安装

双击`bank_system_mac_v1.0.dmg`，根据提示拖动完成安装.

![install](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/install.ef49d454hxs.png)

### Windows安装

解压`bank_system_win_v1.0.zip`，双击`BankSystem.exe`运行.

### 选择文件夹

进入程序后会提示选择用以存放用户数据的文件夹, 在弹出的窗口中选择即可

![select_dir](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/select_dir.2a6kazvtegpw.jpg)

### 登录

选择好文件夹后会进入登录界面, 首次使用需要点击`Register`按钮注册账户, 完成后即可登录进入主界面

![login](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/login.x9fq67puxdc.png)

### 主界面

![mainwindow](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/mainwindow.1cj5t6522c1s.png)

进入后程序会自动恢复用户数据, 新用户需要点击`创建信用卡`和`创建储蓄卡`按钮创建自己的两类账户, 创建完成后相应区块按钮将开放操作权限, 用户可以使用账户进行存取款

![sav](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/sav.iu4ygowjm5c.png)

![cre](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/cre.1ia18ew82fcw.png)

### 切换日期

点击主界面左侧的`日期设置`, 展开日期选择菜单即可切换日期, 系统会自动处理利息与年费

![change_date](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/change_date.4dwxm9uhvme0.png)

### 查询流水

在主界面右侧选择**查询账户**和**流水排序**, 点击`查询流水`, 即可查看指定日期的账户流水

![query](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/query.6dyvaz3ypj40.png)

![querydemo](https://cdn.jsdelivr.net/gh/LinYuanChan/image-hosting@master/BankSystem/querydemo.4yov6w3wwe80.png)


