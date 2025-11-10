#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem> // 需要 C++17
#include <sstream>
#include <cctype> // for isspace
// 为了方便使用 std::filesystem
namespace fs = std::filesystem;
// 辅助函数：移除字符串左侧的空白字符 (空格, tab等)
std::string trim_left(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\n\r\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}
int main() {
  // 1. 定义目标头文件和要查找的 include 指令前缀
  const std::string header_to_replace = "z.h";
  const std::string include_directive_prefix = "#include \"" + header_to_replace + "\"";
  // 2. 读取 z.h 文件的全部内容
  std::ifstream header_file(header_to_replace);
  if (!header_file.is_open()) {
    std::cerr << "错误: 无法打开头文件 '" << header_to_replace << "'。请确保它在当前目录下。\n";
    return 1;
  }
  std::stringstream buffer;
  buffer << header_file.rdbuf();
  const std::string header_content = buffer.str();
  header_file.close();
  std::cout << "成功读取 '" << header_to_replace << "' 的内容。\n\n";
  // 3. 查找当前目录下所有的 .cpp 文件
  std::vector<fs::path> cpp_files;
  try {
    for (const auto &entry : fs::directory_iterator(".")) {
      if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
        if (entry.path().filename() != "R.cpp") {
          // 排除自己
          cpp_files.push_back(entry.path());
        }
      }
    }
  } catch (const fs::filesystem_error &e) {
    std::cerr << "错误: 遍历目录时出错: " << e.what() << std::endl;
    return 1;
  }
  // 4. 逐个处理找到的 .cpp 文件
  int files_processed = 0;
  for (const auto &input_path : cpp_files) {
    std::ifstream input_file(input_path);
    if (!input_file.is_open()) {
      std::cerr << "警告: 无法打开输入文件 '" << input_path.string() << "'，已跳过。\n";
      continue;
    }
    bool found_include = false;
    std::stringstream new_content_stream; // 在内存中构建新文件的内容
    std::string current_line;
    while (std::getline(input_file, current_line)) {
      // 移除行首的空白字符，以应对缩进
      std::string trimmed_line = trim_left(current_line);
      // 检查处理后的行是否以我们的目标指令开头
      // 使用 rfind(prefix, 0) == 0 判断是否以 prefix 开头
      if (trimmed_line.rfind(include_directive_prefix, 0) == 0) {
        found_include = true;
        // 替换为头文件内容
        new_content_stream << header_content;
        // 确保头文件内容后有一个换行符
        if (!header_content.empty() && header_content.back() != '\n') {
          new_content_stream << '\n';
        }
      } else {
        // 保持原始行不变
        new_content_stream << current_line << '\n';
      }
    }
    input_file.close();
    // 只有在找到了 include 指令的情况下，才写入新文件
    if (found_include) {
      std::string output_filename_str = input_path.stem().string() + "_replace.cpp";
      std::ofstream output_file(output_filename_str);
      if (!output_file.is_open()) {
        std::cerr << "警告: 无法创建输出文件 '" << output_filename_str << "'，已跳过。\n";
        continue;
      }
      output_file << new_content_stream.str();
      output_file.close();
      std::cout << "已处理: " << input_path.string() << " -> " << output_filename_str << "\n";
      files_processed++;
    } else {
      std::cout << "已跳过: " << input_path.string() << " (未找到 '" << include_directive_prefix << "')\n";
    }
  }
  std::cout << "\n处理完成！共生成 " << files_processed << " 个新文件。\n";
  return 0;
}
