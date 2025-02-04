#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

std::vector<std::string> split_into_words(const std::string& text) {
  return text | std::views::split(' ') |
         std::views::transform([](auto&& word_range) {
           return std::string(word_range.begin(), word_range.end());
         }) |
         std::ranges::to<std::vector>();
}

void analyze_sentence(size_t index, const std::vector<std::string>& words) {
  const size_t word_count = words.size();

  const double total_word_length = std::ranges::fold_left(
      words, 0.0,
      [](double sum, const std::string& word) { return sum + word.size(); });

  const double avg_word_length =
      word_count > 0 ? total_word_length / word_count : 0.0;
  const auto longest_word = std::ranges::max(words, {}, &std::string::size);

  std::cout << "Sentence " << index + 1 << ": ";
  for (const auto& w : words) std::cout << w << ' ';
  std::cout << "\n  Word count: " << word_count << "\n";
  std::cout << "  Average word length: " << avg_word_length << "\n";
  std::cout << "  Longest word: " << longest_word << "\n";
}

int main() {
  std::string text =
      "This is the first sentence. Here is another one! "
      "And yet another sentence. It is fun to analyze text.";

  auto all_words = split_into_words(text);
  auto sentences = all_words | std::views::chunk_by([](const std::string& a,
                                                       const std::string& b) {
                     return !a.ends_with('.') && !a.ends_with('!');
                   });

  for (const auto& [index, sentence] : std::views::enumerate(sentences)) {
    auto words = sentence | std::ranges::to<std::vector>();
    if (!words.empty() &&
        (words.back().ends_with('.') || words.back().ends_with('!'))) {
      words.back()
          .pop_back();  // Remove the sentence-ending punctuation for analysis
    }
    analyze_sentence(index, words);
  }
}
