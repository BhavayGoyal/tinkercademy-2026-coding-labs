/*
 * Assignment 1: Marriage Pact
 * Adapted by Tinkercademy from Stanford CS106L
 * (originally by Haven Whitney, with modifications by Fabio Ibanez
 * & Jacob Roberts-Baca).
 *
 * Complete each STUDENT TODO below. Read the README carefully — the
 * requirements there (ranges, projections, sample, reserve, no raw
 * for-loops in find_matches, iterator-safe erase in run_mixer) are
 * part of the assignment, not optional polish.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

/**
 * Reads `filename` line by line and returns the applicants.
 *
 * Requirements:
 *   - Take `filename` as `const std::string&`.
 *   - Call `reserve()` before populating, with a sensible capacity.
 *     Justify your choice in short_answer.txt.
 */
std::vector<std::string> get_applicants(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) throw std::runtime_error("Could not open file: " + filename);
  std::vector<std::string> applicants;
  applicants.reserve(1000);
  std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
          line.back() == '\r' ? line.pop_back() : void();
          applicants.push_back(line);
        }
    }
    file.close();
    return applicants;
}

/**
 * Returns the initials of `name`, uppercased.
 *   e.g. initials("Marceline McMillan") == "MM"
 *
 * Requirements:
 *   - Parameter must be `std::string_view` (no allocation).
 */
std::string initials(std::string_view name) {
  std::string res;
  size_t space_pos = name.find(' ');
  if (space_pos == std::string_view::npos) {
    res += std::toupper(name[0]);
  } else {
    res += std::toupper(name[0]);
    if (space_pos + 1 < name.size()) res += std::toupper(name[space_pos + 1]);
  }
  return res;
}

/**
 * Returns every applicant in `students` who shares initials with `name`.
 *
 * Requirements:
 *   - No raw `for` loops. Use std::ranges::copy_if (or views::filter
 *     piped into a vector). Use a projection where it makes the call
 *     clearer.
 *   - Take `students` as `const std::vector<std::string>&`.
 */
std::vector<std::string> find_matches(std::string_view name,
                                      const std::vector<std::string>& students) {
  std::vector<std::string> matches;
  std::string target = initials(name);
  std::ranges::copy_if(students, std::back_inserter(matches), 
      [&target](const std::string& proj) { return proj == target; },
      initials
  );
  return matches;
}

/**
 * Returns one randomly-chosen match, or "NO MATCHES FOUND." if empty.
 *
 * Requirements:
 *   - Use std::sample with a seeded std::mt19937.
 *   - Do NOT use pop_back() or rand() % size.
 */
std::string get_match(const std::vector<std::string>& matches) {
  if (matches.empty()) return "NO MATCHES FOUND.";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::string match;
    std::sample(matches.begin(), matches.end(), &match, 1, gen);
    return match;
}

/**
 * Runs a multi-round mixer. In each round, scan the remaining
 * applicants left-to-right; for each applicant, look for another
 * applicant with the same initials still in the pool. If found,
 * pair them, remove both from `applicants`, and record the pair.
 * Continue rounds until a full pass yields no new pairs.
 *
 * `applicants` is mutated: paired names are removed. Whatever is
 * left over at the end is unpaired.
 *
 * Requirements:
 *   - The naive "iterate and erase as you go" approach WILL invalidate
 *     your iterator. You must handle this — see the README for the
 *     three acceptable strategies — and document your choice in
 *     short_answer.txt.
 */
std::vector<std::pair<std::string, std::string>> run_mixer(std::vector<std::string>& applicants) {
  std::vector<std::pair<std::string, std::string>> pairs;
  while (true) {
    bool found = false;
    for (auto it = applicants.begin(); it != applicants.end(); ) {
      auto match_it = std::find_if(it + 1, applicants.end(),
                [&](const std::string& s) { return initials(s) == initials(*it); });
      if (match_it == applicants.end()) it++;
      else {
        pairs.emplace_back(*it, *match_it);
        applicants.erase(match_it);
        it = applicants.erase(it);
        found = true;
      }
    }
    if (!found) break;
  }
  return pairs;
}

/* #### Please don't remove this line! #### */
#include "tests/utils.hpp"