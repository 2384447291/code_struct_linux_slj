<!-- 常用linux命令 -->
rm -rf ./*
sudo gedit
sudo  find / -name  libstdc++.so.6*
strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX
ls /dev | grep ttyUSB
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DCMAKE_BUILD_TYPE=Release ..
ulimit -c unlimited
pwd

<!-- 批量显示图片的函数 -->
// const int imagesPerRow = 4; // 每行显示4张图片
// const int imagesPerCol = 4; // 每列显示4张图片
// const int totalImages = imagesPerRow * imagesPerCol; // 总共16张图片
// const int imageWidth = 100; // 每张图片的宽度
// const int imageHeight = 100; // 每张图片的高度

// cv::Mat combinedImage(imageHeight * imagesPerCol, imageWidth * imagesPerRow, CV_8UC3, cv::Scalar(0, 0, 0));

// for (int i = 0; i < totalImages; ++i) {
//     std::string S_id = formatNumber(i,2);
//     std::string filePath = "../Capture_Photo/xx_xxx_2/" +  S_id + "_200_2.jpg";
//     cv::Mat image = cv::imread(filePath);

//     if (image.empty()) {
//         std::cout << "Error loading image: " << filePath << std::endl;
//         continue;
//     }

//     // Resize image to fit in the grid
//     cv::resize(image, image, cv::Size(imageWidth, imageHeight));

//     // Calculate position in the combined image
//     int row = i / imagesPerRow;
//     int col = i % imagesPerRow;
//     image.copyTo(combinedImage(cv::Rect(col * imageWidth, row * imageHeight, imageWidth, imageHeight)));
// }

// cv::imshow("Combined Image", combinedImage);
// cv::waitKey(0);
// cv::destroyAllWindows();

<!-- 改文件名的函数 -->
#include <iostream>
#include <filesystem>
#include <string>

int main() {
    std::string directoryPath = "../Capture_Photo/xx_xxx_1"; // 目标目录

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".jpg") {
            std::string oldName = entry.path().string();
            std::string newName = oldName; // 保留原始名称

            // 更改最后一位
            newName[newName.size() - 5] = 'X'; // 将倒数第二个字符（文件名部分）改为 'X'

            std::filesystem::rename(oldName, newName);
            std::cout << "Renamed: " << oldName << " to " << newName << std::endl;
        }
    }

    return 0;
}


https://blog.csdn.net/weixin_48617416/article/details/131729829
https://blog.csdn.net/free555/article/details/128131875
https://blog.csdn.net/weixin_44796670/article/details/115900538
https://blog.csdn.net/u011622208/article/details/115208377#:~:text=%E8%A7%A3%E5%86%B3%E6%96%B9%E6%A1%88%20%E8%BF%99%E6%98%AF%E5%9B%A0%E4%B8%BA%20opencv%20%E5%A4%B4%E6%96%87%E4%BB%B6%E7%9A%84%E8%B7%AF%E5%BE%84%E4%B8%AD%E5%A4%9A%E4%BA%86%E4%B8%80%E4%B8%AA,opencv4%20%E7%9A%84%E6%96%87%E4%BB%B6%E5%A4%B9%EF%BC%9A%20%2Fusr%2Finclude%2Fopencv4%2Fopencv2%EF%BC%8C%20%E5%8F%AF%E4%BB%A5%E5%B0%86opencv2%E6%8B%B7%E8%B4%9D%E5%88%B0%E8%87%AA%E5%B7%B1%E7%9A%84include%E6%96%87%E4%BB%B6%E5%A4%B9%20%E5%8F%AF%E4%BB%A5%E5%B0%86opencv2%E6%96%87%E4%BB%B6%E5%A4%B9%E9%93%BE%E6%8E%A5%E5%88%B0include%E6%96%87%E4%BB%B6%E5%A4%B9%E4%B8%8B
https://blog.csdn.net/weixin_39379635/article/details/129159713
https://blog.csdn.net/huazhang_001/article/details/128828999
我们在安装opencv的时候，没有考虑到一些额外的依赖：
libgtk2.0-dev
pkg-config
这两个依赖环境是需要在opencv安装之前安装的;此时正确的做法是将之前安装好的opencv卸了，重新安装，在确保安装了opencv一些必要的依赖后，还需要安装libgtk2.0-dev和pkg-config。之后再进行编译、安装、配置环境
sudo ln -s /usr/local/include/opencv4/opencv2/ usr/local/include