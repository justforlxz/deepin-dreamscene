[ppa地址](https://blog.mkacg.com/)

sudo apt install mkacg-dreamscene

安装完成以后需要注销一下。

调用方法 


```
dbus-send --session --print-reply --dest=com.deepin.dde.Wallpaper /com/deepin/dde/Wallpaper com.deepin.dde.Wallpaper.setVideoFile array:string:""

```

最后的引号中是文件的绝对路径。

dbus-send --session --print-reply --dest=com.deepin.dde.Wallpaper /com/deepin/dde/Wallpaper com.deepin.dde.Wallpaper.setVideoFile array:string:"/home/kirigaya/Videos/t5.mp4" 
