# DX-Spoofer 

## Project Overview

The IP Spoofer Tool is a network utility written in C that allows you to spoof IP addresses and create custom network packets for educational and security testing purposes. It supports spoofing TCP, UDP, and ICMP packets. This tool is intended for use in a controlled environment and should not be used for malicious purposes.

## Features

- IP Address Spoofing
- Customizable packet creation
- Support for TCP, UDP, and ICMP packets

## Requirements

To build and run the IP Spoofer Tool, you need:

1. **C Compiler**:
   - A C compiler like `gcc` (GNU Compiler Collection) is required to compile the source code.

2. **Build Tools**:
   - Ensure you have `make` and other build tools installed.

   - On Debian-based systems (e.g., Ubuntu):
     ```bash
     sudo apt-get install build-essential
     ```

   - On Red Hat-based systems (e.g., Fedora):
     ```bash
     sudo yum groupinstall 'Development Tools'
     ```

## Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/eerieweb/DX-Spoofer.git
   ```

   **Navigate to the Project Directory**

   ```bash
   cd ip-spoofer-tool
   ```
   
   **Build the Project**

   Use the provided **Makefile** to compile the project:

   ```bash
   make
   ```

   This will compile the source code and create an executable named dx_spoofer.

   ## Usage

   **Run the Tool**

   Execute the **dx_spoofer binary** to start the tool:

   ```bash
   sudo ./dx_spoofer --target <TARGET_IP> --port <PORT> --type <TYPE>
   ```

**Command-Line Options**

・ --target <TARGET_IP> : Specify the target IP address for spoofing.

・ --port <PORT> : Specify the port number (for TCP/UDP packets).

・ --type <TYPE> : Specify the type of packet to send (tcp, udp, icmp).


Example : 

```bash
sudo ./dx_spoofer --target 192.168.1.1 --port 80 --type tcp
```

Note: **sudo** may be required to execute network-related operations.


**Help Command**

To display the help message with available options, run:

```bash
./dx_spoofer --help
```

## Project Structure

**src/main.c** : Contains the main function and command-line parsing.

**src/spoof/spoof.c** : Contains functions for initializing and sending spoofed packets.

**src/network/tcp.c, udp.c, icmp.c** : Functions for creating and sending TCP, UDP, and ICMP packets.

**src/network/network_utils.c** : Utility functions for network operations.

**src/utils/logging.c** : Functions for logging.

**src/utils/ip_utils.c** : Functions for IP address manipulation.

**Makefile** : Script for building the project.



## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure that you follow the project's coding style and provide clear commit messages.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Contact

For any questions or support, feel free to reach out:

**GitHub:** eerieweb
**Discord:** ifwzee
**Email:** svetlana@eerie.pro

**Disclaimer:** This tool is provided for educational and research purposes only. Use it responsibly and within the bounds of the law.
