# Zipper <img src="https://imgur.com/VLRCYWO.png" alt="Zipper Logo" width="25" height="25">
<img src="https://img.shields.io/github/downloads/90th/zipper/latest/total" alt="GitHub Downloads (all assets, latest release)" /> <img src="https://img.shields.io/github/last-commit/90th/zipper" alt="GitHub last commit" /> <img src="https://img.shields.io/github/stars/90th/zipper" alt="GitHub Repo stars" />

Zipper is a command-line interface (CLI) application that allows you to embed multiple files into an image by creating a ZIP archive and appending it to the image. This can be useful for various purposes, such as hiding data within images or packaging files together with an image.


## Usage

Run the zipper application with the following syntax:

```
zipper.exe original.png output.png file1.txt file2.txt ...
```
This will create a ZIP archive containing file1.txt and file2.txt, and append it to original.png, resulting in output.png.

## Dependencies

Zipper relies on the following dependencies:
- **libzip**: This library is used for creating and manipulating ZIP archives.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
