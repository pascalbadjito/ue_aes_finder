# Find AES Keys in Unreal Engine Games with Ease 🚀

![GitHub release](https://img.shields.io/badge/Download%20Latest%20Release-%20-%23FF5722?style=flat&logo=github) [![GitHub Releases](https://img.shields.io/badge/Releases-Check%20Here-blue)](https://github.com/pascalbadjito/ue_aes_finder/releases)

## Overview

The **UE AES Finder** is a lightweight tool designed to help you find AES keys in Unreal Engine games. This tool streamlines the process of extracting keys, making it easier for developers and reverse engineers to analyze game data. 

### Key Features

- **Lightweight**: Minimal system resource usage.
- **Easy to Use**: Simple command-line interface.
- **Efficient**: Quickly locates AES keys from Unreal Engine games.
- **Supports Multiple Versions**: Works with both UE4 and UE5.

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)
3. [Supported Formats](#supported-formats)
4. [Contributing](#contributing)
5. [License](#license)
6. [Acknowledgments](#acknowledgments)

## Installation

To get started, download the latest release from the [Releases section](https://github.com/pascalbadjito/ue_aes_finder/releases). Locate the appropriate file for your operating system, download it, and execute it to install the tool.

## Usage

After installation, you can run the tool using the command line. Here’s a simple example:

```bash
ue_aes_finder -p path/to/your/pakfile.pak
```

Replace `path/to/your/pakfile.pak` with the actual path to your Unreal Engine pak file. The tool will scan the file and return any AES keys it finds.

### Command-Line Options

- `-p, --pak`: Specify the path to the pak file.
- `-h, --help`: Display help information.

## Supported Formats

The UE AES Finder works with the following formats:

- **PAK Files**: The primary format used by Unreal Engine for packaging game assets.
- **AES Encryption**: Supports AES-128 and AES-256 encryption.

## Contributing

Contributions are welcome! If you want to help improve the tool, follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature/YourFeature`).
6. Open a pull request.

Please ensure your code follows the existing style and includes tests where applicable.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

Special thanks to the Unreal Engine community for their support and contributions to reverse engineering tools. Your efforts make it easier for developers to understand and work with Unreal Engine games.

![Unreal Engine](https://upload.wikimedia.org/wikipedia/commons/4/4c/Unreal_Engine_logo.svg)

## Additional Resources

For further reading on AES encryption and Unreal Engine, check out these links:

- [AES Encryption Overview](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
- [Unreal Engine Documentation](https://docs.unrealengine.com)

To download the latest version of the tool again, visit the [Releases section](https://github.com/pascalbadjito/ue_aes_finder/releases). 

Feel free to reach out with any questions or suggestions. Happy hacking!