/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <set>
#include <string>
#include <cctype>
#include <unordered_set>

std::string kYourName = "Phil Huang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> applicants;
  std::ifstream in(filename);
  if (!in.is_open()) {
    return applicants;
  }

  std::string line;
  while (std::getline(in, line)) {
    if (!line.empty()) {
      applicants.insert(line);
    }
  }

  return applicants;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> q;

  // Helper to compute initials from a full name (extract first and last words).
  auto initials = [](const std::string& s) -> std::pair<char,char> {
    std::istringstream iss(s);
    std::string first, word, last;
    if (!(iss >> first)) return {'\0', '\0'};
    last = first;
    while (iss >> word) last = word;
    char a = first.empty() ? '\0' : std::toupper(static_cast<unsigned char>(first[0]));
    char b = last.empty() ? '\0' : std::toupper(static_cast<unsigned char>(last[0]));
    return {a, b};
  };

  auto target = initials(name);

  for (const auto& student : students) {
    if (initials(student) == target) {
      q.push(&student);
    }
  }

  return q;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) return "NO MATCHES FOUND.";

  // Simple deterministic but non-trivial selection: rotate half of the queue
  // then pick the front. This mixes order a bit rather than always picking
  // the first element.
  size_t n = matches.size();
  size_t rotate = n / 2;
  for (size_t i = 0; i < rotate; ++i) {
    const std::string* p = matches.front();
    matches.pop();
    matches.push(p);
  }

  const std::string* chosen = matches.front();
  return chosen ? *chosen : std::string("NO MATCHES FOUND.");
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
