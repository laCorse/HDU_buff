    Update:
    2020/5/9 Version: 0.0.1 加入OPENCV模块和Buff类，代码主要基于深圳大学开源代码


# HDU_RM大符文档



## 更新建议：
ver 0.0.1
1. 将代码中的较长的函数拆分成更小的函数，便于进行替换。
2. 添加一些更具备通用性质的轮子，独立于Detect类内函数，便于拓展到整个项目中。
3. 优化算法，特别是替换yolov2和lenet，初步可以考虑用更快的SVM进行替代。
4. 尝试将跟踪算法添加到使用中来，相比来说不需要实时运行，能提高效率，但需要一整套的解决方案。跟踪算法可以直接使用OPENCV自带算法(boosting、KCF等)。
5. 文档的编写方式需要规范：目的是将函数作为框架式的黑箱使用。




## 一些OPENCV的tips：

### cv::Size类

    可以使用Size(width,height) ，注意其宽度和高度的顺序是和Mat相反的( Mat(height,width) )。

### cv::Rect类
    有一个Point类的成员（x, y），用来表示矩阵左上角。
    有一个Size类成员(width, height),用来表示矩阵的大小。
    构造方式多样：
        1.cv::Rect r; 
        2.cv::Rect r2(r); 复制构造
        3.cv::Rect(x, y, w, h) 值构造
        4.cv::Rect(p, sz) 两个成员构造
        5.cv::Rect(p1, p2) 两个对角点构造
    常用功能：计算面积、提取左上右下的点、判断点是否在矩阵内、集合操作。

### cv::RotateRect类
    有一个Point类成员(x,y),用来表示旋转矩阵中心点。
    有一个Size2f类成员(width,height)，用来表示矩阵的大小。x轴顺时针旋转所碰到的第一个边为height。
    构造方式可以参考Rect类，有复制构造、两个对角点构造、值构造cv::RotatedRect(p,sz,theta)需要一个点、一个大小和一个角度。
    角度的确定： width与x轴的夹角，（-90,0]
   ![](https://codimd.s3.shivering-isles.com/demo/uploads/upload_334630f6a804bfabadcc8c0bfe4a2238.png)

## Buff类

``` 类说明
enum detectMode : 二值化时的红蓝通道相减顺序

class Detect //主要的类，用来检测能量机关的相关参数和函数的封装
{    enum binaryMode //定义使用的颜色空间
     enum predictMode //预测模式
     struct armorData //装甲板数据，参数有：中心、圆心、角度、象限、是否识别
     struct switchParam  //切换调试模式
     struct DectParam //检测时的参数 调试时在这调整 
}
```


### Detect类具体说明

#### Detect::Detect()
    作用：构造函数，目前只是用来加载lenet/yolo
#### void Detect::clear()
    作用：清理已经识别的装甲板信息

#### bool Detect::makeRectSafe(const Rect rect, const Size size) 
    作用：当画布（即某张图）中的某个ROI的坐标出了画布，或者其宽度和高度小于0时，返回false
    参数：const Rect rect：待测量ROI
         const Size size：画布大小
    返回：是否在画布内

#### bool Detect::circleLeastFit(const vector<Point2f> &points, Point2f &R_center)
    作用：根据点集使用最小二乘法拟合圆
    参数：const vector<Point2f> &points：已有的点集
         Point2f &R_center：需要拟合出来的圆心
    返回：是否拟合成功


#### bool Detect::change_angle(const int quadrant, const float angle, float &tran_angle)
    作用：使用的是amorData类的象限和角度，其中角度为[0,90)，把角度按照象限的不同映射到[0,360)
    参数：const int quadrant：装甲板所在象限(以能量机关中心为原点)
         const float angle：装甲板的角度，[0,90)
         float &tran_angle：所要求的的[0,360)的角度
    返回：是否修改成功

#### bool Detect::forward(const Mat src, Mat &dect_src, Point2f &offset)
    作用：使用yolo目标检测得目标区域,需要输入3通道的图片
    参数：const Mat src：待检测图片
         Mat &dect_src：从src检测得到的ROI区域
         Point2f &offset：偏移量（一般从setImage函数中获得）
    返回:是否检测成功
#### bool Detect::setImage(const Mat src, Mat &dect_src, Point2f &offset)
    作用：在摄像头上直接获取的图片src中取出固定大小、中心为能量机关的图片，便于处理但需要把offset信息也输出
    参数：const Mat src：原始图像
         Mat &dect_src：待获得的中心为能量机关的图像，也是src的ROI
         Point2f &offset：dect_src在src的左上角点
    返回：是否取出所需ROI

#### bool Detect::setBinary(const Mat src, Mat &binary, int bMode)
    作用：根据不同的bMode进行不同的二值化，目的是二值化图上只有灯条是白色区域
    参数：const Mat src：待二值化图像
         Mat &binary：二值化后的图像
         int bMode：二值化模式，可选值为BGR、HSV、BGR_useG、OTSU、GRAY、YCrCb、LUV，可用整数1~7代替
    返回：是否二值化成功

#### bool Detect::getArmorCenter(const Mat src, const int bMode, armorData &data, Point2f offset)
    作用：从图片中检测装甲板
    参数：const Mat src：待检测图像
         const int bMode：二值化处理模式
         armorData &data：待检测装甲板信息
         Point2f offset：偏移量（一般从setImage函数中获得）
    返回：是否检测成功

ps:数据填充步骤中，tran_angle简略示意图：

![tran_angle](HDU_RM大符文档.assets/tran_angle.jpg)
