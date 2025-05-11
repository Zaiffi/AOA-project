#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Function to compress the input string using LZW
vector<int> lzw_compress(const string& input) {
    unordered_map<string, int> dictionary;
    string p, c;
    int code = 256; // ASCII values cover 0-255

    // Initialize dictionary with single characters
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, char(i))] = i;
    }

    vector<int> compressed;
    p = "";

    for (char ch : input) {
        c = string(1, ch);
        if (dictionary.find(p + c) != dictionary.end()) {
            p = p + c;
        } else {
            compressed.push_back(dictionary[p]);
            dictionary[p + c] = code++;
            p = c;
        }
    }

    if (!p.empty())
        compressed.push_back(dictionary[p]);

    return compressed;
}

// Function to decompress the code using LZW
string lzw_decompress(const vector<int>& compressed) {
    unordered_map<int, string> dictionary;
    int code = 256;

    // Initialize dictionary with single characters
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, char(i));
    }

    string previous = string(1, char(compressed[0]));
    string result = previous;

    for (size_t i = 1; i < compressed.size(); i++) {
        string entry;

        if (dictionary.find(compressed[i]) != dictionary.end()) {
            entry = dictionary[compressed[i]];
        } else if (compressed[i] == code) {
            entry = previous + previous[0];
        } else {
            cerr << "Error during decompression!" << endl;
            return "";
        }

        result += entry;
        dictionary[code++] = previous + entry[0];
        previous = entry;
    }

    return result;
}

int main() {
    string text;
    cout << "Enter text to compress: ";
    getline(cin, text);

    vector<int> compressed = lzw_compress(text);

    cout << "\nCompressed data: ";
    for (int code : compressed) {
        cout << code << " ";
    }
    cout << endl;

    string decompressed = lzw_decompress(compressed);
    cout << "\nDecompressed text: " << decompressed << endl;

    return 0;
}
