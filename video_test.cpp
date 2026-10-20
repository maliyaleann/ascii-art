
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp>
#include <algorithm>

int main() {
    std::cerr << "PROGRAM STARTED\n";
    std::string filename;

    std::cout << "Enter video path: ";
    std::getline(std::cin, filename);

    // open the video
    cv::VideoCapture video(filename);

    if (!video.isOpened()) {
        std::cout << "Failed to open video!\n";
        return 1;
    }

    // store each frame here
    cv::Mat frame;

    std::string ascii_chars = "@%#*+=-:. ";
    // std::string ascii_chars = "MWNXK0Okxdolc:,. ";
    //std::string ascii_chars = " .,:clodxkO0KXNWM";

    cv::Ptr<cv::freetype::FreeType2> ft = cv::freetype::createFreeType2();
    ft->loadFontData("C:\\Windows\\Fonts\\consola.ttf", 0);

    // read frames until the video ends
    while (video.read(frame)) {
        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        gray_frame.convertTo(gray_frame, -1, 1.2, 0);

        cv::Mat small_frame; 

        int target_width = 140;
        int char_width = 8;
        int char_height = 10;

        double aspect_ratio = static_cast<double>(frame.rows) / frame.cols;

        int target_height = static_cast<int>(target_width * aspect_ratio * (static_cast<double>(char_width) / static_cast<double>(char_height)));
        
        cv::resize(gray_frame, small_frame, cv::Size(target_width, target_height));

        // create fresh black canvas for every video frame
        int canvas_width = small_frame.cols * char_width + 80;  
        int canvas_height = small_frame.rows * char_height + 80;
        cv::Mat ascii_canvas(canvas_height, canvas_width, CV_8UC3, cv::Scalar(0, 0, 0));

        int offset_x = (ascii_canvas.cols - small_frame.cols * char_width) / 2;
        int offset_y = (ascii_canvas.rows - small_frame.rows * char_height) / 2;

        // convert grayscale pixels into ASCII characters
        for (int y = 0; y < small_frame.rows; y++) {
            for (int x = 0; x < small_frame.cols; x++) {
                // read pixel brightness
                int brightness = small_frame.at<unsigned char>(y, x);
                
                if (brightness < 20) {
                    continue;
                }

                // boost brightness for rendering
                int text_brightness = std::min(255, brightness * 3); 

                int ascii_index = (brightness / 255.0) * (ascii_chars.length() - 1);
                char ascii_char = ascii_chars[ascii_index];


                // collect all characters from the current video frame  
                int draw_x = offset_x + x * char_width;
                int draw_y = offset_y + (y + 1) * char_height;

                ft->putText(
                    ascii_canvas,
                    std::string(1, ascii_char),
                    cv::Point(draw_x, draw_y),
                    11,
                    cv::Scalar(text_brightness, text_brightness, text_brightness),
                    -1,
                    cv::LINE_AA,
                    true
                );
            }
        }

        for (int y = 0; y < small_frame.rows; y++) {
            for (int x = 0; x < small_frame.cols; x++) {

                int brightness = small_frame.at<unsigned char>(y, x);

            }
        }

        cv::imshow("ASCII Studio", ascii_canvas);

        // wait 33 milliseconds (~30 FPS)
        // press ESC to exit
        if (cv::waitKey(33) == 27) {
            break;
        }
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}
