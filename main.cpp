#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
     std::string filename; 
     std::cout << "Enter the path to the image file: "; 
     std::getline(std::cin, filename); 

    // load image data
    int width, height, channels; 

    // stbi_load returns image as a collection of bytes
    unsigned char* img_data = stbi_load(filename.c_str(), &width, &height, &channels, 0); 

    if (img_data == nullptr) {
        std::cout << "Failed to load image." << std::endl; 
        return 1;
    }

    std::cout << "Image loaded successfully!" << std::endl; 
    std::cout << "Width: " << width << "px, Height: " << height << "px" << std::endl;
    std::cout << "Channels: " << channels << " (3=RGB 4=RGBA)" << std::endl; 

    // ascii characters being used 
    std::string ascii_chars = "@%#*+=-:. ";

    // dynamically resize ascii image
    int target_width = 80; 
    double step_x = static_cast<double>(width) / target_width;    // calculate horizontal sampling interval 
    
    int target_height = height * (static_cast<double>(target_width) / width) / 2;
    double step_y = static_cast<double>(height) / target_height; 

    // calculate rectangular regions
    for (int row = 0; row < target_height; row++) {
        int y = static_cast<int>(row * step_y); // region start
        int next_y = static_cast<int>((row + 1) * step_y); // next region start
        
        for (int col = 0; col < target_width; col++) {
            int x = static_cast<int>(col * step_x); // region start
            int next_x = static_cast<int>((col + 1) * step_x); // next region start

            // averaging variables
            double brightness; 
            double total_brightness = 0; 
            int pixel_count = 0;

            for (int sample_y = y; sample_y < next_y; sample_y++) {
                for (int sample_x = x; sample_x < next_x; sample_x++) {

                    int pixel_index = (sample_y * width + sample_x) * channels;

                    // read the pixel's color values 
                    int red = img_data[pixel_index];
                    int green = img_data[pixel_index + 1]; 
                    int blue = img_data[pixel_index + 2];

                    // convert RGB to grayscale 
                    brightness = (0.299 * red) + (0.587 * green) + (0.114 * blue);  
                    
                    // accumulatre brightness values
                    total_brightness += brightness;
                    pixel_count++;  
                }
            }
            double average_brightness = total_brightness / pixel_count;
            // convert brightness to ASCII character
            int ascii_index = ( average_brightness / 255) * (ascii_chars.length() - 1);
            std::cout << ascii_chars[ascii_index];
        }
        std::cout << "\n";
    }

    // free image memory when done
    stbi_image_free(img_data); 
    return 0;
}