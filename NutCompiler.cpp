#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <unordered_set>
#include <sys/stat.h>
#include <dirent.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <regex>
#include <algorithm>
#include <sstream>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int TEXT_AREA_X = 300;
const int TEXT_AREA_Y = 100;
const int TEXT_AREA_WIDTH = SCREEN_WIDTH - TEXT_AREA_X;
const int TEXT_AREA_HEIGHT = SCREEN_HEIGHT - TEXT_AREA_Y;

bool gotoLineMode = false;
std::string gotoLineInput = "";

bool selecting = false;
int selectionStartLine = -1;
int selectionStartPos = -1;
int selectionEndLine = -1;
int selectionEndPos = -1;

bool darkmode = false;
SDL_Color defaultColor1 = {0, 0, 0, 255};
SDL_Color darkBlueColor = {0, 51, 102, 255};
SDL_Color greenbColor = {0, 128, 128, 255};
SDL_Color darkOrangeColor1 = {255, 140, 9, 255};
SDL_Color darkRedColor = {139, 0, 0, 255};
SDL_Color darkGreenColor = {0, 100, 0, 255};
SDL_Color purpleColor = {128, 0, 128, 255};
SDL_Color greyColor = {128, 128, 128, 255};
SDL_Color bluefColor = {0, 139, 139, 255};
SDL_Color zereshkiColor = {128, 0, 0, 255};
SDL_Color darkGoldColor = {184, 134, 11, 255};

SDL_Color defaultColor2 = {255, 255, 255, 255};
SDL_Color lightPurpleColor = {198,120,221, 255};
SDL_Color redColor = {224 , 108 , 117, 255};
SDL_Color lightBlueColor = {97 , 175 , 254, 255};
SDL_Color yellowColor = {229 , 192 , 123, 255};
SDL_Color greenColor = {152 , 195 , 121, 255};
SDL_Color orangeColor = {209 , 154 , 102, 255};
SDL_Color darkGreyColor = {92 , 99 , 112, 255};
SDL_Color firozeiColor = {86 , 182 , 194, 255};
SDL_Color darkOrangeColor2 = {213,94 , 0, 255};
SDL_Color lightGreyColor = {171 , 178 , 191, 255};

std::unordered_set<std::string> KEYWORDS1 = {
        "class", "if", "else", "else if", "switch", "case", "default", "for", "while", "do", "break", "continue", "return"
};
std::unordered_set<std::string> KEYWORDS2 = {
        "int", "float", "double" , "bool" , "long", "char"
};
std::unordered_set<std::string> KEYWORDS3 = {
        "include"
};
std::unordered_set<std::string> KEYWORDS4 = {
        // C++ keywords
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
        "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
        "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", "include",

        // Containers and Algorithms
        "vector", "list", "deque", "array", "forward_list", "set", "map",
        "unordered_set", "unordered_map", "stack", "queue", "algorithm", "numeric",

        // Iterators
        "iterator",

        // Strings and Character Handling
        "string", "cctype", "cwctype", "cstring", "cwchar",

        // Streams and Input/Output
        "iostream", "fstream", "sstream", "iomanip",

        // Memory Management
        "memory", "new", "scoped_allocator",

        // Utilities
        "utility", "tuple", "optional", "variant", "any", "functional",
        "type_traits", "typeinfo", "typeindex",

        // Time and Date
        "chrono", "ctime",

        // Mathematical Functions
        "cmath", "complex", "valarray", "random", "ratio", "numbers",

        // Concurrency
        "thread", "mutex", "future", "condition_variable", "atomic",

        // Error Handling
        "exception", "stdexcept", "system_error",

        // C Standard Library Headers (Compatibility)
        "cassert", "cctype", "cerrno", "cfenv", "cfloat", "cinttypes",
        "climits", "clocale", "cmath", "csetjmp", "csignal", "cstdarg",
        "cstddef", "cstdint", "cstdio", "cstdlib", "cstring", "ctime",
        "cuchar", "cwchar", "cwctype",

        // Miscellaneous
        "bitset", "codecvt", "filesystem", "regex", "locale", "limits",

        // C++20 and Beyond
        "concepts", "coroutine", "compare", "span", "ranges",

        // Standard library identifiers
        "cin", "cout", "cerr", "clog", "endl", "flush", "std", "string", "vector", "map",
        "set", "unordered_map", "unordered_set", "pair", "make_pair", "tuple", "make_tuple",
        "array", "list", "deque", "stack", "queue", "priority_queue", "sort", "find",
        "reverse", "accumulate", "max", "min", "swap", "move", "forward", "emplace",
        "push_back", "push_front", "pop_back", "pop_front", "begin", "end", "rbegin", "rend",
        "size", "empty", "clear", "insert", "erase", "count", "lower_bound", "upper_bound",
        "equal_range", "unique_ptr", "shared_ptr", "weak_ptr", "make_unique", "make_shared",
        "function", "bind", "ref", "cref", "thread", "mutex", "lock_guard", "unique_lock",
        "condition_variable", "async", "future", "promise", "packaged_task", "launch",

        // <math.h> / <cmath> identifiers
        "abs", "acos", "asin", "atan", "atan2", "ceil", "cos", "cosh", "exp", "fabs",
        "floor", "fmod", "log", "log10", "pow", "sin", "sinh", "sqrt", "tan", "tanh",
        "acosf", "asinf", "atanf", "atan2f", "ceilf", "cosf", "coshf", "expf", "fabsf",
        "floorf", "fmodf", "logf", "log10f", "powf", "sinf", "sinhf", "sqrtf", "tanf", "tanhf",
        "acosl", "asinl", "atanl", "atan2l", "ceill", "cosl", "coshl", "expl", "fabsl",
        "floorl", "fmodl", "logl", "log10l", "powl", "sinl", "sinhl", "sqrtl", "tanl", "tanhl",
        "M_PI", "M_E", "M_LOG2E", "M_LOG10E", "M_LN2", "M_LN10", "M_PI_2", "M_PI_4", "M_1_PI",
        "M_2_PI", "M_2_SQRTPI", "M_SQRT2", "M_SQRT1_2",

        "_", "size_t", "h", "bits", "stdc", "math",

        // <iomanip> identifiers
        "setprecision", "setw", "setfill", "setbase", "setiosflags",
        "resetiosflags", "left", "right", "internal", "fixed",
        "scientific", "showpoint", "noshowpoint", "showbase", "noshowbase",
        "showpos", "noshowpos", "uppercase", "nouppercase"
};
std::unordered_set<std::string> var = {
};
std::unordered_set<std::string> func = {
    "sqrt", "pow", "sin", "cos", "tan", "abs", "exp", "log", "floor", "ceil", "scanf", "printf", "strlen", "main"
};

std::vector<std::string> keywords = {
    "int", "return", "if", "else", "while", "switch", "case", "default", "scanf", "printf",
    "strlen", "abs", "sqrt", "float", "double", "long", "for", "void", "main", "#include",
    "using namespace std;", "<iostream>", "<cmath>", "<bits/stdc++.h>", "bool", "break"
};

bool showUndoRedoButtons = false;
bool showNewSaveButtons = false;
bool comline1 = false;
bool comline2 = false;

struct FileNode {
    std::string name;
    std::string path;
    bool isFolder;
    std::vector<FileNode> children;
    bool isExpanded;

    FileNode(const std::string& name = "", const std::string& path = "", bool isFolder = false, bool isExpanded = false)
            : name(name), path(path), isFolder(isFolder), isExpanded(isExpanded) {}
};

struct TextChange {
    std::vector<std::string> lines;
    int currentLine;
    int cursorPos;
};

bool compile(const std::string &filename) {
    std::string compileCommand = "g++ " + filename + " -o output";
    int result = std::system(compileCommand.c_str());
    return (result == 0);
}

void run(const std::string &filename) {
#ifdef _WIN32 // Windows
    std::string runCommand = "start cmd /c \"" + filename + ".exe & pause\"";
#elif __linux__ // Linux
    std::string runCommand = "x-terminal-emulator -e \"" + filename + "; read -n 1 -s -r -p 'Press any key to continue...'\"";
#elif __APPLE__ // macOS
    std::string runCommand = "osascript -e 'tell application \"Terminal\" to do script \"" + filename + "\"'";
#else
    std::cerr << "Unsupported operating system." << std::endl;
    return;
#endif
    std::system(runCommand.c_str());
}

bool createDirectory(const std::string& path) {
#ifdef _WIN32
    return _mkdir(path.c_str()) == 0;
#else
    return mkdir(path.c_str(), 0777) == 0;
#endif
}

std::string captureCompilationOutput(const std::string& command) {
    std::string result;
    char buffer[128];
#ifdef _WIN32
    FILE* pipe = _popen(command.c_str(), "r");
#else
    FILE* pipe = popen(command.c_str(), "r");
#endif
    if (!pipe) {
        return "Error: Failed to execute command.";
    }
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
    } catch (...) {
#ifdef _WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
        return "Error: Failed to read command output.";
    }
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    return result;
}

std::vector<std::string> splitIntoWords(const std::string& text) {
    std::vector<std::string> words;
    std::istringstream stream(text);
    std::string word;
    while (stream >> word) {
        words.push_back(word);
    }
    return words;
}

int levenshteinDistance(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)});
            }
        }
    }
    return dp[m][n];
}

bool infunc = false;
bool invar = false;

std::string findClosestKeyword(const std::string& word, const std::vector<std::string>& keywords) {
    std::string closestKeyword;
    int minDistance = INT_MAX;

    std::string cleanedWord;
    for (char ch : word) {
        if (isalnum(ch)) {
            cleanedWord += ch;
        }
    }

    for (const auto& keyword : keywords) {
        int distance = levenshteinDistance(cleanedWord, keyword);
        if (distance < minDistance) {
            minDistance = distance;
            closestKeyword = keyword;
        }
    }

    if (minDistance <= 1 && !invar && !infunc) {
        return closestKeyword;
    }
    return "";
}

std::string optimizeTextswitch(const std::string& text) {
    std::string optimizedText = text;

    std::regex ifElseIfPattern(R"(if\s*\(\s*(\w+)\s*==\s*(\w+)\s*\)\s*\{([^}]+)\}(\s*else\s*if\s*\(\s*(\w+)\s*==\s*(\w+)\s*\)\s*\{([^}]+)\})*\s*else\s*\{([^}]+)\})");
    std::smatch matches;

    if (std::regex_search(optimizedText, matches, ifElseIfPattern)) {
        std::string variable = matches[1].str();
        std::string firstCaseValue = matches[2].str();
        std::string firstBlock = matches[3].str();
        std::string elseBlock = matches[matches.size() - 1].str();

        std::string switchCase = "switch (" + variable + ") {\n";
        switchCase += "    case " + firstCaseValue + ":\n";
        switchCase += "        " + firstBlock + "\n";
        switchCase += "        break;\n";

        for (size_t i = 4; i + 2 < matches.size(); i += 3) {
            std::string elseIfVariable = matches[i + 1].str();
            std::string elseIfCaseValue = matches[i + 2].str();
            std::string elseIfBlock = matches[i + 3].str();

            if (elseIfVariable == variable) {
                switchCase += "    case " + elseIfCaseValue + ":\n";
                switchCase += "        " + elseIfBlock + "\n";
                switchCase += "        break;\n";
            }
        }

        switchCase += "    default:\n";
        switchCase += "        " + elseBlock + "\n";
        switchCase += "        break;\n";
        switchCase += "}";

        optimizedText = std::regex_replace(optimizedText, ifElseIfPattern, switchCase);
    }

    return optimizedText;
}

std::string optimizeTextfor(const std::string& text) {
    std::string optimizedText = text;

    std::regex coutPattern(R"(cout\s*<<\s*\"?(\d+)\"?\s*;\s*)");

    std::smatch matches;
    std::string::const_iterator searchStart(optimizedText.cbegin());
    std::vector<std::pair<size_t, size_t>> matchPositions;
    std::vector<int> coutValues;

    while (std::regex_search(searchStart, optimizedText.cend(), matches, coutPattern)) {
        size_t matchStart = matches.position(0) + std::distance(optimizedText.cbegin(), searchStart);
        size_t matchEnd = matchStart + matches.length(0);
        int value = std::stoi(matches[1].str());

        matchPositions.emplace_back(matchStart, matchEnd);
        coutValues.push_back(value);

        searchStart = matches.suffix().first;
    }

    std::vector<std::pair<size_t, size_t>> coutRanges;
    size_t i = 0;
    while (i < coutValues.size()) {
        size_t j = i;
        while (j + 1 < coutValues.size() && coutValues[j + 1] == coutValues[j] + 1) {
            j++;
        }
        if (j > i) {
            coutRanges.emplace_back(i, j);
        }
        i = j + 1;
    }

    std::string result;
    size_t lastPos = 0;

    for (const auto& range : coutRanges) {
        size_t startIdx = range.first;
        size_t endIdx = range.second;

        size_t startPos = matchPositions[startIdx].first;
        size_t endPos = matchPositions[endIdx].second;

        result += optimizedText.substr(lastPos, startPos - lastPos);

        result += "for (int i = " + std::to_string(coutValues[startIdx]) +
                  "; i <= " + std::to_string(coutValues[endIdx]) + "; i++) {\n";
        result += "    cout << i << endl;\n";
        result += "}\n";

        lastPos = endPos;
    }

    result += optimizedText.substr(lastPos);

    return result;
}

void ensureLastLineVisible(int currentLine, int &scrollOffset, int SCREEN_HEIGHT, int LINE_HEIGHT, int totalLines) {
    int cursorY = currentLine * LINE_HEIGHT - scrollOffset;
    if (cursorY < 0) {
        scrollOffset = currentLine * LINE_HEIGHT;
    } else if (cursorY + LINE_HEIGHT > SCREEN_HEIGHT) {
        scrollOffset = (currentLine + 1) * LINE_HEIGHT - SCREEN_HEIGHT;
    }

    int contentHeight = totalLines * LINE_HEIGHT;
    if (contentHeight > SCREEN_HEIGHT) {
        scrollOffset = std::min(scrollOffset, contentHeight - SCREEN_HEIGHT);
    } else {
        scrollOffset = 0;
    }
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int getCharWidth(TTF_Font* font, char ch) {
    int width = 0;
    TTF_SizeText(font, std::string(1, ch).c_str(), &width, nullptr);
    return width;
}

void renderLine(SDL_Renderer* renderer, TTF_Font* font, const std::string& line, int x, int y) {
    std::string token;
    bool inChar = false;
    bool inString = false;
    bool inComment = false;
    bool inVariable = false;
    bool inFunction = false;
    if (comline2) {
        inComment = true;
    }

    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '(') {
            inFunction = true;
        }
    }

    SDL_Color currentColor = darkmode ? defaultColor2 : defaultColor1;

    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];
        bool end1 = false;
        bool end2 = false;

        // Handle strings
        if (ch == '"' && !inComment) {
            if ( !inString) {
                inString = !inString;
                end1 = true;
            }
            if (!darkmode) {
                currentColor = inString ? darkGreenColor : defaultColor1;
            } else {
                currentColor = inString ? greenColor : defaultColor2;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            if (!end1) {
                inString = !inString;
            }
            continue;
        }

        // Handle char
        if (ch == '\'' && !inComment) {
            if (!inChar) {
                inChar = !inChar;
                end2 = true;
            }
            if (!darkmode) {
                currentColor = inChar ? darkGreenColor : defaultColor1;
            } else {
                currentColor = inChar ? greenColor : defaultColor2;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            if (!end2) {
                inChar = !inChar;
            }
            continue;
        }

        // Handle comments
        if (!inString && !inChar && ch == '/' && i + 1 < line.size() && line[i + 1] == '/') {
            inComment = true;
            if (!darkmode) {
                currentColor = greyColor;
            } else {
                currentColor = darkGreyColor;
            }
        } else if (!inString && !inChar && ch == '/' && i + 1 < line.size() && line[i + 1] == '*') {
            inComment = true;
            comline1 = true;
            if (!darkmode) {
                currentColor = greyColor;
            } else {
                currentColor = darkGreyColor;
            }
        } else if (!inString && !inChar && line[i - 1] == '/' && i - 2 > 0 && line[i - 2] == '*') {
            inComment = false;
            comline1 = false;
            comline2 = false;
            if (!darkmode) {
                currentColor = defaultColor1;
            } else {
                currentColor = defaultColor2;
            }
        }

        if (inComment) {
            if (!darkmode) {
                currentColor = greyColor;
            } else {
                currentColor = darkGreyColor;
            }
        }

        // Handle numbers
        if (!inString && !inChar && !inComment && isdigit(ch)) {
            if (!darkmode) {
                currentColor = purpleColor;
            } else {
                currentColor = orangeColor;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            continue;
        }

        // Handle special characters
        if (!inString && !inChar && !inComment && ( ch == '(' || ch == ')' || ch == '{'|| ch == '}' || ch == '[' || ch == ']')) {
            if (!darkmode) {
                currentColor = darkGoldColor;
            } else {
                currentColor = lightGreyColor;
            }
            inFunction = false;
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            continue;
        }
        if (!inString && !inChar && !inComment && ( ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'  || ch == '!'  || ch == '&' || ch == '|' || ch == '<' || ch == '>')) {
            if (!darkmode) {
                currentColor = zereshkiColor;
            } else {
                currentColor = darkOrangeColor2;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            continue;
        }
        if (!inString && !inChar && !inComment && ( ch == '^' || ch == '~' || ch == '<' || ch == '>' ||ch == ',' || ch == ';' || ch == ':' || ch == '?')) {
            if (!darkmode) {
                currentColor = defaultColor1;
            } else {
                currentColor = defaultColor2;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            continue;
        }
        if (!inString && !inChar && !inComment && ( ch == '#')) {
            if (!darkmode) {
                currentColor = bluefColor;
            } else {
                currentColor = firozeiColor;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            continue;
        }
        if (!inString && !inChar && !inComment && ( ch == '.')) {
            if (!darkmode) {
                currentColor = purpleColor;
            } else {
                currentColor = orangeColor;
            }
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
            continue;
        }

        // Handle keywords
        if (!inString && !inChar && !inComment && (isalpha(ch) || ch == '_')) {
            token += ch;
            if (i + 1 >= line.size() || (!isalpha(line[i + 1]) && line[i + 1] != '_')) {
                if (KEYWORDS1.find(token) != KEYWORDS1.end()) {
                    if (!darkmode) {
                        currentColor = darkBlueColor;
                    } else {
                        currentColor = lightPurpleColor;
                    }
                } else if (KEYWORDS2.find(token) != KEYWORDS2.end()) {
                    if (!darkmode) {
                        currentColor = greenbColor;
                    } else {
                        currentColor = redColor;
                    }
                    inVariable = true;
                } else if (KEYWORDS3.find(token) != KEYWORDS3.end()) {
                    if (!darkmode) {
                        currentColor = bluefColor;
                    } else {
                        currentColor = firozeiColor;
                    }
                } else if (var.find(token) != var.end()) {
                    if (!darkmode) {
                        currentColor = darkRedColor;
                    } else {
                        currentColor = yellowColor;
                    }
                } else if (func.find(token) != func.end()) {
                    if (!darkmode) {
                        currentColor = darkOrangeColor1;
                    } else {
                        currentColor = lightBlueColor;
                    }
                } else {
                    if (!darkmode) {
                        currentColor = defaultColor1;
                    } else {
                        currentColor = defaultColor2;
                    }
                }
                if (KEYWORDS4.find(token) == KEYWORDS4.end() && var.find(token) == var.end() && func.find(token) == func.end()) {
                    std::string closestKeyword = findClosestKeyword(token, keywords);
                    if (!closestKeyword.empty() && closestKeyword != token) {
                        int wordWidth = 0;
                        TTF_SizeText(font, token.c_str(), &wordWidth, nullptr);
                        aalineRGBA(renderer, x, y + 20, x + getCharWidth(font, ch) * token.size(), y + 20, 200, 0, 200, 255);
                    } else if (var.find(token) == var.end() && func.find(token) == func.end() && KEYWORDS4.find(token) == KEYWORDS4.end()) {
                        aalineRGBA(renderer, x, y + 20, x + getCharWidth(font, ch) * token.size(), y + 20, 200, 0, 0, 255);
                    }
                }
                if (inFunction && inVariable) {
                    func.insert(token);
                    var.erase(token);
                } else if (inVariable && KEYWORDS2.find(token) == KEYWORDS2.end() && i + 1 != line.size()) {
                    var.insert(token);
                    func.erase(token);
                }

                renderText(renderer, font, token, x, y, currentColor);
                x += getCharWidth(font, ch) * token.size();
                token.clear();
            }
        } else {
            renderText(renderer, font, std::string(1, ch), x, y, currentColor);
            x += getCharWidth(font, ch);
        }
        invar = inVariable;
        infunc = inFunction;
    }
}

void buildFileTree(FileNode& node, const std::string& path) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile((path + "/*").c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) return;
    bool checkname = false;
    do {
        std::string name = findData.cFileName;
        if (name == "." || name == "..") continue;

        std::string fullPath = path + "/" + name;
        FileNode child(name, fullPath, (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY), false);

        if (child.isFolder) {
            buildFileTree(child, fullPath);
        }
        for (auto k : node.children) {
            if (k.name == child.name) {
                checkname = true;
            }
        }
        if (!checkname) {
            node.children.push_back(child);
        }
    } while (FindNextFile(hFind, &findData) != 0);
    FindClose(hFind);
}

void renderFileTree(SDL_Renderer* renderer, TTF_Font* font, const FileNode& node, int x, int& y, int indent, int LINE_HEIGHT) {
    SDL_Color textColor = {0, 0, 0, 255};
    if (y>=80) {
        if (node.isFolder) {
            std::string displayText = node.isExpanded ? "[-] " + node.name : "[+] " + node.name;
            renderText(renderer, font, displayText, x + indent, y, textColor);
        } else {
            renderText(renderer, font, node.name, x + indent, y, textColor);
        }
    }
    y += LINE_HEIGHT;
    if (node.isFolder && node.isExpanded) {
        for (const auto& child : node.children) {
            renderFileTree(renderer, font, child, x, y, indent + 20, LINE_HEIGHT);
        }
    }
}

void handleFileTreeClick(FileNode& node, int mouseX, int mouseY, int x, int& y, int indent, int LINE_HEIGHT, int& currentLine, int& cursorPos, std::vector<std::string>& lines, std::string& filePath) {
    if (mouseX >= x && mouseX <= x + 280 && mouseY >= y && mouseY <= y + LINE_HEIGHT) {
        if (node.isFolder) {
            node.isExpanded = !node.isExpanded;
        } else {
            var = {};
            func = {
                "sqrt", "pow", "sin", "cos", "tan", "abs", "exp", "log", "floor", "ceil", "scanf", "printf", "strlen", "main"
            };
            std::ifstream file(node.path);
            if (file.is_open()) {
                lines.clear();
                std::string line;
                while (std::getline(file, line)) {
                    lines.push_back(line);
                }
                file.close();
                currentLine = 0;
                cursorPos = 0;
                filePath = node.path;
            } else {
                std::cerr << "Failed to open file: " << node.path << std::endl;
            }
        }
    }
    y += LINE_HEIGHT;

    if (node.isFolder && node.isExpanded) {
        for (auto& child : node.children) {
            handleFileTreeClick(child, mouseX, mouseY, x, y, indent + 20, LINE_HEIGHT, currentLine, cursorPos, lines, filePath);
        }
    }
}

void updateHistory(std::vector<std::string>& lines, int currentLine, int cursorPos, std::vector<TextChange>& history, int& historyIndex) {
    if (historyIndex < history.size() - 1) {
        history.erase(history.begin() + historyIndex + 1, history.end());
    }
    history.push_back({lines, currentLine, cursorPos});
    historyIndex = history.size() - 1;

    const size_t MAX_HISTORY_SIZE = 100;
    if (history.size() > MAX_HISTORY_SIZE) {
        history.erase(history.begin());
        historyIndex--;
    }
}

int main(int argc, char* argv[]) {

    std::vector<TextChange> history;
    int historyIndex = -1;

    FileNode root("cmake-build-debug", "C:\\Users\\Mahyar\\CLionProjects\\untitled\\cmake-build-debug", true, true);
    buildFileTree(root, root.path);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("NUT COMPILER 1.03",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Surface* icon = IMG_Load("C:\\Users\\Mahyar\\CLionProjects\\untitled\\cmake-build-debug\\icon.png");
    SDL_SetWindowIcon(window, icon);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    TTF_Font* font = TTF_OpenFont(R"(C:\Windows\Fonts\consola.ttf)", 24);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    Mix_Music* bgMusic = Mix_LoadMUS("music.mp3");
    if (!bgMusic) {
        std::cerr << "Failed to load music! Mix_Error: " << Mix_GetError() << std::endl;
        Mix_Quit();
        SDL_Quit();
        return -1;
    }

    std::vector<std::string> lines = {""};
    int currentLine = 0;
    int cursorPos = 0;
    int scrollOffset = 0;
    int scrollOffsetSave = 0;
    const int LINE_HEIGHT = TTF_FontHeight(font);

    std::string selectedText = "";

    Uint32 lastCursorToggle = SDL_GetTicks();
    bool cursorVisible = true;
    const Uint32 CURSOR_BLINK_INTERVAL = 500;

    SDL_StartTextInput();

    SDL_Rect playbutton = {960, 10, 50, 40};
    bool isPlaying = false;

    std::string filePath;
    bool isTyping = false;

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > lastCursorToggle + CURSOR_BLINK_INTERVAL) {
            cursorVisible = !cursorVisible;
            lastCursorToggle = currentTime;
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                if (mouseY > 100 && mouseX > 300) {
                    selectionStartLine = std::min((int)((mouseY + scrollOffset - 100) / LINE_HEIGHT), (int)lines.size() - 1);
                    selectionStartPos = 0;

                    int startLine = std::min(selectionStartLine, selectionEndLine);
                    int startPos = (selectionStartLine < selectionEndLine) ? selectionStartPos : selectionEndPos;
                    currentLine = startLine;
                    cursorPos = startPos;

                    for (int i = 0; i < lines[selectionStartLine].size(); ++i) {
                        int charWidth;
                        TTF_SizeText(font, lines[selectionStartLine].substr(0, i + 1).c_str(), &charWidth, nullptr);
                        if (mouseX - 300 < charWidth) {
                            selectionStartPos = i;
                            break;
                        }
                        selectionStartPos = lines[selectionStartLine].size();
                    }
                    selecting = true;
                    selectionEndLine = selectionStartLine;
                    selectionEndPos = selectionStartPos;
                }

                if (mouseX >= 10 && mouseX <= 90 && mouseY >= 10 && mouseY <= 50) {
                    showUndoRedoButtons = !showUndoRedoButtons;
                }

                // Check if the "File" button is clicked
                if (mouseX >= 20 && mouseX <= 100 && mouseY >= 620 && mouseY <= 660) {
                    showNewSaveButtons = !showNewSaveButtons;
                }

                // Check if the "New" button is clicked
                if (showNewSaveButtons && mouseX >= 290 && mouseX <= 340 && mouseY >= 10 && mouseY <= 50) {
                    lines = {""};
                    cursorPos = 0;
                    currentLine = 0;
                    if (!filePath.empty()) {
                        bool cpp = false;
                        for (const auto& k : filePath) {
                            if (k == '.') {
                                cpp = true;
                            }
                        }
                        std::ofstream file(cpp ? filePath : filePath + ".cpp");
                        if (file.is_open()) {
                            for (const auto& line : lines) {
                                file << line << std::endl;
                            }
                            file.close();
                        }
                    }
                    root = {"cmake-build-debug", "C:\\Users\\Mahyar\\CLionProjects\\untitled\\cmake-build-debug", true, true};
                    buildFileTree(root, root.path);
                }

                // Check if the "D/C" button is clicked
                if (mouseX >= 1020 && mouseX <= 1070 && mouseY >= 10 && mouseY <= 50) {
                    std::ofstream outFile("temp.cpp");
                    for (const auto& line : lines) {
                        outFile << line << std::endl;
                    }
                    outFile.close();

                    std::string compileCommand = "g++ temp.cpp -o output 2>&1";
                    std::string compileOutput = captureCompilationOutput(compileCommand);

                    if (compileOutput.empty()) {
                        SDL_Window* compileWindow = SDL_CreateWindow("Compiled Successfully",
                                                                     SDL_WINDOWPOS_CENTERED,
                                                                     SDL_WINDOWPOS_CENTERED,
                                                                     400, 200,
                                                                     SDL_WINDOW_SHOWN);
                        if (!compileWindow) {
                            std::cerr << "Failed to create compile window: " << SDL_GetError() << std::endl;
                            return -1;
                        }

                        SDL_Renderer* compileRenderer = SDL_CreateRenderer(compileWindow, -1, SDL_RENDERER_ACCELERATED);
                        if (!compileRenderer) {
                            std::cerr << "Failed to create compile renderer: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(compileWindow);
                            return -1;
                        }
                        bool compileQuit = false;
                        SDL_Event compileEvent;
                        while (!compileQuit) {
                            SDL_SetRenderDrawColor(compileRenderer, 0, 0, 0, 255);
                            SDL_RenderClear(compileRenderer);

                            renderText(compileRenderer, font, "Compiled Successfully", 20, 20, {0, 255, 0, 255});

                            SDL_RenderPresent(compileRenderer);

                            std::this_thread::sleep_for(std::chrono::seconds(2));
                            compileQuit = true;
                        }

                        SDL_DestroyRenderer(compileRenderer);
                        SDL_DestroyWindow(compileWindow);
                    } else {
                        SDL_Window* errorWindow = SDL_CreateWindow("Compilation Errors",
                                                                   SDL_WINDOWPOS_CENTERED,
                                                                   SDL_WINDOWPOS_CENTERED,
                                                                   1000, 600,
                                                                   SDL_WINDOW_SHOWN);
                        if (!errorWindow) {
                            std::cerr << "Failed to create error window: " << SDL_GetError() << std::endl;
                            return -1;
                        }

                        SDL_Renderer* errorRenderer = SDL_CreateRenderer(errorWindow, -1, SDL_RENDERER_ACCELERATED);
                        if (!errorRenderer) {
                            std::cerr << "Failed to create error renderer: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(errorWindow);
                            return -1;
                        }
                        bool errorQuit = false;
                        SDL_Event errorEvent;
                        while (!errorQuit) {
                            SDL_SetRenderDrawColor(errorRenderer, 0, 0, 0, 255);
                            SDL_RenderClear(errorRenderer);

                            int y = 20;
                            std::string line;
                            std::istringstream errorStream(compileOutput);
                            while (std::getline(errorStream, line)) {
                                renderText(errorRenderer, font, line, 20, y, {255, 0, 0, 255});
                                y += LINE_HEIGHT;
                            }

                            SDL_RenderPresent(errorRenderer);

                            std::this_thread::sleep_for(std::chrono::seconds(10));
                            errorQuit = true;
                        }

                        SDL_DestroyRenderer(errorRenderer);
                        SDL_DestroyWindow(errorWindow);
                    }
                }

                // Check if the "Run" button is clicked
                if (mouseX >= 1080 && mouseX <= 1130 && mouseY >= 10 && mouseY <= 50) {
                    std::ofstream outFile("temp.cpp");
                    for (const auto& line : lines) {
                        outFile << line << std::endl;
                    }
                    outFile.close();

                    std::string compileCommand = "g++ temp.cpp -o output 2>&1";
                    std::string compileOutput = captureCompilationOutput(compileCommand);

                    if (compileOutput.empty()) {
                        SDL_Window* compileWindow = SDL_CreateWindow("Compiled Successfully",
                                                                     SDL_WINDOWPOS_CENTERED,
                                                                     SDL_WINDOWPOS_CENTERED,
                                                                     400, 200,
                                                                     SDL_WINDOW_SHOWN);
                        if (!compileWindow) {
                            std::cerr << "Failed to create compile window: " << SDL_GetError() << std::endl;
                            return -1;
                        }

                        SDL_Renderer* compileRenderer = SDL_CreateRenderer(compileWindow, -1, SDL_RENDERER_ACCELERATED);
                        if (!compileRenderer) {
                            std::cerr << "Failed to create compile renderer: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(compileWindow);
                            return -1;
                        }
                        bool compileQuit = false;
                        SDL_Event compileEvent;
                        while (!compileQuit) {
                            SDL_SetRenderDrawColor(compileRenderer, 0, 0, 0, 255);
                            SDL_RenderClear(compileRenderer);

                            renderText(compileRenderer, font, "Compiled Successfully", 20, 20, {0, 255, 0, 255});

                            SDL_RenderPresent(compileRenderer);

                            std::this_thread::sleep_for(std::chrono::seconds(2));
                            compileQuit = true;
                        }

                        SDL_DestroyRenderer(compileRenderer);
                        SDL_DestroyWindow(compileWindow);

                        run("output");
                    } else {
                        SDL_Window* errorWindow = SDL_CreateWindow("Compilation Errors",
                                                                   SDL_WINDOWPOS_CENTERED,
                                                                   SDL_WINDOWPOS_CENTERED,
                                                                   800, 600,
                                                                   SDL_WINDOW_SHOWN);
                        if (!errorWindow) {
                            std::cerr << "Failed to create error window: " << SDL_GetError() << std::endl;
                            return -1;
                        }

                        SDL_Renderer* errorRenderer = SDL_CreateRenderer(errorWindow, -1, SDL_RENDERER_ACCELERATED);
                        if (!errorRenderer) {
                            std::cerr << "Failed to create error renderer: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(errorWindow);
                            return -1;
                        }
                        bool errorQuit = false;
                        SDL_Event errorEvent;
                        while (!errorQuit) {
                            SDL_SetRenderDrawColor(errorRenderer, 0, 0, 0, 255);
                            SDL_RenderClear(errorRenderer);

                            int y = 20;
                            std::string line;
                            std::istringstream errorStream(compileOutput);
                            while (std::getline(errorStream, line)) {
                                renderText(errorRenderer, font, line, 20, y, {255, 0, 0, 255});
                                y += LINE_HEIGHT;
                            }

                            SDL_RenderPresent(errorRenderer);

                            std::this_thread::sleep_for(std::chrono::seconds(10));
                            errorQuit = true;
                        }

                        SDL_DestroyRenderer(errorRenderer);
                        SDL_DestroyWindow(errorWindow);
                    }
                }

                if (mouseX >= playbutton.x && mouseX <= (playbutton.x + playbutton.w) && mouseY >= playbutton.y && mouseY <= (playbutton.y + playbutton.h)) {
                    if (!isPlaying) {
                        Mix_PlayMusic(bgMusic, -1);
                        isPlaying = true;
                    } else {
                        Mix_HaltMusic();
                        isPlaying = false;
                    }
                }

                // Check if the "Mode" button is clicked
                if (mouseX >= 1140 && mouseX <= 1190 && mouseY >= 10 && mouseY <= 50) {
                    darkmode = !darkmode;
                }

                // Check if the "Exit" button is clicked
                if (showNewSaveButtons && mouseX >= 870 && mouseX <= 950 && mouseY >= 10 && mouseY <= 50) {
                    quit = true;
                }

                // Check if the "Undo" button is clicked
                if (showUndoRedoButtons && mouseX >= 100 && mouseX <= 150 && mouseY >= 10 && mouseY <= 50) {
                    if (historyIndex > 0) {
                        historyIndex--;
                        lines = history[historyIndex].lines;
                        currentLine = history[historyIndex].currentLine;
                        cursorPos = history[historyIndex].cursorPos;
                    }
                }

                // Check if the "Redo" button is clicked
                if (showUndoRedoButtons && mouseX >= 160 && mouseX <= 210 && mouseY >= 10 && mouseY <= 50) {
                    if (historyIndex < history.size() - 1) {
                        historyIndex++;
                        lines = history[historyIndex].lines;
                        currentLine = history[historyIndex].currentLine;
                        cursorPos = history[historyIndex].cursorPos;
                    }
                }

                // Check if the click is within the file tree area
                if (mouseX >= 10 && mouseX <= 280 && mouseY >= 80 && mouseY <= 600) {
                    int treeY = 80 - scrollOffsetSave;
                    handleFileTreeClick(root, mouseX, mouseY, 10, treeY, 0, LINE_HEIGHT, currentLine, cursorPos, lines, filePath);
                }

                // Check if the click is within the input box
                if (showNewSaveButtons) {
                    if (mouseX >= 450 && mouseX <= 850 && mouseY >= 10 && mouseY <= 50) {
                        isTyping = true;
                    } else {
                        isTyping = false;
                    }
                }

                // Check if the click is within the save button
                if (showNewSaveButtons && mouseX >= 350 && mouseX <= 430 && mouseY >= 10 && mouseY <= 50) {
                    if (!filePath.empty()) {
                        bool cpp = false;
                        for (const auto& k : filePath) {
                            if (k == '.') {
                                cpp = true;
                            }
                        }
                        std::ofstream file(cpp ? filePath : filePath + ".cpp");
                        if (file.is_open()) {
                            for (const auto& line : lines) {
                                file << line << std::endl;
                            }
                            file.close();
                        }
                    }
                    root = {"cmake-build-debug", "C:\\Users\\Mahyar\\CLionProjects\\untitled\\cmake-build-debug", true, true};
                    buildFileTree(root, root.path);
                }
            } else if (e.type == SDL_MOUSEMOTION && selecting && e.motion.x >= 300 && e.motion.y >= 100) {
                int mouseY = e.motion.y + scrollOffset;
                selectionEndLine = std::min((int)((mouseY - 100)/ LINE_HEIGHT), (int)lines.size() - 1);
                selectionEndPos = 0;
                int mouseX = e.motion.x;
                for (int i = 0; i < lines[selectionEndLine].size(); ++i) {
                    int charWidth;
                    TTF_SizeText(font, lines[selectionEndLine].substr(0, i + 1).c_str(), &charWidth, nullptr);
                    if (mouseX - 300 < charWidth) {
                        selectionEndPos = i;
                        break;
                    }
                    selectionEndPos = lines[selectionEndLine].size();
                }
            } else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                selecting = false;
            } else if (e.type == SDL_MOUSEWHEEL) {
                int mousex;
                int mousey;
                SDL_GetMouseState(&mousex, &mousey);
                if (mousex > 300 && mousey > 100) {
                    if (e.wheel.y > 0) {
                        scrollOffset = std::max(0, scrollOffset - LINE_HEIGHT);
                    } else if (e.wheel.y < 0) {
                        scrollOffset += LINE_HEIGHT;
                    }
                } else if (mousex > 10 && mousex < 280 && mousey > 100 && mousey < 600) {
                    if (e.wheel.y > 0) {
                        scrollOffsetSave = std::max(0, scrollOffsetSave - LINE_HEIGHT);
                    } else if (e.wheel.y < 0) {
                        scrollOffsetSave += LINE_HEIGHT;
                    }
                }
            } else if (e.type == SDL_KEYDOWN) {

                const Uint8* state = SDL_GetKeyboardState(NULL);

                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (isTyping && !filePath.empty()) {
                        filePath.pop_back();
                    } else if (!isTyping) {
                        if (selectionStartLine != -1 && selectionEndLine != -1 && abs(selectionStartPos - selectionEndPos) > 0) {
                            int startLine = std::min(selectionStartLine, selectionEndLine);
                            int endLine = std::max(selectionStartLine, selectionEndLine);
                            int startPos = (selectionStartLine < selectionEndLine) ? selectionStartPos : selectionEndPos;
                            int endPos = (selectionStartLine < selectionEndLine) ? selectionEndPos : selectionStartPos;
                            if (startLine == endLine) {
                                lines[startLine].erase(startPos, endPos - startPos);
                            } else {
                                lines[startLine].erase(startPos);
                                lines[endLine].erase(0, endPos);
                                lines.erase(lines.begin() + startLine  + 1, lines.begin() + endLine);
                                lines[startLine] += lines[startLine + 1];
                                lines.erase(lines.begin() + startLine + 1);
                            }
                            currentLine = startLine;
                            cursorPos = startPos;
                            selectionStartLine = -1;
                            selectionEndLine = -1;
                            selectionStartPos = -1;
                            selectionEndPos = -1;
                        } else {
                            if (cursorPos > 0 && cursorPos <= lines[currentLine].size()) {
                                lines[currentLine].erase(cursorPos - 1, 1);
                                cursorPos--;
                            } else if (currentLine > 0) {
                                cursorPos = lines[currentLine - 1].size();
                                lines[currentLine - 1] += lines[currentLine];
                                lines.erase(lines.begin() + currentLine);
                                currentLine--;
                            }
                        }
                        updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                        if (lines.empty()) {
                            lines.push_back("");
                            currentLine = 0;
                            cursorPos = 0;
                        }
                    }
                } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    if (gotoLineMode) {
                        gotoLineMode = false;
                    }
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    if (gotoLineMode && !gotoLineInput.empty()) {
                        int targetLine = std::stoi(gotoLineInput);
                        if (targetLine >= 1 && targetLine <= lines.size()) {
                            currentLine = targetLine - 1;
                            cursorPos = 0;
                            ensureLastLineVisible(currentLine, scrollOffset, SCREEN_HEIGHT, LINE_HEIGHT, lines.size());
                        }
                        gotoLineMode = false;
                    } else {
                        int k = 0;
                        if (cursorPos <= lines[currentLine].size()) {
                            for (int i = cursorPos; i >= 3; --i) {
                                if (lines[currentLine][i] == ' ' && lines[currentLine][i - 1] == ' ' && lines[currentLine][i - 2] == ' ' && lines[currentLine][i - 3] == ' ') {
                                    i -= 3;
                                    k++;
                                }
                            }
                            std::string remainder = lines[currentLine].substr(cursorPos);
                            lines[currentLine] = lines[currentLine].substr(0, cursorPos);
                            std::string Tabs = "";
                            for (int i = 0; i < k; ++i) {
                                Tabs += "    ";
                            }
                            lines.insert(lines.begin() + currentLine + 1, Tabs + remainder);
                            currentLine++;
                            cursorPos = 4 * k;
                            ensureLastLineVisible(currentLine, scrollOffset, SCREEN_HEIGHT, LINE_HEIGHT, lines.size());
                            updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                        }
                    }
                } else if (e.key.keysym.sym == SDLK_TAB) {
                    if (state[SDL_SCANCODE_LCTRL]) {
                        std::string currentLineText = lines[currentLine];
                        int wordStart = cursorPos - 1;
                        while (wordStart >= 0 && !isspace(currentLineText[wordStart])) {
                            wordStart--;
                        }
                        wordStart++;

                        std::string currentWord = currentLineText.substr(wordStart, cursorPos - wordStart);

                        std::string bestMatch = "";
                        for (const auto& keyword : keywords) {
                            if (keyword.find(currentWord) == 0) {
                                if (bestMatch.empty() || keyword.length() < bestMatch.length()) {
                                    bestMatch = keyword;
                                }
                            }
                        }

                        if (!bestMatch.empty()) {
                            lines[currentLine].erase(wordStart, cursorPos - wordStart);
                            lines[currentLine].insert(wordStart, bestMatch);
                            cursorPos = wordStart + bestMatch.length();
                        }
                    } else {
                        lines[currentLine].insert(cursorPos, "    ");
                        cursorPos += 4;
                    }
                    updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                } else if (state[SDL_SCANCODE_LCTRL]) {
                    if (e.key.keysym.sym == SDLK_n ) {  // Ctrl + N (Fix Spelling Errors)
                        for (size_t i = 0; i < lines.size(); i++) {
                            std::string& line = lines[i];
                            std::vector<std::string> words = splitIntoWords(line);

                            std::string correctedLine;
                            for (size_t j = 0; j < words.size(); j++) {
                                std::string& word = words[j];
                                std::string closestKeyword = findClosestKeyword(word, keywords);

                                if (!closestKeyword.empty() && closestKeyword != word) {
                                    word = closestKeyword;
                                }

                                correctedLine += word;
                                if (j < words.size() - 1) {
                                    correctedLine += " ";
                                }
                            }

                            lines[i] = correctedLine;
                        }

                        cursorPos = std::min(cursorPos, (int)lines[currentLine].size());

                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderClear(renderer);

                        SDL_Color textColor = {0, 0, 0, 255};
                        int y = -scrollOffset;

                        for (size_t i = 0; i < lines.size(); ++i) {
                            if (y + LINE_HEIGHT > 0 && y < SCREEN_HEIGHT) {
                                if (lines[i].empty()) {
                                    lines[i] = " ";
                                }
                                SDL_Surface* textSurface = TTF_RenderText_Blended(font, lines[i].c_str(), textColor);
                                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

                                int textWidth = textSurface->w;
                                int textHeight = textSurface->h;
                                SDL_Rect renderQuad = {10, y, textWidth, textHeight};

                                SDL_FreeSurface(textSurface);
                                SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
                                SDL_DestroyTexture(textTexture);

                                if (i == currentLine) {
                                    int cursorX = 0;
                                    if (cursorPos > 0) {
                                        TTF_SizeText(font, lines[i].substr(0, cursorPos).c_str(), &cursorX, nullptr);
                                    }
                                    cursorX += 10;
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                    SDL_RenderDrawLine(renderer, cursorX, y, cursorX, y + LINE_HEIGHT);
                                }
                            }
                            y += LINE_HEIGHT;
                        }
                        updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                        SDL_RenderPresent(renderer);
                    } else if (e.key.keysym.sym == SDLK_z) {  // Ctrl + Z (Undo)
                        if (historyIndex > 0) {
                            historyIndex--;
                            lines = history[historyIndex].lines;
                            currentLine = history[historyIndex].currentLine;
                            cursorPos = history[historyIndex].cursorPos;
                        }
                    } else if (e.key.keysym.sym == SDLK_m) {  // Ctrl + M (Optimize Text For)
                        std::string fullText;
                        for (const auto& line : lines) {
                            fullText += line + "\n";
                        }

                        std::string optimizedText = optimizeTextfor(fullText);

                        lines.clear();
                        size_t pos = 0;
                        while ((pos = optimizedText.find('\n')) != std::string::npos) {
                            lines.push_back(optimizedText.substr(0, pos));
                            optimizedText.erase(0, pos + 1);
                        }
                        if (!optimizedText.empty()) {
                            lines.push_back(optimizedText);
                        }
                        cursorPos = std::min(cursorPos, (int)lines[currentLine].size());
                        currentLine = lines.size() - 1;
                        updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                    } else if (e.key.keysym.sym == SDLK_b) {  // Ctrl + B (Optimize Text Switch)
                        std::string fullText;
                        for (const auto& line : lines) {
                            fullText += line + "\n";
                        }

                        std::string optimizedText = optimizeTextswitch(fullText);

                        lines.clear();
                        size_t pos = 0;
                        while ((pos = optimizedText.find('\n')) != std::string::npos) {
                            lines.push_back(optimizedText.substr(0, pos));
                            optimizedText.erase(0, pos + 1);
                        }
                        if (!optimizedText.empty()) {
                            lines.push_back(optimizedText);
                        }
                        cursorPos = std::min(cursorPos, (int)lines[currentLine].size());
                        currentLine = lines.size() - 1;
                        updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                    } else if (e.key.keysym.sym == SDLK_c) {  // Ctrl + C (Copy)
                        if (selectionStartLine != -1 && selectionEndLine != -1) {
                            int startLine = std::min(selectionStartLine, selectionEndLine);
                            int endLine = std::max(selectionStartLine, selectionEndLine);
                            int startPos = (selectionStartLine < selectionEndLine) ? selectionStartPos : selectionEndPos;
                            int endPos = (selectionStartLine < selectionEndLine) ? selectionEndPos : selectionStartPos;
                            std::string selectedText = "";
                            for (int i = startLine; i <= endLine; ++i) {
                                int lineStart = (i == startLine) ? startPos : 0;
                                int lineEnd = (i == endLine) ? endPos : lines[i].size();
                                selectedText += lines[i].substr(lineStart, lineEnd - lineStart);
                                if (i != endLine) selectedText += '\n';
                            }
                            SDL_SetClipboardText(selectedText.c_str());
                        }
                    } else if (e.key.keysym.sym == SDLK_x) {  // Ctrl + X (Cut)
                        if (selectionStartLine != -1 && selectionEndLine != -1) {
                            int startLine = std::min(selectionStartLine, selectionEndLine);
                            int endLine = std::max(selectionStartLine, selectionEndLine);
                            int startPos = (selectionStartLine < selectionEndLine) ? selectionStartPos : selectionEndPos;
                            int endPos = (selectionStartLine < selectionEndLine) ? selectionEndPos : selectionStartPos;
                            std::string selectedText = "";
                            for (int i = startLine; i <= endLine; ++i) {
                                int lineStart = (i == startLine) ? startPos : 0;
                                int lineEnd = (i == endLine) ? endPos : lines[i].size();
                                selectedText += lines[i].substr(lineStart, lineEnd - lineStart);
                                if (i != endLine) selectedText += '\n';
                            }
                            SDL_SetClipboardText(selectedText.c_str());
                            if (startLine == endLine) {
                                lines[startLine].erase(startPos, endPos - startPos);
                            } else {
                                lines[startLine].erase(startPos);
                                lines[endLine].erase(0, endPos);
                                lines.erase(lines.begin() + startLine  + 1, lines.begin() + endLine);
                                lines[startLine] += lines[startLine + 1];
                                lines.erase(lines.begin() + startLine + 1);
                            }
                            currentLine = startLine;
                            cursorPos = startPos;
                            selectionStartLine = -1;
                            selectionEndLine = -1;
                            selectionStartPos = -1;
                            selectionEndPos = -1;
                        }
                    } else if (e.key.keysym.sym == SDLK_v) {  // Ctrl + V (Paste)
                        char* clipboardText = SDL_GetClipboardText();
                        if (clipboardText && strlen(clipboardText) > 0) {
                            std::string pasteText(clipboardText);
                            SDL_free(clipboardText);

                            size_t pos = 0;
                            size_t prev = 0;

                            while ((pos = pasteText.find('\n', prev)) != std::string::npos) {
                                std::string linePart = pasteText.substr(prev, pos - prev - 1);
                                lines[currentLine].insert(cursorPos, linePart);
                                cursorPos += linePart.length();

                                std::string remainder = lines[currentLine].substr(cursorPos);
                                lines[currentLine] = lines[currentLine].substr(0, cursorPos);
                                lines.insert(lines.begin() + currentLine + 1, remainder);

                                currentLine++;
                                cursorPos = 0;

                                prev = pos + 1;
                            }

                            std::string remainingText = pasteText.substr(prev);
                            lines[currentLine].insert(cursorPos, remainingText);
                            cursorPos += remainingText.length();

                            ensureLastLineVisible(currentLine, scrollOffset, SCREEN_HEIGHT, LINE_HEIGHT, lines.size());
                        }
                    } else if (e.key.keysym.sym == SDLK_s) {  // Ctrl + S (Save)
                        if (!filePath.empty()) {
                            std::ofstream file(filePath + ".cpp");
                            if (file.is_open()) {
                                for (const auto& line : lines) {
                                    file << line << std::endl;
                                }
                                file.close();
                            }
                            root = {"cmake-build-debug", "C:\\Users\\Mahyar\\CLionProjects\\untitled\\cmake-build-debug", true, true};
                            buildFileTree(root, root.path);
                        }
                    } else if (e.key.keysym.sym == SDLK_g) { // Ctrl + G (Go to line)
                        gotoLineMode = true;
                        gotoLineInput = "";
                    } else if (e.key.keysym.sym == SDLK_a) { // Ctrl + A (select all)
                        selectionStartLine = 0;
                        selectionStartPos = 0;
                        selectionEndLine = lines.size() - 1;
                        selectionEndPos = lines[selectionEndLine].size();
                    }
                } else if (e.key.keysym.sym == SDLK_LEFT) {
                    if (cursorPos > 0) {
                        cursorPos--;
                    } else if (currentLine > 0) {
                        currentLine--;
                        cursorPos = lines[currentLine].size();
                    }
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    if (cursorPos < lines[currentLine].size()) {
                        cursorPos++;
                    } else if (currentLine < lines.size() - 1) {
                        currentLine++;
                        cursorPos = 0;
                    }
                } else if (e.key.keysym.sym == SDLK_UP) {
                    if (currentLine > 0) {
                        currentLine--;
                        cursorPos = std::min(cursorPos, (int)lines[currentLine].size());
                        ensureLastLineVisible(currentLine, scrollOffset, SCREEN_HEIGHT, LINE_HEIGHT, lines.size());
                    }
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    if (currentLine < lines.size() - 1) {
                        currentLine++;
                        cursorPos = std::min(cursorPos, (int)lines[currentLine].size());
                        ensureLastLineVisible(currentLine, scrollOffset, SCREEN_HEIGHT, LINE_HEIGHT, lines.size());
                    }
                }
            } else if (e.type == SDL_TEXTINPUT) {
                if (e.text.text) {
                    if (isTyping) {
                        filePath += e.text.text;
                    } else if (gotoLineMode) {
                        if (isdigit(e.text.text[0])) {
                            gotoLineInput += e.text.text[0];
                        }
                    } else {
                        lines[currentLine].insert(cursorPos, e.text.text);
                        cursorPos += strlen(e.text.text);
                        if (cursorPos >= 68) {
                            lines.insert(lines.begin() + currentLine + 1, "");
                            currentLine ++;
                            cursorPos = 0;
                        }
                        if (e.text.text[0] == '(') {
                            lines[currentLine].insert(cursorPos, ")");
                        }
                        if (e.text.text[0] == '{') {
                            lines[currentLine].insert(cursorPos, "}");
                        }
                        if (e.text.text[0] == '[') {
                            lines[currentLine].insert(cursorPos, "]");
                        }
                        if (e.text.text[0] == '"') {
                            lines[currentLine].insert(cursorPos, "\"");
                        }
                        if (e.text.text[0] == '\'') {
                            lines[currentLine].insert(cursorPos, "\'");
                        }
                        ensureLastLineVisible(currentLine, scrollOffset, SCREEN_HEIGHT, LINE_HEIGHT, lines.size());
                        updateHistory(lines, currentLine, cursorPos, history, historyIndex);
                    }
                }
            }
        }

        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 115, 123, 200, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 29, 45, 73, 255);
        }
        SDL_RenderClear(renderer);

        // Render "Edit" button
        SDL_Rect editButton = {10, 10, 80, 40};
        SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
        SDL_RenderFillRect(renderer, &editButton);
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &editButton);

        renderText(renderer, font, "Edit", 24, 20, {0, 0, 0, 255});

        // Render "Undo" and "Redo" buttons if visible
        if (showUndoRedoButtons) {
            SDL_Rect undoButton = {100, 10, 50, 40};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &undoButton);
            renderText(renderer, font, "[<]", 105, 20, {0, 0, 0, 255});

            SDL_Rect redoButton = {160, 10, 50, 40};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &redoButton);
            renderText(renderer, font, "[>]", 165, 20, {0, 0, 0, 255});

            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &undoButton);

            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &redoButton);
        }

        if (showNewSaveButtons) {
            // Draw the input box
            SDL_Rect inputBoxRect = {450, 10, 400, 40};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &inputBoxRect);
            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &inputBoxRect);

            // Render the file path text
            std::string displayText = filePath.empty() ? std::string("Enter file path") : filePath;
            renderText(renderer, font, displayText, 460, 20, {0, 0, 0, 255});
            SDL_Rect cover = {850, 10, 400, 40};
            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 115, 123, 200, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 29, 45, 73, 255);
            }
            SDL_RenderFillRect(renderer, &cover);

            // Draw the save button
            SDL_Rect saveButtonRect = {350, 10, 80, 40};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &saveButtonRect);
            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &saveButtonRect);

            // Render the save button text
            renderText(renderer, font, "Save", 364, 20, {0, 0, 0, 255});

            // Draw the new file button
            SDL_Rect newButtonRect = {260, 10, 80, 40};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &newButtonRect);
            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &newButtonRect);

            // Render the new file button text
            renderText(renderer, font, "New", 269, 20, {0, 0, 0, 255});

            // Draw the exit button
            SDL_Rect exitButton = {870, 10, 80, 40};
            SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            SDL_RenderFillRect(renderer, &exitButton);
            if (!darkmode) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderDrawRect(renderer, &exitButton);

            renderText(renderer, font, "Exit", 884, 20, {0, 0, 0, 255});
        }

        // Render the mode button
        SDL_Rect modeButton = {1140, 10, 50, 40};
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &modeButton);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &modeButton);

            renderText(renderer, font, "[L]", 1145, 20, {255, 255, 255, 255});
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &modeButton);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &modeButton);

            renderText(renderer, font, "[D]", 1145, 20, {0, 0, 0, 255});
        }

        // Render debug/compile and run buttons
        SDL_Rect CompileButton = {1020, 10, 50, 40};
        SDL_SetRenderDrawColor(renderer, 100, 50, 40, 255);
        SDL_RenderFillRect(renderer, &CompileButton);
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &CompileButton);

        renderText(renderer, font, "D/C", 1026, 20, {255, 255, 255, 255});

        SDL_Rect RunButton = {1080, 10, 50, 40};
        SDL_SetRenderDrawColor(renderer, 0, 140, 0, 255);
        SDL_RenderFillRect(renderer, &RunButton);
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &RunButton);

        renderText(renderer, font, "RUN", 1086, 20, {0, 0, 0, 255});

        // Draw the sidebar background
        SDL_Rect sidebarRect = {10, 80, 270, 600};
        SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
        SDL_RenderFillRect(renderer, &sidebarRect);

        // Draw the file tree
        int treeY = 80 - scrollOffsetSave;
        renderFileTree(renderer, font, root, 10, treeY, 0, LINE_HEIGHT);

        // Draw the file button
        SDL_Rect fileRect = {10, 600, 270, 80};
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &fileRect);

        SDL_Rect fileButton = {20, 620, 80, 40};
        SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
        SDL_RenderFillRect(renderer, &fileButton);

        renderText(renderer, font, "File", 34, 630, {0, 0, 0, 255});

        // Set button color based on music state
        if (isPlaying) SDL_SetRenderDrawColor(renderer, 0, 170, 0, 255);
        else SDL_SetRenderDrawColor(renderer, 170, 0, 0, 255);

        // Draw play button
        SDL_RenderFillRect(renderer, &playbutton);
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &playbutton);

        // Draw play button text
        SDL_Color textColor = {0, 0, 0, 255};
        std::string buttonText = isPlaying ? "stop" : "play";
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, buttonText.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_Rect textRect = {playbutton.x + (playbutton.w - textWidth) / 2, playbutton.y + (playbutton.h - textHeight) / 2, textWidth, textHeight};

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        // Design
        SDL_Rect textback = {290, 80, 900, 600};
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        SDL_RenderFillRect(renderer, &textback);

        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &textback);

        SDL_Rect coverr = {280, 80, 10, 600};
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 115, 123, 200, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 29, 45, 73, 255);
        }
        SDL_RenderFillRect(renderer, &coverr);

        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawRect(renderer, &fileRect);
        SDL_RenderDrawRect(renderer, &fileButton);
        SDL_RenderDrawRect(renderer, &sidebarRect);

        if (gotoLineMode) {
            SDL_Color promptColor = {255, 0, 0, 255};
            std::string promptText = "Go to Line: " + gotoLineInput;

            SDL_Surface* promptSurface = TTF_RenderText_Blended(font, promptText.c_str(), promptColor);
            SDL_Texture* promptTexture = SDL_CreateTextureFromSurface(renderer, promptSurface);

            SDL_Rect promptRect = {105, SCREEN_HEIGHT - 70, promptSurface->w, promptSurface->h};
            SDL_RenderCopy(renderer, promptTexture, NULL, &promptRect);

            SDL_FreeSurface(promptSurface);
            SDL_DestroyTexture(promptTexture);
        }

        // Highlight selected text
        if (selectionStartLine != -1 && selectionEndLine != -1) {
            int startLine = std::min(selectionStartLine, selectionEndLine);
            int endLine = std::max(selectionStartLine, selectionEndLine);
            int startPos = (selectionStartLine < selectionEndLine) ? selectionStartPos : selectionEndPos;
            int endPos = (selectionStartLine < selectionEndLine) ? selectionEndPos : selectionStartPos;
            for (int i = startLine; i <= endLine; ++i) {
                int lineStart = (i == startLine) ? startPos : 0;
                int lineEnd = (i == endLine) ? endPos : lines[i].size();
                int startX = 0;
                if (lineStart > 0) {
                    TTF_SizeText(font, lines[i].substr(0, lineStart).c_str(), &startX, nullptr);
                }
                int endX = startX;
                if (lineEnd > lineStart) {
                    TTF_SizeText(font, lines[i].substr(lineStart, lineEnd - lineStart).c_str(), &endX, nullptr);
                    endX += startX;
                }
                SDL_Rect selectionRect = {startX + 300, i * LINE_HEIGHT - scrollOffset + 100, endX - startX, LINE_HEIGHT};
                if (!darkmode) {
                    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 230, 255);
                }
                SDL_RenderFillRect(renderer, &selectionRect);
            }
        }

        comline1 = false;
        comline2 = false;
        int y = TEXT_AREA_Y - scrollOffset;
        for (size_t i = 0; i < lines.size(); ++i) {
            if (y + LINE_HEIGHT > TEXT_AREA_Y && y < TEXT_AREA_Y + TEXT_AREA_HEIGHT) {

                renderLine(renderer, font, lines[i], TEXT_AREA_X, y);

                if (comline1) {
                    comline2 = true;
                } else {
                    comline2 = false;
                }

                if (i == currentLine && cursorVisible) {
                    int cursorX = TEXT_AREA_X;
                    if (cursorPos > 0) {
                        TTF_SizeText(font, lines[i].substr(0, cursorPos).c_str(), &cursorX, nullptr);
                        cursorX += TEXT_AREA_X;
                    }
                    if (!darkmode) {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    }
                    SDL_RenderDrawLine(renderer, cursorX, y, cursorX, y + LINE_HEIGHT);
                }
            }
            y += LINE_HEIGHT;
        }

        SDL_Rect coverd = {10, 680, 1190, 20};
        if (!darkmode) {
            SDL_SetRenderDrawColor(renderer, 115, 123, 200, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 29, 45, 73, 255);
        }
        SDL_RenderFillRect(renderer, &coverd);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

//