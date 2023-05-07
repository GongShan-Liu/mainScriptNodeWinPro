1.下载cmake版本3.17，并使用visual studio code部署cmake


2.下载python的3.7本版
    https://www.python.org/downloads/

出现无法找到python37_d.lib的错误
    去到python的include路径下找到pyconfig.h文件，把
    
        #                               pragma comment(lib,"python37_d.lib")

    修改为
        #                               pragma comment(lib,"python37.lib")

    保存即可




3.下载qt的5.12.6的win 版本
    http://download.qt.io/archive/qt/5.12/5.12.6/

注意：python和qt的5.12.6最好都是32位版本

4.在系统环境变量path中添加python安装路径和脚本路径、添加qt的bin路径、添加cmake的路径
例如：

    cmake：D:\Program Files\CMake\bin
    python：C:\Program Files (x86)\Python37-32
            C:\Program Files (x86)\Python37-32\Scripts
    qt：D:\Qt\Qt5.12.6\5.12.6\msvc2017\bin
    pyside2的DLL路径：{project_path}\mainScriptNodeWinPro\pythonLib

    新增环境变量：QT_QPA_PLATFORM_PLUGIN_PATH=D:\Qt\Qt5.12.6\5.12.6\msvc2017\plugins\platforms

5.修改CMakeLists.txt文件的qt5路径和python库路径和头文件路径，修改为qt和python的安装路径

    set(QT5_COMPILERS_DIR "C:/Qt/Qt5.12.6/5.12.6/msvc2017")


    set(PYTHON_DIR "C:/Program Files (x86)/Python37-32")


6.使用cmake的Release运行项目，这样脚本编辑器中使用pyside2的代码才能读取到qt的DLL

7.测试PySide2代码
import sys

# 添加pyside2的路径，路径需要根据实际修改
sys.path.append(r"{project_path}\mainScriptNodeWinPro\pythonLib\site-packages")

from PySide2 import QtWidgets

print(QtWidgets.QApplication.activeWindow())
