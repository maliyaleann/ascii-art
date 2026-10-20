
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cerr << "PROGRAM STARTED\n";
    std::string filename;

    std::cout << "Enter video path: ";
    std::getline(std::cin, filename);

    // Open the video
    cv::VideoCapture video(filename);

    if (!video.isOpened()) {
        std::cout << "Failed to open video!\n";
        return 1;
    }

    // Store each frame here
    cv::Mat frame;

    // Read frames until the video ends
    while (video.read(frame)) {
        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        cv::Mat small_frame; 
        cv::resize(gray_frame, small_frame, cv::Size(80,45));

        for (int y = 0; y < small_frame.rows; y++) {
            for (int x = 0; x < small_frame.cols; x++) {

                int brightness = small_frame.at<unsigned char>(y, x);

            }
        }

        cv::imshow("My First Video Player", small_frame);

        // Wait 33 milliseconds (~30 FPS)
        // Press ESC to exit
        if (cv::waitKey(33) == 27) {
            break;
        }
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}
