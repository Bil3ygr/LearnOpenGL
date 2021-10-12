# LearnOpenGL

## 环境配置

**CMake**、**Visual Studio 2019**

## Graphics Library Framework(GLFW)

到[官方网站](https://www.glfw.org/download)下载源码，解压后在本地自行编译生成`glfw3.lib`，
或直接下载编译好的静态库。将`GLFW`目录拷贝至`include`目录下，将`glfw3.lib`拷贝至`lib`目录下

## Boost

到[官方网站](https://www.boost.org/users/download/)下载源码，将`boost`目录拷贝至`include`目录下，
根据实际使用情况，对比[官方文档](https://www.boost.org/doc/libs/1_77_0/more/getting_started/windows.html#header-only-libraries)，如有用到文档描述的库，则需要生成静态库（或直接一步到位直接下载
`Prebuilt windows binaries`，里面包含所有目录外加静态库），并将所有静态库拷贝至`lib`目录下

## 生成VS工程

可通过**CMake**的图形界面，也可以通过**MakeSolution.bat**快捷生成

- 图形界面：需要自行选择生成目录、VS版本等内容，再生成工程
- 控制台：右键编辑**MakeSolution.bat**，根据需要修改生成目录和VS版本，完成后保存运行
