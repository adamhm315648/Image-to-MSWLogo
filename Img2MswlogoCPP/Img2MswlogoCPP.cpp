#include <opencv2/opencv.hpp>
#include <fstream>

cv::Vec4b rgba_of_pixel(const cv::Mat& img, int x, int y) {
    cv::Vec4b color = img.at<cv::Vec4b>(y, x);
    return color;
}

int main() {
    std::string img_path = "logo.png";
    cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);

    if (img.empty()) {
        std::cerr << "Could not open or read the image." << std::endl;
        return -1;
    }

    int width = img.cols;
    int height = img.rows;

    std::ofstream file("logo_commands.txt");
    file << "PU LT 90 FD 200 RT 90 FD 100 RT 90 PD \n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cv::Vec4b pixel_color = rgba_of_pixel(img, x, y);

            // Check if the pixel is transparent
            if (pixel_color[3] == 0) {
                file << "PU ";
            }
            else {
                file << "SETPENCOLOR [" << static_cast<int>(pixel_color[2]) << " " << static_cast<int>(pixel_color[1]) << " " << static_cast<int>(pixel_color[0]) << "] ";
                file << "PD ";
            }

            file << "FD 1 ";
            std::cout << "fd 1" << std::endl;
        }

        file << "PU RT 90 FD 1 RT 90 FD " << width << " RT 180 PD \n";
        std::cout << "next line" << std::endl;
    }

    return 0;
}
