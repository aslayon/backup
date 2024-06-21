//
// Created by Minseok Chu on 11/14/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>

class PlayFair {
    char encryptMatrix[5][5] = { 0 };
    std::string encryptKey;
    std::string overlappedPair;
public:
    PlayFair(const std::string& encryptKey, std::string overlappedPair);

    std::string EncryptString(std::string string);

    void EncryptFile(const std::string& inputFilename, const std::string& outputFilename);
};

std::string RemoveDuplicates(std::string string) {
    for (int i = 0; i < string.size(); i++) {
        int j = i + 1;

        while (j < string.size()) {
            if (string[i] == string[j]) {
                string.erase(j, 1);
            }
            else {
                j++;
            }
        }
    }

    return string;
}

PlayFair::PlayFair(const std::string& encryptKey, std::string overlappedPair) {
    if (overlappedPair.length() != 2) {
        throw std::invalid_argument("overlappedPair must be string of length 2");
    }

    this->encryptKey = encryptKey;
    this->overlappedPair = overlappedPair;

    std::string encryptKeyBase = RemoveDuplicates(encryptKey);
    std::string anotherElements;

    bool overlapFound = false;

    for (int i = 0; i < encryptKeyBase.size(); i++) {
        int j = 0;

        while (j < overlappedPair.size()) {
            if (encryptKeyBase[i] == overlappedPair[j]) {
                if (overlapFound) {
                    encryptKeyBase.erase(i, 1);
                }
                else {
                    encryptKeyBase.replace(i, 1, "0");
                    overlapFound = true;
                    j++;
                }
            }
            else {
                j++;
            }
        }
    }

    for (char i = 'a'; i <= 'z'; i++) {
        int j = 0;

        while (j < encryptKeyBase.size()) {
            if (encryptKeyBase[j] == i) {
                break;
            }
            else {
                j++;
            }
        }

        int k = 0;

        while (k < overlappedPair.size()) {
            if (overlappedPair[k] == i) {
                break;
            }
            else {
                k++;
            }
        }

        if (k < overlappedPair.size()) {
            if (!overlapFound) {
                anotherElements.push_back('0');
                overlapFound = true;
            }
        }
        else if (j == encryptKeyBase.size()) {
            anotherElements.push_back(i);
        }
    }

    int n = 0;
    int m = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (n < encryptKeyBase.size()) {
                encryptMatrix[i][j] = encryptKeyBase[n++];
            }
            else {
                if (m < anotherElements.size()) {
                    encryptMatrix[i][j] = anotherElements[m++];
                }
            }
        }
    }

    std::cout << "-- Encrypt Matrix --" << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << encryptMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-- Matrix Ends --" << std::endl;
    std::cout << "'0' can be '" << overlappedPair[0] << "' or '" << overlappedPair[1] << "'" << std::endl;
}

std::string PlayFair::EncryptString(std::string string) {
    if (string.length() % 2 != 0) {
        string.push_back('x');
    }

    for (int i = 0; i < string.size(); ++i) {
        int j = 0;

        while (j < overlappedPair.size()) {
            if (string[i] == overlappedPair[j]) {
                break;
            }
            else {
                ++j;
            }
        }

        if (j < overlappedPair.size()) {
            string[i] = '0';
        }
    }

    for (int i = 0; i < string.size(); i += 2) {
        if (string[i] == string[i + 1]) {
            string[i + 1] = 'x';
        }

        int charPosition[2][2] = { 0 };

        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (encryptMatrix[j][k] == string[i]) {
                    charPosition[0][0] = j;
                    charPosition[0][1] = k;
                }
                if (encryptMatrix[j][k] == string[i + 1]) {
                    charPosition[1][0] = j;
                    charPosition[1][1] = k;
                }
            }
        }

        if (charPosition[1][0] == charPosition[0][0]) {
            // If y point is same.
            charPosition[0][1] = charPosition[0][1] + 1 > 4 ? 0 : charPosition[0][1] + 1;
            charPosition[1][1] = charPosition[1][1] + 1 > 4 ? 0 : charPosition[1][1] + 1;
        }
        else if (charPosition[1][1] == charPosition[0][1]) {
            // If x point is same.
            charPosition[0][0] = charPosition[0][0] + 1 > 4 ? 0 : charPosition[0][0] + 1;
            charPosition[1][0] = charPosition[1][0] + 1 > 4 ? 0 : charPosition[1][0] + 1;
        }
        else {
            int temp = charPosition[0][0];
            charPosition[0][0] = charPosition[1][0];
            charPosition[1][0] = temp;
        }

        string[i] = encryptMatrix[charPosition[0][0]][charPosition[0][1]];
        string[i + 1] = encryptMatrix[charPosition[1][0]][charPosition[1][1]];
    }

    return string;
}

void PlayFair::EncryptFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename, std::ios::in);
    std::ofstream outputFile(outputFilename, std::ios::out);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Cannot open encryption files!");
    }

    outputFile << "ENCRYPTION KEY  : " << encryptKey << std::endl;
    outputFile << "OVERLAPPED PAIR : '" << overlappedPair[0] << "', " << overlappedPair[1] << "'" << std::endl;

    while (!inputFile.eof()) {
        std::string rawLine;
        getline(inputFile, rawLine, '.');
        outputFile << EncryptString(rawLine) << std::endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    std::string encryptKey, overlappedPair, input;
    int modeSelection;

    std::cout << "TYPE ENCRYPT KEY : ";
    std::cin >> encryptKey;

    std::cout << "TYPE OVERLAPPED PAIR : ";
    std::cin >> overlappedPair;

    std::cout << "TYPE MODE SELECTION CODE (0 => File, 1 => Console) : ";
    std::cin >> modeSelection;

    std::cin.ignore();

    PlayFair playFair(encryptKey, overlappedPair);

    if (modeSelection == 0) {
        std::string inputFilename, outputFilename;

        std::cout << "TYPE INPUT FILE PATH : ";
        std::cin >> inputFilename;

        std::cout << "TYPE OUTPUT FILE PATH : ";
        std::cin >> outputFilename;

        playFair.EncryptFile(inputFilename, outputFilename);

        std::cout << "ENCRYPTION ENDED!" << std::endl;
    }
    else if (modeSelection == 1) {
        while (true) {
            std::cout << "TYPE STRING FOR ENCRYPT : ";
            getline(std::cin, input);

            if (input == "exit") {
                break;
            }

            std::cout << playFair.EncryptString(input) << std::endl;
        }
    }
    else {
        throw std::runtime_error("Mode selection code must be 1 or 0");
    }

    return EXIT_SUCCESS;
}