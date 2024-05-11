#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string base64_encode(const std::string& input) {
    std::string encoded;
    size_t input_length = input.length();
    uint8_t a, b, c;
    size_t i = 0;

    while (i < input_length) {
        a = static_cast<uint8_t>(input[i++]);
        encoded += base64_chars[(a >> 2) & 0x3F];

        if (i == input_length) {
            encoded += base64_chars[(a & 0x03) << 4];
            encoded += "==";
            break;
        }

        b = static_cast<uint8_t>(input[i++]);
        encoded += base64_chars[((a & 0x03) << 4) | ((b >> 4) & 0x0F)];

        if (i == input_length) {
            encoded += base64_chars[(b & 0x0F) << 2];
            encoded += "=";
            break;
        }

        c = static_cast<uint8_t>(input[i++]);
        encoded += base64_chars[((b & 0x0F) << 2) | ((c >> 6) & 0x03)];
        encoded += base64_chars[c & 0x3F];
    }

    return encoded;
}

std::string base64_decode(const std::string& input) {
    std::string decoded;
    size_t input_length = input.length();
    uint8_t a, b, c, d;
    size_t i = 0;

    while (i < input_length) {
        a = base64_chars.find(input[i++]);
        b = base64_chars.find(input[i++]);
        c = base64_chars.find(input[i++]);
        d = base64_chars.find(input[i++]);

        uint8_t byte1 = (a << 2) | (b >> 4);
        uint8_t byte2 = ((b & 0x0F) << 4) | (c >> 2);
        uint8_t byte3 = ((c & 0x03) << 6) | d;

        decoded.push_back(byte1);

        if (c != std::string::npos)
            decoded.push_back(byte2);
        if (d != std::string::npos)
            decoded.push_back(byte3);
    }

    return decoded;
}

int main() {
    std::cout << "Welcome to SBase64! Select 1 to encode or 2 to decode in Base64: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Ignore newline character

    if (choice == 1) {
        std::cout << "Enter text to encode in Base64: ";
        std::string input;
        std::getline(std::cin, input);

        std::string encoded = base64_encode(input);
        std::cout << "Base64 Encoded: " << encoded << std::endl;
    }
    else if (choice == 2) {
        std::cout << "Enter text to decode from Base64: ";
        std::string input;
        std::getline(std::cin, input);

        std::string decoded = base64_decode(input);
        std::cout << "Base64 Decoded: " << decoded << std::endl;
    }
    else {
        std::cout << "Invalid choice. Please select either 1 or 2." << std::endl;
    }

    return 0;
}
