/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH =
    "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;
};

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */
#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(const std::string& filename, std::vector<Course>& courses) {
  std::ifstream file(filename);
  std::string line;
  // Skip header
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::vector<std::string> parts = split(line, ',');
    Course c;
    c.title = parts[0];
    c.number_of_units = parts[1];
    c.quarter = parts[2];
    courses.push_back(c);
  }
}

/**
 * This function has TWO requirements.
 *
 * 1) Write the courses that are offered to the file
 * "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered
 * courses.
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  std::ofstream file(COURSES_OFFERED_PATH);
  file << "Title,Number of Units,Quarter" << std::endl;

  // std::vector<Course> offered_courses;
  for (const auto& course : all_courses) {
    if (course.quarter != "null") {
      file << course.title << "," << course.number_of_units << ","
           << course.quarter << std::endl;
      // offered_courses.push_back(course);
    }
  }
  file.close();

  // Alternative implementation without std::remove_if
  std::vector<Course> courses_to_keep;
  courses_to_keep.reserve(all_courses.size());  // Optional: pre-allocate memory
  for (const auto& course : all_courses) {
    if (course.quarter == "null") {
      courses_to_keep.push_back(course);
    }
  }
  all_courses = courses_to_keep;

  /*
  // Original implementation using std::remove_if
  auto it = std::remove_if(all_courses.begin(), all_courses.end(),
                           [](const Course& course) {
                             return course.quarter != "null";
                           });

  all_courses.erase(it, all_courses.end());
  */
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(const std::vector<Course>& unlisted_courses) {
  std::ofstream file(COURSES_NOT_OFFERED_PATH);
  file << "Title,Number of Units,Quarter" << std::endl;

  for (const auto& course : unlisted_courses) {
    file << course.title << "," << course.number_of_units << ","
         << course.quarter << std::endl;
  }
  file.close();
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>,
                "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}