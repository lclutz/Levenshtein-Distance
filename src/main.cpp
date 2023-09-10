// Calculates the edit distance (through deletions, insertions and substitutions
// of characters) to get from a to b.
size_t levenshteinDistance(std::string_view a, std::string_view b)
{
    std::vector<std::vector<size_t>> table(
        b.size() + 1, std::vector<size_t>(a.size() + 1, 0));

    for (size_t i = 1; i <= a.size(); ++i)
    {
        table[0][i] = i;
    }

    for (size_t i = 1; i <= b.size(); ++i)
    {
        table[i][0] = i;
    }

    for (size_t j = 1; j <= b.size(); ++j)
    {
        for (size_t i = 1; i <= a.size(); ++i)
        {
            size_t substitution_cost = a[i - 1] == b[j - 1] ? 0 : 1;

            table[j][i] = std::min({
                table[j - 1][i] + 1,                     // deletion
                table[j][i - 1] + 1,                     // insertion
                table[j - 1][i - 1] + substitution_cost, // substitution
            });
        }
    }

    return table[b.size()][a.size()];
}

int main()
{
    std::string pattern("kitten");
    std::vector<std::string> words = {"smitten", "mitten", "kitty", "fitting",
                                      "written"};

    std::cout << "Distance to " << pattern << ":" << std::endl;
    for (const auto &word : words)
    {
        std::cout << word << ": " << levenshteinDistance(pattern, word)
                  << std::endl;
    }

    return 0;
}
