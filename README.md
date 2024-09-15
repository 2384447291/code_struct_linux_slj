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