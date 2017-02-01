获取代码，然后自行编译。

```
git clone https://github.com/kirigayakazushin/DreamScene.git
```

```
cd DreamScene && mkdir build && cd build && qmake ../ && make && sudo cp dreamscene /usr/bin/ && sudo chmod +x /usr/bin/dreamscene
```

然后在创建文件 ~/.local/mkacg/main.qml   
文件内容在代码中，需要自行修改内部的source为自己视频的地址。   
然后运行编译好的二进制。   
目前仅支持DDE桌面环境。
附带了systemd单元文件。

```
systemctl --user enable dreamscene && systemctl --user start dreamscene
```


壁纸素材下载:

```
链接: https://pan.baidu.com/s/1skONEcH 密码: 6rr5
```


<embed height="415" width="544" quality="high" allowfullscreen="true" type="application/x-shockwave-flash" src="https://static.hdslb.com/miniloader.swf" flashvars="aid=7691099&page=1" pluginspage="//www.adobe.com/shockwave/download/download.cgi?P1_Prod_Version=ShockwaveFlash"></embed>