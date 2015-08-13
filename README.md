Parse command-line options (C++11).


# Examples

```c++
int main(int ac, char ** av) {
    namespace po = program_options;

    std::string in;

    po::options_description desc({
        {'v', "verbose", "For more verbose basic debugging"},
        {"no-message", "Suppress error"},
        {'a', "Build all targets"},
        {'x' "xxx", ""/*no desciption*/},
        {"in", &in, "input file"}
    });

    auto map = po::parse_command_line(ac, av, desc);

    if (!map.count("in")) {
        std::cerr << "blah blah\n\n" << desc;
        return 1;
    }

    std::cout << "in: " << in << "\n";

    ...

    return 0;
}

```


# Exceptions

- `program_options::unknow_option`
- `program_options::invalid_option_value`
- `program_options::invalid_command_line_syntax`


# Tests

`$ bjam test_program_options`


# Install libraries

`$ bjam install`

or

`$ bjam install link=static`


This command make two directories: `lib` and `include/program_options`.

Paths configurable with `LIB_PREFIX` and `INCLUDE_PREFIX` variables environment.

`$ LIB_PREFIX=/usr/local/lib INCLUDE_PREFIX=/usr/local/include/program_options bjam install`


# Package

With Wallix packager (https://github.com/wallix/packager).

`$ $PACKAGER_PROJECT/packager.py --version 1.0 --no-entry-changelog`

`$ dpkg-buildpackage -I.git -Ibin -uc -us`
