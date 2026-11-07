#pragma once

#include <pqxx/pqxx>
#include <string>
#include <iostream>

// Retrieve and display all students.
void getAllStudents(pqxx::connection& db);

// Insert a new student into the database.
// Returns the generated student ID, or -1 on failure.
int addStudent(
    pqxx::connection& db,
    const std::string& first_name,
    const std::string& last_name,
    const std::string& email,
    const std::string& enrollment_date
);

// Update a student's email address.
// Returns true if the student was found and updated.
bool updateStudentEmail(
    pqxx::connection& db,
    int student_id,
    const std::string& new_email
);

// Delete a student by ID.
// Returns true if the student was found and deleted.
bool deleteStudent(
    pqxx::connection& db,
    int student_id
);