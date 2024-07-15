#include <iostream>
#include <fstream>
#include <vector>
#include <zip.h>
#include <cstdio>

class Zipper {
public:
	Zipper() : zip_(nullptr) {}

	~Zipper() {
		if (zip_) {
			zip_close(zip_);
		}
	}

	bool createZipAndEmbedInImage(const std::vector<std::string>& files,
		const std::string& imagePath,
		const std::string& outputImagePath) {
		std::string zipFilePath = "temp.zip";
		if (!createZip(files, zipFilePath)) {
			std::cerr << "Failed to create ZIP file." << std::endl;
			return false;
		}

		if (!appendZipToImage(imagePath, zipFilePath, outputImagePath)) {
			std::cerr << "Failed to append ZIP file to the image." << std::endl;
			return false;
		}

		if (std::remove(zipFilePath.c_str()) != 0) {
			std::cerr << "Failed to delete temporary ZIP file." << std::endl;
		}

		return true;
	}

private:
	zip_t* zip_;

	bool createZip(const std::vector<std::string>& files, const std::string& zipFilePath) {
		int error;
		zip_ = zip_open(zipFilePath.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &error);
		if (!zip_) return false;

		for (const auto& file : files) {
			zip_source_t* source = zip_source_file(zip_, file.c_str(), 0, 0);
			if (source == nullptr) {
				zip_close(zip_);
				return false;
			}
			zip_file_add(zip_, file.c_str(), source, ZIP_FL_OVERWRITE);
		}

		zip_close(zip_);
		return true;
	}

	bool appendZipToImage(const std::string& imagePath, const std::string& zipFilePath, const std::string& outputFilePath) {
		std::ifstream imageFile(imagePath, std::ios::binary);
		std::ifstream zipFile(zipFilePath, std::ios::binary);

		if (!imageFile || !zipFile) return false;

		std::ofstream outputFile(outputFilePath, std::ios::binary);

		outputFile << imageFile.rdbuf();
		outputFile << zipFile.rdbuf();

		imageFile.close();
		zipFile.close();
		outputFile.close();

		return true;
	}
};

int main(int argc, char* argv[]) {
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <image_path> <output_image_path> <file1> <file2> ..." << std::endl;
		return 1;
	}

	std::string imagePath = argv[1];
	std::string outputImagePath = argv[2];
	std::vector<std::string> filesToZip;

	for (int i = 3; i < argc; ++i) {
		filesToZip.push_back(argv[i]);
	}

	Zipper zipper;

	if (zipper.createZipAndEmbedInImage(filesToZip, imagePath, outputImagePath)) {
		std::cout << "ZIP file appended successfully to the image!" << std::endl;
	}
	else {
		std::cerr << "Failed to create or append ZIP file to the image." << std::endl;
		return 1;
	}

	return 0;
}