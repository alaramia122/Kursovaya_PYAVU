// Struct.h
// Все структуры данных проекта. Чисто, без реализации.
#pragma once

// Узел префиксного дерева
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;   // символ → следующий узел
    int                count;                       // сколько раз слово закончилось здесь
    std::vector<std::string> documents;             // имена файлов, где встретилось слово

    TrieNode() : count(0) {}
};

// Результат «слово + частота»
struct WordFrequency {
    std::string               word;       // слово в нижнем регистре
    int                       frequency;  // сколько раз встретилось
    std::vector<std::string> documents;  // в каких файлах (если нужен режим «все файлы»)

    // Для сортировки по убыванию частоты (и по алфавиту при равенстве)
    bool operator<(const WordFrequency& other) const {
        if (frequency != other.frequency)
            return frequency > other.frequency;
        return word < other.word;
    }
};

// Твоя классическая структура ввода с клавиатуры
struct Input_data {
    bool Esc_controller = false;
    bool Enter_controller = false;
    bool Left_controller = false;
    bool Right_controller = false;
    bool Up_controller = false;
    bool Down_controller = false;
    bool Del_controller = false;
    std::string result;

    Input_data() = default;   // всё обнуляется автоматически
};

// Режимы сортировки результата
enum class SortMode {
    ByFrequency,     // по убыванию частоты (по умолчанию)
    Alphabetical,    // по алфавиту
    NoSort           // как собралось в Trie (порядок обхода)
};