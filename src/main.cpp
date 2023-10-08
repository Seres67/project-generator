#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_set>

std::string add_leading_slash(const std::string &name)
{
    if (name.back() == '/') return name;
    return std::string(name + "/");
}

void setup_directories(const std::string &name)
{
    std::filesystem::create_directories(name);
    std::filesystem::create_directory(name + "/include");
    std::filesystem::create_directory(name + "/src");
    std::cout << "Created project, source and header directories!" << std::endl;
}

void setup_main_c(const std::string &name)
{
    std::ofstream file;
    file.open("./" + name + "/src/main.c");
    file << "#include <stdio.h>" << std::endl << std::endl;
    file << "int main(int ac, char **av)" << std::endl;
    file << "{" << std::endl;
    file << "    printf(\"Hello world!\\n\");" << std::endl;
    file << "    return 0;" << std::endl;
    file << "}" << std::endl;
    file.close();
    std::cout << "Created src/main.c with a hello world!" << std::endl;
}

void setup_main_cpp(const std::string &name)
{
    std::ofstream file;
    file.open("./" + name + "/src/main.cpp");
    file << "#include <iostream>" << std::endl << std::endl;
    file << "int main(int ac, char *av[])" << std::endl;
    file << "{" << std::endl;
    file << "    std::cout << \"Hello world!\" << std::endl;" << std::endl;
    file << "}" << std::endl;
    file.close();
    std::cout << "Created src/main.cpp with a hello world!" << std::endl;
}

void setup_meson(const std::string &name, const std::string &lang)
{
    std::ofstream file;
    file.open("./" + name + "/meson.build");
    file << "project('" << name << "', '" << lang << "')" << std::endl;
    file << "src = ['src/main." << lang << "']" << std::endl;
    file << "executable('" << name << "', src)" << std::endl;
    file.close();
    std::cout << "Created meson.build file!" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "USAGE: project-generator <language> <name>" << std::endl;
    }
    std::string lang(argv[1]);
    std::cout << "argv[1] = " << argv[1] << std::endl;
    std::unordered_set<std::string> langs{"c", "cpp", "c++"};
    if (!langs.contains(lang)) {
        std::cout << "Language not supported yet!" << std::endl;
        return 0;
    }
    std::string name(argv[2]);
    setup_directories(name);
    if (lang == "c") {
        setup_main_c(name);
    } else if (lang == "c++" || lang == "cpp") {
        setup_main_cpp(name);
    }
    setup_meson(name, lang);
    return 0;
}
