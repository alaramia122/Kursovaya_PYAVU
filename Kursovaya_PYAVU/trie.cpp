// trie.cpp
// Реализация префиксного дерева — сердце проекта.

#include "Header.h"

Trie::Trie() {
    root = new TrieNode();                                      // создаём корневой узел
    std::cout << "[OK] Префиксное дерево создано.\n";
}

Trie::~Trie() {
    delete_subtree(root);                                       // чистим всю память
    std::cout << "[OK] Префиксное дерево удалено.\n";
}

void Trie::insert(const std::string& word, const std::string& document_name) {
    if (word.empty())                                           // защита от пустых слов
        return;

    TrieNode* current = root;

    // Проходим по каждому символу слова
    for (char c : word) {
        // Если символа ещё нет — создаём новый узел
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        // Переходим к следующему узлу
        current = current->children[c];
    }

    // Дошли до конца слова
    current->count++;                                           // увеличиваем счётчик окончаний
    // Добавляем имя файла (если ещё не добавляли)
    if (std::find(current->documents.begin(), current->documents.end(), document_name)
        == current->documents.end()) {
        current->documents.push_back(document_name);
    }
}

void Trie::collect_words_recursive(TrieNode* node,
    std::string current_word,
    std::vector<WordFrequency>& result,
    bool include_documents) const {
    // Если в этом узле закончилось слово — сохраняем его
    if (node->count > 0) {
        WordFrequency wf;
        wf.word = current_word;
        wf.frequency = node->count;
        if (include_documents) {
            wf.documents = node->documents;                     // копируем список файлов
        }
        result.push_back(wf);
    }

    // Рекурсивно обходим всех детей
    for (std::unordered_map<char, TrieNode*>::const_iterator it = node->children.begin();
        it != node->children.end(); ++it) {
        char next_char = it->first;
        TrieNode* child = it->second;
        collect_words_recursive(child, current_word + next_char, result, include_documents);
    }
}

std::vector<WordFrequency> Trie::get_top_k(int k, bool include_documents) const {
    std::vector<WordFrequency> all_words;

    // Собираем ВСЕ слова из дерева
    collect_words_recursive(root, "", all_words, include_documents);

    // Сортируем по убыванию частоты
    std::sort(all_words.begin(), all_words.end());

    // Берём только первые k (или меньше, если слов мало)
    std::vector<WordFrequency> top;
    int limit = (k < 0) ? 0 : k;
    for (int i = 0; i < limit and i < static_cast<int>(all_words.size()); ++i) {
        top.push_back(all_words[i]);
    }

    return top;
}

void Trie::delete_subtree(TrieNode* node) {
    if (node == nullptr)
        return;

    // Сначала удаляем всех детей
    for (std::unordered_map<char, TrieNode*>::iterator it = node->children.begin();
        it != node->children.end(); ++it) {
        delete_subtree(it->second);
    }

    // Потом удаляем сам узел
    delete node;
}

void Trie::clear() {
    delete_subtree(root);                                       // удаляем всё поддерево
    root = new TrieNode();                                      // создаём новый чистый корень
    std::cout << "[OK] Дерево очищено.\n";
}

int Trie::total_unique_words() const {
    std::vector<WordFrequency> all;
    collect_words_recursive(root, "", all, false);
    return static_cast<int>(all.size());
}

int Trie::total_occurrences() const {
    // Считаем сумму всех count в листьях и промежуточных узлах
    int total = 0;
    std::vector<WordFrequency> all;
    collect_words_recursive(root, "", all, false);
    for (std::vector<WordFrequency>::const_iterator it = all.begin(); it != all.end(); ++it) {
        total += it->frequency;
    }
    return total;
}