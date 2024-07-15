#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

class Zipper {
public:
	Zipper() = default;

	bool embedZipInImage(const std::string& zipFilePath,
		const std::string& imagePath,
		const std::string& outputImagePath) {
		if (!fileExists(zipFilePath)) {
			std::cerr << "ZIP file does not exist: " << zipFilePath << std::endl;
			return false;
		}

		if (!fileExists(imagePath)) {
			std::cerr << "Image file does not exist: " << imagePath << std::endl;
			return false;
		}

		if (!appendZipToImage(imagePath, zipFilePath, outputImagePath)) {
			std::cerr << "Failed to append ZIP file to the image.\n";
			return false;
		}

		return true;
	}

private:
	bool fileExists(const std::string& path) {
		std::ifstream file(path);
		return file.good();
	}

	bool appendZipToImage(const std::string& imagePath, const std::string& zipFilePath, const std::string& outputFilePath) {
		try {
			std::ifstream imageFile(imagePath, std::ios::binary);
			std::ifstream zipFile(zipFilePath, std::ios::binary);

			if (!imageFile.is_open()) {
				std::cerr << "Failed to open image file: " << imagePath << std::endl;
				return false;
			}

			if (!zipFile.is_open()) {
				std::cerr << "Failed to open ZIP file: " << zipFilePath << std::endl;
				return false;
			}

			std::ofstream outputFile(outputFilePath, std::ios::binary);
			if (!outputFile.is_open()) {
				std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
				return false;
			}

			outputFile << imageFile.rdbuf();
			outputFile << zipFile.rdbuf();
		}
		catch (const std::ios_base::failure& e) {
			std::cerr << "File operation failed: " << e.what() << std::endl;
			return false;
		}

		return true;
	}
};

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <image_path> <output_image_path> <zip_file_path>\n";
		return 1;
	}

	std::string imagePath = argv[1];
	std::string outputImagePath = argv[2];
	std::string zipFilePath = argv[3];

	Zipper zipper;

	if (zipper.embedZipInImage(zipFilePath, imagePath, outputImagePath)) {
		std::cout << "ZIP file appended successfully to the image!\n";
	}
	else {
		std::cerr << "Failed to append ZIP file to the image.\n";
		return 1;
	}

	return 0;
}