// Header.h
// Центральный заголовочный файл проекта «Top-K самых частых слов через префиксное дерево»
// Подключаем один раз — во всех .cpp файлах включаем только его.
#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <conio.h>
#include <Windows.h>

namespace fs = std::filesystem;               // как у тебя везде

#include "Struct.h"                            // структуры проекта
#include "trie.h"                              // главное префиксное дерево
#include "utils.h"                             // твои классические утилиты
#include "file_reader.h"                       // чтение файлов и нормализация
#include "menu.h"                              // все меню и ввод пользователя
#include "output.h"                            // красивый вывод и сохранение