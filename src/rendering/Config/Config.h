

namespace Snake::Rendering {

class Config {
public:
  /// @brief Configures the conosole window and encoding
  static void ConfigureConsole();

private:
  /// @brief Sets the console encofing to UTF-8
  static void SetConsoleEncoding();
  /// @brief Sets the console size
  static void SetConsoleSize();
};
} // namespace Snake::Rendering
