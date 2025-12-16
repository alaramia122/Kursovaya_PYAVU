// file_reader.h
// Чтение файлов и подготовка слов.
// Только функции — никакого состояния.
#pragma once


// Читает один конкретный файл и заносит все слова в дерево
void read_single_file(const std::string& filename, Trie& trie);

// Читает ВСЕ .txt файлы из папки SourceTexts
void read_all_files_in_folder(Trie& trie);

// Приводит слово к «чистому» виду: только кириллица, нижний регистр, без пунктуации
std::string normalize_word(const std::string& raw);

