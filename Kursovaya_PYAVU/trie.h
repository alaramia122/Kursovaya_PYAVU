// trie.h
// Главный класс проекта — префиксное дерево.
// Содержит ВСЁ, что нужно: вставку, сбор Top-K, очистку.
#pragma once

class Trie {
private:
    TrieNode* root;

    // Рекурсивные помощники — скрыты от внешнего мира
    void collect_words_recursive(TrieNode* node,
        std::string current_word,
        std::vector<WordFrequency>& result,
        bool include_documents) const;

    void delete_subtree(TrieNode* node);                 // освобождение памяти

public:
    Trie();                                              // создаёт корень
    ~Trie();                                             // автоматически чистит всё

    // Вставляем слово из конкретного документа
    void insert(const std::string& word, const std::string& document_name);

    // Основная «фишка» проекта — получаем Top-K самых частых слов
    std::vector<WordFrequency> get_top_k(int k,
        bool include_documents = false) const;

    // Полезные утилиты
    void clear();                                        // полная очистка дерева
    int  total_unique_words() const;                     // сколько разных слов
    int  total_occurrences() const;                      // сколько всего вставок (с повторениями)
};