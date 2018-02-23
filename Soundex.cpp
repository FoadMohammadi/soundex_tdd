#include "Soundex.h"

std::string Soundex::encode(const std::string& word) {
    return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
}

std::string Soundex::encodedDigit(char letter) {
    const std::unordered_map<char, std::string> encodings {
        {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
        {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"},
        {'s', "2"}, {'x', "2"}, {'z', "2"},
        {'d', "3"}, {'t', "3"},
        {'l', "4"},
        {'m', "5"}, {'n', "5"},
        {'r', "6"}
    };
    auto it = encodings.find(lower(letter));
    return it == encodings.end() ? NotADigit : it->second;
}

std::string Soundex::upperFront(const std::string& string) {
    return std::string(1, std::toupper(static_cast<unsigned char>(string.front())));
}

char Soundex::lower(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

std::string Soundex::head(const std::string& word) {
    return word.substr(0, 1);
}

std::string Soundex::tail(const std::string& word) {
    return word.substr(1);
}

std::string Soundex::encodedDigits(const std::string& word) {
    std::string encoding;
    encodeHead(encoding, word);
    encodeTail(encoding, word);
    return encoding;
}

void Soundex::encodeHead(std::string& encoding, const std::string& word) {
    encoding += encodedDigit(word.front());
}

void Soundex::encodeTail(std::string& encoding, const std::string& word) {
    for (auto i = 1u; i < word.length(); i++)
        if (!isComplete(encoding))
            encodeLetter(encoding, word[i], word[i-1]);
}

void Soundex::encodeLetter(std::string& encoding, char letter, char lastLetter) {
    auto digit = encodedDigit(letter);
    if (digit != NotADigit && (digit != lastDigit(encoding) || isVowel(lastLetter)))
        encoding += digit;
}

bool Soundex::isVowel(char letter) {
    return std::string("aeiouy").find(lower(letter)) != std::string::npos;
}
	
std::string Soundex::lastDigit(const std::string& encoding) {
    if (encoding.empty()) return NotADigit;
    return std::string(1, encoding.back());
}

bool Soundex::isComplete(const std::string& encoding) {
    return encoding.length() == MaxCodeLenght;
}

std::string Soundex::zeroPad(const std::string& word) {
    auto zerosNeeded = MaxCodeLenght - word.length();
    return word + std::string(zerosNeeded, '0');
}
