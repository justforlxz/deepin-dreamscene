第一版本请访问[release](https://github.com/kirigayakazushin/DreamScene/releases)

后续版本还在开发中，新版本将支持设置面板和配置文件，以及参数启动。

获取代码，然后自行编译。

```
git clone https://github.com/kirigayakazushin/DreamScene.git
```

依赖包：

```
libqt5x11extras5-dev libxcb-ewmh-dev qtdeclarative5-dev
```

```
cd DreamScene && mkdir build && cd build && qmake ../ && make && sudo cp dreamscene /usr/bin/ && sudo chmod +x /usr/bin/dreamscene
```

然后在创建文件 ~/.local/mkacg/main.qml   
文件内容在代码中，需要自行修改内部的source为自己视频的地址。   
然后运行编译好的二进制。   
目前仅支持DDE桌面环境。
附带了desktop文件，复制到自动启动目录。

```
cp dreamscene.desktop ~/.config/autostart/
```


壁纸素材下载:

```
链接: https://pan.baidu.com/s/1skONEcH 密码: 6rr5
```

demo video :

[bilibili演示视频](http://www.bilibili.com/video/av7892530/)
